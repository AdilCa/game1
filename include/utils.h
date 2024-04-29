//
// Created by caowei on 2024/4/28.
//

#ifndef GAME1_UTILS_H
#define GAME1_UTILS_H

#include <random>
#include <vector>
#include <easyx.h>

 // 随机数生成器
int uniformIntRand(int a, int b);                           // 生成均匀整形随机数，区间为[a, b]
std::vector<int> uniformIntRandArr(int a, int b, int size); // 生成均匀整形随机数组，区间为[a, b]， 长度为size

#endif //GAME1_UTILS_H
