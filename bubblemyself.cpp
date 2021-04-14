#include "bubblemyself.h"
#include "ui_bubblemyself.h"
#include <QTextBlock>

BubbleMyself::BubbleMyself(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BubbleMyself)
{
    ui->setupUi(this);
}

BubbleMyself::~BubbleMyself()
{
    delete ui;
}

void BubbleMyself::setText(QString text)
{
    ui->textEditMyself->setText(text);
    ui->textEditMyself->setAlignment(Qt::AlignRight);
}

void BubbleMyself::adjustTextHeight()
{
//    qreal doc_margin = ui->textEditMyself->document()->documentMargin();    //字体到边框的距离默认为4
//    QTextDocument *doc = ui->textEditMyself->document();
//    qreal text_height = 0;
//    //把每一段的高度相加=文本高
//    for (QTextBlock it = doc->begin(); it != doc->end(); it = it.next())
//    {
//        QTextLayout *pLayout = it.layout();
//        QRectF text_rect = pLayout->boundingRect();                             //这段的rect
//        text_height += text_rect.height();
//    }
//    int vMargin = this->layout()->contentsMargins().top();
//    //设置这个气泡需要的高度 文本高+文本边距+TextEdit边框到气泡边框的距离
//    setFixedHeight(text_height + doc_margin *2 + vMargin*2 );

}
