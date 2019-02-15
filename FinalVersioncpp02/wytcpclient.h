#ifndef WYTCPCLIENT_H
#define WYTCPCLIENT_H

#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>
class QTcpSocket;

namespace Ui {
class WyTcpClient;
}

class WyTcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit WyTcpClient(QWidget *parent = 0);
    ~WyTcpClient();

    void setHostAddress(QHostAddress address);
    void setFileName(QString fileName);

protected:
    void closeEvent(QCloseEvent *);

private:
    Ui::WyTcpClient *ui;

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

private slots:
    void on_tcpClientCancleBtn_clicked();
    void on_tcpClientCloseBtn_clicked();

    void newConnect();
    void readMessage();
    void displayError(QAbstractSocket::SocketError);
};

#endif // TCPCLIENT_H
