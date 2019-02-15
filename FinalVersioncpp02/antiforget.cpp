#include "antiforget.h"
#include "ui_antiforget.h"


Widget2::Widget2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::widget)
{
    ui->setupUi(this);
    this->setStyleSheet("background-image:url(:/image/6.jpg);");
    ui->textEdit->setStyleSheet("border-image:url(:/image/6.jpg);");
    ui->dateEdit->setStyleSheet("border-image:url(:/image/6.jpg);");
    ui->themeEdit->setStyleSheet("border-image:url(:/image/6.jpg);");
    QObject::connect(ui->calendarButton,SIGNAL(clicked()),this,SLOT(showcalendar()));
    QObject::connect(ui->saveButton,SIGNAL(clicked()),this,SLOT(onsave()));
}

Widget2::~Widget2()
{
    delete ui;
}

//在lineedit中显示所选择的日期
void Widget2::showcalendar()
{
    QDate date=ui->calendarWidget->selectedDate();
    QString datestr=date.toString("yyyy-MM-dd"); //设置输出格式
    //ui->calendarWidget=new QCalendarWidget(this);

    //QDate date=ui->calendarWidget->selectedDate();
    //QString datestr=date.toString("yyyy/MM/dd"); //设置输出格式
    //QString datestr=("123");
    /*ui->calendarWidget->setLocale(QLocale(QLocale::Chinese,QLocale::China));
    ui->calendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    ui->calendarWidget->setSelectionMode(QCalendarWidget::SingleSelection);
    ui->calendarWidget->setFirstDayOfWeek(Qt::Sunday);
    QTextCharFormat weekdays;
    weekdays.setBackground(QColor(255,255,255));
    ui->calendarWidget->setWeekdayTextFormat(Qt::Saturday,weekdays);
    ui->calendarWidget->setWeekdayTextFormat(Qt::Sunday,weekdays);
    ui->calendarWidget->setGridVisible(true);*/
    //ui->lineEdit->setText(datestr);
    ui->dateEdit->setText(datestr);
    QString filename="date/"+datestr+".txt";
    QFile file( filename );
    if ( file.exists())
    {
//        QFile *file1=new QFile( filename );  //file.setFileName( "xx.txt" );
//        file1->open(QIODevice::ReadOnly|QIODevice::Text);
//        //QString line = QString(file1->readLine());
//        char *line1;
//        line1 = file1->readLine().data();
//        ui->textEdit->setText(line1);
//        while(!file1.atEnd()){
//            line1 = file1->readLine().data();

//            ui->textEdit->setText(line1);
//        }
////         char *line2 = file1->readAll().data();

////        ui->textEdit->setText(line2);
//        file1->close(); QString line;
        QTextCodec *code=QTextCodec::codecForName("UTF-8");//本人采用的是UTF8格式显示的
        //QFile file("/file.txt");
        file.open(QIODevice::ReadOnly);
        QTextStream stream(&file);
        stream.setCodec(code);//输出流的设置--------必须嘀
        ui->themeEdit->setText(stream.readLine());
        while(stream.atEnd()==0)
        {
           ui->textEdit ->append(stream.readLine());
        }
        return;
    }
}


//保存所填备忘内容
void Widget2::onsave()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QString str1=ui->dateEdit->text();
    QString str2=ui->themeEdit->text();
    //QString str3;
    if(str1==NULL){
        QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("备忘日期不能为空，请选择日期！"));
        return;
    }
    else if(str2==NULL){
        QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("备忘主题不能为空，请填写主题！"));
        return;
    }
    else {
        //QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("已备忘，请勿多次点击！"));
        QString filename="date/"+str1+".txt";
        QFile file( filename );  //file.setFileName( "xx.txt" );
        if ( file.exists())
        {
              QMessageBox::warning(NULL, QString::fromLocal8Bit("警告"), QString::fromLocal8Bit("已备忘，请勿多次点击！"));
              //return;
        }
        file.open( QIODevice::ReadWrite );
        QTextStream in(&file); //这两句是在往里面写内容，不用这两句，也可以
        in<<str2<<"\r\n";
        QTextDocument* textDocument = ui->textEdit->document();

        QTextBlock textBlock ; // lineNumber就是你要指定的第几行
        QString str3 = textBlock.text(); //这里的readString就是你想要的
        for(int i=0;i<textDocument->lineCount();i++){
            textBlock = textDocument->findBlockByLineNumber(i);
            str3 = textBlock.text();
            in<<str3<<"\r\n";
        }

        file.close();
        return ;
    }

}
//清除所填内容
void Widget2::on_cancelButton_clicked()
{
    ui->dateEdit->setText(NULL);
    ui->textEdit->setText(NULL);
    ui->themeEdit->setText(NULL);
    return;
}
