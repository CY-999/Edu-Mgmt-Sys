#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"


int mainJi1(void) {
	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����
	List stu = readStu(STU_FILE);

	wchar_t name[30];
	wcscpy(name, L"����");
	int id = 55230002;

	Node* stuu = searchStu(&stu, name,id);
	//printStu(stu);
	int all, must;

	//all = AllGrid(stuu->item.crslist->crs_next);
	//must = MustGrid(stu->item.crslist);

	//wprintf(L"%d",all);
	wprintf(L"111");
	/*wchar_t name[30];
	int id;
	wscanf(L"%s %d", name, &id);
	Node* test = searchStu(&stu, name, id);

	wchar_t pcourse_id[10];
	wchar_t pcourse_name[100];
	double pscore;
	int psemester;
	int pcourse_nature;
	double pcredit;
	double pgrid;*/
	//wscanf(L"%s %s", pcourse_name, pcourse_id);
	//Crsnode* testcrs = searchCrsInStu(test, pcourse_id, pcourse_name);
	//wprintf(L"%s", testcrs->score.course_id);
	//deleteCrsInStu(test, testcrs);
	//wscanf(L"%s %s %lf %d %d %lf %lf", pcourse_name, pcourse_id,&pscore,&psemester,&pcourse_nature,&pcredit,&pgrid);
	////modifyCrsInStu(testcrs, pcourse_id, pcourse_name, pscore, psemester, pcourse_nature, pcredit, pgrid);
	//addCrsToStu(test, pcourse_id, pcourse_name, pscore, psemester, pcourse_nature, pcredit, pgrid);

	//printStu(stu);
	//saveStu(stu, STU_FILE);
	return 0;
}


//wchar_t name[30];
//wcscpy(name, L"������");
//int id;
//int gender;
//int grade;
//wchar_t college[50];
//wcscpy(college, L"������");
//wchar_t major[50];
//wcscpy(major,L"������")
//wchar_t pname[30];
//int pid;
//Node* test;
//wscanf(L"%s %d", &pname, &pid);
//wscanf(L"%s %d %d %d %s %s", &name, &id,&gender,&grade,&college,&major);
//test = searchStu(&stu, pname, pid);
//addStu(&stu,name, id, gender, grade, college, major);
//���� 40240001
//�ߵ���ѧAI 10001












