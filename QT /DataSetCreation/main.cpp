#include "cleaningapp.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CleaningApp w;
    w.show();
    return a.exec();
}
