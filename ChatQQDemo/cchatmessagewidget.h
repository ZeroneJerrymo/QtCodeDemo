#ifndef CCHATMESSAGEWIDGET_H
#define CCHATMESSAGEWIDGET_H

#include <QWidget>
#include <QWebEngineView>
#include <QTextEdit>

class CChatMessageWidget : public QWidget
{
    Q_OBJECT

public:
    CChatMessageWidget(QWidget *parent = 0);
    ~CChatMessageWidget();

public slots:
    void ppppp();
    void ppppp1();
    void slot_btnpicClicked();
    void slot_lineEditReturnpressed();
private:
    QWebEngineView *m_pView;
    QTextEdit* pTextEdit1;
    QTextEdit* pTextEdit2;
    QString otherhead;
    QString Myhead;
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
protected:
    void SendMsgShow(QString msg, QString head);
    void RevMsgShow(QString msg, QString head);
};

#endif // CCHATMESSAGEWIDGET_H
