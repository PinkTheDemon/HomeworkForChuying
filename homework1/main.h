#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>

#include "leetcode46.h"
#include "leetcode120.h"
#include "leetcode1823.h"

void printNums(int* nums, int numsSize);
void printNumsOfNums(int** nums, int numsSize, int* numsColSize);
void Free2ndPtr(int** ptr, int ptrSize);
void test1823();
void test46();
void test120();

#endif