#include "mainFunctions.h"
#ifdef _QT_COMPILE
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{

    return mainQt(argc, argv);
    //return mainQtLinux(argc, argv);
}
#else
#include "defines.h"
int main(int argc, char *argv[])
{
    return mainLinux(argc, argv);
}
#endif
