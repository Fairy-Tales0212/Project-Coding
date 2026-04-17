#include "Tetris_Windows.h"

HANDLE handle;

///1.初始化句柄
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

///2.设置颜色
void setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}

///3.设置光标位置
void setPos(int x, int y)
{
    COORD coord = (COORD){.X = x * 2, .Y = y};
    SetConsoleCursorPosition(handle, coord);
}
///4.隐藏光标
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;//隐藏光标
    info.dwSize = 1;//光标大小
    SetConsoleCursorInfo(handle, &info);
}
