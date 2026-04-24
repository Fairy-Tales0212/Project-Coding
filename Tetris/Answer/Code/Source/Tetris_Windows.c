#include "Tetris_Windows.h"

HANDLE handle;

//1.初始化句柄
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}

//2.设置颜色
void setColor(int color)
{
    SetConsoleTextAttribute(handle, color);
}

//3.设置光标位置
void setPos(int x, int y)
{
    COORD coord = (COORD){.X = x * 2, .Y = y};
    SetConsoleCursorPosition(handle, coord);
}

//4.隐藏光标
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;//隐藏光标
    info.dwSize = 1;//光标大小
    SetConsoleCursorInfo(handle, &info);
}

//5.设置字体
void setConsoleFontToTrueType()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) 
    {
        return;
    }

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    if (!GetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) 
    {
        cfi.dwFontSize.Y = 24;
    }

    // 配置字体属性
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    cfi.dwFontSize.X = 0; 
    wcscpy_s(cfi.FaceName, LF_FACESIZE, L"Consolas");

    // 尝试设置字体
    if (!SetCurrentConsoleFontEx(hConsole, FALSE, &cfi)) 
    {
    }
}

//6.控制台窗口尺寸
void setConsoleSize(int cols, int lines) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT windowRect = {0, 0, cols - 1, lines - 1};
    COORD bufferSize = {cols, lines};

    SetConsoleScreenBufferSize(hConsole, bufferSize);
    SetConsoleWindowInfo(hConsole, TRUE, &windowRect);
    SetConsoleScreenBufferSize(hConsole, bufferSize);
}
