//
// Created by caowei on 2024/4/28.
//

#ifndef GAME1_GAME_H
#define GAME1_GAME_H

#include "game_matrix.h"
#include "game_ui.h"
#include <vector>
#include <easyx.h>
#include <string>

enum GenNewNumMode {one, two};  // 生成新数的模式

enum MoveDir {moveUp, moveDown, moveLeft, moveRight};   // 移动方向

enum KeyBoard {VK_W = 0x57, VK_S = 0x53, VK_A = 0x41, VK_D = 0x44,};

class Game2048 {
    // 整个游戏相关内容，包括数值，UI，流程控制
private:
    // 数值相关
    GenNewNumMode genMode = one;           // 生成新填充数的模式
    int maxGrid;                           // 尺寸
    int maxPower;                          // 最大幂次
    std::vector<int> valArr;              // 格内所有可能值
    Matrix2048 gridMat;                    // 每格内的值
    int score;                            // 得分
    int bestScore;                        // 最佳得分

    // UI相关
    int gridWidth;                         // 每格宽度
    int interval;                          // 两格间隔宽度
    int fontSize;                          // 数字高度
    int controlPartHeight;                 // 控制部分的高度
    int margin;                            // 游戏框与窗口边界距离
    int windowsWidth;                      // 窗体宽度
    int windowsHeight;                     // 窗体高度
    Point gameBox;                         // 游戏窗口左上角坐标
    Point bestScorePos;                   // 显示最佳分数
    Point scorePos;                       // 显示分数
    int scoreBoxWidth;                     // 分数块宽度
    int scoreBoxHeight;                    // 分数快高度
    std::vector<std::vector<Point>> ltPos; // 每格左上角坐标

public:
    // 初始化
    Game2048();                             // 默认初始化
    Game2048(int maxGrid, int maxPower);    // 带参初始化
    void GameInit();                          // 手动初始化

    // 画UI
    void Draw();                            // 根据当前情况画界面

    // 在特定位置生成新数
    int NewNum(int mode);                               // 根据模式生成新数
    void CreateNumber(std::vector<Point> emptyPos);     // 在空白位置随机生成新的数
    void CreateNumber(int row, int col);                // 在指定位置生成新的数

    // 更新最高分数
    void RefreshScore();

    // 游戏流程控制
    bool Start();              // 游戏流程控制
    void Gaming();              // 游戏进行中
    bool ClickRestart();                // 点击重新开始按钮重启游戏
    bool CheckEnd();                    // 判断游戏是否结束
};

#endif //GAME1_GAME_H
