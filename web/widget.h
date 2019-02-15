#ifndef WIDGET_H
#define WIDGET_H

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
private:
    QWebEngineView *m_pView;
    QTextEdit* pTextEdit1;
    QTextEdit* pTextEdit2;
    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // WIDGET_H
