#pragma once

/*游戏逻辑模块*/

#include <stdio.h>
#include <time.h>

//方块结构体
typedef struct {
    int shape;   //方块类型
    int color;   //方块颜色
    int state;  //方块旋转状态
    int x;      //方块左上角x坐标
    int y;      //方块左上角y坐标
} Block;

///1.绘制游戏边框
void windowPrint(int x, int y);

///2.游戏初始化
void gameInit();

///3.打印操作说明
void printInfo();

///4.打印分数
void printGradeLevel(int line_num);

///5.游戏计时
void gameTimer(clock_t startTime);

///6.左边框
void leftBorder();

///7.打印方块
void printBlock(int x, int y, int shape, int state, int color);

///8.删除方块
void deleteBlock(int x, int y, int shape, int state);

///9.产生第一个方块
void startBlock();

///10.产生下一个方块
void nextBlock();

///11.复制方块
int copyBlock();

///12.方块下移
///返回值：1.成功下移 0.无法下移
int blockDown();

///13.方块左移
void blockLeft();

///14.方块右移
void blockRight();

///15.方块旋转
void blockRotate();

///16.方块落地
void bottomBlock();

///17.碰撞检测
int crash(int x, int y, int shape, int state);

///18.保存方块
void saveBlock();

///19.刷新屏幕
void updategame(int n);

///20.游戏暂停
void gamePause();

///21.消除检测
void lineClear();

///22.消除行下移
void lineDown(int line);

//23.游戏结束动画
void printOver();

//24.游戏重新开始
void printFinish();

//25.重新开始游戏
void againGame();

//26.游戏结束
void endGame();

//27.打印开始界面
void printStart(int x, int y);

//28.清除开始动画
void deleteStart(int x, int y);

//29.动画效果
void gameAnimation();

//31.游戏主循环
void gameLoop(float time, int n);
