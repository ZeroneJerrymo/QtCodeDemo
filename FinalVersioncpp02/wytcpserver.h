#ifndef WYTCPSERVER_H
#define WYTCPSERVER_H

#include <QDialog>

#include <QTime>
class QFile;
class QTcpServer;
class QTcpSocket;

namespace Ui {
class WyTcpServer;
}

class WyTcpServer : public QDialog
{
    Q_OBJECT

public:
    explicit WyTcpServer(QWidget *parent = 0);
    ~WyTcpServer();

    void initServer();
    void refused();

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::WyTcpServer *ui;

    qint16 tcpPort;
    QTcpServer *tcpServer;
    QString fileName;
    QString theFileName;
    QFile *localFile;

    qint64 TotalBytes;
    qint64 bytesWritten;
    qint64 bytesToWrite;
    qint64 payloadSize;
    QByteArray outBlock;

    QTcpSocket *clientConnection;
    QTime time;

private slots:
    void sendMessage();

    void updateClientProgress(qint64 numBytes);

    void on_serverOpenBtn_clicked();

    void on_serverSendBtn_clicked();

    void on_serverCloseBtn_clicked();

signals:
    void sendFileName(QString fileName);


};

#endif // TCPSERVER_H
