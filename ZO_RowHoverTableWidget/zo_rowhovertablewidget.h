#ifndef ZO_ROWHOVERTABLEWIDGET_H
#define ZO_ROWHOVERTABLEWIDGET_H

#include <QObject>
#include <QWidget>
#include <QTableWidget>
class Zo_RowHoverTableModel;
class Zo_RowHoverTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    explicit Zo_RowHoverTableWidget(QWidget *parent = nullptr);
    void setHoverColor(QColor color);
signals:

public slots:
    void m_cellEntered(int row, int column);
protected:
    void leaveEvent(QEvent *event);
private:
    void setRowColor(int row, QColor color);

    int previousColorRow;
    QColor  lastRowBkColor;
    QColor  m_hoverColor;

};
class Zo_RowHoverTableView : public QTableView
{
    Q_OBJECT
public:
    explicit Zo_RowHoverTableView(QWidget *parent = nullptr);

    void updateRow(int row);
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void leaveEvent(QEvent *event);
private:
    Zo_RowHoverTableModel* table_model;
    int current_row;
};

class Zo_RowHoverTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Zo_RowHoverTableModel(QObject* pobject);

    void setHoverRow(int hover_row);
protected:
    QVariant data(const QModelIndex &index, int role) const;
private:
    int hover_row;
};
#endif // ZO_ROWHOVERTABLEWIDGET_H
