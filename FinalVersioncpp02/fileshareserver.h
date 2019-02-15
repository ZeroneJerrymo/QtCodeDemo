#ifndef FILESHAREServer_H
#define FILESHAREServer_H
#include <QDialog>
#include <QTime>
#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMainWindow>
#include <QFileDialog>
#include <QtGui>
#include <vector>
#include <QUdpSocket>
#include <QNetworkInterface>
#include "filepackage.h"
#include "fileshareclient.h"

enum MessageShareType{New=17,File=18,Left=19,cancel=20,FB=21,FN=22};

namespace Ui {
class FileShareServer;
}

class FileShareServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit FileShareServer(QWidget *parent = 0);
    ~FileShareServer();
    void initServer();

private slots:

    void on_UpLoadButton_clicked();
    void receiveMessage();
    void sendFile();
    void updateClientProgress(qint64 numBytes);
    void on_CancelButton_clicked();

    void on_DownLoadButton_clicked();

private:
    QString fileName;
    QString theFileName;
    QString UpLoadTime;
    QString UpLoadUserName;
    QString clientAddress;
    Ui::FileShareServer *ui;
    std::vector<FilePackage> FpackageList;
    FilePackage Fpackage;

    QUdpSocket *udpSend;
    QUdpSocket *udpReceive;
    QUdpSocket *udpSocket;


    qint16 tcpPort;
    QTcpServer *tcpServer;
    QFile *localFile;
    qint64 TotalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 payloadSize;
    QByteArray outBlock;
    QTcpSocket *clientConnection;
    QTime time;


protected:
    QString getIP();
    QString getUserName();
    void newFile(QString FileName,
                        QString UpLoadTime, QString UpLoadUserName, QString UserIp);
    void sendSignal(MessageShareType type ,QString serverAddress="");
    void hasPendingFile(QString serverAddress,
                                QString clientAddress, QString fileName);

};

#endif // FILESHARESERVER_H
