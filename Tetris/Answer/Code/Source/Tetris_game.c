#include "Tetris_game.h"
#include "Tetris_Data.h"
#include "Tetris_Windows.h"
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

int grade = 0; //分数
int level = 1; //等级
int one = 0, two = 0, three = 0, four = 0; //消除行数
clock_t startTime; //游戏开始时间
clock_t timeInterval; //上次消除时间

Block cur_block; //当前方块
Block next_block; //下一个方块

//1.绘制游戏边框
void windowPrint(int x, int y)
{
    int i, j;
    for (i = 0; i < 25; i++)
    {
        for (j = 0; j < 26; j++)
        {
            if (windowShape[i][j] == 1)
            {
                setColor(9);
                setPos(x + j, y + i);
                printf("%2s", "██");
            }
        }
    }
}

//2.游戏初始化(放置最后，因为需要调用其他函数)
//void gameInit()


//3.打印操作说明
void printInfo()
{
    setColor(0x0a);
    setPos(33, 10);
    printf("操作说明:");
    setPos(33, 12);
    printf("1.按A键左移");
    setPos(33, 14);
    printf("2.按D键右移");
    setPos(33, 16);
    printf("3.按W键旋转");
    setPos(33, 18);
    printf("4.按S键落地");
}

//4.打印分数
void printGradeLevel(int line_num)
{
    clock_t timeNow = clock();
    int gradeNow = 0;
    double interval = (double) (timeNow - timeInterval) / CLOCKS_PER_SEC;

    //根据消行时间间隔判断基础分数
    if (line_num > 0)
    {
        if (interval > 10 )
        {
            gradeNow = 1;
        }
        else if (interval > 5)
        {
            gradeNow = 3;
        }
        else if (interval > 3)
        {
            gradeNow = 5;
        }
        else
        {
            gradeNow = 10;
        }
    }

    //根据消除行数翻倍分数
    switch(line_num)
    {
        case 1:
            gradeNow *= 1;
            one++;
            break;
        case 2:
            gradeNow *= 2;
            two++;
            break;
        case 3:
            gradeNow *= 4;
            three++;
            break;
        case 4:
            gradeNow *= 8;
            four++;
            break;
    }

    //根据时间提升等级
    double timeTotal = (double) (timeNow - startTime) / CLOCKS_PER_SEC;
    if (timeTotal < 120)
    {
        level = 1;
    }
    else if (timeTotal < 240)
    {
        level = 2;
    }
    else if (timeTotal < 480)
    {
        level = 3;
    }
    else
    {
        level = 4;
    }

    //根据等级调整分数
    gradeNow *= level;
    grade += gradeNow;

    //打印分数和等级
    setColor(0x0e);
    setPos(5, 6);
    printf("分数: %d", grade);
    setPos(5, 7);
    switch (level)
    {
        case 1:
            printf("等级: 新手");
            break;
        case 2:
            printf("等级: 普通");
            break;
        case 3:
            printf("等级: 困难");
            break;
        case 4:
            printf("等级: 噩梦");
            break;
    }

    //更新上次消除时间
    timeInterval = timeNow;

    setPos(3, 22);
    printf("C语言项目——俄罗斯方块");
}


//5.游戏计时(弃置)
//void gameTimer(clock_t startTime);

//6.左边框
void leftBorder()
{
    setColor(9);
    setPos(0, 0);
    printf("╔════════════════════════════╗\n");
    setPos(0, 1);
    printf("║                            ║\n");
    setPos(0, 2);
    printf("║                            ║\n");
    setPos(0, 3);
    printf("║                            ║\n");
    setPos(0, 4);
    printf("║                            ║\n");
    setPos(0, 5); 
    printf("║                            ║\n");
    setPos(0, 6);
    printf("║                            ║\n");
    setPos(0, 7);
    printf("║                            ║\n");
    setPos(0, 8);
    printf("║                            ║\n");
    setPos(0, 9);
    printf("║                            ║\n");
    setPos(0, 10);
    printf("║                            ║\n");
    setPos(0, 11);
    printf("║                            ║\n");
    setPos(0, 12);
    printf("║                            ║\n");
    setPos(0, 13);
    printf("║                            ║\n");
    setPos(0, 14);
    printf("║                            ║\n");
    setPos(0, 15);
    printf("║                            ║\n");
    setPos(0, 16);
    printf("║                            ║\n");
    setPos(0, 17);
    printf("║                            ║\n");
    setPos(0, 18);
    printf("║                            ║\n");
    setPos(0, 19);
    printf("║                            ║\n");
    setPos(0, 20);
    printf("║                            ║\n");
    setPos(0, 21);
    printf("║                            ║\n");
    setPos(0, 22);
    printf("║                            ║\n");
    setPos(0, 23);
    printf("║                            ║\n");
    setPos(0, 24);
    printf("╚════════════════════════════╝\n");
}

//7.打印方块
void printBlock(int x, int y, int shape, int state, int color)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][state][i][j] == 1)
            {
                setColor(color);
                setPos(x + j, y + i);
                printf("%2s", "██");
            }
        }
    }
}

//8.删除方块
void deleteBlock(int x, int y, int shape, int state)
{
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][state][i][j] == 1)
            {
                setPos(x + j, y + i);
                printf("%2s", "");
            }
        }
    }
}

//9.产生第一个方块
void startBlock()
{
    //第一个方块颜色/形态随机生成，位置固定
    //初始化cur_block
    //设置随机种子（根据当前时间）
    srand((unsigned) time(NULL));
    cur_block.x = 22;
    cur_block.y = 1;
    cur_block.shape = rand() % 7;
    cur_block.state = rand() % 4;
    cur_block.color = rand() % 15 + 1;

    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
}

//10.产生下一个方块
void nextBlock()
{
    //下一个方块颜色/形态随机生成，位置固定
    //初始化next_block  
    next_block.x = 33;
    next_block.y = 2;
    deleteBlock(next_block.x, next_block.y, next_block.shape, next_block.state);

    next_block.shape = rand() % 7;
    next_block.state = rand() % 4;
    next_block.color = rand() % 15 + 1;
    printBlock(next_block.x, next_block.y, next_block.shape, next_block.state, next_block.color);
}

//11.复制方块
int copyBlock()
{
    // 将 next_block 复制到 cur_block
    cur_block.x = 22;
    cur_block.y = 1;
    cur_block.shape = next_block.shape;
    cur_block.state = next_block.state;
    cur_block.color = next_block.color;

    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
    nextBlock();

    // 关键：检测新方块是否与固定方块重叠
    if (crash(cur_block.x, cur_block.y, cur_block.shape, cur_block.state) == -2)
    {
        return -2;   // 游戏结束
    }
    return 0;
}

//12.方块下移
int blockDown(int n)
{
    if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.state) == -1)
    {
        saveBlock();
        lineClear();
        updategame(n);
        if (copyBlock() == -2)   // 复制新块时发生顶端碰撞
            return -2;
        return -1;
    }
    else if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.state) == -2)
    {
        return -2;
    }
    else
    {
        deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state);
        cur_block.y++;
        printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
        return 0;
    }
}

//13.方块左移
void blockLeft()
{
    if (crash(cur_block.x-1, cur_block.y, cur_block.shape, cur_block.state) == -1)
    {
        //无法左移
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state);
    cur_block.x--;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
}

//14.方块右移
void blockRight()
{
    if (crash(cur_block.x+1, cur_block.y, cur_block.shape, cur_block.state) == -1)
    {
        //无法右移
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state);
    cur_block.x++;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
}

//15.方块旋转
void blockRotate()
{
    //通过数组下标改变变换形态
    if (crash(cur_block.x, cur_block.y, cur_block.shape, (cur_block.state + 1) % 4) == -1)
    {
        //无法旋转
        return;
    }
    deleteBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state);
    cur_block.state = (cur_block.state + 1) % 4;
    printBlock(cur_block.x, cur_block.y, cur_block.shape, cur_block.state, cur_block.color);
}

//16.方块落地
void bottomBlock(int n)
{
    while(1)
    {
        if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.state) == -1)
        {
            //碰撞保存消行刷新复制
            saveBlock();
            lineClear();
            updategame(n);
            copyBlock();
            return;
        }
        else if (crash(cur_block.x, cur_block.y + 1, cur_block.shape, cur_block.state) == -2)
        {
            // 游戏结束
            return;
        }
        else
        {
            cur_block.y++;
        }
    }
}

//17.碰撞检测
int crash(int x, int y, int shape, int state)
{
    //基于下一位置检测
    int i, j;
    for (i = 3; i >= 0; i--)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[shape][state][i][j] == 1)
            {
                if (windowShape[y + i][x + j - 15] == 1)
                {
                    //碰撞
                    if (x == 22 && y == 1)
                    {
                        //碰撞且游戏结束
                        return -2;
                    }
                    //碰撞但游戏未结束
                    return -1;
                }
            }
        }
    }
    //未碰撞
    return 0;
}

//18.保存方块
void saveBlock()
{
    //方块坐标对应界面坐标
    int i, j;
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (block[cur_block.shape][cur_block.state][i][j] == 1)
            {
                windowShape[cur_block.y + i][cur_block.x + j - 15] = 1;
            }
        }
    }
}

//19.刷新屏幕
void updategame(int n)
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j <= 14; j++)
        {
           switch (n)
           {
            case 1:
            if (windowShape[i][j] == 1)
            {
                setColor(3);
                setPos(j + 15, i);
                printf("%2s", "██");
            }
            else
            {
                setPos(j + 15, i);
                printf("%2s", "");
            }
            break;
            case 2:
            if (windowShape[i][j] == 1)           
            {
                setColor(0xce);
                setPos(j + 15, i);
                printf("%2s", "");
            }
            else
            {
                setColor(0x00);
                setPos(j + 15, i);
                printf("%2s", "");
                break;
            }
           }
        }
    }
}

//20.游戏暂停(废弃)
/*void gamePause()
{
    while(1)
    {
        if (getch() == 32)
        {
            return;
        }
    }
}*/

//21.消除检测
void lineClear()
{
    //遍历检测是否满行
    int i, j, line_num = 0;
    for (i = 23; i > 0; i--)
    {
        int count = 0;
        for (j = 1; j < 15; j++)
        {
            count += windowShape[i][j];
        }
        if (count == 14)
        {
            line_num++;
            lineDown(i);
            i++;
        }
    }
    if (line_num > 0)
    {
        printGradeLevel(line_num);
    }
}

//22.消除行下移
void lineDown(int line)
{
    //将line行以上的行下移一行
    int i, j;
    for (i = line; i > 1; i--)
    {
        for (j = 1; j <= 14; j++)
        {
            windowShape[i][j] = windowShape[i-1][j];
        }
    }
     //将第一行置空
    for (j = 1; j <= 14; j++)
    {
        windowShape[0][j] = 0;
    }
}

//23.游戏结束动画
void printOver()
{
    int i, j;
    for (i = 23; i > 0; i--)
    {
        for (j = 1; j < 15; j++)
        {
            setColor(0x2e);
            setPos(j + 15, i);
            printf("$$");
            Sleep(5);//动画效果(停顿)
        }
    }
}

//24.游戏重新开始
void printFinish()
{
    setColor(0x0f);
    setPos(20, 8);
    printf("游戏结束!");
    setPos(20, 10);
    printf("按Y键重新开始");
    setPos(20, 11);
    printf("按N键退出游戏");
    
    //检测用户输入
    switch (getch())
    {
        case 'Y':
        case 'y':
        {
            againGame();
            break;
        }
        case 'N':
        case 'n':
        {
            //mcisendstring(TEXT("stop a"), NULL, 0, NULL);
            endGame();
            break;
        }
        default:
        {
            printFinish();
        }
    }
}

//25.重新开始游戏
void againGame()
{
    //重置分数等级游戏状态
    level = 1;
    grade = 0;
    one = 0;
    two = 0;
    three = 0;
    four = 0;

    int i, j;
    for (i = 0; i < 24; i++)
    {
        for (j = 1; j < 15; j++)
        {
            windowShape[i][j] = 0;
        }
    }
    system("cls"); //清屏
    gameInit();
}

//26.游戏结束
void endGame()
{
    system("cls");
    
    setPos(21, 8);
    setColor(12);
    printf("Game Over!");

    setPos(21, 10);
    printf("分数: %d", grade);

    setPos(21, 12);
    if (grade < 5)
    {
        printf("段位: 倔强青铜");
    }
    else if (grade < 15)
    {
        printf("段位: 不屈白银");
    }
    else if (grade < 30)
    {
        printf("段位: 荣耀黄金");
    }
    else if (grade < 50)
    {
        printf("段位: 尊贵铂金");
    }
    else if (grade < 80)
    {
        printf("段位: 永恒钻石");
    }
    else if (grade < 120)
    {
        printf("段位: 至尊星耀");
    }
    else
    {
        printf("段位: 最强王者");
    }

    setPos(21, 14);
    printf("消除一行: %d", one);
    setPos(21, 16);
    printf("消除两行: %d", two);
    setPos(21, 18);
    printf("消除三行: %d", three);
    setPos(21, 20);
    printf("消除四行: %d", four);

    setPos(8, 5);
    setColor(11);
    printf("+------------------------");

    setPos(17, 5);
    setColor(14);
    printf("o00o");

    setPos(19, 5);
    setColor(11);
    printf("---------");

    setPos(24, 5);
    setColor(14);
    printf("---");

    setPos(26, 5);
    setColor(11);
    printf("---------");

    setPos(31, 5);
    setColor(14);
    printf("o00o");

    setPos(33, 5);
    setColor(11);
    printf("------------------------");

    for (int i = 6; i <= 24; i++)
    {
        setPos(8, i);
        setColor(11);
        printf("|");

        setPos(41, i);
        setColor(11);
        printf("|");
    }

    setPos(8, 25);
    printf("+------------------------");

    setPos(23, 25);
    setColor(14);
    printf("+ + +");

    setPos(28, 25);
    setColor(11);
    printf("------------------------+\n\n");

    getch();
    exit(0);
}

//27.打印开始界面
void printStart(int x, int y)
{
    //随机图案颜色
    int color = rand() % 15 + 1;
    setColor(color);
    setPos(x, y);
    printf("██████████   ██████████    ██████████       ██████       ████████");
    setPos(x, y + 1);
    printf("    ██       ██            ██         ██      ██      ██");
    setPos(x, y + 2);
    printf("    ██       ████████      ████████           ██          ██");
    setPos(x, y + 3);
    printf("    ██       ██            ██    ██           ██              ██");
    setPos(x, y + 4); 
    printf("    ██       ██████████    ██          ██   ██████     ████████");


    setPos(25, 15);
    printf("按Enter键开始游戏!");
}

//28.清除开始动画
void deleteStart(int x, int y)
{
    int i, j;
    for (i =y; i <= y + 5; i++)
    {
        for (j = x; j <= x + 35; j++)
        {
            setPos(j, i);
            printf("%2s", "");
        }
    }
}

//29.动画效果
void gameAnimation()
{
    clock_t time1, time2;
    time1 = clock();
    int x = 5;
    printStart(x, 5);
    while(1)
    {
        time2 = clock();
        if ((time2 - time1) > 200)
        {
            deleteStart(x, 5);
            printStart(++x, 5);
            time1 = time2;
            if (x >= 22)
            {
                deleteStart(x, 5);
                x = 5;
            }
        }
        if (kbhit())
        {
            if (getch() == 13)
            {
                break;
            }
            else
            {
                setPos(22, 17);
                int color = rand() % 15 + 1;
                printf("输入有误！请按Enter键开始游戏!");
                getch();
                system("cls");
            }
        }
    }
    system("cls");
}

//31.游戏主循环
void gameLoop(float time, int n)
{
    //游戏开始时间
    startTime = clock();
    timeInterval = startTime;

    clock_t time1, time2;
    time1 = clock();

    while (1)
    {
        //检测按键
        if (kbhit())
        {
            switch(getch())
            {
                //方块变形
                case 'w':
                case 'W':
                case 72:
                    {
                        blockRotate();
                        break;
                    }
                
                //方块左移
                case 'a':
                case 'A':
                case 75:
                    {
                        blockLeft();
                        break;
                    }
                //方块右移
                case 'd':
                case 'D':
                case 77:
                    {
                        blockRight();
                        break;
                    }
                //方块落地
                case 's':
                case 'S':
                case 80:
                    {
                        bottomBlock(1);
                        break;
                    }
            }
        }
        //方块自动下落
        time2 = clock();
        if ((time2 - time1) > time * CLOCKS_PER_SEC / level)
        {
            if (blockDown(n) == -2)
            {
                printOver();
                printFinish();
                break;
            }
            time1 = time2;
        }

    }


}

//30.游戏初始化
void gameInit()
{
    //句柄初始化
    initHandle();
    
    //打开音乐文件
    //mciSendstring("open alias a", NULL, 0, NULL);

    //播放音乐
    //mciSendstring(TEXT("play a"), NULL, 0, NULL);

    gameAnimation();
    system("cls");
    windowPrint(15, 0);
    leftBorder();
    printInfo();
    startBlock();

    printGradeLevel(0);
    grade = 0;

    nextBlock();

    gameLoop(0.65, 1);;

}