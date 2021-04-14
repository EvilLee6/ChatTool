#include "dialoguemodule.h"
#include "ui_dialoguemodule.h"

DialogueModule::DialogueModule(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogueModule)
{
    ui->setupUi(this);

}

DialogueModule::~DialogueModule()
{
    delete ui;
}
