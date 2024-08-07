#pragma once

#ifndef _IO_H_
#define _IO_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#include <tchar.h>



int getNumber(int max); //输入数字

double getDouble(double max);

void getText(wchar_t* str); //输入文字


bool getNumberInBox(int max, int* target, const wchar_t* line);
bool getDoubleInBox(double max, double* target,  wchar_t* line);
bool getTextInBox(wchar_t* target, const wchar_t* line);

/*
显示菜单并提供选择
参数：(wchar_t*)标题，(int)选项数量，(wchar_t*)选项一，(wchar_t*)选项二...
返回：选项对应的数字
*/
int showMenu(const wchar_t* title, int optNum, ...);








#endif
