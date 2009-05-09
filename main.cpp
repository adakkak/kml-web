#include <QtGui/QApplication>
#include "kmlweb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KMLWeb w;
    w.show();
    return a.exec();
}
