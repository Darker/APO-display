#include <QApplication>
void startLinuxRenderer(const std::string );
void exitLinuxRenderer();

int mainQtLinux(int argc, char *argv[])
{
    QApplication a(argc, argv);
    startLinuxRenderer("");
    a.exec();
    exitLinuxRenderer();
}
