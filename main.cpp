#include "mainFunctions.h"
#ifdef _QT_COMPILE
#include <iostream>
using namespace std;
void func(int x)
{
    cout << x ;
}
int main(int argc, const char * argv[]) {

    void (*n)(int);
    n = &func;
    (*n)( 5 );
    n( 8 );
    return 0;
}
//int main(int argc, char *argv[])
//{

//    return mainQt(argc, argv);
//    //return mainQtLinux(argc, argv);
//}
#else
#include "defines.h"
int main(int argc, char *argv[])
{
    return mainLinux(argc, argv);
}
#endif
