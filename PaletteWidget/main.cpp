#include "PaletteWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaletteWidget w;
    w.show();
    return a.exec();
}
