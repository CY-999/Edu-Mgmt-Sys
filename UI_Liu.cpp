#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"



bool showAllMajor(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm);

int mainLIUTY(void) {
	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����



	// ��ʼ��ͼ�δ���
	initgraph(1500, 810);
	BeginBatchDraw(); //��ʼ������ͼ
	setbkcolor(RGB(55, 61, 53)); //������ɫ
	cleardevice();


	//Cpnode tmpCrs = readCrs(CRS_FILE);
	//exportCrs(tmpCrs, ".\\export\\tempCrs.csv");
	//saveCrs(tmpCrs, CRS_FILE);

	//List tmpStu = readStu(STU_FILE);
	////saveStu(tmpStu, STU_FILE);
	//exportStu(tmpStu, ".\\export\\tempStu.csv");


	//testUI();
	//stuAccountUI(55230001);


	//allStuUI();
	loginUI();
	//menuUI();







	EndBatchDraw(); //����������ͼ
	closegraph(); // �ر�ͼ�δ���





	return 0;
}


// ��ʾתרҵ����רҵ
bool showAllMajor(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pCurrent = StuList->next; //�ӵ�һ�������ݽڵ㿪ʼ
	data.clear(); // �������
	data.push_back(vector<wstring>(8, L"")); //����һ��(ÿ��8��)

	//��ʼ����ͷ
	data[0][0] = L"ѧ��";
	data[0][1] = L"����";
	data[0][2] = L"�Ա�";
	data[0][3] = L"�꼶";
	data[0][4] = L"ѧԺ";
	data[0][5] = L"רҵ";
	//data[0][6] = L"ԭѧԺ";
	data[0][7] = L"ԭרҵ";



	int row = 1;
	while (pCurrent != NULL) { //��������

		// ����Ƿ���������
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // ����תΪ�ַ�����תΪwchar_t�����бȽ�
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			|| wcsstr(std::to_wstring(pCurrent->item.data.grade).c_str(), searchTerm) != NULL // ����תΪ�ַ�����תΪwchar_t�����бȽ�
			|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.major, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.original_college, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.original_major, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(8, L"")); //����һ��(ÿ��8��)

			//ÿ�е�����
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //����תΪ�ַ���
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = (pCurrent->item.data.gender) ? L"��" : L"Ů";
			data[row][3] = std::to_wstring(pCurrent->item.data.grade); //����תΪ�ַ���
			data[row][4] = pCurrent->item.data.college;
			data[row][5] = pCurrent->item.data.major;
			if (wcscmp(pCurrent->item.data.college, pCurrent->item.data.original_college) != 0 ||
				wcscmp(pCurrent->item.data.major, pCurrent->item.data.original_major) != 0) {
				//data[row][6] = pCurrent->item.data.original_college;
				data[row][7] = pCurrent->item.data.original_major;
			}

			row++; // ����+1
		}

		pCurrent = pCurrent->next; // ������һ���ڵ�

	}

	return true;
}


//void testShowChart(vector<vector<wstring>> _data, vector<vector<wstring>> _chart) {
//	chartUI(_chart, 1, 2);
//}

void changeMajorUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {
	cleardevice();

	//drawLine();


	//List allStuList = readStu(STU_FILE);

	vector<vector<std::wstring>> allStuData;
	showAllMajor(allStuList, allStuData, (judge == 1) ? tch_or_admin->item.data.college : L"");

	Table allStuTable(310, 90, 1160, 700, allStuData);

	Text titleText(25, 50, L"תרҵ����", 64);
	Text IDText(-500, 150, L"", 32);
	Text nameText(-500, 220, L"", 32);
	Text genderText(-500, 290, L"", 32);
	Text gradeText(-500, 360, L"", 32);
	Text collegeText(-500, 430, L"", 32);
	Text majorText(-500, 500, L"", 32);

	TextBox searchInputBox(310, 20, 1040, L"����", (judge == 1) ? tch_or_admin->item.data.college : L"");
	TextBox gradeBox(-500, 360, 290, L"�꼶", L"");
	TextBox collegeBox(-500, 430, 290, L"ѧԺ", L"");
	TextBox majorBox(-500, 500, 290, L"רҵ", L"");

	Button searchBtn(1370, 20, 100, 50, L"����", 1);
	Button modifyBtn(-50, 190, 330, 60, L"   תרҵ", 1);
	Button sortBtn(-50, 280, 330, 60, L"   ����", 1);
	Button exportBtn(-50, 370, 330, 60, L"   ����", 1);
	Button inportBtn(-50, 460, 330, 60, L"   ����", 1);
	Button backButton(-50, 580, 330, 60, L"   ����", 0);
	Button modifyOKButton(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button cancelButton(-500, 660, 290, 60, L"ȡ��", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		// ��������(����)
		searchInputBox.draw();
		gradeBox.draw();
		collegeBox.draw();
		majorBox.draw();

		if (peekmessage(&msg, -1, true)) {

			// ������¼�
			if (searchBtn.mouseClick(msg)) {
				showAllMajor(allStuList, allStuData, searchInputBox.text);
				allStuTable.setData(allStuData);
			}


			if (cancelButton.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"תרҵ����");

				// ������������
				gradeBox.clear();
				collegeBox.clear();
				majorBox.clear();

				// ʹ���ɱ仯
				allStuTable.canChange = true;

				// ����
				IDText.move(-500, 150);
				nameText.move(-500, 220);
				genderText.move(-500, 290);
				IDText.move(-500, 150);
				gradeBox.move(-500, 360);
				collegeBox.move(-500, 430);
				majorBox.move(-500, 500);
				modifyOKButton.move(-500, 580);
				cancelButton.move(-500, 660);

				// ��ʾ
				modifyBtn.move(-50, 190);
				sortBtn.move(-50, 280);
				exportBtn.move(-50, 370);
				inportBtn.move(-50, 460);
				backButton.move(-50, 580);

			}


			if (modifyBtn.mouseClick(msg)) {
				// ��ȡ��ǰ��
				int selectedRow = allStuTable.getSelectedRow();
				vector<std::wstring> selectedData = allStuData[selectedRow];

				// δѡ��ѧ��
				if (allStuTable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else if (selectedData[7] != L"") {
					MessageBox(GetHWnd(), L"ÿλѧ�����תһ��רҵ����ѧ���Ѵ����תרҵ������", L"����!", MB_ICONERROR);
				}
				else {
					// ���ı���
					titleText.setText(L"תרҵ����");
					// ����
					modifyBtn.move(-500, 310);
					sortBtn.move(-500, 470);
					exportBtn.move(-500, 550);
					inportBtn.move(-500, 630);
					backButton.move(-500, 730);


					// ʹ��񲻿ɱ仯
					allStuTable.canChange = false;


					//// ��ȡ��ǰ�� //����д��
					//int selectedRow = allStuTable.getSelectedRow();
					//vector<std::wstring> selectedData = allStuData[selectedRow];


					// �ı���Ĭ������
					IDText.setText((L"ѧ��: " + selectedData[0]).c_str()); // C++�﷨
					nameText.setText((L"����: " + selectedData[1]).c_str());
					genderText.setText((L"�Ա�: " + selectedData[2]).c_str());
					gradeBox.setText(selectedData[3].c_str());
					collegeBox.setText(selectedData[4].c_str());
					majorBox.setText(selectedData[5].c_str());

					// ��ʾ
					IDText.move(20, 180);
					nameText.move(20, 235);
					genderText.move(20, 290);
					gradeBox.move(10, 360);
					collegeBox.move(10, 430);
					majorBox.move(10, 500);
					modifyOKButton.move(10, 580);
					cancelButton.move(10, 660);
				}

			}

			if (modifyOKButton.mouseClick(msg)) {
				int id;
				int grade;
				wchar_t college[50];
				wchar_t major[50];

				// ��ȡ��ǰ���(�ж��꼶Ҫ��)
				time_t Current_time = time(NULL);
				int Current_year = localtime(&Current_time)->tm_year + 1900;

				// ��ȷ����ѧ���ڵ�
				int tempID;
				int selectedRow = allStuTable.getSelectedRow(); // ��ȡ��ǰ��
				getNumberInBox(99999999, &tempID, allStuData[selectedRow][0].c_str());
				Node* modifyingStu = searchStu(&allStuList, (wchar_t*)allStuData[selectedRow][1].c_str(), tempID);

				// �ж������ʽ
				if (
					getNumberInBox(9999, &grade, gradeBox.text) &&
					getTextInBox(college, collegeBox.text) &&
					getTextInBox(major, majorBox.text) &&
					(grade > 1970 && grade <= Current_year)
					) {
					if (MessageBox(GetHWnd(), (wstring(L"ȷ�������ѧ����רҵ��\"") + modifyingStu->item.data.original_college + L"\"��\"" + modifyingStu->item.data.original_major + L"\"תΪ\"" + college + L"\"��\"" + major + L"\"��").c_str(), L"תרҵȷ��", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						// �޸�
						modifyStu(&allStuList, modifyingStu, modifyingStu->item.data.name, tempID, modifyingStu->item.data.gender, grade, college, major);

						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"�޸�ѧ��:") + to_wstring(tempID) + L"��רҵ��Ϣ");


						//��־
						//writeLog();

						// ʹ���ɱ仯
						allStuTable.canChange = true;

						// ˢ�±��
						showAllMajor(allStuList, allStuData, searchInputBox.text);
						allStuTable.setData(allStuData);

					}

					// ʹ���ɱ仯
					allStuTable.canChange = true;

					// ������������
					gradeBox.clear();
					collegeBox.clear();
					majorBox.clear();


					// ���ı���
					titleText.setText(L"תרҵ����");

					// ����
					IDText.move(-500, 150);
					nameText.move(-500, 220);
					genderText.move(-500, 290);
					gradeBox.move(-500, 360);
					collegeBox.move(-500, 430);
					majorBox.move(-500, 500);
					modifyOKButton.move(-500, 580);
					cancelButton.move(-500, 660);

					// ��ʾ
					modifyBtn.move(-50, 190);
					sortBtn.move(-50, 280);
					exportBtn.move(-50, 370);
					inportBtn.move(-50, 460);
					backButton.move(-50, 580);



				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}


			if (sortBtn.mouseClick(msg)) {
				sortStuaccID(&allStuList);

				// ����
				saveStu(allStuList, STU_FILE);

				// ˢ�±��
				showAllMajor(allStuList, allStuData, L"");
				allStuTable.setData(allStuData);
			}

			if (exportBtn.mouseClick(msg)) {
				if (exportStu(allStuList, ".\\export\\Stu.csv")) {
					MessageBox(GetHWnd(), L"�����ɹ�", L"����ѧ��", 0);
					writeLog(judge, tch_or_admin, wstring(L"��������ѧ����Ϣ"));

				}
				else {
					MessageBox(GetHWnd(), L"����ʧ��", L"����ѧ��", MB_ICONERROR);
				}
			}

			if (inportBtn.mouseClick(msg)) {
				importStu(allStuList, ".\\import\\Stu.csv");


				// ˢ�±��
				showAllStu(allStuList, allStuData, L"");
				allStuTable.setData(allStuData);

				// ����
				saveStu(allStuList, STU_FILE);

				writeLog(judge, tch_or_admin, wstring(L"����ѧ����Ϣ"));

			}

			if (backButton.mouseClick(msg)) {
				return;
				if (judge == 1)
					menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				else
					menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}


			//�����껬������
			allStuTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
			gradeBox.onMessage(msg);
			collegeBox.onMessage(msg);
			majorBox.onMessage(msg);
		}

		//showxy(msg); // ��ʾ����



		//-------------------------------------------------
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}
}




void logUI(Node* admin, List adminList, List allStuList, Cpnode allCrsList) {
	cleardevice();


	FILE* fp;
	char file_name[50] = ".\\log\\Log.log";
	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"��־��ȡʧ�ܣ������˳�!", L"����!", MB_ICONERROR);
		exit(EXIT_FAILURE);
	}//��ȡʧ���˳�

	vector<vector<std::wstring>> data;
	data.push_back(vector<wstring>(1, L""));
	data[0][0] = L"[ʱ��] : ����";

	int logRow = 0;
	static wchar_t line[1024][128];
	while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
		if (line[logRow][0] == '\n') {//��������
			continue;
		}
		if (wcsstr(line[logRow], L"")) {
			line[logRow][wcslen(line[logRow]) - 1] = L'\0';
			logRow++;
		}
	}
	fclose(fp);
	int tmpRow = logRow--;
	while (tmpRow--) {
		data.push_back(vector<wstring>(1, L""));
	}
	int row = 1;
	while (logRow >= 0) {
		//if (wcsstr(line[logRow], L"")) {
		data[row++][0] = wstring(line[logRow]);
		//}
		logRow--;
	}


	//showLog(data, L"");



	Table allTchTable(310, 90, 1160, 700, data);

	Text titleText(40, 50, L"������־", 64);

	TextBox searchInputBox(310, 20, 1040, L"����", L"");

	Button searchBtn(1370, 20, 100, 50, L"����", 1);
	Button backButton(-50, 700, 330, 60, L"   ����", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// ��������(����)
		searchInputBox.draw();
		if (peekmessage(&msg, -1, true)) {

			// ������¼�
			if (searchBtn.mouseClick(msg)) {

				//fp = fopen(file_name, "r");//��ȡ�ļ�
				//if (fp == NULL) {
				//	printf("Read \"%s\" error, please check and reboot the system!", file_name);
				//	MessageBox(GetHWnd(), L"��־��ȡʧ�ܣ������˳�!", L"����!", MB_ICONERROR);
				//	exit(EXIT_FAILURE);
				//}//��ȡʧ���˳�

				//data.clear();
				////data.resize(0);
				//data.push_back(vector<wstring>(1, L""));
				//data[0][0] = L"[ʱ��] : ����";

				//logRow = 0;
				//int trueRow = 0;
				//for (int i = 0; i < 1024; i++) {
				//	line[i][0] == L'\0';
				//}
				//while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
				//	if (line[logRow][0] == '\n') {//��������
				//		continue;
				//	}
				//	line[logRow][wcslen(line[logRow]) - 1] = L'\0';
				//	if (wcsstr(line[logRow], searchInputBox.text)) {
				//		trueRow++;
				//	}
				//	logRow++;
				//}
				//fclose(fp);
				////tmpRow = trueRow--;
				//while (trueRow--) {
				//	data.push_back(vector<wstring>(1, L""));
				//}
				//row = 1;
				//while (logRow >= 0) {
				//	if (wcsstr(line[logRow], searchInputBox.text)) {
				//		data[row++][0] = wstring(line[logRow]);
				//	}
				//	logRow--;
				//}

				fp = fopen(file_name, "r");//��ȡ�ļ�
				if (fp == NULL) {
					printf("Read \"%s\" error, please check and reboot the system!", file_name);
					MessageBox(GetHWnd(), L"��־��ȡʧ�ܣ������˳�!", L"����!", MB_ICONERROR);
					exit(EXIT_FAILURE);
				}//��ȡʧ���˳�

				vector<vector<std::wstring>> data;
				data.push_back(vector<wstring>(1, L""));
				data[0][0] = L"[ʱ��] : ����";

				logRow = 0;
				while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
					if (line[logRow][0] == '\n') {//��������
						continue;
					}
					if (wcsstr(line[logRow], searchInputBox.text)) {
						line[logRow][wcslen(line[logRow]) - 1] = L'\0';
						logRow++;
					}
				}
				fclose(fp);
				tmpRow = logRow--;
				while (tmpRow--) {
					data.push_back(vector<wstring>(1, L""));
				}
				row = 1;
				while (logRow >= 0) {
					//if (wcsstr(line[logRow], L"")) {
					data[row++][0] = wstring(line[logRow]);
					//}
					logRow--;
				}

				allTchTable.setData(data);
			}

			if (backButton.mouseClick(msg)) {
				return;
				menuUI_Administrator(admin, adminList, allStuList, allCrsList);
			}

			//�����껬������
			allTchTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
		}

		//showxy(msg); // ��ʾ����



		//-------------------------------------------------
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}

}




void showLog(vector<vector<wstring>> data, wchar_t* searchTerm) {
	//data.clear(); // �������
	//data.push_back(vector<wstring>(1, L"")); //����һ��(ÿ��1��)

	////��ʼ����ͷ
	//data[0][0] = L"[ʱ��] : ����";

	//int logRow = data.size();
	//while (logRow--) {

	//	// ����Ƿ���������
	//	if (data[logRow][0] == (wstring)searchTerm) // ����תΪ�ַ�����תΪwchar_t�����бȽ�
	//		|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
	//		|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
	//		) {

	//		data.push_back(vector<std::wstring>(1, L"")); //����һ��(ÿ��1��)

	//		//ÿ�е�����
	//		data[row][0] = std::to_wstring(pCurrent->item.data.ID); //����תΪ�ַ���
	//		data[row][1] = pCurrent->item.data.name;
	//		data[row][2] = (pCurrent->item.data.gender) ? L"��" : L"Ů";
	//		data[row][3] = pCurrent->item.data.college;


	//		row++; // ����+1
	//	}


	//}
}

void showStuAllCrs(const Cpnode cphead, vector<vector<wstring>>& data, const wchar_t* searchTerm)
{
	Cpnode cplist = cphead->next; //�ӵ�һ�������ݽڵ㿪ʼ
	data.clear(); // �������
	data.push_back(vector<wstring>(5, L""));

	//��ʼ����ͷ
	data[0][0] = L"�γ�����";
	data[0][1] = L"�γ̺�";
	data[0][2] = L"�γ�����";
	data[0][3] = L"ѧ��";
	data[0][4] = L"ѧ��";


	int row = 1;
	while (cplist != NULL)//��������
	{
		// ����Ƿ���������
		if (
			wcsstr(cplist->cname, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->cnum).c_str(), searchTerm) != NULL ||
			wcsstr(cplist->character, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->credit).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->SchYear).c_str(), searchTerm) != NULL
			)
		{
			data.push_back(vector<std::wstring>(5, L""));

			//ÿ�е�����
			data[row][0] = cplist->cname;
			data[row][1] = std::to_wstring(cplist->cnum);
			data[row][2] = cplist->character;
			data[row][3] = std::to_wstring(cplist->credit);
			data[row][4] = std::to_wstring(cplist->SchYear);

			//����С��
			data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
			row++; // ����+1
		}
		cplist = cplist->next; // ������һ���ڵ�
	}
	return;
}


void showStuChooseCrs(const Node* Stu, vector<vector<wstring>>& data)
{
	Crsnode* cplist = Stu->item.crslist->crs_next; //�ӵ�һ�������ݽڵ㿪ʼ
	data.clear(); // �������
	data.push_back(vector<wstring>(5, L""));

	//��ʼ����ͷ
	data[0][0] = L"�γ�����";
	data[0][1] = L"�γ̺�";
	data[0][2] = L"�γ�����";
	data[0][3] = L"ѧ��";
	data[0][4] = L"ѧ��";


	int row = 1;
	while (cplist != NULL)//��������
	{
		// ����Ƿ���������
		data.push_back(vector<std::wstring>(5, L""));

		//ÿ�е�����
		data[row][0] = cplist->score.course_name;
		data[row][1] = cplist->score.course_id;
		data[row][2] = (cplist->score.course_nature == 1) ? L"����" : L"ѡ��";
		data[row][3] = std::to_wstring(cplist->score.credit);
		data[row][4] = std::to_wstring(cplist->score.semester);

		//����С��
		data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
		row++; // ����+1
		cplist = cplist->crs_next; // ������һ���ڵ�
	}
	return;
}


void chooseCrsUI(int stuID, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {
	cleardevice();

	//List StuList = readStu(STU_FILE);
	Node* pstu = allStuList->next;
	while (pstu != NULL) {
		if (stuID == pstu->item.data.ID) {
			break;
		}
		pstu = pstu->next;
	}

	Crsnode* allCrsInStuList = pstu->item.crslist->crs_next;
	sortStuCrsYear(pstu->item.crslist);
	vector<vector<std::wstring>> stuAllCrs;
	vector<vector<std::wstring>> stuChooseCrs;
	showStuAllCrs(allCrsList, stuAllCrs, L"");
	showStuChooseCrs(pstu, stuChooseCrs);

	Table allCrsTable(400, 90, 525, 700, stuAllCrs);
	Table chooseCrsTable(945, 90, 525, 700, stuChooseCrs);

	//����
	TextBox searchInputBox(400, 20, 960, L"����", L"");


	//��ť
	Button searchBtn(1370, 20, 100, 50, L"����", 1);


	Text idBtn(40, 100, (wstring(L"ѧ�ţ�") + to_wstring(stuID)).c_str(), 32);
	Text nameBtn(40, 150, (wstring(L"������") + pstu->item.data.name).c_str(), 32);
	Text titleText(50, 20, (wstring(L"ѡ�˿�")).c_str(), 56);


	//���㼨��
	Button chooseBtn(-50, 520, 330, 60, L"   ѡ��", 1);
	Button cancelBtn(-50, 600, 330, 60, L"   �˿�", 1);
	Button backButton(-50, 690, 330, 60, L"   ���", 0);





	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		searchInputBox.draw();



		if (peekmessage(&msg, -1, true)) {
			//������¼�

			//����
			if (searchBtn.mouseClick(msg)) {
				showStu(pstu, stuAllCrs, searchInputBox.text);
				allCrsTable.setData(stuAllCrs);
			}

			if (chooseBtn.mouseClick(msg)) {
				// ��ȡ��ǰ��
				int selectedRowAll = allCrsTable.getSelectedRow();
				if (selectedRowAll == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��δѡ�γ�", L"����!", MB_ICONERROR);
				}
				else {
					vector<std::wstring> selectedData = stuAllCrs[selectedRowAll];
					Cpnode addingCrs = searchCrs(allCrsList, stoi(selectedData[1]), stoi(selectedData[4]));


					if (addStuInCrs(addingCrs, pstu->item.data.name, pstu->item.data.ID, 0) == 0) {
						MessageBox(GetHWnd(), L"���Ѿ�ѡ�������ſγ�", L"����!", MB_ICONERROR);
					}
					else {
						addCrsToStu(pstu, selectedData[1].c_str(), selectedData[0].c_str(), 0, stoi(selectedData[4]), wcscmp(selectedData[2].c_str(), L"����") == 0 ? 1 : 0, stod(selectedData[3]), 0);

						//ˢ�±��
						showStuChooseCrs(pstu, stuChooseCrs);
						chooseCrsTable.setData(stuChooseCrs);

						// ����
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);

						writeLog(0, pstu, wstring(L"ѡ��:") + selectedData[1]);
					}
				}
			}

			if (cancelBtn.mouseClick(msg)) {
				// ��ȡ��ǰ��
				int selectedRowChoose = chooseCrsTable.getSelectedRow();
				if (selectedRowChoose == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ����ѡ�γ�", L"����!", MB_ICONERROR);
				}
				else {
					vector<std::wstring> selectedData = stuChooseCrs[selectedRowChoose];
					Cpnode deletingCrs = searchCrs(allCrsList, stoi(selectedData[1]), stoi(selectedData[4]));
					Crsnode* tmpcrs = searchCrsInStu(pstu, selectedData[1].c_str(), selectedData[0].c_str());

					if (tmpcrs->score.score != 0) {
						MessageBox(GetHWnd(), L"���ſγ�������ɿ��ԣ������˿Σ�", L"����!", MB_ICONERROR);
					}
					else {
						deleteStuInCrs(deletingCrs, pstu->item.data.name, pstu->item.data.ID);
						deleteCrsInStu(pstu, tmpcrs);
						MessageBox(GetHWnd(), L"�˿γɹ�", L"�˿�!", MB_ICONINFORMATION);

						//ˢ�±��
						showStuChooseCrs(pstu, stuChooseCrs);
						chooseCrsTable.setData(stuChooseCrs);

						// ����
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);

						writeLog(0, pstu, wstring(L"�˿�:") + selectedData[1]);
					}
				}
			}

			if (backButton.mouseClick(msg))
			{
				writeLog(0, pstu, wstring(L"ѡ�����"));
				return;
				loginUI();
			}

			//�����껬������
			allCrsTable.onMouse(msg);
			chooseCrsTable.onMouse(msg);



			// �ı�������
			searchInputBox.onMessage(msg);
		}


		//-------------------------------------------------
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}




}


