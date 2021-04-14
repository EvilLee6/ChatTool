#include "mainwindow.h"
#include "chatinterface.h"
#include "inputip.h"
#include "dialoguemodule.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ChatInterface w;
    w.show();
    return a.exec();
}
