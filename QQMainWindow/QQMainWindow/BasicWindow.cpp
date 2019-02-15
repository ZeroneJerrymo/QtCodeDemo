#include "BasicWindow.h"
#include "notifymanager.h"

#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QStyleOption>
#include <Windows.h>
#include <QMouseEvent>
#include <QDebug>

BasicWindow::BasicWindow(QWidget *parent)
	: QDialog(parent)
	, m_colorBackGround(QColor(22, 154, 218))
	, m_bSupportMoveWindow(true)
{
	setWindowFlags(Qt::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);

	connect(NotifyManager::getInstance(), SIGNAL(signalSkinChanged(const QColor&)), this, SLOT(onSignalSkinChanged(const QColor&)));
}

BasicWindow::~BasicWindow()
{
	
}

void BasicWindow::onSignalSkinChanged(const QColor& color)
{
	m_colorBackGround = color;
	loadStyleSheet(m_styleName);
}

void BasicWindow::loadStyleSheet(const QString &sheetName)
{
	QFile file(":/QQMainWindow/Resources/QSS/" + sheetName + ".css");
	file.open(QFile::ReadOnly);
	if (file.isOpen())
	{
		this->setStyleSheet("");
		QString qsstyleSheet = QLatin1String(file.readAll());
		//获取用户当前皮肤的RGB值
		QString r = QString::number(m_colorBackGround.red());
		QString g = QString::number(m_colorBackGround.green());
		QString b = QString::number(m_colorBackGround.blue());

		qsstyleSheet += QString("QWidget[titleskin=true] {background-color:rgb(%1,%2,%3);border-top-left-radius:4px;border-top-right-radius:4px;}\
								 QWidget#searchWidget {background-color:rgba(%1,%2,%3,50);}\
								 QWidget[bottomskin=true] {border-top: 1px solid rgba(%1,%2,%3,100);background-color:rgba(%1,%2,%3,50);border-bottom-left-radius:4px;border-bottom-right-radius:4px;}").arg(r).arg(g).arg(b);
		this->setStyleSheet(qsstyleSheet);
	}
	file.close();
}

void BasicWindow::setSupportMoveWindow(bool bSupportMove)
{
	m_bSupportMoveWindow = bSupportMove;
}

void BasicWindow::initBackGroundColor()
{
	// 背景图
	QStyleOption opt;
	opt.init(this);
	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void BasicWindow::paintEvent(QPaintEvent *event)
{
	initBackGroundColor();
	QWidget::paintEvent(event);
}

void BasicWindow::mousePressEvent(QMouseEvent *event)
{

}

QPixmap BasicWindow::getRoundImage(const QPixmap &src, QPixmap& mask, QSize masksize)
{
	if (masksize == QSize(0, 0))
	{
		masksize = mask.size();
	}
	else
	{
		mask = mask.scaled(masksize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	}

	QImage resultImage(masksize, QImage::Format_ARGB32_Premultiplied);
	QPainter painter(&resultImage);
	painter.setCompositionMode(QPainter::CompositionMode_Source);
	painter.fillRect(resultImage.rect(), Qt::transparent);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawPixmap(0, 0, mask);
	painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
	painter.drawPixmap(0, 0, src.scaled(masksize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	painter.end();
	return QPixmap::fromImage(resultImage);
}

void BasicWindow::onShowClose(bool)
{
	close();
}

void BasicWindow::onShowMin(bool)
{
	showMinimized();
}

void BasicWindow::onShowHide(bool)
{
	hide();
}

void BasicWindow::onShowNormal(bool)
{
	show();
	activateWindow();
}

void BasicWindow::onShowQuit(bool)
{
	QApplication::quit();
}
