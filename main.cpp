#include "mainFunctions.h"
#ifdef _QT_COMPILE
int main(int argc, char *argv[])
{
    return mainQt(argc, argv);
    //return mainLinux(argc, argv);
}
#else
#include "defines.h"
void runGame() {

}
int main(int argc, char *argv[])
{
    return mainLinux(argc, argv);
}
#endif
