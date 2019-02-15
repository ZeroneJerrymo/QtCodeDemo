#ifndef BASICWINDOW_H
#define BASICWINDOW_H

#include <QDialog>
#include <QIcon>

#define BACK_SHADOW_WIDTH 8

class BasicWindow : public QDialog
{
	Q_OBJECT

public:
	BasicWindow(QWidget *parent = 0);
	virtual ~BasicWindow();

public:
	// 加载qss
	void loadStyleSheet(const QString &sheetName);
	// 是否支持窗口拖动
	void setSupportMoveWindow(bool bSupportMove = true);
	QPixmap getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize = QSize(0, 0));

private:
	void initBackGroundColor();//初始化背景
	void moveDirection();
	void sizeDirection();

protected:
	void paintEvent(QPaintEvent*);// 绘制事件
	void mousePressEvent(QMouseEvent *event);

public slots:
	void onShowClose(bool);
	void onShowMin(bool);
	void onShowHide(bool);
	void onShowNormal(bool);
	void onShowQuit(bool);
	void onSignalSkinChanged(const QColor& color);

protected:
	bool m_bSupportMoveWindow;
	QColor m_colorBackGround;
	QString m_styleName;
};

#endif // TMQWIDGET_H
