//
// Created by caowei on 2024/4/29.
//

#ifndef GAME1_GAME_UI_H
#define GAME1_GAME_UI_H

#include <easyx.h>
#include <string>
#include <vector>

enum Color {
    // 初始化颜色
    zero    = RGB(205, 193, 180),
    twoTo1  = RGB(238, 228, 218),
    twoTo2  = RGB(237, 224, 200),
    twoTo3  = RGB(242, 177, 121),
    twoTo4  = RGB(245, 149, 99),
    twoTo5  = RGB(246, 124, 95),
    twoTo6  = RGB(246, 94, 59),
    twoTo7  = RGB(242, 177, 121),
    twoTo8  = RGB(237, 204, 97),
    twoTo9  = RGB(255, 0, 128),
    twoTo10 = RGB(145, 0, 72),
    twoTo11 = RGB(242, 17, 158),
    back    = RGB(187, 173, 160),
    windowsBack = RGB(250, 248, 239),
};

enum TextPosition {center, left, right, top, bottom, leftTop, leftBottom, rightTop, rightBottom};

enum BlockBoard {on, off};

class SubWidget {
    // 将图块封装
private:
    IMAGE subImg;           // 用于画图的子图窗
    int blockHeight;        // 图块高
    int blockWidth;         // 图块宽度
    int fontSize;           // 文本高度

public:
    SubWidget(int width, int height, Color fillColor);  // 初始化一个矩形普通图块
    SubWidget(int radius, Color fillColor);             // 初始化一个圆形无边框普通图块

    IMAGE getImg();     // 获取当前图层

    void setText(std::string text, TextPosition txtPos);       // 放置文本内容
    void setFontsize(int fontsize);                 // 设置字体高度

    void setPosition(int x, int y);                     // 放置按钮在图窗下
};

bool checkSign(int m, std::vector<int> signArr);  // 判断输入信号

#endif //GAME1_GAME_UI_H
