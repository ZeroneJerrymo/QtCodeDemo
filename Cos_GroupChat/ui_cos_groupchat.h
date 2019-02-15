/********************************************************************************
** Form generated from reading UI file 'cos_groupchat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COS_GROUPCHAT_H
#define UI_COS_GROUPCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cos_GroupChat
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QWidget *m_title;
    QHBoxLayout *horizontalLayout;
    QLabel *m_label_title;
    QSpacerItem *horizontalSpacer;
    QPushButton *m_Btn_close;
    QFrame *m_pframe;
    QFrame *line;
    QTextEdit *m_textEdit_send;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *m_Btn_Send;

    void setupUi(QWidget *Cos_GroupChat)
    {
        if (Cos_GroupChat->objectName().isEmpty())
            Cos_GroupChat->setObjectName(QStringLiteral("Cos_GroupChat"));
        Cos_GroupChat->resize(448, 545);
        Cos_GroupChat->setStyleSheet(QString::fromUtf8("#m_title{\n"
"	background-color: rgb(233,233,235);\n"
"}\n"
"#Cos_GroupChat{\n"
"	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"#m_pframe1{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"#m_label_title{\n"
"	\n"
"	font: 12pt \"\351\273\221\344\275\223\";\n"
"}\n"
"#m_widget_bottom{  \n"
"	border-style: solid;\n"
"  border-width: 2px;\n"
"  border-color: rgb(233,233,235);\n"
"}\n"
"#m_textEdit_send{\n"
"	border:0px;\n"
"}\n"
"#m_Btn_close{\n"
"	\n"
"	border-image: url(:/NewCos/Resources/close.png);\n"
"}"));
        gridLayout = new QGridLayout(Cos_GroupChat);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_title = new QWidget(Cos_GroupChat);
        m_title->setObjectName(QStringLiteral("m_title"));
        horizontalLayout = new QHBoxLayout(m_title);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_label_title = new QLabel(m_title);
        m_label_title->setObjectName(QStringLiteral("m_label_title"));

        horizontalLayout->addWidget(m_label_title);

        horizontalSpacer = new QSpacerItem(283, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        m_Btn_close = new QPushButton(m_title);
        m_Btn_close->setObjectName(QStringLiteral("m_Btn_close"));

        horizontalLayout->addWidget(m_Btn_close);


        verticalLayout->addWidget(m_title);

        m_pframe = new QFrame(Cos_GroupChat);
        m_pframe->setObjectName(QStringLiteral("m_pframe"));
        m_pframe->setMinimumSize(QSize(0, 300));
        m_pframe->setFrameShape(QFrame::StyledPanel);
        m_pframe->setFrameShadow(QFrame::Raised);

        verticalLayout->addWidget(m_pframe);

        line = new QFrame(Cos_GroupChat);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        m_textEdit_send = new QTextEdit(Cos_GroupChat);
        m_textEdit_send->setObjectName(QStringLiteral("m_textEdit_send"));

        verticalLayout->addWidget(m_textEdit_send);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        pushButton = new QPushButton(Cos_GroupChat);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(Cos_GroupChat);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);

        m_Btn_Send = new QPushButton(Cos_GroupChat);
        m_Btn_Send->setObjectName(QStringLiteral("m_Btn_Send"));

        horizontalLayout_2->addWidget(m_Btn_Send);


        verticalLayout->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);


        retranslateUi(Cos_GroupChat);

        QMetaObject::connectSlotsByName(Cos_GroupChat);
    } // setupUi

    void retranslateUi(QWidget *Cos_GroupChat)
    {
        Cos_GroupChat->setWindowTitle(QApplication::translate("Cos_GroupChat", "Cos_GroupChat", Q_NULLPTR));
        m_label_title->setText(QApplication::translate("Cos_GroupChat", "\345\221\206\345\221\206\350\202\211\350\202\211\347\232\204\350\201\212\345\244\251", Q_NULLPTR));
        m_Btn_close->setText(QString());
        pushButton->setText(QApplication::translate("Cos_GroupChat", "\346\222\244\351\224\200\345\257\271\346\226\271", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Cos_GroupChat", "\345\210\240\351\231\244\346\210\221\346\226\271", Q_NULLPTR));
        m_Btn_Send->setText(QApplication::translate("Cos_GroupChat", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Cos_GroupChat: public Ui_Cos_GroupChat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COS_GROUPCHAT_H
