#ifndef CHATINTERFACE_H
#define CHATINTERFACE_H

#include <QWidget>
#include <QAction>
#include "inputip.h"
#include <QUdpSocket>
#include <QMap>

namespace Ui {
class ChatInterface;
}

//基于UDP协议的简易聊天界面
class ChatInterface : public QWidget
{
    Q_OBJECT

public:
    explicit ChatInterface(QWidget *parent = nullptr);
    ~ChatInterface();

private slots:
    //切换到输入ip地址和端口号界面
    void slotShowInput();
    //处理接收信息
    void slotDealMessage();
    //发送信息
    void on_send_clicked();
    //创建聊天对象
    void slotCreateObject();

private:
    //读取样式表
    void readQss();
    //设置工具按钮
    void setToolButton();
    //设置搜索LineEdit
    void setSearchLineEdit();
    //设置输入框
    void setTextEdit();
    //获取本机IP地址
    QString getLocalIP();
    //保存对方IP信息
    QMap<QString,QString> getInfoIP(const QString &IP = tr(""),const QString &port = tr(""));
    //IP地址固定为IPv4格式
    QString toIPv4(const QHostAddress &addr);

private:
    Ui::ChatInterface *ui;
    QMap<QString,QString> infoIP;
    QAction *m_setIPAndPort;
    InputIP *m_intIP;
    QUdpSocket *m_udpSocket;
};

#endif // CHATINTERFACE_H
