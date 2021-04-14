#ifndef BUBBLEMYSELF_H
#define BUBBLEMYSELF_H

#include <QWidget>

namespace Ui {
class BubbleMyself;
}

class BubbleMyself : public QWidget
{
    Q_OBJECT

public:
    explicit BubbleMyself(QWidget *parent = nullptr);
    ~BubbleMyself();
    //接收并显示发送文本
    void setText(QString text);

private:
    //调整气泡框的高度
    void adjustTextHeight();

private:
    Ui::BubbleMyself *ui;
};

#endif // BUBBLEMYSELF_H
