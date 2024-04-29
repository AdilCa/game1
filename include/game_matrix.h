//
// Created by caowei on 2024/4/29.
//

#ifndef GAME1_GAME_MATRIX_H
#define GAME1_GAME_MATRIX_H

#include <vector>

struct Point {int x; int y;};

class Matrix2048 {
    // 将2048中的数封装成类
private:
    std::vector<std::vector<int>> matrix;
    int size;
    int record;
    bool moveFlag;

public:
    // 初始化
    Matrix2048();
    Matrix2048(int size, int num);
    Matrix2048(std::vector<std::vector<int>> initMat);
    void zeros(int size);

    // 信息查看
    void showMat();                 // 打印矩阵
    int getSize() const;
    int getRecord() const;
    bool checkMove();
    std::vector<int> operator () (int x) const;

    int operator () (int x, int y) const;
    std::vector<std::vector<int>> getMatrix(); // 获取数组
    std::vector<Point> ZerosInd();

    // 赋值操作
    void setVal(int x, int y, int val);
    void setVal(int x, std::vector<int> val);
    void resetMoveFlag();

    // 矩阵旋转
    void RotateClockWise ();        // 方阵顺时针旋转90°
    void RotateCounterClockWise (); // 方阵逆时针旋转90°

    // 矩阵移动
    void MoveLeft();                // 矩阵左移
    void MoveRight();               // 矩阵右移
    void MoveUp();                  // 矩阵上移
    void MoveDown();                // 矩阵下移
};

#endif //GAME1_GAME_MATRIX_H
