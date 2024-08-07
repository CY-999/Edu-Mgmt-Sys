#pragma warning(disable:4996)
#include "ui.h"
#define PAGE_FILE "Page.txt"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"



void printStu(const List StuList) {

	List pStu = StuList->next; // ��ͷ������һ���ڵ㿪ʼ
	while (pStu != NULL) {
		wprintf(L"ѧ����Ϣ:\n%d\t%s\t%d\t%d\t%s\t%s\t%s\t%s\t%s\t%.2lf\t%.4lf\t%.2lf\t%.4lf\n\n�γ̣�\n",
			pStu->item.data.ID,
			pStu->item.data.name,
			pStu->item.data.gender,
			pStu->item.data.grade,
			pStu->item.data.college,
			pStu->item.data.major,
			pStu->item.data.original_college,
			pStu->item.data.original_major,
			pStu->item.data.password,

			pStu->item.data.all_avg_score,
			pStu->item.data.all_avg_grid,
			pStu->item.data.req_avg_score,
			pStu->item.data.req_avg_grid
		);

		Crsnode* pcrs = pStu->item.crslist->crs_next; // ����һ���γ̽ڵ㿪ʼ
		while (pcrs != NULL) {
			wprintf(L"%s\t%s\t%.1lf\t%d\t%d\t%.1lf\t%.1lf\n",
				pcrs->score.course_id,
				pcrs->score.course_name,
				pcrs->score.score,
				pcrs->score.semester,
				pcrs->score.course_nature,
				pcrs->score.credit,
				pcrs->score.grid);

			pcrs = pcrs->crs_next; // �ƶ�����һ���ڵ�
		}

		wprintf(L"\n���гɹ���\n");
		Rnode* pres = pStu->item.rlist->rnext; // ����һ�����гɹ��ڵ㿪ʼ
		while (pres != NULL) {
			wprintf(L"%s\t%s\t%s\t%s\t%s\t%s\t%s\t%.2lf\n",
				pres->research.paper_name,
				pres->research.journal_or_conference_name,
				pres->research.author,
				pres->research.date,
				pres->research.volume_num,
				pres->research.issue_num,
				pres->research.page,
				pres->research.GPA_bonus);

			pres = pres->rnext; // �ƶ�����һ���ڵ�
		}


		wprintf(L"\n�����񽱣�\n");
		Cnode* pcpt = pStu->item.clist->cnext; // ����һ�������񽱽ڵ㿪ʼ
		while (pcpt != NULL) {
			wprintf(L"%s\t%s\t%s\t%s\t%.2lf\n",
				pcpt->competition.competition_name,
				pcpt->competition.organizer,
				pcpt->competition.category,
				pcpt->competition.date,
				pcpt->competition.GPA_bonus);

			pcpt = pcpt->cnext; // �ƶ�����һ���ڵ�
		}


		wprintf(L"\n--------------------------------------------------------------------------\n\n");
		pStu = pStu->next; // �ƶ�����һ���ڵ�
	}


}
void printCrs(const Cpnode CrsList) {
	Cpnode pCrs = CrsList->next; // ��ͷ������һ���ڵ㿪ʼ
	while (pCrs != NULL) {
		wprintf(L"�γ���Ϣ:\n%d\t%s\t%s\t%.1lf\t%d\t%.1lf\t%.2lf\t%.1lf\t%.2lf\t%d\t%d\t%.2lf\t%d\t%.2lf\n\nѧ����\n",
			pCrs->cnum,
			pCrs->cname,
			pCrs->character,
			pCrs->credit,
			pCrs->headcount,
			pCrs->totscore,
			pCrs->averscore,
			pCrs->totGPA,
			pCrs->averGPA,
			pCrs->SchYear,
			pCrs->PassNum,
			pCrs->PassRate,
			pCrs->ExcelNum,
			pCrs->ExcelRate
		); // д��


		Spnode pstu = pCrs->sphead->next; // ����һ��ѧ���ڵ㿪ʼ
		while (pstu != NULL) {
			wprintf(L"%d\t%s\t%.1lf\t%.1lf\n",
				pstu->snum,
				pstu->sname,
				pstu->score,
				pstu->GPA); // д��

			pstu = pstu->next; // �ƶ�����һ���ڵ�
		}
		wprintf(L"\n--------------------------------------------------------------------------\n\n");
		pCrs = pCrs->next; // �ƶ�����һ���ڵ�
	}
}



void drawLine() {
	setlinecolor(0x777777);
	for (int i = 0; i <= 1280; i += 50) {
		line(0, i, 1280, i);
		line(i, 0, i, 850);
	}
}

void showxy(ExMessage& msg) {

	wchar_t text[50];
	swprintf(text, L"x:%d, y:%d", msg.x, msg.y);
	setfillcolor(BLACK);
	solidrectangle(0, 0, 220, 36);

	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(32, 0, L"΢���ź�");
	outtextxy(0, 0, text);



}


void testUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List) {
	cleardevice();
	//drawLine();


	// ������ť���󲢻���
	//Button button1(-50, 100, 300, 50, L"���԰�ť", 0x00009688, WHITE);
	//Text text1(100, 0, L"���� Test", 50);
	//Button button2(-50, 160, 300, 50, L"���԰�ť", 0x123456, WHITE);
	Button exitButton(10, 50, 200, 60, L"�˳�", 1);
	Button selectRowBtn1(10, 130, 300, 60, L"ѡ�������", 0);

	Chart testChart(360, 50, 900, 600,
		{
			{L"ѧ��1", L"ѧ��2", L"ѧ��3��", L"ѧ��4", L"ѧ��5", L"666", L"������"},
			{L"10", L"60", L"55", L"70", L"60", L"89", L"35"}
		});

	//TextBox box1(50, 250, 500, L"����1", L"ceshi");
	//TextBox box2(90, 400, 800, L"����2", L"");


	//TextBox selectBox(280, 400, 300, L"�ĸ����", L"");



	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//box1.draw();
		//box2.draw();
		//selectBox.draw();

		if (peekmessage(&msg, -1, true)) {


			//box1.onMessage(msg);
			//box2.onMessage(msg);
			//if (button1.mouseClick(msg)) {
			//	wprintf(L"press button1\n");
			//	wprintf(L"box1 is:%s\n", box1.text);
			//}
			if (selectRowBtn1.mouseClick(msg)) {


			}
			if (exitButton.mouseClick(msg)) {
				exit(0);
			}
			////box1.onMessage(msg);
			////box2.onMessage(msg);
			//selectBox.onMessage(msg);
		}

		showxy(msg);


		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}





}


void chartUI(vector<vector<wstring>> _data, int row1, int row2, int stuID, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {
	cleardevice();
	Button backButton(1270, 20, 200, 60, L"����", 1);

	vector<vector<wstring>> _chart;
	_data.erase(_data.begin()); //ɾ����ͷ
	_chart.push_back(vector<wstring>(_data.size(), L""));
	_chart.push_back(vector<wstring>(_data.size(), L""));
	int trueCol = 0;
	for (int i = 0; i < _data.size(); i++) {
		if (wcscmp(_data[i][row2].c_str(), L"") != 0) {
			_chart[0][trueCol] = _data[i][row1];
			_chart[1][trueCol] = _data[i][row2];
			trueCol++;
		}
	}
	_chart[0].resize(trueCol);
	_chart[1].resize(trueCol);

	Chart testChart(100, 110, 1300, 480, _chart);



	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		if (peekmessage(&msg, -1, true)) {
			if (backButton.mouseClick(msg)) {
				return;
				if (judge == 1)
					menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				else if (judge == 0) {
					stuAccountUI(stuID, admin, Admin_List, allStuList, allCrsList);
				}
				else
					menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}
		}

		//showxy(msg);


		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}







}


void menuUI_Administrator(Node* admin, List adminList, List allStuList, Cpnode allCrsList) {//����Ա�˽���
	cleardevice();

	IMAGE Image;
	loadimage(&Image, L".\\res\\background.jpeg", 1500, 810, true);
	putimage(0, 0, &Image, SRCCOPY);

	//drawLine();

	Text titleText(90, 50, L"��ӭ", 64);

	int dy = -30;
	Button allStuButton(-50, 170 + dy, 350, 60, L"  ѧ������", 1);
	Button allCrsButton(-50, 250 + dy, 350, 60, L"  �γ̹���", 1);
	Button allQualityButton(-50, 330 + dy, 350, 60, L"  ��������Ŀ����", 1);
	Button changeMajorButton(-50, 410 + dy, 350, 60, L"  תרҵ����", 1);
	Button allTchButton(-50, 490 + dy, 350, 60, L"  ��ʦ����", 1);
	Button settingsButton(-50, 570 + dy, 350, 60, L"  �������", 1);
	Button logButton(-50, 650 + dy, 350, 60, L"  �鿴��־", 1);
	Button exitButton(-50, 740 + dy, 350, 60, L"  �˳���¼", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		if (peekmessage(&msg, -1, true)) {
			if (allStuButton.mouseClick(msg)) {
				allStuUI(admin, adminList, 2, admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();
			}
			if (allTchButton.mouseClick(msg)) {
				allTchUI(admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (allCrsButton.mouseClick(msg)) {
				allCrsUI(admin, adminList, 2, admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (allQualityButton.mouseClick(msg)) {
				allQualityUI(admin, adminList, 2, admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (changeMajorButton.mouseClick(msg)) {
				changeMajorUI(admin, adminList, 2, admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (settingsButton.mouseClick(msg)) {
				manageUI(admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (logButton.mouseClick(msg)) {
				logUI(admin, adminList, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				changeMajorButton.draw();
				allTchButton.draw();
				settingsButton.draw();
				logButton.draw();
				exitButton.draw();

			}
			if (exitButton.mouseClick(msg)) {
				writeLog(2, admin, wstring(L"�˳�ϵͳ"));
				freeStu(allStuList);
				freeCrs(allCrsList);
				loginUI();
			}
		}

		//showxy(msg);




		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}
}

void menuUI_Tch(Node* Tch, List TchList, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {//��ʦ�˽���
	cleardevice();

	IMAGE Image;
	loadimage(&Image, L".\\res\\background.jpeg", 1500, 810, true);
	putimage(0, 0, &Image, SRCCOPY);

	//drawLine();

	Text titleText(90, 50, L"��ӭ", 64);

	int dy = 50;
	Button allStuButton(-50, 170 + dy, 350, 60, L"  �鿴ѧ��", 1);
	Button allCrsButton(-50, 250 + dy , 350, 60, L"  �鿴�γ�", 1);
	Button allQualityButton(-50, 330 + dy, 350, 60, L"  ��������Ŀ����", 1);
	Button settingsButton(-50, 410 + dy, 350, 60, L"  �޸�����", 1);
	Button exitButton(-50, 510 + dy, 350, 60, L"  �˳���¼", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		if (peekmessage(&msg, -1, true)) {
			if (allStuButton.mouseClick(msg)) {
				allStuUI(Tch, TchList, 1, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				settingsButton.draw();
				exitButton.draw();

			}
			if (allCrsButton.mouseClick(msg)) {
				allCrsUI(Tch, TchList, 1, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				settingsButton.draw();
				exitButton.draw();

			}
			if (allQualityButton.mouseClick(msg)) {
				allQualityUI(Tch, TchList, 1, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				settingsButton.draw();
				exitButton.draw();

			}
			if (settingsButton.mouseClick(msg)) {
				Modify_Stu_or_Tch_Password_UI(to_wstring(Tch->item.data.ID).c_str(), Tch, 1, TchList, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				putimage(0, 0, &Image, SRCCOPY);
				titleText.draw();
				allStuButton.draw();
				allCrsButton.draw();
				allQualityButton.draw();
				settingsButton.draw();
				exitButton.draw();

			}
			if (exitButton.mouseClick(msg)) {
				writeLog(1, Tch, wstring(L"�˳�ϵͳ"));
				freeStu(allStuList);
				freeCrs(allCrsList);
				loginUI();
			}
		}

		//showxy(msg);




		FlushBatchDraw(); //������ͼ

		//ULONGLONG end_time = GetTickCount();
		//if (end_time - start_time < 1) {
		//	Sleep(1);
		//}
		Sleep(2);
	}







}



double preditcGrid(vector<vector<wstring>> _data, int col1, int col2) {
	// �ع����
	double a, b, c, d;

	vector<vector<wstring>> _chart;
	_data.erase(_data.begin()); //ɾ����ͷ
	_chart.push_back(vector<wstring>(_data.size(), L""));
	_chart.push_back(vector<wstring>(_data.size(), L""));
	int trueCol = 0;
	for (int i = 0; i < _data.size(); i++) {
		if (wcscmp(_data[i][col2].c_str(), L"") != 0) {
			_chart[0][trueCol] = _data[i][col1];
			_chart[1][trueCol] = _data[i][col2];
			trueCol++;
		}
	}
	_chart[0].resize(trueCol);
	_chart[1].resize(trueCol);


	// ����ع�
	linear_regression(_chart[1], _chart[1].size(), &a, &b);

	// Ԥ�������ݵ�
	double new_x = _chart[1].size();

	double prediction = (a * new_x + b <= 4) ? (a * new_x + b >= 0) ? a * new_x + b : 0 : 3.9999;
	return prediction;
}

void linear_regression(vector<wstring> y, int n, double* slope, double* intercept) {
	double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0;

	// ������ֺ�
	for (int i = 0; i < n; i++) {
		sum_x += (i + 1);
		sum_y += stod(y[i]);
		sum_xy += (i + 1) * stod(y[i]);
		sum_x_squared += (i + 1) * (i + 1);
	}

	// ����б�ʺͽؾ�
	*slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
	*intercept = (sum_y - *slope * sum_x) / n;
}





//int abc(){
//	int a[100];
//
//	vector<int> b;
//	b.push_back(1);
//	b[0];
//	b.pop_back();
//	b.clear();
//}






