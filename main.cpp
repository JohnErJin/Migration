#include "Migration.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Migration w;
    w.show();
    return a.exec();
}
