/********************************************************************************
** Form generated from reading UI file 'qrcode.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QRCODE_H
#define UI_QRCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>
#include "qimageviewer.h"

QT_BEGIN_NAMESPACE

class Ui_QRCode
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QLabel *label_2;
    QImageViewer *imageWidget;
    QImageViewer *logowidget;
    QRadioButton *radioButton;

    void setupUi(QWidget *QRCode)
    {
        if (QRCode->objectName().isEmpty())
            QRCode->setObjectName(QStringLiteral("QRCode"));
        QRCode->resize(448, 310);
        label = new QLabel(QRCode);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(11, 9, 96, 16));
        lineEdit = new QLineEdit(QRCode);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(113, 10, 241, 20));
        pushButton = new QPushButton(QRCode);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(360, 10, 75, 23));
        groupBox = new QGroupBox(QRCode);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 421, 241));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"     border: 1px solid gray;\n"
"     border-radius: 5px;\n"
"     margin-top: 1ex; \n"
" }\n"
"\n"
" QGroupBox::title {\n"
"     color:green;\n"
"     subcontrol-origin: margin;\n"
"     subcontrol-position: top center; \n"
"     padding: 0 3px;\n"
" }"));
        groupBox->setFlat(false);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 81, 21));
        imageWidget = new QImageViewer(groupBox);
        imageWidget->setObjectName(QStringLiteral("imageWidget"));
        imageWidget->setGeometry(QRect(180, 20, 201, 201));
        logowidget = new QImageViewer(imageWidget);
        logowidget->setObjectName(QStringLiteral("logowidget"));
        logowidget->setGeometry(QRect(80, 70, 51, 51));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(60, 130, 89, 16));

        retranslateUi(QRCode);

        QMetaObject::connectSlotsByName(QRCode);
    } // setupUi

    void retranslateUi(QWidget *QRCode)
    {
        QRCode->setWindowTitle(QApplication::translate("QRCode", "QRCode", 0));
        label->setText(QApplication::translate("QRCode", "\350\276\223\345\205\245\344\272\214\347\273\264\347\240\201\344\277\241\346\201\257\357\274\232", 0));
        lineEdit->setText(QApplication::translate("QRCode", "\344\272\214\347\273\264\347\240\201\346\265\213\350\257\225--Hello World\357\274\201", 0));
        pushButton->setText(QApplication::translate("QRCode", "\347\224\237\346\210\220", 0));
        groupBox->setTitle(QApplication::translate("QRCode", "\344\272\214\347\273\264\347\240\201", 0));
        label_2->setText(QApplication::translate("QRCode", "\344\272\214\347\273\264\347\240\201\345\233\276\347\211\207\357\274\232", 0));
        radioButton->setText(QApplication::translate("QRCode", "\346\267\273\345\212\240Logo", 0));
    } // retranslateUi

};

namespace Ui {
    class QRCode: public Ui_QRCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QRCODE_H
