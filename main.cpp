#include "sonerit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    sonerit w;
    w.show();
    return a.exec();
}
