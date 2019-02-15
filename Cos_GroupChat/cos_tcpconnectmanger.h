#ifndef COS_TCPCONNECTMANGER_H
#define COS_TCPCONNECTMANGER_H

#include <QObject>
#include <QTcpSocket>

typedef struct  ConnectParam
{
    QString Server_IP;
    int Server_port;

    ConnectParam(){

//        Server_IP =  QString("10.50.12.100");
        Server_IP =  QString("123.113.247.207");
        Server_port =  8765;
    }
} ConnectServerParam;

class Cos_TcpConnectManger : public QObject
{
    Q_OBJECT
public:
    explicit Cos_TcpConnectManger(QObject *parent = nullptr);
    ~Cos_TcpConnectManger();

signals:
    void sig_connectSuccess();
    void sig_connectFailed();
    void sig_disconnect();
    void  sig_receiveMessage(QString);
public slots:
    void onConnect_Server();
    void ondisConnect_Server();
    void sendMessage(QString msg);
protected slots:
    void socket_Read_Data();
    void socket_Disconnected();
private:
    QTcpSocket *socket;
};

#endif // COS_TCPCONNECTMANGER_H
