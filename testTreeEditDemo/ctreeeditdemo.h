#ifndef CTREEEDITDEMO_H
#define CTREEEDITDEMO_H

#include <QLineEdit>
#include <QMenu>
#include <QPushButton>
#include <QWidgetAction>
#include "caseconcepts.h"
class CTreeLineEdit:public QLineEdit
{
    Q_OBJECT
public:
    CTreeLineEdit(QWidget *parent);
    ~CTreeLineEdit();

public slots:
    void slot_inputCaseConcepts(QString str);
    void slot_deleteCaseConcepts(QString str);
protected:
    virtual void paintEvent(QPaintEvent * e);
    virtual void mouseMoveEvent(QMouseEvent* event);

protected:

    virtual void focusInEvent(QFocusEvent *e);
    virtual void focusOutEvent(QFocusEvent *e);
private slots:

//    void slot_textChanged(const QString &text);
    void slot_m_pBtnClicked();
signals:
    void signalFocusIn();
private:
    QPushButton * m_pBtn;
    QMenu * m_pMenu;
    QWidgetAction * m_widgetAction;
     caseConcepts* temp_caseconcepts;

     QStringList list_caseReason;
};

#endif // CTREEEDITDEMO_H
