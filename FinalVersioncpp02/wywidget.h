#ifndef WYWIDGET_H
#define WYWIDGET_H

#include <QWidget>
class QUdpSocket;
class WyTcpServer;

namespace Ui {
class WyWidget;
}

//ö�ٱ�����־��Ϣ���ͣ��ֱ�Ϊ��Ϣ�����û����롢�û��˳����ļ������ܾ������ļ���ͼ��
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
                        QString clientAddress, QString fileName);//�ж��Ƿ�����ļ�
    bool saveFile(const QString& filename);
    void createTempimageDir();
private:
    Ui::WyWidget *ui;
    QUdpSocket *udpSocket;
    qint16 port;//qt�Զ������ͣ���ʾ16λ�޷�������
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
