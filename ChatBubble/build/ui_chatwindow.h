/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "chatbubble.h"

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    BubbleList *widgetChat;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QCheckBox *checkBox;
    QPushButton *pushButton_3;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout;
    QTextEdit *textEditSnd;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QWidget *widget_4;

    void setupUi(QWidget *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QStringLiteral("ChatWindow"));
        ChatWindow->resize(608, 498);
        verticalLayout_3 = new QVBoxLayout(ChatWindow);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter = new QSplitter(ChatWindow);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetChat = new BubbleList(layoutWidget);
        widgetChat->setObjectName(QStringLiteral("widgetChat"));

        verticalLayout_2->addWidget(widgetChat);

        widget_2 = new QWidget(layoutWidget);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        checkBox = new QCheckBox(widget_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        horizontalLayout_2->addWidget(checkBox);

        pushButton_3 = new QPushButton(widget_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setCheckable(false);

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout_2->addWidget(widget_2);

        widget_3 = new QWidget(layoutWidget);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        verticalLayout = new QVBoxLayout(widget_3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textEditSnd = new QTextEdit(widget_3);
        textEditSnd->setObjectName(QStringLiteral("textEditSnd"));

        verticalLayout->addWidget(textEditSnd);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_5 = new QPushButton(widget_3);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        horizontalLayout->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(widget_3);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        horizontalLayout->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addWidget(widget_3);

        verticalLayout_2->setStretch(0, 3);
        verticalLayout_2->setStretch(2, 1);
        splitter->addWidget(layoutWidget);
        widget_4 = new QWidget(splitter);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        splitter->addWidget(widget_4);

        verticalLayout_3->addWidget(splitter);


        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QWidget *ChatWindow)
    {
        ChatWindow->setWindowTitle(QApplication::translate("ChatWindow", "Chat\350\201\212\345\244\251\344\276\213\345\255\220", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ChatWindow", "\350\256\276\347\275\256\351\242\234\350\211\262", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ChatWindow", "\350\256\276\347\275\256\345\255\227\344\275\223", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ChatWindow", "\350\201\212\345\244\251\350\203\214\346\231\257", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("ChatWindow", "\346\270\205\347\251\272", Q_NULLPTR));
        textEditSnd->setHtml(QApplication::translate("ChatWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#55ffff;\">\344\273\212\345\244\251\345\244\251\346\260\224\345\276\210\344\270\215\351\224\231\357\274\201~</span></p></body></html>", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("ChatWindow", "\351\200\200\345\207\272", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("ChatWindow", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
