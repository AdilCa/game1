//
// Created by caowei on 2024/4/29.
//

#include "game.h"
#include "game_matrix.h"
#include "game_ui.h"
#include "utils.h"
#include <iostream>
#include <conio.h>

using namespace std;

Color colorArr[11] = {twoTo1, twoTo2, twoTo3, twoTo4, twoTo5, twoTo6,
                      twoTo7, twoTo8, twoTo9, twoTo10, twoTo11};

Game2048::Game2048() {
    // 数值初始化
    this->maxGrid = 4;
    this->maxPower = 11;
    this->score = 0;
    this->bestScore = 0;
    this->valArr.push_back(0);
    for (int i = 1; i < this->maxPower; ++i) {
        // 初始化可能值数组，除了第一个为零，其余值都是2的索引次幂
        this->valArr.push_back(pow(2, i));
    }

    // UI初始化
    this->gridWidth = 100;
    this->interval = 15;
    this->fontSize = 60;
    this->margin = 10;
    this->controlPartHeight = 80;
    this->windowsWidth = this->maxGrid * this->gridWidth + (this->maxGrid + 1) * this->interval + 2 * this->margin;
    this->windowsHeight = this->windowsWidth + this->controlPartHeight;
    this->scoreBoxWidth = this->gridWidth * 2 + this->interval;
    this->scoreBoxHeight = this->controlPartHeight / 2;
    this->restartButtonWidth = this->gridWidth+this->interval;
    this->restartButtonHeight = this->controlPartHeight / 2;
    this->gameBox = {this->margin, this->margin + this->controlPartHeight};
    this->bestScorePos = {0, 0};
    this->scorePos = {0, scoreBoxHeight};
    this->restartButtonPos = {this->windowsWidth - (2*this->gridWidth + this->interval + this->restartButtonWidth) / 2, (this->controlPartHeight - this->restartButtonHeight) / 2};
    for (int row = 0; row < this->maxGrid; ++row) {
        this->ltPos.push_back(vector<Point>(this->maxGrid, {0, 0}));
        for (int col = 0; col < this->maxGrid; ++col) {
            // 初始化每个格子的位置
            this->ltPos[row][col].x = col*this->gridWidth + (col+1)*this->interval + this->gameBox.x;
            this->ltPos[row][col].y = row*this->gridWidth + (row+1)*this->interval + this->gameBox.y;
        }
    }
}

void Game2048::GameInit() {
    // 数值初始化
    this->score = 0;
    this->gridMat.zeros(this->maxGrid);
    this->gridMat.resetMoveFlag();
    for (int i = 0; i < 2; ++i){
        // 初始化两个随机位置
        vector<Point> emptyPos = this->gridMat.ZerosInd();
        CreateNumber(emptyPos);
    }

    // 窗口初始化
    initgraph(this->windowsWidth, this->windowsHeight, 1);
    setbkcolor(windowsBack);
    cleardevice();
    this->mainWindowsBuffer = GetImageBuffer();
    this->Draw();
}

// 生成新数
int Game2048::NewNum(int mode) {
    // 控制生成新数的模式
    if (mode == one)
        return 2;
    else if (mode == two)
        return pow(2, uniformIntRand(1, 2));
    else {
        cout << "New Number Mode Error!" << endl;
        return 0;
    }
}
void Game2048::CreateNumber(std::vector<Point> emptyPos) {
    // 在随机空白位置生成新数
    int posInd = uniformIntRand(0, emptyPos.size()-1);  // 从空格序列中提取一个
    this->gridMat.setVal(emptyPos[posInd].x, emptyPos[posInd].y, this->NewNum(this->genMode));
}
void Game2048::CreateNumber(int row, int col) {
    // 在指定位置生成新数
    this->gridMat.setVal(row, col, this->NewNum(this->genMode));
}

// 更新数据
void Game2048::RefreshScore() {
    if (this->score > this->bestScore)
        this->bestScore = this->score;
}

// 画界面
void Game2048::Draw() {
    // 最佳分数
    SubWidget bestScoreBox(this->scoreBoxWidth, this->scoreBoxHeight, windowsBack, BlockBoard::off);
    bestScoreBox.setFontsize(this->scoreBoxHeight);
    bestScoreBox.setText(" best : ", TextPosition::left);
    bestScoreBox.setText(to_string(this->bestScore), TextPosition::right);
    bestScoreBox.setPosition(this->bestScorePos.x, this->bestScorePos.y);
    // 当前分数
    SubWidget scoreBox(this->scoreBoxWidth, this->scoreBoxHeight, windowsBack, BlockBoard::off);
    scoreBox.setFontsize(this->scoreBoxHeight);
    scoreBox.setText("score: ", TextPosition::left);
    scoreBox.setText(to_string(this->score), TextPosition::right);
    scoreBox.setPosition(this->scorePos.x, this->scorePos.y);
    // 重新开始
    SubWidget restartButton(this->restartButtonWidth, this->restartButtonHeight, restartBack, BlockBoard::off);
    restartButton.setText("RESTART", center);
    restartButton.setPosition(restartButtonPos.x, restartButtonPos.y);
    // 游戏块
    SubWidget gameBox(this->maxGrid * this->gridWidth + (this->maxGrid + 1) * this->interval,
                      this->maxGrid * this->gridWidth + (this->maxGrid + 1) * this->interval,
                      back, BlockBoard::off);
    gameBox.setPosition(this->gameBox.x, this->gameBox.y);
    // 游戏块内每个小方块
    for (int row = 0; row < this->maxGrid; ++row) {
        for (int col = 0; col < this->maxGrid; ++col) {
            // 上面两层循环遍历每格中的数值
            for (int i = 0; i < this->maxPower; ++i) {
                // 这个循环用于检查格内的值与可能值数组中哪个相等，并取其索引以获得该值对应的格子颜色
                if (this->gridMat(row, col) == this->valArr[i]) {
                    SubWidget block(this->gridWidth, this->gridWidth, colorArr[i], BlockBoard::off);
                    if (this->gridMat(row, col) != 0)
                        block.setText(to_string(this->gridMat(row, col)), center);
                    block.setPosition(this->ltPos[row][col].x, this->ltPos[row][col].y);
                    break;
                }
            }
        }
    }
}

bool Game2048::ClickRestart() {
    ExMessage m;
    m = getmessage(EX_MOUSE);
    if (m.x >= this->restartButtonPos.x && m.x <= this->restartButtonPos.x+this->restartButtonWidth
    &&  m.y >= this->restartButtonPos.y && m.y <= this->restartButtonPos.y+this->restartButtonHeight
    &&  m.message == WM_LBUTTONDOWN) {
        closegraph();
        this->GameInit();
        return true;
    }
    return false;
}

bool Game2048::Start() {
    this->GameInit();
    while (true) {
        this->Gaming();
    }
}

void Game2048::Gaming() {
    ExMessage m;
    while (true) {
        m = getmessage(EX_KEY | EX_MOUSE);
        switch (m.message) {
            case WM_KEYDOWN:
                if (checkSign(m.vkcode, {VK_W, VK_UP, VK_NUMPAD8})) {
                    this->gridMat.MoveUp();
                }
                else if (checkSign(m.vkcode, {VK_A, VK_LEFT, VK_NUMPAD4})) {
                    this->gridMat.MoveLeft();
                }
                else if (checkSign(m.vkcode, {VK_S, VK_DOWN, VK_NUMPAD2})) {
                    this->gridMat.MoveDown();
                }
                else if (checkSign(m.vkcode, {VK_D, VK_RIGHT, VK_NUMPAD6})) {
                    this->gridMat.MoveRight();
                }
                break;
            case WM_LBUTTONDOWN:
                if (m.x >= this->restartButtonPos.x && m.x <= this->restartButtonPos.x+this->restartButtonWidth
                    &&  m.y >= this->restartButtonPos.y && m.y <= this->restartButtonPos.y+this->restartButtonHeight
                    &&  m.message == WM_LBUTTONDOWN) {
                    closegraph();
                    this->GameInit();
                }
            default:
                break;
        }
        if (this->gridMat.checkMove()) {
            // 判断是否有效移动
            this->score = this->gridMat.getRecord();
            CreateNumber(this->gridMat.ZerosInd());
            this->Draw();
            this->gridMat.resetMoveFlag();  // 不知道为什么，一个输入会运行两次循环，所以在这重置flag，令其不重复生成新数
        }
        if (this->CheckEnd())
            break;
    }
}

bool Game2048::CheckEnd() {
    auto tmpMat = this->gridMat.getMatrix();
    tmpMat.emplace_back(this->maxGrid, -1);
    for (int row = 0; row < this->maxGrid; ++row) {
        tmpMat[row].emplace_back(-1);
        for (int col = 0; col < this->maxGrid; ++col) {
            if (tmpMat[row][col] == 0 || tmpMat[row+1][col] == tmpMat[row][col] || tmpMat[row][col+1] == tmpMat[row][col])
                return false;
        }
    }
    return true;
}