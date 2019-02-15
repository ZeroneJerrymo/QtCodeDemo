/**
 * qrencode - QR Code encoder
 *
 * QR Code encoding tool
 * Copyright (C) 2006-2013 Kentaro Fukuchi <kentaro@fukuchi.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#include "qrencode.h"

#define INCHES_PER_METER (100.0/2.54)
#if defined(_MSC_VER)
#define strcasecmp _stricmp
#endif

static int casesensitive = 1;
static int eightbit = 0;
static int version = 0;
//size表示生成图片大小，默认是3；margin表示二维码周围边框空白区域间距值；
static int size = 3;
static int margin = -1;
static int dpi = 72;
static int structured = 0;
static int rle = 0;
static int micro = 0;
//level表示容错率，也就是有被覆盖的区域还能识别，分别是 L（QR_ECLEVEL_L，7%），M（QR_ECLEVEL_M，15%），Q（QR_ECLEVEL_Q，25%），H（QR_ECLEVEL_H，30%）；
//static QRecLevel level = QR_ECLEVEL_L;
static QRecLevel level = QR_ECLEVEL_M;
static QRencodeMode hint = QR_MODE_8;
static unsigned int fg_color[4] = {0, 0, 0, 255};
static unsigned int bg_color[4] = {255, 255, 255, 255};

static int verbose = 0;

enum imageType {
    PNG_TYPE,
    EPS_TYPE,
    SVG_TYPE,
    ANSI_TYPE,
    ANSI256_TYPE,
    ASCII_TYPE,
    ASCIIi_TYPE,
    UTF8_TYPE,
    ANSIUTF8_TYPE
};

static enum imageType image_type = PNG_TYPE;

static int color_set(unsigned int color[4], const char *value)
{
    int len = strlen(value);
    int count;
    if(len == 6) {
        count = sscanf(value, "%02x%02x%02x%n", &color[0], &color[1], &color[2], &len);
        if(count < 3 || len != 6) {
            return -1;
        }
        color[3] = 255;
    } else if(len == 8) {
        count = sscanf(value, "%02x%02x%02x%02x%n", &color[0], &color[1], &color[2], &color[3], &len);
        if(count < 4 || len != 8) {
            return -1;
        }
    } else {
        return -1;
    }
    return 0;
}

#define MAX_DATA_SIZE (7090 * 16) /* from the specification */
static unsigned char *readStdin(int *length)
{
    unsigned char *buffer;
    int ret;

    buffer = (unsigned char *)malloc(MAX_DATA_SIZE + 1);
    if(buffer == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    ret = fread(buffer, 1, MAX_DATA_SIZE, stdin);
    if(ret == 0) {
        fprintf(stderr, "No input data.\n");
        exit(EXIT_FAILURE);
    }
    if(feof(stdin) == 0) {
        fprintf(stderr, "Input data is too large.\n");
        exit(EXIT_FAILURE);
    }

    buffer[ret] = '\0';
    *length = ret;

    return buffer;
}

static FILE *openFile(const char *outfile)
{
    FILE *fp;

    if(outfile == NULL || (outfile[0] == '-' && outfile[1] == '\0')) {
        fp = stdout;
    } else {
        fp = fopen(outfile, "wb");
        if(fp == NULL) {
            fprintf(stderr, "Failed to create file: %s\n", outfile);
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }

    return fp;
}

static int writePNG(QRcode *qrcode, const char *outfile)
{
    static FILE *fp; // avoid clobbering by setjmp.
    png_structp png_ptr;
    png_infop info_ptr;
    png_colorp palette;
    png_byte alpha_values[2];
    unsigned char *row, *p, *q;
    int x, y, xx, yy, bit;
    int realwidth;

    realwidth = (qrcode->width + margin * 2) * size;
    row = (unsigned char *)malloc((realwidth + 7) / 8);
    if(row == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    if(outfile[0] == '-' && outfile[1] == '\0') {
        fp = stdout;
    } else {
        fp = fopen(outfile, "wb");
        if(fp == NULL) {
            fprintf(stderr, "Failed to create file: %s\n", outfile);
            perror(NULL);
            exit(EXIT_FAILURE);
        }
    }

    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL) {
        fprintf(stderr, "Failed to initialize PNG writer.\n");
        exit(EXIT_FAILURE);
    }

    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL) {
        fprintf(stderr, "Failed to initialize PNG write.\n");
        exit(EXIT_FAILURE);
    }

    if(setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fprintf(stderr, "Failed to write PNG image.\n");
        exit(EXIT_FAILURE);
    }

    palette = (png_colorp) malloc(sizeof(png_color) * 2);
    if(palette == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    palette[0].red   = fg_color[0];
    palette[0].green = fg_color[1];
    palette[0].blue  = fg_color[2];
    palette[1].red   = bg_color[0];
    palette[1].green = bg_color[1];
    palette[1].blue  = bg_color[2];
    alpha_values[0] = fg_color[3];
    alpha_values[1] = bg_color[3];
    png_set_PLTE(png_ptr, info_ptr, palette, 2);
    png_set_tRNS(png_ptr, info_ptr, alpha_values, 2, NULL);

    png_init_io(png_ptr, fp);
    png_set_IHDR(png_ptr, info_ptr,
            realwidth, realwidth,
            1,
            PNG_COLOR_TYPE_PALETTE,
            PNG_INTERLACE_NONE,
            PNG_COMPRESSION_TYPE_DEFAULT,
            PNG_FILTER_TYPE_DEFAULT);
    png_set_pHYs(png_ptr, info_ptr,
            dpi * INCHES_PER_METER,
            dpi * INCHES_PER_METER,
            PNG_RESOLUTION_METER);
    png_write_info(png_ptr, info_ptr);

    /* top margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }

    /* data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        bit = 7;
        memset(row, 0xff, (realwidth + 7) / 8);
        q = row;
        q += margin * size / 8;
        bit = 7 - (margin * size % 8);
        for(x=0; x<qrcode->width; x++) {
            for(xx=0; xx<size; xx++) {
                *q ^= (*p & 1) << bit;
                bit--;
                if(bit < 0) {
                    q++;
                    bit = 7;
                }
            }
            p++;
        }
        for(yy=0; yy<size; yy++) {
            png_write_row(png_ptr, row);
        }
    }
    /* bottom margin */
    memset(row, 0xff, (realwidth + 7) / 8);
    for(y=0; y<margin * size; y++) {
        png_write_row(png_ptr, row);
    }

    png_write_end(png_ptr, info_ptr);
    png_destroy_write_struct(&png_ptr, &info_ptr);

    fclose(fp);
    free(row);
    free(palette);

    return 0;
}

static int writeEPS(QRcode *qrcode, const char *outfile)
{
    FILE *fp;
    unsigned char *row, *p;
    int x, y, yy;
    int realwidth;

    fp = openFile(outfile);

    realwidth = (qrcode->width + margin * 2) * size;
    /* EPS file header */
    fprintf(fp, "%%!PS-Adobe-2.0 EPSF-1.2\n"
                "%%%%BoundingBox: 0 0 %d %d\n"
                "%%%%Pages: 1 1\n"
                "%%%%EndComments\n", realwidth, realwidth);
    /* draw point */
    fprintf(fp, "/p { "
                "moveto "
                "0 1 rlineto "
                "1 0 rlineto "
                "0 -1 rlineto "
                "fill "
                "} bind def "
                "%d %d scale ", size, size);

    /* data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        row = (p+(y*qrcode->width));
        yy = (margin + qrcode->width - y - 1);

        for(x=0; x<qrcode->width; x++) {
            if(*(row+x)&0x1) {
                fprintf(fp, "%d %d p ", margin + x,  yy);
            }
        }
    }

    fprintf(fp, "\n%%%%EOF\n");
    fclose(fp);

    return 0;
}

static void writeSVG_writeRect(FILE *fp, int x, int y, int width, char* col, float opacity)
{
    if(fg_color[3] != 255) {
        fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
                "fill=\"#%s\" fill-opacity=\"%f\" />\n",
                x, y, width, col, opacity );
    } else {
        fprintf(fp, "\t\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"1\" "\
                "fill=\"#%s\" />\n",
                x, y, width, col );
    }
}

static int writeSVG( QRcode *qrcode, const char *outfile )
{
    FILE *fp;
    unsigned char *row, *p;
    int x, y, x0, pen;
    int symwidth, realwidth;
    float scale;
    char fg[7], bg[7];
    float fg_opacity;
    float bg_opacity;

    fp = openFile(outfile);

    scale = dpi * INCHES_PER_METER / 100.0;

    symwidth = qrcode->width + margin * 2;
    realwidth = symwidth * size;

    snprintf(fg, 7, "%02x%02x%02x", fg_color[0], fg_color[1],  fg_color[2]);
    snprintf(bg, 7, "%02x%02x%02x", bg_color[0], bg_color[1],  bg_color[2]);
    fg_opacity = (float)fg_color[3] / 255;
    bg_opacity = (float)bg_color[3] / 255;

    /* XML declaration */
    fputs( "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n", fp );

    /* DTD
       No document type specified because "while a DTD is provided in [the SVG]
       specification, the use of DTDs for validating XML documents is known to be
       problematic. In particular, DTDs do not handle namespaces gracefully. It
       is *not* recommended that a DOCTYPE declaration be included in SVG
       documents."
       http://www.w3.org/TR/2003/REC-SVG11-20030114/intro.html#Namespace
    */

    /* Vanity remark */
    fprintf( fp, "<!-- Created with qrencode %s (http://fukuchi.org/works/qrencode/index.html.en) -->\n",
            QRcode_APIVersionString() );

    /* SVG code start */
    fprintf( fp, "<svg width=\"%0.2fcm\" height=\"%0.2fcm\" viewBox=\"0 0 %d %d\""\
            " preserveAspectRatio=\"none\" version=\"1.1\""\
            " xmlns=\"http://www.w3.org/2000/svg\">\n",
            realwidth / scale, realwidth / scale, symwidth, symwidth
           );

    /* Make named group */
    fputs( "\t<g id=\"QRcode\">\n", fp );

    /* Make solid background */
    if(bg_color[3] != 255) {
        fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" fill-opacity=\"%f\" />\n", symwidth, symwidth, bg, bg_opacity);
    } else {
        fprintf(fp, "\t\t<rect x=\"0\" y=\"0\" width=\"%d\" height=\"%d\" fill=\"#%s\" />\n", symwidth, symwidth, bg);
    }

    /* Create new viewbox for QR data */
    fputs( "\t\t<g id=\"Pattern\">\n", fp);

    /* Write data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        row = (p+(y*qrcode->width));

        if( !rle ) {
            /* no RLE */
            for(x=0; x<qrcode->width; x++) {
                if(*(row+x)&0x1) {
                    writeSVG_writeRect(fp,	margin + x,
                                margin + y, 1,
                                fg, fg_opacity);
                }
            }
        } else {
            /* simple RLE */
            pen = 0;
            x0  = 0;
            for(x=0; x<qrcode->width; x++) {
                if( !pen ) {
                    pen = *(row+x)&0x1;
                    x0 = x;
                } else {
                    if(!(*(row+x)&0x1)) {
                        writeSVG_writeRect(fp, x0 + margin, y + margin, x-x0, fg, fg_opacity);
                        pen = 0;
                    }
                }
            }
            if( pen ) {
                writeSVG_writeRect(fp, x0 + margin, y + margin, qrcode->width - x0, fg, fg_opacity);
            }
        }
    }
    /* Close QR data viewbox */
    fputs( "\t\t</g>\n", fp );

    /* Close group */
    fputs( "\t</g>\n", fp );

    /* Close SVG code */
    fputs( "</svg>\n", fp );
    fclose( fp );

    return 0;
}

static void writeANSI_margin(FILE* fp, int realwidth,
                             char* buffer, int buffer_s,
                             char* white, int white_s )
{
    int y;

    strncpy(buffer, white, white_s);
    memset(buffer + white_s, ' ', realwidth * 2);
    strcpy(buffer + white_s + realwidth * 2, "\033[0m\n"); // reset to default colors
    for(y=0; y<margin; y++ ){
        fputs(buffer, fp);
    }
}

static int writeANSI(QRcode *qrcode, const char *outfile)
{
    FILE *fp;
    unsigned char *row, *p;
    int x, y;
    int realwidth;
    int last;

    char white[30], black[30], *buffer;
    int white_s, black_s, buffer_s;

    if( image_type == ANSI256_TYPE ){
        /* codes for 256 color compatible terminals */
//                white = "\033[48;5;231m";
        sprintf_s(white,sizeof(white),"%s","\033[48;5;231m");
        white_s = 11;
        //        black = "\033[48;5;16m";
        sprintf_s(black,sizeof(black),"%s","\033[48;5;16m");
        black_s = 10;
    } else {
        //        white = "\033[47m";
        sprintf_s(white,sizeof(white),"%s","\033[47m");
        white_s = 5;
        //        black = "\033[40m";
        sprintf_s(black,sizeof(black),"%s","\033[40m");
        black_s = 5;
    }

    size = 1;

    fp = openFile(outfile);

    realwidth = (qrcode->width + margin * 2) * size;
    buffer_s = ( realwidth * white_s ) * 2;
    buffer = (char *)malloc( buffer_s );
    if(buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    /* top margin */
    writeANSI_margin(fp, realwidth, buffer, buffer_s, white, white_s);

    /* data */
    p = qrcode->data;
    for(y=0; y<qrcode->width; y++) {
        row = (p+(y*qrcode->width));

//		bzero( buffer, buffer_s );
        memset(buffer,0,buffer_s);
        strncpy( buffer, white, white_s );
        for(x=0; x<margin; x++ ){
            strncat( buffer, "  ", 2 );
        }
        last = 0;

        for(x=0; x<qrcode->width; x++) {
            if(*(row+x)&0x1) {
                if( last != 1 ){
                    strncat( buffer, black, black_s );
                    last = 1;
                }
            } else {
                if( last != 0 ){
                    strncat( buffer, white, white_s );
                    last = 0;
                }
            }
            strncat( buffer, "  ", 2 );
        }

        if( last != 0 ){
            strncat( buffer, white, white_s );
        }
        for(x=0; x<margin; x++ ){
            strncat( buffer, "  ", 2 );
        }
        strncat( buffer, "\033[0m\n", 5 );
        fputs( buffer, fp );
    }

    /* bottom margin */
    writeANSI_margin(fp, realwidth, buffer, buffer_s, white, white_s);

    fclose(fp);
    free(buffer);

    return 0;
}

static void writeUTF8_margin(FILE* fp, int realwidth,
                 const char* white, const char *reset,
                 int use_ansi)
{
    int x, y;

    for (y = 0; y < margin/2; y++) {
        fputs(white, fp);
        for (x = 0; x < realwidth; x++)
            fputs("\342\226\210", fp);
        fputs(reset, fp);
        fputc('\n', fp);
    }
}

static int writeUTF8(QRcode *qrcode, const char *outfile, int use_ansi)
{
    FILE *fp;
    int x, y;
    int realwidth;
    const char *white, *reset;

    if (use_ansi){
        white = "\033[40;37;1m";
        reset = "\033[0m";
    } else {
        white = "";
        reset = "";
    }

    fp = openFile(outfile);

    realwidth = (qrcode->width + margin * 2);

    /* top margin */
    writeUTF8_margin(fp, realwidth, white, reset, use_ansi);

    /* data */
    for(y = 0; y < qrcode->width; y += 2) {
        unsigned char *row1, *row2;
        row1 = qrcode->data + y*qrcode->width;
        row2 = row1 + qrcode->width;

        fputs(white, fp);

        for (x = 0; x < margin; x++)
            fputs("\342\226\210", fp);

        for (x = 0; x < qrcode->width; x++) {
            if(row1[x] & 1) {
                if(y < qrcode->width - 1 && row2[x] & 1) {
                    fputc(' ', fp);
                } else {
                    fputs("\342\226\204", fp);
                }
            } else {
                if(y < qrcode->width - 1 && row2[x] & 1) {
                    fputs("\342\226\200", fp);
                } else {
                    fputs("\342\226\210", fp);
                }
            }
        }

        for (x = 0; x < margin; x++)
            fputs("\342\226\210", fp);

        fputs(reset, fp);
        fputc('\n', fp);
    }

    /* bottom margin */
    writeUTF8_margin(fp, realwidth, white, reset, use_ansi);

    fclose(fp);

    return 0;
}

static void writeASCII_margin(FILE* fp, int realwidth, char* buffer, int buffer_s, int invert)
{
    int y, h;

    h = margin;

    memset(buffer, (invert?'#':' '), realwidth);
    buffer[realwidth] = '\n';
    buffer[realwidth + 1] = '\0';
    for(y=0; y<h; y++ ){
        fputs(buffer, fp);
    }
}

static int writeASCII(QRcode *qrcode, const char *outfile, int invert)
{
    FILE *fp;
    unsigned char *row;
    int x, y;
    int realwidth;
    char *buffer, *p;
    int buffer_s;
    char black = '#';
    char white = ' ';

    if(invert) {
        black = ' ';
        white = '#';
    }

    size = 1;

    fp = openFile(outfile);

    realwidth = (qrcode->width + margin * 2) * 2;
    buffer_s = realwidth + 2;
    buffer = (char *)malloc( buffer_s );
    if(buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    /* top margin */
    writeASCII_margin(fp, realwidth, buffer, buffer_s, invert);

    /* data */
    for(y=0; y<qrcode->width; y++) {
        row = qrcode->data+(y*qrcode->width);
        p = buffer;

        memset(p, white, margin * 2);
        p += margin * 2;

        for(x=0; x<qrcode->width; x++) {
            if(row[x]&0x1) {
                *p++ = black;
                *p++ = black;
            } else {
                *p++ = white;
                *p++ = white;
            }
        }

        memset(p, white, margin * 2);
        p += margin * 2;
        *p++ = '\n';
        *p++ = '\0';
        fputs( buffer, fp );
    }

    /* bottom margin */
    writeASCII_margin(fp, realwidth, buffer, buffer_s, invert);

    fclose(fp);
    free(buffer);

    return 0;
}

static QRcode *encode(const unsigned char *intext, int length)
{
    QRcode *code;

    if(micro) {
        if(eightbit) {
            code = QRcode_encodeDataMQR(length, intext, version, level);
        } else {
            code = QRcode_encodeStringMQR((char *)intext, version, level, hint, casesensitive);
        }
    } else {
        if(eightbit) {
            code = QRcode_encodeData(length, intext, version, level);
        } else {
            code = QRcode_encodeString((char *)intext, version, level, hint, casesensitive);
        }
    }

    return code;
}

static void qrencode(const unsigned char *intext, int length, const char *outfile)
{
    QRcode *qrcode;

    qrcode = encode(intext, length);
    if(qrcode == NULL) {
        perror("Failed to encode the input data");
        exit(EXIT_FAILURE);
    }

    if(verbose) {
        fprintf(stderr, "File: %s, Version: %d\n", (outfile!=NULL)?outfile:"(stdout)", qrcode->version);
    }

    switch(image_type) {
        case PNG_TYPE:
            writePNG(qrcode, outfile);
            break;
        case EPS_TYPE:
            writeEPS(qrcode, outfile);
            break;
        case SVG_TYPE:
            writeSVG(qrcode, outfile);
            break;
        case ANSI_TYPE:
        case ANSI256_TYPE:
            writeANSI(qrcode, outfile);
            break;
        case ASCIIi_TYPE:
            writeASCII(qrcode, outfile,  1);
            break;
        case ASCII_TYPE:
            writeASCII(qrcode, outfile,  0);
            break;
        case UTF8_TYPE:
            writeUTF8(qrcode, outfile, 0);
            break;
        case ANSIUTF8_TYPE:
            writeUTF8(qrcode, outfile, 1);
            break;
        default:
            fprintf(stderr, "Unknown image type.\n");
            exit(EXIT_FAILURE);
    }

    QRcode_free(qrcode);
}

static QRcode_List *encodeStructured(const unsigned char *intext, int length)
{
    QRcode_List *list;

    if(eightbit) {
        list = QRcode_encodeDataStructured(length, intext, version, level);
    } else {
        list = QRcode_encodeStringStructured((char *)intext, version, level, hint, casesensitive);
    }

    return list;
}

static void qrencodeStructured(const unsigned char *intext, int length, const char *outfile)
{
    QRcode_List *qrlist, *p;
    char filename[FILENAME_MAX];
    char *base, *q, *suffix = NULL;
    const char *type_suffix;
    int i = 1;
    size_t suffix_size;

    switch(image_type) {
        case PNG_TYPE:
            type_suffix = ".png";
            break;
        case EPS_TYPE:
            type_suffix = ".eps";
            break;
        case SVG_TYPE:
            type_suffix = ".svg";
            break;
        case ANSI_TYPE:
        case ANSI256_TYPE:
        case ASCII_TYPE:
        case UTF8_TYPE:
        case ANSIUTF8_TYPE:
            type_suffix = ".txt";
            break;
        default:
            fprintf(stderr, "Unknown image type.\n");
            exit(EXIT_FAILURE);
    }

    if(outfile == NULL) {
        fprintf(stderr, "An output filename must be specified to store the structured images.\n");
        exit(EXIT_FAILURE);
    }
    base = strdup(outfile);
    if(base == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    suffix_size = strlen(type_suffix);
    if(strlen(base) > suffix_size) {
        q = base + strlen(base) - suffix_size;
        if(strcasecmp(type_suffix, q) == 0) {
            suffix = strdup(q);
            *q = '\0';
        }
    }

    qrlist = encodeStructured(intext, length);
    if(qrlist == NULL) {
        perror("Failed to encode the input data");
        exit(EXIT_FAILURE);
    }

    for(p = qrlist; p != NULL; p = p->next) {
        if(p->code == NULL) {
            fprintf(stderr, "Failed to encode the input data.\n");
            exit(EXIT_FAILURE);
        }
        if(suffix) {
            snprintf(filename, FILENAME_MAX, "%s-%02d%s", base, i, suffix);
        } else {
            snprintf(filename, FILENAME_MAX, "%s-%02d", base, i);
        }

        if(verbose) {
            fprintf(stderr, "File: %s, Version: %d\n", filename, p->code->version);
        }

        switch(image_type) {
            case PNG_TYPE:
                writePNG(p->code, filename);
                break;
            case EPS_TYPE:
                writeEPS(p->code, filename);
                break;
            case SVG_TYPE:
                writeSVG(p->code, filename);
                break;
            case ANSI_TYPE:
            case ANSI256_TYPE:
                writeANSI(p->code, filename);
                break;
            case ASCIIi_TYPE:
                writeASCII(p->code, filename, 1);
                break;
            case ASCII_TYPE:
                writeASCII(p->code, filename, 0);
                break;
            case UTF8_TYPE:
                writeUTF8(p->code, filename, 0);
                break;
            case ANSIUTF8_TYPE:
                writeUTF8(p->code, filename, 0);
                break;

            default:
                fprintf(stderr, "Unknown image type.\n");
                exit(EXIT_FAILURE);
        }
        i++;
    }

    free(base);
    if(suffix) {
        free(suffix);
    }

    QRcode_List_free(qrlist);
}
