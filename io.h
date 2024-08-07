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



int getNumber(int max); //��������

double getDouble(double max);

void getText(wchar_t* str); //��������


bool getNumberInBox(int max, int* target, const wchar_t* line);
bool getDoubleInBox(double max, double* target,  wchar_t* line);
bool getTextInBox(wchar_t* target, const wchar_t* line);

/*
��ʾ�˵����ṩѡ��
������(wchar_t*)���⣬(int)ѡ��������(wchar_t*)ѡ��һ��(wchar_t*)ѡ���...
���أ�ѡ���Ӧ������
*/
int showMenu(const wchar_t* title, int optNum, ...);








#endif
