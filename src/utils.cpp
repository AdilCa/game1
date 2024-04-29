//
// Created by caowei on 2024/4/29.
//

#include "utils.h"
#include <random>
#include <vector>

// 随机数生成器
int uniformIntRand(int a, int b) {
    // 生成均匀整形随机数，区间为[a, b]
    std::mt19937 rng;
    std::random_device rd;
    rng.seed(rd());
    std::uniform_int_distribution uniIntGen(a, b);
    return uniIntGen(rng);
}
std::vector<int> uniformIntRandArr(int a, int b, int size) {
    // 生成均匀整形随机数组，区间为[a, b]， 长度为size
    std::vector<int> randArr;
    for (int i = 0; i < size; ++i) {
        randArr.push_back(uniformIntRand(a, b));
    }
    return randArr;
}