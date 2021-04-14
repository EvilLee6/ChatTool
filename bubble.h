#ifndef BUBBLE_H
#define BUBBLE_H

#include <QWidget>

namespace Ui {
class Bubble;
}

class Bubble : public QWidget
{
    Q_OBJECT

public:
    explicit Bubble(QWidget *parent = nullptr);
    ~Bubble();
    //接受并显示对方发送的文本
    void setText(QString text);

private:


private:
    Ui::Bubble *ui;
};

#endif // BUBBLE_H
