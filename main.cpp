#include "mainFunctions.h"
#ifdef _QT_COMPILE
int main(int argc, char *argv[])
{
    return mainQt(argc, argv);
}
#else
#include "defines.h"
Game game;
void runGame() {

}
int main(int argc, char *argv[])
{

}
#endif
