#include <QApplication>
void startLinuxRenderer();
void exitLinuxRenderer();

int mainQtLinux(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startLinuxRenderer();
    a.exec();
    exitLinuxRenderer();
}
