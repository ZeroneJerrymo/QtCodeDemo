/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Tue Jul 14 16:24:04 2015
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include<QAction>
#include<QApplication>
#include<QButtonGroup>
#include<QDialog>
#include<QHBoxLayout>
#include<QHeaderView>
#include<QLineEdit>
#include<QToolButton>
#include<QWidget>

QT_BEGIN_NAMESPACE

class Ui_widget
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *settings;
    QToolButton *gameCenter;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_2;
    QToolButton *toolButton;
    QToolButton *toolButton_4;
    QLineEdit *lineEdit;
    QWidget *widget_2;

    void setupUi(QDialog *widget)
    {
        if (widget->objectName().isEmpty())
            widget->setObjectName(QString::fromUtf8("widget"));
        widget->resize(333, 493);
        horizontalLayoutWidget = new QWidget(widget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(0, 439, 341, 58));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        settings = new QToolButton(horizontalLayoutWidget);
        settings->setObjectName(QString::fromUtf8("settings"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("resource/images/imageForIcon/4.png"), QSize(), QIcon::Normal, QIcon::Off);
        settings->setIcon(icon);
        settings->setIconSize(QSize(40, 40));
        settings->setAutoRaise(true);

        horizontalLayout->addWidget(settings);

        gameCenter = new QToolButton(horizontalLayoutWidget);
        gameCenter->setObjectName(QString::fromUtf8("gameCenter"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("resource/images/imageForIcon/5.png"), QSize(), QIcon::Normal, QIcon::Off);
        gameCenter->setIcon(icon1);
        gameCenter->setIconSize(QSize(50, 50));
        gameCenter->setAutoRaise(true);

        horizontalLayout->addWidget(gameCenter);

        horizontalLayoutWidget_2 = new QWidget(widget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(-1, 130, 341, 48));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        toolButton_3 = new QToolButton(horizontalLayoutWidget_2);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("resource/images/imageForIcon/1.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon2);
        toolButton_3->setIconSize(QSize(40, 40));
        toolButton_3->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_3);

        toolButton_2 = new QToolButton(horizontalLayoutWidget_2);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("resource/images/imageForIcon/2.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon3);
        toolButton_2->setIconSize(QSize(40, 40));
        toolButton_2->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton_2);

        toolButton = new QToolButton(horizontalLayoutWidget_2);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("resource/images/imageForIcon/3.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon4);
        toolButton->setIconSize(QSize(40, 40));
        toolButton->setAutoRaise(true);

        horizontalLayout_2->addWidget(toolButton);

        toolButton_4 = new QToolButton(widget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setGeometry(QRect(10, 20, 111, 111));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("resource/images/personalHead/1.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon5);
        toolButton_4->setIconSize(QSize(110, 110));
        toolButton_4->setAutoRaise(true);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setGeometry(QRect(149, 39, 113, 20));
        lineEdit->setReadOnly(false);
        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 180, 331, 261));

        retranslateUi(widget);

        QMetaObject::connectSlotsByName(widget);
    } // setupUi

    void retranslateUi(QDialog *widget)
    {
        widget->setWindowTitle(QApplication::translate("widget", "ChatSimulation", 0));
        settings->setText(QApplication::translate("widget", "\350\256\276\347\275\256", 0));
        gameCenter->setText(QApplication::translate("widget", "\345\272\224\347\224\250\344\270\255\345\277\203", 0));
        toolButton_3->setText(QApplication::translate("widget", "\345\245\275\345\217\213", 0));
        toolButton_2->setText(QApplication::translate("widget", "\347\276\244", 0));
        toolButton->setText(QApplication::translate("widget", "\346\234\200\350\277\221\350\201\224\347\263\273\344\272\272", 0));
        toolButton_4->setText(QApplication::translate("widget", "...", 0));
        lineEdit->setText(QApplication::translate("widget", "wood", 0));
    } // retranslateUi

};

namespace Ui {
    class widget: public Ui_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
