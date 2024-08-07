#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"


int main000() {
	setlocale(LC_ALL, ""); //使控制台支持宽字符输出

	//Cpnode  crs = readCrs(CRS_FILE);
	List stu = readStu(STU_FILE);
	
	wchar_t name[200];
	wchar_t a1[200];
	wchar_t a2[200];
	wchar_t b[200];
	wchar_t c[200];
	wchar_t d[200];
	wchar_t e[200];
	wchar_t f[200];
	wchar_t g[200];
	double h = 0;
	
	getText(name);
	getText(a1);

	Node* Stu = searchStu_InQuality(stu, name);

	deleteQuality_rlist(Stu, a1);

	printStu(stu);
	return 0;
}
