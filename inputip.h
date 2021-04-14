#ifndef INPUTIP_H
#define INPUTIP_H

#include <QDialog>

namespace Ui {
class InputIP;
}

class InputIP : public QDialog
{
    Q_OBJECT

public:
    explicit InputIP(QWidget *parent = nullptr);
    ~InputIP();
    //返回输入的IP和端口号
    QString setIP();
    QString setPort();

signals:
    void signalCreateReceiver();

private slots:
    void on_buttonBox_accepted();

private:
    //限制输入格式
    void inputLimit();

private:
    Ui::InputIP *ui;
};

#endif // INPUTIP_H
