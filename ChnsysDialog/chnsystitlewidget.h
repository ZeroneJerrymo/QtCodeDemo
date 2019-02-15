#ifndef CHNSYSTITLEWIDGET_H
#define CHNSYSTITLEWIDGET_H

#include <QLabel>
#include <QWidget>

class ChnsysTitleButtonGroup;
//可拖动标题栏
class ChnsysTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChnsysTitleWidget(QWidget *parent = nullptr);

    void setTitleText(QString titleText);
    void setTitleIcon(QString iconPath);
signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
private:
    QLabel* m_titleLabel;
    QLabel* m_titleIcon;
    ChnsysTitleButtonGroup * m_titlebtnGroup;

private:
    bool            m_isPressed;
    QPoint          m_startMovePos;
};

#endif // CHNSYSTITLEWIDGET_H
