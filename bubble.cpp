#include "bubble.h"
#include "ui_bubble.h"

Bubble::Bubble(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bubble)
{
    ui->setupUi(this);
}

Bubble::~Bubble()
{
    delete ui;
}

void Bubble::setText(QString text)
{
    ui->textEditOpposite->setText(text);
}
