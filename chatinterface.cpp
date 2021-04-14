#include "chatinterface.h"
#include "ui_chatinterface.h"
#include "qfile.h"
#include <QDebug>
#include "bubble.h"
#include "bubblemyself.h"
#include <QProcess>
#include <QScrollBar>

ChatInterface::ChatInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatInterface)
{
    ui->setupUi(this);
    m_intIP = new InputIP(this);
    connect(ui->toolButton,&QToolButton::clicked,this,&ChatInterface::slotShowInput);

    //读取样式表
    readQss();
    //设置工具按钮
    setToolButton();
    //设置搜索文本输入
    setSearchLineEdit();
    //设置输入框
    setTextEdit();

    m_udpSocket = new QUdpSocket(this);
    //绑定端口号
    m_udpSocket->bind(6666);

    //获取本机ip
    QString strIPAddress = getLocalIP();

    //设置窗口标题
    QString title = QString("你的IP：%1，端口号为：6666").arg(strIPAddress);
    setWindowTitle(title);

    //当对方成功发送数据时,自动触发readyRead()
    connect(m_udpSocket,&QUdpSocket::readyRead,this,&ChatInterface::slotDealMessage);
    //当添加了对方IP和端口号后，创建聊天对象
    connect(m_intIP,&InputIP::signalCreateReceiver,this,&ChatInterface::slotCreateObject);
}

ChatInterface::~ChatInterface()
{
    delete ui;
}

void ChatInterface::readQss()
{
    QFile file(":Style.qss");
    if(file.open(QFile::ReadOnly))
    {
        QTextStream filetext(&file);
        QString stylesheet = filetext.readAll();
        this->setStyleSheet(stylesheet);
        file.close();
    }
    else
    {
        qDebug()<<"Open file fail";
    }
}

void ChatInterface::slotShowInput()
{
    m_intIP->show();
}

//处理接收的信息
void ChatInterface::slotDealMessage()
{
    char buf[512]={0};
    QHostAddress clientAddress;
    quint16 port;

    qint64 len = m_udpSocket->readDatagram(buf,sizeof(buf),&clientAddress,&port);
    QString IP = toIPv4(clientAddress);
    if(len > 0)
    {
        QString content = QString("[%1:%2] \n%3").arg(IP).arg(port).arg(buf);
        QString Port = QString("%1").arg(port);

        QListWidgetItem *receiveItem = new QListWidgetItem();
        Bubble *receiver = new Bubble();
        receiver->setText(content);
        receiveItem->setSizeHint(QSize(200,120));
        ui->chatWindow->addItem(receiveItem);
        ui->chatWindow->setItemWidget(receiveItem,receiver);
        //添加新项之后，滚动条自动到最底
        ui->chatWindow->scrollToBottom();

        //接收新IP发送的信息时，创建聊天对象
        if(infoIP.value("IP") != IP || infoIP.value("port") != Port)
        {
            getInfoIP(IP,Port);
            QString IPAndPort = QString("对方IP：%1\n端口号：%2").arg(infoIP.value("IP")).arg(infoIP.value("port"));
            QListWidgetItem *objectItem = new QListWidgetItem();
            Bubble *bubbleReceiver = new Bubble();
            bubbleReceiver->setText(IPAndPort);
            objectItem->setSizeHint(QSize(200,120));
            ui->chatObject->addItem(objectItem);
            ui->chatObject->setItemWidget(objectItem,bubbleReceiver);
            //添加新项之后，滚动条自动到最底
            ui->chatObject->scrollToBottom();
        }
    }
}

void ChatInterface::setToolButton()
{
    m_setIPAndPort = new QAction(this);
    m_setIPAndPort->setText("设置");
    ui->toolButton->setDefaultAction(m_setIPAndPort);
}

void ChatInterface::setSearchLineEdit()
{
    ui->search->setPlaceholderText("搜索");
}

void ChatInterface::setTextEdit()
{
    ui->textEdit->setFocus();
}

//获取本机IP地址
QString ChatInterface::getLocalIP()
{
    QString ip = "";
    QProcess cmd_pro ;
    QString cmd_str = QString("ipconfig");
    cmd_pro.start("cmd.exe", QStringList() << "/c" << cmd_str);
    cmd_pro.waitForStarted();
    cmd_pro.waitForFinished();
    QString result = cmd_pro.readAll();
    QString pattern("[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}");
    QRegExp rx(pattern);

    int pos = 0;
    bool found = false;
    while((pos = rx.indexIn(result, pos)) != -1)
    {
        QString tmp = rx.cap(0);
        //跳过子网掩码 eg:255.255.255.0
        if(-1 == tmp.indexOf("255"))
        {
            if(ip != "" && -1 != tmp.indexOf(ip.mid(0,ip.lastIndexOf("."))))
            {
                found = true;
                break;
            }
            ip = tmp;
        }
        pos += rx.matchedLength();
    }
    return ip;
}

//保存IP和端口号
QMap<QString, QString> ChatInterface::getInfoIP(const QString &IP,const QString &port)
{
    infoIP.insert("IP",IP);
    infoIP.insert("port",port);
    return infoIP;
}

//IP地址固定为IPv4格式
QString ChatInterface::toIPv4(const QHostAddress &addr)
{
    quint32  addrOrigin = addr.toIPv4Address();
    QHostAddress addrHost = QHostAddress(addrOrigin);
    QString  addrStr = addrHost.toString();
    return addrStr;
}

//发送信息
void ChatInterface::on_send_clicked()
{
    //获取接受方IP
    QString IP = infoIP.value("IP");
    quint16 port = infoIP.value("port").toUInt();

    //获取编辑区内容
    QString content = ui->textEdit->toPlainText();   

    //没有输入不能发送消息
    //没有设置IP和端口号也不能发送消息
    if(content != tr("") && IP != tr("") && infoIP.value("port") != tr(""))
    {
        //给指定IP发送数据
        m_udpSocket->writeDatagram(content.toUtf8(), QHostAddress(IP), port);
        qDebug() << IP << port << content;

        QListWidgetItem *sendItem = new QListWidgetItem();
        BubbleMyself *sender = new BubbleMyself();
        sender->setText(ui->textEdit->toPlainText());
        sendItem->setSizeHint(QSize(200,100));
        ui->chatWindow->addItem(sendItem);
        ui->chatWindow->setItemWidget(sendItem,sender);
        //添加新项之后，滚动条自动到最底
        ui->chatWindow->scrollToBottom();
    }
    //发送之后清空输入框，光标聚焦
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

//创建聊天对象
void ChatInterface::slotCreateObject()
{
    QString IP = m_intIP->setIP();
    QString port = m_intIP->setPort();
    //如果ip地址或端口号为空，不能创建聊天对象
    //如果ip地址和端口号都与上一个发送者的相同，也不能创建对象
    if((IP != tr("") && port != tr("")) && (IP != infoIP.value("IP") || port != infoIP.value("port")))
    {
        //保存IP和端口号
        getInfoIP(IP,port);

        QString IPAndPort = QString("对方IP：%1\n端口号：%2").arg(IP).arg(port);
        QListWidgetItem *receiveItem = new QListWidgetItem();
        Bubble *receiver = new Bubble();
        receiver->setText(IPAndPort);
        receiveItem->setSizeHint(QSize(200,120));
        ui->chatObject->addItem(receiveItem);
        ui->chatObject->setItemWidget(receiveItem,receiver);
        //添加新项之后，滚动条自动到最底
        ui->chatObject->scrollToBottom();
    }
}
