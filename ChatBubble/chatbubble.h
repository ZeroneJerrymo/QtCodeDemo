#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QHBoxLayout>
#include <QScrollBar>
#include <QTimer>

#define ITEM_START_ANGLE 270
#define ITEM_D_ANGLE 2
#define ITEM_D_ZOOMING_FACTOR 0.05
#define UPDATE_TIMER_INTERVAL 10 // ms
#define ITEM_COUNTER_TIMER_INTERVAL 200
#define SIZE_HINT QSize(300,300)

#define ITEM_HEIGHT 50
#define BG_START_COLOR QColor(179,179,183)
#define BG_END_COLOR QColor(187,193,207)

#define ITEM_START_COLOR ITEM_END_COLOR.lighter()
#define ITEM_END_COLOR QColor(62,135,166)

#define ITEM_START_COLOR_A ITEM_END_COLOR_A.lighter()
#define ITEM_END_COLOR_A QColor(221,221,221)

#define HOVER_OPACITY 0.2
#define HOVER_START_COLOR HOVER_END_COLOR.lighter()
#define HOVER_END_COLOR QColor(98,139,21)

#define HOVER_TEXT_COLOR Qt::red
#define SELECT_TEXT_COLOR Qt::white
#define NORMAL_TEXT_COLOR Qt::black

#define RECT_RADIUS 4

#define ITEM_SPACE          10

//namespace BubbleWidget
//{

//};

enum Orientation{
    None,
    Left,
    Right
};

class ItemInfo
{
public:
    ItemInfo(const QString& str):
        m_strData(str),
        m_orientation(Left),
        m_Angle(ITEM_START_ANGLE)
      ,m_ZoomingFactor(0)
    {

    }

    ItemInfo(const QString& str,const int &orientation):
        m_strData(str),
        m_orientation(orientation),
        m_Angle(ITEM_START_ANGLE),
        m_ZoomingFactor(0)
    {

    }

    ItemInfo():m_orientation(Left),m_Angle(ITEM_START_ANGLE),m_ZoomingFactor(0){}
    ~ItemInfo(){}

public:
    /// public interfaces
    void setText(const QString& str)
    {
        m_strData = str;
    }

    QString getText() const
    {
        return m_strData;
    }

    void updateAngle()
    {
        m_Angle += ITEM_D_ANGLE;

        if(m_Angle >  360)
        {
            m_Angle = 0;
        }
    }

    void updateZoomingFactor()
    {
        m_ZoomingFactor += ITEM_D_ZOOMING_FACTOR;

        if(m_ZoomingFactor > 1.0)
        {
            m_ZoomingFactor = 1.0;
        }
    }

    bool jobDone() const
    {
        return m_Angle == 360 || m_ZoomingFactor == 1.0;
    }

    void resetAngle()
    {
        m_Angle = ITEM_START_ANGLE;
    }

    void resetZoomingFactor()
    {
        m_ZoomingFactor = 0.0;
    }

    qreal getAngle() const
    {
        return m_Angle;
    }

    qreal getZoomingFactor() const
    {
        return m_ZoomingFactor;
    }

    bool inWrongPosition() const
    {
        return m_Angle > ITEM_START_ANGLE && m_Angle < 360;
    }

    bool inWrongZoomingPosition()
    {
        return m_ZoomingFactor < 1.0;
    }

    int getOrientation() const
    {
        return m_orientation;
    }

    void setOrientation(int orientation)
    {
        m_orientation = orientation;
    }

private:
    QString m_strData;
    int m_orientation;
    qreal m_Angle;
    qreal m_ZoomingFactor;
};

class BubbleListPrivate;
class BubbleList: public QWidget
{
    Q_OBJECT
public:
    BubbleList(QWidget* parent = 0);
    ~BubbleList();

public:
    /// proxy public interfaces for PYFlashListPrivate
    void addItem(const QString& str, const int &orientation);

    void clear();

    void render();

    void setCurrItem(const int &index) {
        scrollbar->setValue(index);
    }

protected:
    QSize sizeHint() const
    {
        return QSize(SIZE_HINT);
    }

    void resizeEvent(QResizeEvent *);


private:
    /// private utility functoins
    void initVars();
    void initWgts();
    void initStgs();
    void initConns();

    void calcGeo();

private Q_SLOTS:
    void setMaximum(int max);

private:
    QHBoxLayout* mainLayout;
    QScrollBar* scrollbar;
    BubbleListPrivate* d;

Q_SIGNALS:
    void sig_setCurrentIndex(int currIndex);
    void sig_itemClicked(const QString& str);
};

class BubbleListPrivate : public QWidget
{
    Q_OBJECT
public:
    explicit BubbleListPrivate(QWidget *parent = 0);

public:
    /// public interfaces
    void addItem(const QString& str, const int &orientation);

    void clear();

    void render();

    int itemCount() const
    {
        return m_IIVec.count();
    }
public Q_SLOTS:
    void setCurrentIndex(int curIndex);

protected:
    void paintEvent(QPaintEvent *);

    void mouseMoveEvent(QMouseEvent *);

    void mousePressEvent(QMouseEvent *);

    void resizeEvent(QResizeEvent *);

    void leaveEvent(QEvent *);

    void showEvent(QShowEvent *);

    void wheelEvent(QWheelEvent *);

private:
    /// painting functions
    void drawBg(QPainter* painter);

    void drawItems(QPainter* painter);

    void drawHoverRect(QPainter* painter);

private:
    /// private utility functoins
    void initVars();
    void initSettings();
    void calcGeo();
    void makeupJobs();
    void wheelUp();
    void wheelDown();

private:
    QVector<ItemInfo> m_IIVec;

    int m_currIndex;
    int m_selectedIndex;
    int m_VisibleItemCnt;
    int m_ItemCounter;

    bool m_bAllJobsDone;

    QRectF m_HoverRect;

    QString m_strHoverText;

    QTimer* m_RotateTimer;
    QTimer* m_ItemCountTimer;

private Q_SLOTS:
    void DoRotation();
    void UpdateItemCount();

Q_SIGNALS:
    void sig_setMaximum(int max);
    void sig_setCurrentIndex(int currIndex);
    void sig_itemClicked(const QString& str);
};
#endif // CHATBUBBLE_H
