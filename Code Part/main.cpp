#pragma warning(disable:4996)
#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"


int main(void) {
	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����
	// ��ʼ��ͼ�δ���
	initgraph(1500, 810, EX_NOCLOSE);
	BeginBatchDraw(); //��ʼ������ͼ
	//setbkcolor(RGB(55, 61, 53)); //������ɫ
	setbkcolor(backgroundColor); //������ɫ
	cleardevice();
	loginUI(); //��½����
	EndBatchDraw(); //����������ͼ
	closegraph(); // �ر�ͼ�δ���
	return 0;
}