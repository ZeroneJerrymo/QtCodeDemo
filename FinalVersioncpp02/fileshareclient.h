#ifndef FILESHARECLIENT_H
#define FILESHARECLIENT_H

#include <QMainWindow>
#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>
#include <QTcpSocket>
#include <QtGui>
#include <QObject>

namespace Ui {
class FileShareClient;
}

class FileShareClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileShareClient(QWidget *parent = 0);
    ~FileShareClient();
    void setHostAddress(QHostAddress address);
    void setFileName(QString fileName);


private slots:
    void newConnect();
    void readFile();

private:
    Ui::FileShareClient *ui;
    QTcpSocket *tcpClient;
    quint16 blockSize;
    QHostAddress hostAddress;
    qint16 tcpPort;

    qint64 TotalBytes;
    qint64 bytesReceived;
    qint64 bytesToReceive;
    qint64 fileNameSize;
    QString fileName;
    QFile *localFile;
    QByteArray inBlock;

    QTime time;
};

#endif // FILESHARECLIENT_H
