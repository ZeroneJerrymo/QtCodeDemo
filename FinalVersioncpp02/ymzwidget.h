#ifndef YMZWIDGET_H
#define YMZWIDGET_H

#include <QWidget>
#include <QTextCharFormat>
#include<QCloseEvent>
#include "tcpserver.h"
#include "tcpclient.h"


class QUdpSocket;
class TcpServer;

namespace Ui {
class Widget;
}

enum MessageType{Message, NewParticipant, ParticipantLeft, FileName, Refuse};

class Widget : public QWidget
{
    Q_OBJECT

public:
   explicit Widget(QWidget *parent = 0);
    Widget(QString ip, QString hostName, QString userName,  QString imagePath, bool* flag = NULL,  QWidget *parent = 0);
    ~Widget();
protected:
    void sendMessage(MessageType type);

    QString getIP();
    QString getUserName();
    QString getMessage();
    void closeEvent(QCloseEvent *e);
    bool saveFile(const QString& fileName);

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;
    QColor color;
    bool *flag;
public:
    TcpServer *server;
    QString fileName;

private slots:
    //void processPendingDatagrams();

    void on_pushButton_clicked();

    void on_fontComboBox_currentFontChanged(QFont f);
    void on_sizeComboBox_currentIndexChanged(QString );
    void on_toolButton_2_clicked(bool checked);
    void on_italicToolBtn_clicked(bool checked);
    void on_underlineToolBtn_clicked(bool checked);
    void on_colorToolBtn_clicked();
    void currentFormatChanged(const QTextCharFormat &format);
    void on_face_clicked();
    void on_saveToolBtn_clicked();
    void on_file_clicked();
    void getFileName(QString);
    void on_clear_clicked();

public :
    void setText(QString msg);
};

#endif // WIDGET_H
