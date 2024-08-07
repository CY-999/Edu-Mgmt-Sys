#pragma warning(disable:4996)
#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"


int main(void) {
	setlocale(LC_ALL, ""); //使控制台支持宽字符输出
	// 初始化图形窗口
	initgraph(1500, 810, EX_NOCLOSE);
	BeginBatchDraw(); //开始批量绘图
	//setbkcolor(RGB(55, 61, 53)); //背景颜色
	setbkcolor(backgroundColor); //背景颜色
	cleardevice();
	loginUI(); //登陆界面
	EndBatchDraw(); //结束批量绘图
	closegraph(); // 关闭图形窗口
	return 0;
}