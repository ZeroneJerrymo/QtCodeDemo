#ifndef WYWIDGET_H
#define WYWIDGET_H

#include <QWidget>
class QUdpSocket;
class WyTcpServer;

namespace Ui {
class WyWidget;
}

//枚举变量标志信息类型，分别为消息、新用户加入、用户退出、文件名、拒绝接收文件、图像
enum WyMessageType{WyMessage,WyNewParticipant,WyParticipantLeft,WyFileName,WyRefuse,Image};

class WyWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WyWidget(QWidget *parent = 0);
    ~WyWidget();

protected:
    void newParticipant(QString userName,
                        QString localHostName,QString ipAddress);
    void participantLeft(QString userName,
                         QString localHostName,QString time);
    void sendMessage(WyMessageType type,QString serverAddress="");
    void closeEvent(QCloseEvent *);

    QString getIP();
    QString getUserName();
    QString getMessage();
    void hasPendingFile(QString userName, QString serverAddress,
                        QString clientAddress, QString fileName);//判断是否接收文件
    bool saveFile(const QString& filename);
    void createTempimageDir();
private:
    Ui::WyWidget *ui;
    QUdpSocket *udpSocket;
    qint16 port;//qt自定义类型，表示16位无符号整形
    QColor color;

    QString fileName;
    QString imageName;
    WyTcpServer *server;

private slots:
    void processPendingDatagrams();
    void on_sendButton_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_sizeComboBox_currentIndexChanged(const QString &arg1);
    void on_boldToolBtn_clicked(bool checked);
    void on_italicToolBtn_clicked(bool checked);
    void on_underlineToolBtn_clicked(bool checked);
    void on_colorToolBtn_clicked();
    void on_saveToolBtn_clicked();
    void on_clearToolBtn_clicked();
    void getFileName(QString);
    void on_sendToolBtn_clicked();
    void on_biaoqing_Button_clicked();
    void on_tupian_clicked();
};

#endif // WIDGET_H
