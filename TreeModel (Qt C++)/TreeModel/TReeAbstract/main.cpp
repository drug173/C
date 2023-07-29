#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget window;
    window.resize(800, 600);
    window.setWindowTitle(QObject::tr("Представление в виде дерева"));
    QPalette pal1;
    pal1.setColor(window.backgroundRole(),  Qt::lightGray);
    window.setPalette(pal1);
    window.setWindowIcon(QIcon("../build/img2.png"));


    window.show();
    return a.exec();
}
