#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Tetris_game.h"
int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    gameInit();
    system("pause");
    return 0;
}