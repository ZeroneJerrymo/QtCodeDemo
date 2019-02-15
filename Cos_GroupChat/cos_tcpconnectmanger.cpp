#include "cos_tcpconnectmanger.h"

Cos_TcpConnectManger::Cos_TcpConnectManger(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
   // onConnect_Server();
    //连接信号槽
    QObject::connect(socket, &QTcpSocket::readyRead, this, &Cos_TcpConnectManger::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &Cos_TcpConnectManger::socket_Disconnected);
}

Cos_TcpConnectManger::~Cos_TcpConnectManger()
{
    delete this->socket;
}

void Cos_TcpConnectManger::sendMessage(QString msg)
{
    qDebug()<<msg;
    socket->write(msg.toUtf8());
    socket->flush();
}

void  Cos_TcpConnectManger::socket_Read_Data()
{
    QByteArray buffer;
    //读取缓冲区数据
    buffer = socket->readAll();
    if(!buffer.isEmpty())
    {
       // QString str = ui->textEdit_Recv->toPlainText();
        //str+=tr(buffer);
        //刷新显示
        emit sig_receiveMessage(buffer);
      //  ui->textEdit_Recv->setText(str);
    }
}

void Cos_TcpConnectManger::onConnect_Server()
{
        QString IP;
        int port;
        //获取IP地址
     //   IP = ui->lineEdit_IP->text();
        //获取端口号d
      //  port = ui->lineEdit_Port->text().toInt();

        ConnectServerParam socketparam;
        IP =  socketparam.Server_IP;
        port = socketparam.Server_port;
        //取消已有的连接
        socket->abort();
        //连接服务器
        socket->connectToHost(IP, port);

        //等待连接成功
        if(!socket->waitForConnected(30000))
        {
            qDebug() << "Connection failed!";
            return;
        }
        qDebug() << "Connect successfully!";
        emit sig_connectSuccess();
}

void Cos_TcpConnectManger::ondisConnect_Server()
{
    //断开连接
    socket->disconnectFromHost();
    emit sig_disconnect();
}

void Cos_TcpConnectManger::socket_Disconnected()
{
    //发送关闭连接
    emit sig_disconnect();

}
