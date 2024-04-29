//
// Created by caowei on 2024/4/29.
//

#include "game_ui.h"

// 初始化
SubWidget::SubWidget(int width, int height, Color fillColor, BlockBoard mode) {
    // 矩形图块
    this->blockWidth = width;
    this->blockHeight = height;
    this->fontSize = this->blockHeight * 0.5;
    this->subImg.Resize(width, height);
    SetWorkingImage(&this->subImg);
    setfillcolor(fillColor);
    if (mode == BlockBoard::on)
        rectangle(0, 0, width, height);
    else
        solidrectangle(0, 0, width, height);
}
SubWidget::SubWidget(int radius, Color fillColor, BlockBoard mode) {
    // 圆形图块
    this->blockWidth = radius;
    this->blockHeight = radius;
    this->subImg.Resize(radius, radius);
    SetWorkingImage(&this->subImg);
    setfillcolor(fillColor);
    if (mode == BlockBoard::on)
        circle(radius, radius, radius);
    else
        solidcircle(radius, radius, radius);
}

IMAGE SubWidget::getImg() {
    return this->subImg;
}
int SubWidget::getWidth() {
    return this->blockWidth;
}
int SubWidget::getHeight() {
    return this->blockHeight;
}
DWORD *SubWidget::getImgBuffer() {
    return GetImageBuffer(&this->subImg);
}

// 文本设置
void SubWidget::setFontsize(int fontsize) {
    this->fontSize = fontsize;
}
void SubWidget::setText(std::string text, TextPosition txtPos) {
    // 添加文本
    SetWorkingImage(& this->subImg);
    settextstyle(this->fontSize, 0, "Forte");
    settextcolor(RGB(0 ,0, 0));
    setbkmode(TRANSPARENT);
    int txtWidth = textwidth(text.c_str());
    int txtHeight = textheight(text.c_str());
    int centerX = (this->blockWidth - txtWidth) / 2;
    int centerY = (this->blockHeight - txtHeight) / 2;
    switch (txtPos) {
        case center:
            outtextxy(centerX, centerY, text.c_str());
            break;
        case left:
            outtextxy(0, centerY, text.c_str());
            break;
        case right:
            outtextxy(this->blockWidth - txtWidth, centerY, text.c_str());
            break;
        case top:
            outtextxy(centerX, 0, text.c_str());
            break;
        case bottom:
            outtextxy(centerX, this->blockHeight - txtHeight, text.c_str());
            break;
        case leftTop:
            outtextxy(0, 0, text.c_str());
            break;
        case leftBottom:
            outtextxy(0, this->blockHeight - txtHeight, text.c_str());
            break;
        case rightTop:
            outtextxy(this->blockWidth - txtWidth, 0, text.c_str());
            break;
        case rightBottom:
            outtextxy(this->blockWidth - txtWidth, this->blockHeight - txtHeight, text.c_str());
        case halfTop:
            outtextxy(centerX, centerY - this->blockHeight / 4, text.c_str());
        default:
            break;
    }
}

void SubWidget::setPosition(int x, int y) {
    SetWorkingImage();
    putimage(x, y, &this->subImg);
}

// 界面相关函数
bool checkSign(int m, std::vector<int> signArr) {
    for (auto sign : signArr) {
        if (m == sign)
            return true;
    }
    return false;
}