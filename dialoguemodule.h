#ifndef DIALOGUEMODULE_H
#define DIALOGUEMODULE_H

#include <QWidget>

namespace Ui {
class DialogueModule;
}

class DialogueModule : public QWidget
{
    Q_OBJECT

public:
    explicit DialogueModule(QWidget *parent = nullptr);
    ~DialogueModule();

private slots:


private:
    Ui::DialogueModule *ui;
};

#endif // DIALOGUEMODULE_H
