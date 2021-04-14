#include "inputip.h"
#include "ui_inputip.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>

InputIP::InputIP(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputIP)
{
    ui->setupUi(this);
    inputLimit();
    //设置窗口标题
    QString title = "输入对方IP地址和端口号";
    setWindowTitle(title);
}

InputIP::~InputIP()
{
    delete ui;
}

QString InputIP::setIP()
{
    return ui->lineEditIP->text();
}

QString InputIP::setPort()
{
    return ui->lineEditPort->text();
}

void InputIP::inputLimit()
{
    //限制IP输入格式
    QRegExp regxIP("^((2[0-4]\\d|25[0-5]|[01]?\\d\\d?)\\.){3}(2[0-4]\\d|25[0-5]|[01]?\\d\\d?)$"); //IP正则表达式
    QRegExpValidator *m_IPValidator = new QRegExpValidator(regxIP,ui->lineEditIP);
    ui->lineEditIP->setValidator(m_IPValidator);

    //限制端口号输入
    QRegExp regx("[0-9]+$");
    QRegExpValidator *m_portValidator = new QRegExpValidator(regx,ui->lineEditPort);
    ui->lineEditPort->setValidator(m_portValidator);
}

//点击OK之后触发创建对象的信号
void InputIP::on_buttonBox_accepted()
{
    emit signalCreateReceiver();
}
