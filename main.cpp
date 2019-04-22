#include "archimedes.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Archimedes w;
    w.show();

    return a.exec();
}
