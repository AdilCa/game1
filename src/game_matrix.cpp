//
// Created by caowei on 2024/4/29.
//

#include "game_matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

// 初始化
Matrix2048::Matrix2048() {
    // 定义初始化
    this->matrix;
    this->size = 0;
    this->record = 0;
}
Matrix2048::Matrix2048(int size, int num) {
    // 简单初始化
    this->size = size;
    this->record = 0;
    for (int i = 0; i < this->size; ++i) {
        this->matrix.emplace_back(this->size, num);
    }
}
Matrix2048::Matrix2048(std::vector<std::vector<int>> initMat) {
    // 含参初始化
    this->matrix = initMat;
    this->size = this->matrix.size();
    this->record = 0;
}
void Matrix2048::zeros(int size) {
    this->size = size;
    this->matrix = {};
    for (int i = 0; i < this->size; ++i) {
        this->matrix.emplace_back(this->size, 0);
    }
}

// 信息查看
void Matrix2048::showMat() {
    // 打印矩阵
    string eleLineSpe = " -----";
    string lineSpe = "";
    for (int i = 0; i < this->size; ++i) {
        lineSpe += eleLineSpe;
    }
    for (auto row : this->matrix) {
        cout << lineSpe << endl;
        for (auto num : row) {
            cout << '|' << setw(5) << num;
        }
        cout << '|' << endl;
    }
    cout << lineSpe << endl;
}
int Matrix2048::getSize() const {
    return this->size;
}
int Matrix2048::getRecord() const {
    return this->record;
}
std::vector<int> Matrix2048::operator()(int x) const {
    return this->matrix[x];
}
int Matrix2048::operator()(int x, int y) const {
    return this->matrix[x][y];
}
std::vector<std::vector<int>> Matrix2048::getMatrix() {
    return this->matrix;
}
std::vector<Point> Matrix2048::ZerosInd() {
    // 获取值为零的坐标数组
    vector<Point> emptyPos;
    for (int row = 0; row < this->size; ++row) {
        for (int col = 0; col < this->size; ++col) {
            if (this->matrix[row][col] == 0) {
                emptyPos.push_back({row, col});
            }
        }
    }
    return emptyPos;
}
bool Matrix2048::checkMove() {
    return this->moveFlag;
}

// 赋值操作
void Matrix2048::setVal(int x, int y, int val) {
    this->matrix[x][y] = val;
}
void Matrix2048::setVal(int x, std::vector<int> val) {
    this->matrix[x] = val;
}
void Matrix2048::resetMoveFlag() {
    this->moveFlag = false;
}

// 方阵顺时针旋转90°
void Matrix2048::RotateClockWise() {
    int n = this->matrix.size();
    auto tmpMat = this->matrix;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tmpMat[j][n-1-i] = this->matrix[i][j];
        }
    }
    this->matrix = tmpMat;
}
// 方阵逆时针旋转90°
void Matrix2048::RotateCounterClockWise () {
    int n = this->matrix.size();
    auto tmpMat = this->matrix;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            tmpMat[n-1-j][i] = this->matrix[i][j];
        }
    }
    this->matrix = tmpMat;
}
// 矩阵左移
void Matrix2048::MoveLeft() {
    this->moveFlag = false;
    for (int row = 0; row < this->size; ++row) {
        std::vector<bool> merged(this->size, false);    // 记录该行每格参与合成与否
        for (int col = 1; col < this->size; ++col) {
            // 因为第一列一定不会动，所以不从第一列开始遍历
            if (this->matrix[row][col] == 0)
                // 若该数为零，则跳过，不进行操作
                continue;
            for (int i = col-1; i >= 0; --i) {
                // 若该数左边为零，则左移
                if (this->matrix[row][i] == 0) {
                    this->matrix[row][i] = this->matrix[row][i+1];
                    this->matrix[row][i+1] = 0;
                    this->moveFlag = true;
                }
                    // 若该数与左边相等，且两数在本轮操作中都未参与合成，则向左合并
                else if (!merged[i] && !merged[i+1] && this->matrix[row][i] == this->matrix[row][i+1]) {
                    this->matrix[row][i] += this->matrix[row][i+1];
                    this->matrix[row][i+1] = 0;
                    merged[i] = true;
                    this->record += this->matrix[row][i];
                    this->moveFlag = true;
                }
                    // 否则结束该数的移动
                else
                    break;
            }
        }
    }
}
// 矩阵上移
void Matrix2048::MoveUp() {
    this->RotateCounterClockWise();
    this->MoveLeft();
    this->RotateClockWise();
}
// 矩阵右移
void Matrix2048::MoveRight() {
    this->RotateCounterClockWise();
    this->RotateCounterClockWise();
    this->MoveLeft();
    this->RotateClockWise();
    this->RotateClockWise();
}
// 矩阵下移
void Matrix2048::MoveDown() {
    this->RotateClockWise();
    this->MoveLeft();
    this->RotateCounterClockWise();
}
