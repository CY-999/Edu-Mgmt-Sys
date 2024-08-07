#pragma warning(disable:4996)

#include "main.h"
#include<algorithm>
#include<string>
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"



int mainJi(void) {
	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����
	// ��ʼ��ͼ�δ���
	initgraph(1500, 810);
	BeginBatchDraw(); //��ʼ������ͼ
	setbkcolor(RGB(55, 61, 53)); //������ɫ
	cleardevice();

	//testUI();

	//------------
	//allStuUI();
	loginUI();
	//------------



	EndBatchDraw(); //����������ͼ
	closegraph(); // �ر�ͼ�δ���
	return 0;
}

void allStuUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {//judge:1����ʦ 2�ǹ���Ա
	cleardevice();

	//drawLine();


	//List allStuList = readStu(STU_FILE);
	//Cpnode allCrsList = readCrs(CRS_FILE);

	vector<vector<std::wstring>> allStuData;
	showAllStu(allStuList, allStuData, (judge == 1) ? tch_or_admin->item.data.college : L"");
	int i = 0;


	Table allStuTable(310, 90, 1160, 700, allStuData);

	Text titleText(40, 50, L"����ѧ��", 64);
	Text IDText(-500, 150, L"", 32);
	Text nameText(-500, 220, L"", 32);
	Text genderText(-500, 290, L"", 32);
	Text gradeText(-500, 360, L"", 32);
	Text collegeText(-500, 430, L"", 32);
	Text majorText(-500, 500, L"", 32);

	TextBox searchInputBox(310, 20, 1040, L"����", (judge == 1) ? tch_or_admin->item.data.college : L"");
	TextBox IDBox(-500, 150, 290, L"ѧ�� ( ��Ӻ󲻿ɸ��ģ�)", L"");
	TextBox nameBox(-500, 220, 290, L"����", L"");
	TextBox genderBox(-500, 290, 290, L"�Ա�", L"");
	TextBox gradeBox(-500, 360, 290, L"�꼶", L"");
	TextBox collegeBox(-500, 430, 290, L"ѧԺ", L"");
	TextBox majorBox(-500, 500, 290, L"רҵ", L"");

	Button searchBtn(1370, 20, 100, 50, L"����", 1);
	Button lookBtn(-50, 150, 330, 60, L"   ѧ���γ�", 1);//
	Button addBtn(-50, 230, 330, 60, L"   ���", 1);//
	Button modifyBtn(-50, 310, 330, 60, L"   �޸�", 1);
	Button deleteBtn(-50, 390, 330, 60, L"   ɾ��", 1);

	Button sortBtn(0, 470, 135, 60, L"����", 1);//////////////
	Button sortyearBtn(145, 470, 135, 60, L"�ɼ�����", 1);////////////////////
	Button exportBtn(-50, 550, 330, 60, L"   ����", 1);

	Button inportBtn(-50, 630, 330, 60, L"   ����", 1);
	Button backButton(-50, 720, 330, 60, L"   ����", 0);
	Button addOKButton(-500, 580, 290, 60, L"ȷ�����", 1);
	Button modifyOKButton(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button cancelButton(-500, 660, 290, 60, L"ȡ��", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		// ��������(����)
		searchInputBox.draw();
		IDBox.draw();
		nameBox.draw();
		genderBox.draw();
		gradeBox.draw();
		collegeBox.draw();
		majorBox.draw();

		if (peekmessage(&msg, -1, true))
		{

			// ������¼�
			if (searchBtn.mouseClick(msg))
			{
				if (allStuTable.canChange)
				{
					showAllStu(allStuList, allStuData, searchInputBox.text);
					allStuTable.setData(allStuData);
				}
			}

			if (addBtn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"���ѧ��");
				// ����
				lookBtn.move(-500, 150);
				addBtn.move(-500, 230);
				modifyBtn.move(-500, 310);
				deleteBtn.move(-500, 390);
				sortBtn.move(-500, 470);
				sortyearBtn.move(-500, 470);
				exportBtn.move(-500, 550);
				inportBtn.move(-500, 630);
				backButton.move(-500, 720);

				// ��ʾ
				IDBox.move(10, 150);
				nameBox.move(10, 220);
				genderBox.move(10, 290);
				gradeBox.move(10, 360);
				collegeBox.move(10, 430);
				majorBox.move(10, 500);
				addOKButton.move(10, 580);
				cancelButton.move(10, 660);
			}

			if (lookBtn.mouseClick(msg)) {

				if (allStuTable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else {
					wchar_t cname[30];
					int cid;
					int selectedRow = allStuTable.getSelectedRow();
					getNumberInBox(99999999, &cid, allStuData[selectedRow][0].c_str());
					getTextInBox(cname, allStuData[selectedRow][1].c_str());
					Node* Crs = searchStu(&allStuList, cname, cid);


					StuUI(Crs, allStuList, cname, &cid, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allCrsList);



					cleardevice();
					Table allStuTable(310, 90, 1160, 700, allStuData);

					titleText.draw();
					searchInputBox.draw();
					searchBtn.draw();
					lookBtn.draw();
					addBtn.draw();
					modifyBtn.draw();
					deleteBtn.draw();
					sortBtn.draw();
					sortyearBtn.draw();
					exportBtn.draw();
					inportBtn.draw();
					backButton.draw();





					//	// ����
					//	lookBtn.move(-500, 150);
					//	addBtn.move(-500, 230);
					//	modifyBtn.move(-500, 310);
					//	deleteBtn.move(-500, 390);
					//	sortBtn.move(-500, 470);
					//	exportBtn.move(-500, 550);
					//	inportBtn.move(-500, 630);
					//	backButton.move(-500, 720);

					//	// ��ȡ��ǰ��
					//	int selectedRow = allStuTable.getSelectedRow();
					//	vector<std::wstring> selectedData = allStuData[selectedRow];

					//	// ʹ��񲻿ɱ仯
					//	allStuTable.canChange = false;

					//	// �ı���Ĭ������
					//	IDText.setText((L"ѧ��:" + selectedData[0]).c_str()); // C++�﷨
					//	nameText.setText((L"����:"+ selectedData[1]).c_str());
					//	genderText.setText((L"�Ա�:"+selectedData[2]).c_str());
					//	gradeText.setText((L"�꼶:" + selectedData[3]).c_str());
					//	collegeText.setText((L"ѧԺ:" + selectedData[4]).c_str());
					//	majorText.setText((L"רҵ:" + selectedData[5]).c_str());

					//	//��ʾ
					//	IDText.move(10, 150);
					//	nameText.move(10, 220);
					//	genderText.move(10, 290);
					//	gradeText.move(10, 360);
					//	collegeText.move(10, 430);
					//	majorText.move(10, 500);
					//	lookcancelBtn.move(10, 570);
				}

			}

			if (cancelButton.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"����ѧ��");

				// ������������
				IDBox.clear();
				nameBox.clear();
				genderBox.clear();
				gradeBox.clear();
				collegeBox.clear();
				majorBox.clear();

				// ʹ���ɱ仯
				allStuTable.canChange = true;

				// ����
				IDBox.move(-500, 150);
				IDText.move(-500, 150);
				nameBox.move(-500, 220);
				genderBox.move(-500, 290);
				gradeBox.move(-500, 360);
				collegeBox.move(-500, 430);
				majorBox.move(-500, 500);
				addOKButton.move(-500, 580);
				modifyOKButton.move(-500, 580);
				cancelButton.move(-500, 660);

				// ��ʾ
				lookBtn.move(-50, 150);
				addBtn.move(-50, 230);
				modifyBtn.move(-50, 310);
				deleteBtn.move(-50, 390);
				sortBtn.move(0, 470);/////////
				sortyearBtn.move(145, 470);
				exportBtn.move(-50, 550);
				inportBtn.move(-50, 630);
				backButton.move(-50, 720);

			}

			if (addOKButton.mouseClick(msg)) {
				int id;
				wchar_t name[30];
				wchar_t gender[5];
				int grade;
				wchar_t college[50];
				wchar_t major[50];

				// ��ȡ��ǰ���(�ж��꼶Ҫ��)
				time_t Current_time = time(NULL);
				int Current_year = localtime(&Current_time)->tm_year + 1900;

				// �ж������ʽ
				if (
					getNumberInBox(99999999, &id, IDBox.text) &&
					getTextInBox(name, nameBox.text) &&
					getTextInBox(gender, genderBox.text) &&
					getNumberInBox(9999, &grade, gradeBox.text) &&
					getTextInBox(college, collegeBox.text) &&
					getTextInBox(major, majorBox.text) &&
					(id > 9999999 && id < 100000000) &&
					(grade > 1970 && grade <= Current_year) &&
					(!wcscmp(gender, L"��") || !wcscmp(gender, L"Ů"))
					) {

					// ѧ����ͬ�����,��������
					if (!addStu(&allStuList, name, id, wcscmp(gender, L"��") == 0 ? 1 : 0, grade, college, major)) {
						MessageBox(GetHWnd(), L"��ѧ���Ѿ�����,�����ظ����!", L"����!", MB_ICONERROR);
					}
					// ���򱣴�
					else {
						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"���ѧ��:") + to_wstring(id));

						// ˢ�±��
						showAllStu(allStuList, allStuData, L"");
						allStuTable.setData(allStuData);

						// ������������
						IDBox.clear();
						nameBox.clear();
						genderBox.clear();
						gradeBox.clear();
						collegeBox.clear();
						majorBox.clear();


						// ���ı���
						titleText.setText(L"����ѧ��");

						// ����
						IDBox.move(-500, 150);
						nameBox.move(-500, 220);
						genderBox.move(-500, 290);
						gradeBox.move(-500, 360);
						collegeBox.move(-500, 430);
						majorBox.move(-500, 500);
						addOKButton.move(-500, 580);
						cancelButton.move(-500, 660);

						// ��ʾ
						lookBtn.move(-50, 150);
						addBtn.move(-50, 230);
						modifyBtn.move(-50, 310);
						deleteBtn.move(-50, 390);
						sortBtn.move(0, 470);
						sortyearBtn.move(145, 470);
						exportBtn.move(-50, 550);
						inportBtn.move(-50, 630);
						backButton.move(-50, 720);

					}


				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (modifyBtn.mouseClick(msg)) {
				// δѡ��ѧ��
				if (allStuTable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else {
					// ���ı���
					titleText.setText(L"�޸�ѧ��");
					// ����
					lookBtn.move(-500, 150);
					addBtn.move(-500, 230);
					modifyBtn.move(-500, 310);
					deleteBtn.move(-500, 390);
					sortBtn.move(-500, 470);
					sortyearBtn.move(-500, 470);
					exportBtn.move(-500, 550);
					inportBtn.move(-500, 630);
					backButton.move(-500, 720);


					// ʹ��񲻿ɱ仯
					allStuTable.canChange = false;


					// ��ȡ��ǰ��
					int selectedRow = allStuTable.getSelectedRow();
					vector<std::wstring> selectedData = allStuData[selectedRow];


					// �ı���Ĭ������
					IDText.setText((L"ѧ��:" + selectedData[0]).c_str()); // C++�﷨
					nameBox.setText(selectedData[1].c_str());
					genderBox.setText(selectedData[2].c_str());
					gradeBox.setText(selectedData[3].c_str());
					collegeBox.setText(selectedData[4].c_str());
					majorBox.setText(selectedData[5].c_str());

					// ��ʾ
					IDText.move(20, 180);
					nameBox.move(10, 220);
					genderBox.move(10, 290);
					gradeBox.move(10, 360);
					collegeBox.move(10, 430);
					majorBox.move(10, 500);
					modifyOKButton.move(10, 580);
					cancelButton.move(10, 660);
				}

			}

			if (modifyOKButton.mouseClick(msg)) {
				int id;
				wchar_t name[30];
				wchar_t gender[10];
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
					getTextInBox(name, nameBox.text) &&
					getTextInBox(gender, genderBox.text) &&
					getNumberInBox(9999, &grade, gradeBox.text) &&
					getTextInBox(college, collegeBox.text) &&
					getTextInBox(major, majorBox.text) &&
					(grade > 1970 && grade <= Current_year) &&
					(!wcscmp(gender, L"��") || !wcscmp(gender, L"Ů"))
					) {

					Cpnode CrsNode = allCrsList->next;
					while (CrsNode) {
						Spnode StuInCrsNode = searchStuInCrs(CrsNode, tempID);
						if (StuInCrsNode) {
							modifyStuInCrs(allCrsList, StuInCrsNode, name, tempID, StuInCrsNode->score);
						}
						CrsNode = CrsNode->next;
					}

					// �޸�
					modifyStu(&allStuList, modifyingStu, name, tempID, wcscmp(gender, L"��") == 0 ? 1 : 0, grade, college, major);

					// ����
					saveStu(allStuList, STU_FILE);
					saveCrs(allCrsList, CRS_FILE);

					writeLog(judge, tch_or_admin, wstring(L"�޸�ѧ��:") + to_wstring(tempID));

					// ʹ���ɱ仯
					allStuTable.canChange = true;

					// ˢ�±��
					showAllStu(allStuList, allStuData, searchInputBox.text);
					allStuTable.setData(allStuData);

					// ������������
					IDBox.clear();
					nameBox.clear();
					genderBox.clear();
					gradeBox.clear();
					collegeBox.clear();
					majorBox.clear();


					// ���ı���
					titleText.setText(L"����ѧ��");

					// ����
					IDBox.move(-500, 150);
					nameBox.move(-500, 220);
					genderBox.move(-500, 290);
					gradeBox.move(-500, 360);
					collegeBox.move(-500, 430);
					majorBox.move(-500, 500);
					modifyOKButton.move(-500, 580);
					cancelButton.move(-500, 660);

					// ��ʾ
					lookBtn.move(-50, 150);
					addBtn.move(-50, 230);
					modifyBtn.move(-50, 310);
					deleteBtn.move(-50, 390);
					sortBtn.move(0, 470);
					sortyearBtn.move(145, 470);
					exportBtn.move(-50, 550);
					inportBtn.move(-50, 630);
					backButton.move(-50, 720);



				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (deleteBtn.mouseClick(msg)) {
				if (allStuTable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else {
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ�����ѧ����?", L"ɾ��ѧ��", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) { // ���ȷ��

						// ��ȷ����ѧ���ڵ�
						int tempID;
						int selectedRow = allStuTable.getSelectedRow(); // ��ȡ��ǰ��
						getNumberInBox(99999999, &tempID, allStuData[selectedRow][0].c_str());
						Node* deletingStu = searchStu(&allStuList, (wchar_t*)allStuData[selectedRow][1].c_str(), tempID);

						// ɾ��
						deleteStu(&allStuList, deletingStu);


						Cpnode CrsNode = allCrsList;

						while (CrsNode) {
							Spnode stunode = CrsNode->sphead->next;
							while (stunode) {
								if (stunode->snum == tempID) {
									deleteStuInCrs(CrsNode, (wchar_t*)allStuData[selectedRow][1].c_str(), tempID);
									break;
								}
								stunode = stunode->next;
							}

							CrsNode = CrsNode->next;
						}



						// ����
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);


						writeLog(judge, tch_or_admin, wstring(L"ɾ��ѧ��:") + to_wstring(tempID));


						// ˢ�±��
						showAllStu(allStuList, allStuData, searchInputBox.text);
						allStuTable.setData(allStuData);
					}
				}
			}


			if (sortBtn.mouseClick(msg)) {
				if (i == 1) {

					int R = allStuData.size() - 1;
					int L = 1;

					while (L < R) {
						for (int i = L; i < R; i++) {
							if (stof(allStuData[i][0]) > stof(allStuData[i + 1][0])) {
								swap(allStuData[i], allStuData[i + 1]);
							}

						}

						R--;
						for (int i = R; i > L; i--) {
							if (stof(allStuData[i][0]) < stof(allStuData[i - 1][0])) {
								swap(allStuData[i], allStuData[i - 1]);
							}
						}

						L++;
					}



					//sortStuaccID(&allStuList);
					i = 0;
				}
				else {

					int R = allStuData.size() - 1;
					int L = 1;

					while (L < R) {
						for (int i = L; i < R; i++) {
							if (stof(allStuData[i][3]) < stof(allStuData[i + 1][3])) {
								swap(allStuData[i], allStuData[i + 1]);
							}

						}

						R--;
						for (int i = R; i > L; i--) {
							if (stof(allStuData[i][3]) > stof(allStuData[i - 1][3])) {
								swap(allStuData[i], allStuData[i - 1]);
							}
						}

						L++;
					}




					//sortStuaccyear(&allStuList);
					i = 1;
				}

				//// ����
				//saveStu(allStuList, STU_FILE);

				// ˢ�±��
				//showAllStu(allStuList, allStuData, L"");
				allStuTable.setData(allStuData);
			}

			if (sortyearBtn.mouseClick(msg)) {

				RankUI(allStuList, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);


				cleardevice();
				Table allStuTable(310, 90, 1160, 700, allStuData);

				titleText.draw();
				searchInputBox.draw();
				searchBtn.draw();
				lookBtn.draw();
				addBtn.draw();
				modifyBtn.draw();
				deleteBtn.draw();
				sortBtn.draw();
				sortyearBtn.draw();
				exportBtn.draw();
				inportBtn.draw();
				backButton.draw();








			}

			if (exportBtn.mouseClick(msg)) {
				if (exportStu(allStuList, ".\\export\\Stu.csv")) {
					MessageBox(GetHWnd(), L"�����ɹ�", L"����ѧ��", 0);
					writeLog(judge, tch_or_admin, wstring(L"����ѧ����Ϣ"));
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
				//freeStu(allStuList);
				//freeCrs(allCrsList);

				return;
				//if (judge == 1)
				//	menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				//else
				//	menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}


			//�����껬������
			allStuTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
			IDBox.onMessage(msg);
			nameBox.onMessage(msg);
			genderBox.onMessage(msg);
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



void StuUI(Node* Crs, List allStuList, wchar_t* pname, int* pid, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, Cpnode allCrsList) {


	cleardevice();

	//Cpnode allCrsList = readCrs(CRS_FILE);

	sortStuCrsYear(Crs->item.crslist);
	Crsnode* allCrsInStuList = Crs->item.crslist->crs_next;

	vector<vector<std::wstring>>allCrsINStuData;
	showStu(Crs, allCrsINStuData, L"");

	Table allCrsINStuTable(310, 90, 1160, 700, allCrsINStuData);

	Text titleText(40, 20, L"���пγ�", 64);
	//�����
	//TextBox searchInputBox(310, 20, 820, L"����", L"");

	TextBox searchInputBox(310, 20, 920, L"����", L"");

	int tmp_course_id = 0;
	int tmp_semester = 0;

	TextBox course_idBox(-500, 100, 290, L"�γ̱��", L"");
	TextBox course_nameBox(-500, 150, 290, L"�γ�����(�Զ�ƥ��)", L"");
	TextBox scoreBox(-500, 220, 290, L"�ɼ�", L"");
	TextBox course_natureBox(-500, 250, 290, L"�γ�����(�Զ�ƥ��)", L"");
	TextBox creditBox(-500, 300, 290, L"ѧ��(�Զ�ƥ��)", L"");
	TextBox gridBox(-500, 350, 290, L"����(�Զ�ת��)", L"");
	TextBox semesterBox(-500, 400, 290, L"ѧ��", L"");

	TextBox allButton(-500, 280, 290, L"   ����", L"");
	TextBox mustButton(-500, 330, 290, L"   ����", L"");
	TextBox allsButton(-500, 380, 290, L"   ����", L"");
	TextBox mustsButton(-500, 430, 290, L"   ����", L"");
	TextBox predictTxt(-500, 480, 290, L"   Ԥ��", L"");


	//��ť
	//Button searchBtn(1150, 20, 100, 50, L"����", 1);
	Button searchBtn(1250, 20, 100, 50, L"����", 1);
	Button chartBtn(1370, 20, 100, 50, L"ͼ��", 1);

	wchar_t aa[100];
	wchar_t bb[100];
	wchar_t cc[100];
	getTextInBox(cc, std::to_wstring(*pid).c_str());//��ֹ�����ת��
	getTextInBox(aa, (wstring(L"ѧ�ţ�") + cc).c_str());
	getTextInBox(bb, (wstring(L"������") + pname).c_str());

	Button idBtn(40, 100, 200, 50, aa, 1);
	Button nameBtn(40, 180, 200, 50, bb, 1);
	//(wstring(L"ѧ�ţ�")+aa).c_str()
	// (wstring(L"������") + pname).c_str()




	Button addCrsBtn(-50, 300, 330, 60, L"   ��ӿγ�", 1);
	Button modifyCrsBtn(-50, 380, 330, 60, L"   ¼��/�޸ĳɼ�", 1);
	Button deleteCrsBtn(-50, 460, 330, 60, L"   ɾ���γ�", 1);
	Button GridCrsBtn(-50, 540, 330, 60, L"   �鿴����", 1);

	Button backButton(-50, 700, 330, 60, L"   ����", 0);


	Button addOKButton(-500, 580, 290, 60, L"ȷ�����", 1);
	Button modifyOKButton(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button cancelButton(-500, 660, 290, 60, L"ȡ��", 0);




	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		searchInputBox.draw();

		course_idBox.draw();
		course_nameBox.draw();
		scoreBox.draw();
		course_natureBox.draw();
		creditBox.draw();
		gridBox.draw();
		semesterBox.draw();/////////////////////////////


		if (peekmessage(&msg, -1, true)) {
			//������¼�

			//����
			if (searchBtn.mouseClick(msg)) {
				showStu(Crs, allCrsINStuData, searchInputBox.text);
				allCrsINStuTable.setData(allCrsINStuData);
			}
			if (chartBtn.mouseClick(msg)) {
				chartUI(allCrsINStuData, 1, 2, 0, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);


				cleardevice();
				allCrsINStuTable.draw();
				titleText.draw();
				searchInputBox.draw();
				searchBtn.draw();
				chartBtn.draw();
				idBtn.draw();
				nameBtn.draw();
				addCrsBtn.draw();
				modifyCrsBtn.draw();
				deleteCrsBtn.draw();
				GridCrsBtn.draw();
				backButton.draw();


			}

			if (addCrsBtn.mouseClick(msg)) {


				// ���ı���
				titleText.setText(L"��ӿγ�");


				// ʹ��񲻿ɱ仯
				allCrsINStuTable.canChange = false;


				//����
				idBtn.move(-500, 100);
				nameBtn.move(-500, 180);

				addCrsBtn.move(-500, 300);
				modifyCrsBtn.move(-500, 380);
				deleteCrsBtn.move(-500, 460);
				GridCrsBtn.move(-500, 540);
				backButton.move(-500, 700);

				//��ʾ
				course_idBox.move(10, 100);
				course_nameBox.move(10, 260);
				scoreBox.move(10, 500);
				course_natureBox.move(10, 340);
				creditBox.move(10, 420);
				gridBox.move(10, 580);
				semesterBox.move(10, 180);

				addOKButton.move(10, 650);
				cancelButton.move(10, 730);

			}

			// �Զ�ƥ�亯��
			if (semesterBox.isInput == false && course_idBox.text
				&& semesterBox.hovered == true
				&& getNumberInBox(100000, &tmp_course_id, course_idBox.text)
				&& tmp_course_id > 10000 && tmp_course_id < 100000
				&& getNumberInBox(2024, &tmp_semester, semesterBox.text)
				&& tmp_semester >= 2000 && tmp_semester <= 2024

				) {
				Cpnode tmpcpnode = searchCrs(allCrsList, tmp_course_id, tmp_semester);
				if (tmpcpnode != NULL) {
					course_nameBox.setText(tmpcpnode->cname);
					course_natureBox.setText(tmpcpnode->character);
					creditBox.setText(to_wstring(tmpcpnode->credit).substr(0, to_wstring(tmpcpnode->credit).find('.') + 2).c_str());

				}
				else {
					course_nameBox.setText(L"");
					course_natureBox.setText(L"");
					creditBox.setText(L"");
				}

			}

			if (addOKButton.mouseClick(msg)) {
				wchar_t course_id[10];//�γ̺�
				wchar_t course_name[100];//�γ���
				double score;//�γ̳ɼ�
				int semester;//ѧ��ѧ��
				wchar_t course_nature[5];//�γ�����
				double credit;//ѧ��
				double grid;//����


				//�жϳ������ʽ
				if (
					getTextInBox(course_id, course_idBox.text) &&
					getTextInBox(course_name, course_nameBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					getNumberInBox(2024, &semester, semesterBox.text) &&
					getTextInBox(course_nature, course_natureBox.text) &&
					getDoubleInBox(4, &credit, creditBox.text) &&
					credit >= 0 && score >= 0 && semester >= 0
					) {

					grid = CalculGPA(score);





					if (searchCrs(allCrsList, stoi(course_id), semester) == NULL) {
						MessageBox(GetHWnd(), L"û�иÿγ�", L"����!", MB_ICONERROR);
					}
					else {
						if (addCrsToStu(Crs, course_id, course_name, score, semester, wcscmp(course_nature, L"����") == 0 ? 1 : 0, credit, grid) == false) {
							MessageBox(GetHWnd(), L"�Ѵ��ڸÿγ�", L"����!", MB_ICONERROR);
							continue;
						}
						else {
							addStuInCrs(searchCrs(allCrsList, stoi(course_id), semester), pname, *pid, score);
						}
					}


					// ����
					saveStu(allStuList, STU_FILE);
					saveCrs(allCrsList, CRS_FILE);

					writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��:") + to_wstring(*pid) + L"  ��ӿγ�:" + course_id);



					allCrsINStuTable.canChange = true;

					// ˢ�±��
					showStu(Crs, allCrsINStuData, L"");

					allCrsINStuTable.setData(allCrsINStuData);


					//���
					course_idBox.clear();
					course_nameBox.clear();
					scoreBox.clear();
					course_natureBox.clear();
					semesterBox.clear();
					creditBox.clear();
					gridBox.clear();

					//����
					course_idBox.move(-500, 100);
					course_nameBox.move(-500, 180);
					scoreBox.move(-500, 260);
					course_natureBox.move(-500, 340);
					creditBox.move(-500, 420);
					gridBox.move(-500, 500);
					semesterBox.move(-500, 580);

					addOKButton.move(-500, 650);
					cancelButton.move(-500, 730);

					// ���ı���
					titleText.setText(L"ѧ���γ�");

					//��ʾ
					idBtn.move(40, 100);
					nameBtn.move(40, 180);


					addCrsBtn.move(-50, 300);
					modifyCrsBtn.move(-50, 380);
					deleteCrsBtn.move(-50, 460);
					GridCrsBtn.move(-500, 540);
					backButton.move(-50, 700);


				}
				else {
					MessageBox(GetHWnd(), L"����������������!", L"����!", MB_ICONERROR);
				}
			}

			if (cancelButton.mouseClick(msg)) {

				// ʹ���ɱ仯
				allCrsINStuTable.canChange = true;


				//���
				course_idBox.clear();
				course_nameBox.clear();
				scoreBox.clear();
				course_natureBox.clear();
				semesterBox.clear();
				creditBox.clear();
				gridBox.clear();

				//����
				course_idBox.move(-500, 100);
				course_nameBox.move(-500, 180);
				scoreBox.move(-500, 260);
				course_natureBox.move(-500, 340);
				creditBox.move(-500, 420);
				gridBox.move(-500, 500);
				semesterBox.move(-500, 580);

				allButton.move(-500, 300);
				mustButton.move(-500, 380);
				allsButton.move(-500, 300);
				mustsButton.move(-500, 380);
				predictTxt.move(-500, 380);

				addOKButton.move(-500, 600);
				modifyOKButton.move(-500, 650);
				cancelButton.move(-500, 700);

				//��ʾ
				idBtn.move(40, 100);
				nameBtn.move(40, 180);


				addCrsBtn.move(-50, 300);
				modifyCrsBtn.move(-50, 380);
				deleteCrsBtn.move(-50, 460);
				GridCrsBtn.move(-50, 540);

				backButton.move(-50, 700);

				// ���ı���
				titleText.setText(L"ѧ���γ�");


			}

			if (modifyCrsBtn.mouseClick(msg)) {

				if (allCrsINStuTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��γ�", L"����!", MB_ICONERROR);
				}
				else
				{
					// ���ı���
					titleText.setText(L"�޸Ŀγ�");


					// ʹ��񲻿ɱ仯
					allCrsINStuTable.canChange = false;


					//����
					idBtn.move(-500, 100);
					nameBtn.move(-500, 180);

					addCrsBtn.move(-500, 300);
					modifyCrsBtn.move(-500, 380);
					deleteCrsBtn.move(-500, 460);
					GridCrsBtn.move(-500, 540);
					backButton.move(-500, 700);

					//��ʾ
					course_idBox.move(10, 100);
					course_nameBox.move(10, 260);
					scoreBox.move(10, 500);
					course_natureBox.move(10, 340);
					creditBox.move(10, 420);
					gridBox.move(10, 580);
					semesterBox.move(10, 180);


					modifyOKButton.move(10, 650);
					cancelButton.move(10, 730);

					// ��ȡ��ǰ��
					int selectedRow = allCrsINStuTable.getSelectedRow();
					vector<std::wstring> selectedData = allCrsINStuData[selectedRow];

					//�ı���Ĭ������
					course_idBox.setText(selectedData[0].c_str());
					course_nameBox.setText(selectedData[1].c_str());
					scoreBox.setText(selectedData[2].c_str());
					semesterBox.setText(selectedData[3].c_str());
					course_natureBox.setText(selectedData[6].c_str());
					creditBox.setText(selectedData[4].c_str());
					gridBox.setText(selectedData[5].c_str());


				}
			}

			if (modifyOKButton.mouseClick(msg)) {

				wchar_t course_id[10];//�γ̺�
				wchar_t course_name[100];//�γ���
				double score;//�γ̳ɼ�
				int semester;//ѧ��ѧ��
				wchar_t course_nature[5];//�γ�����
				double credit;//ѧ��
				double grid;//����

				wchar_t pcourse_id[10];//�������γ̺�
				wchar_t pcourse_name[30];//�������γ��� 
				int selectedRow = allCrsINStuTable.getSelectedRow(); // ��ȡ��ǰ��
				getTextInBox(pcourse_id, allCrsINStuData[selectedRow][0].c_str());
				getTextInBox(pcourse_name, allCrsINStuData[selectedRow][1].c_str());
				Crsnode* tmp = searchCrsInStu(Crs, pcourse_id, pcourse_name);

				//�жϳ������ʽ
				if (
					getTextInBox(course_id, course_idBox.text) &&
					getTextInBox(course_name, course_nameBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					getNumberInBox(2024, &semester, semesterBox.text) &&
					getTextInBox(course_nature, course_natureBox.text) &&
					getDoubleInBox(4, &credit, creditBox.text) &&
					credit >= 0 && score >= 0 && semester >= 0
					) {

					grid = CalculGPA(score);


					//�Ķ��γ̼�����
					Cpnode StuInCrsNode = searchCrs(allCrsList, stoi(allCrsINStuData[selectedRow][0].c_str()), semester);///////
					Spnode StuInCrsNodeTrue = searchStuInCrs(StuInCrsNode, *pid);
					if (StuInCrsNode) {
						modifyCrs(StuInCrsNode, course_name, stoi(course_id), course_nature, credit, semester);
						modifyStuInCrs(StuInCrsNode, StuInCrsNodeTrue, pname, *pid, score);
					}
					else {
						MessageBox(GetHWnd(), L"�γ̴���", L"����!", MB_ICONERROR);
					}

					//�Ķ�����ѧ���γ�
					Node* everystu = allStuList->next;
					while (everystu) {

						Crsnode* everyStuCrs = everystu->item.crslist->crs_next;
						while (everyStuCrs) {
							if (wcscmp(everyStuCrs->score.course_id, allCrsINStuData[selectedRow][0].c_str()) == 0)
							{
								modifyCrsInStu(everyStuCrs, course_id, course_name, everyStuCrs->score.score, semester, wcscmp(course_nature, L"����") == 0 ? 1 : 0, credit, CalculGPA(everyStuCrs->score.score));
							}
							everyStuCrs = everyStuCrs->crs_next;
						}
						everystu = everystu->next;
					}
					//�Ķ��Լ��Ŀγ�
					modifyCrsInStu(tmp, course_id, course_name, score, semester, wcscmp(course_nature, L"����") == 0 ? 1 : 0, credit, CalculGPA(score));








					// ����
					saveCrs(allCrsList, CRS_FILE);
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��:") + to_wstring(*pid) + L"  �޸Ŀγ�:" + course_id);


					//�γ̱仯
					allCrsINStuTable.canChange = true;

					// ˢ�±��
					showStu(Crs, allCrsINStuData, L"");
					allCrsINStuTable.setData(allCrsINStuData);

					//���
					course_idBox.clear();
					course_nameBox.clear();
					scoreBox.clear();
					course_natureBox.clear();
					semesterBox.clear();
					creditBox.clear();
					gridBox.clear();

					//����
					course_idBox.move(-500, 100);
					course_nameBox.move(-500, 180);
					scoreBox.move(-500, 260);
					course_natureBox.move(-500, 340);
					creditBox.move(-500, 420);
					gridBox.move(-500, 500);
					semesterBox.move(-500, 580);

					modifyOKButton.move(-500, 650);
					cancelButton.move(-500, 730);

					// ���ı���
					titleText.setText(L"ѧ���γ�");

					//��ʾ
					idBtn.move(40, 100);
					nameBtn.move(40, 180);


					addCrsBtn.move(-50, 300);
					modifyCrsBtn.move(-50, 380);
					deleteCrsBtn.move(-50, 460);
					GridCrsBtn.move(-50, 540);
					backButton.move(-50, 700);


				}
				else {
					MessageBox(GetHWnd(), L"�޸�������������!", L"����!", MB_ICONERROR);
				}
			}

			if (deleteCrsBtn.mouseClick(msg)) {
				if (allCrsINStuTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��γ�", L"����!", MB_ICONERROR);
				}
				else
				{
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ�������γ���?", L"ɾ���γ�", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) {
						wchar_t pcourse_id[10];//�������γ̺�
						wchar_t pcourse_name[30];//�������γ��� 
						int selectedRow = allCrsINStuTable.getSelectedRow(); // ��ȡ��ǰ��
						getTextInBox(pcourse_id, allCrsINStuData[selectedRow][0].c_str());
						getTextInBox(pcourse_name, allCrsINStuData[selectedRow][1].c_str());
						Crsnode* ttmp = searchCrsInStu(Crs, pcourse_id, pcourse_name);

						deleteCrsInStu(Crs, ttmp);



						Cpnode CrsNode = searchCrs(allCrsList, stoi(pcourse_id), stoi(allCrsINStuData[selectedRow][3].c_str()));
						Spnode stunode = CrsNode->sphead->next;

						while (stunode) {
							if (stunode->snum == *pid) {
								deleteStuInCrs(CrsNode, pname, *pid);
								break;
							}
							stunode = stunode->next;
						}


						// ����
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��:") + to_wstring(*pid) + L"  ɾ���γ�:" + pcourse_id);

						// ˢ�±��
						showStu(Crs, allCrsINStuData, L"");
						allCrsINStuTable.setData(allCrsINStuData);

						//��ʾ
						idBtn.move(40, 100);
						nameBtn.move(40, 180);


						addCrsBtn.move(-50, 300);
						modifyCrsBtn.move(-50, 380);
						deleteCrsBtn.move(-50, 460);
						GridCrsBtn.move(-500, 540);
						backButton.move(-50, 700);

						//����
						course_idBox.move(-500, 100);
						course_nameBox.move(-500, 180);
						scoreBox.move(-500, 260);
						course_natureBox.move(-500, 340);
						creditBox.move(-500, 420);
						gridBox.move(-500, 500);
						semesterBox.move(-500, 580);

						addOKButton.move(-500, 650);
						cancelButton.move(-500, 730);
					}


				}
			}

			if (GridCrsBtn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"���˳ɼ�");


				// ʹ��񲻿ɱ仯
				allCrsINStuTable.canChange = false;


				//����

				addCrsBtn.move(-500, 300);
				modifyCrsBtn.move(-500, 380);
				deleteCrsBtn.move(-500, 460);
				GridCrsBtn.move(-500, 540);

				backButton.move(-500, 700);

				//��ʾ

				allButton.move(0, 270);
				mustButton.move(0, 350);
				allsButton.move(0, 430);
				mustsButton.move(0, 510);
				predictTxt.move(0, 590);

				cancelButton.move(10, 730);

				//���㼨��
				double all, must, alls, musts;

				all = AllGrid(Crs);
				must = MustGrid(Crs);
				alls = AllScore(Crs);
				musts = MustScore(Crs);




				allButton.setText((wstring(L"ƽ�����㣺") + std::to_wstring(all).substr(0, to_wstring(all).find(L'.') + 5)).c_str());
				mustButton.setText((wstring(L"ƽ������(����)��") + std::to_wstring(must).substr(0, to_wstring(must).find(L'.') + 5)).c_str());
				allsButton.setText((wstring(L"ƽ���ɼ���") + std::to_wstring(alls).substr(0, to_wstring(alls).find(L'.') + 3)).c_str());
				mustsButton.setText((wstring(L"ƽ���ɼ�(����)��") + std::to_wstring(musts).substr(0, to_wstring(musts).find(L'.') + 3)).c_str());

				predictTxt.setText((wstring(L"Ԥ����һѧ�꼨�㣺") + std::to_wstring(preditcGrid(allCrsINStuData, 1, 5)).substr(0, to_wstring(preditcGrid(allCrsINStuData, 1, 5)).find(L'.') + 5)).c_str());


			}




			if (backButton.mouseClick(msg))
			{
				return;
				allStuUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}



			//�����껬������
			allCrsINStuTable.onMouse(msg);


			// �ı�������
			searchInputBox.onMessage(msg);
			course_idBox.onMessage(msg);
			//course_nameBox.onMessage(msg);
			scoreBox.onMessage(msg);
			//course_natureBox.onMessage(msg);
			//creditBox.onMessage(msg);
			//gridBox.onMessage(msg);
			semesterBox.onMessage(msg);
		}


		//-------------------------------------------------
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}



}



void RankUI(List StuList, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {
	cleardevice();

	vector<vector<std::wstring>> RankData;
	int number;
	Rank(StuList, RankData, L"", L"", &number);
	saveStu(StuList, STU_FILE);

	Table RankTable(340, 90, 1100, 700, RankData);

	Text titleText(40, 50, L"ѧ������", 64);
	Text tipText(80, 170, L"������ʽ", 32);

	TextBox searchInputBox(340, 20, 420, L"רҵ����", L"");
	TextBox searchInput2Box(820, 20, 420, L"�꼶����", L"");

	Button searchBtn(1350, 20, 100, 50, L"����", 1);

	Button allscoreBtn(-50, 220, 330, 60, L"   ȫ����Ŀ�ɼ�", 1);
	Button allgridBtn(-50, 300, 330, 60, L"   ȫ����Ŀ����", 1);
	Button mustscoreBtn(-50, 380, 330, 60, L"   ���޿�Ŀ�ɼ�", 1);
	Button mustgridBtn(-50, 460, 330, 60, L"   ���޿�Ŀ����", 1);

	Button backButton(-50, 700, 330, 60, L"   ����", 0);

	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		searchInputBox.draw();
		searchInput2Box.draw();

		if (peekmessage(&msg, -1, true)) {

			if (searchBtn.mouseClick(msg)) {
				Rank(StuList, RankData, searchInputBox.text, searchInput2Box.text, &number);
				RankTable.setData(RankData);
			}

			if (allscoreBtn.mouseClick(msg)) {
				//for (vector<std::wstring>& a : RankData)
					//	//std::cout << stold(a[4]) << std::endl;
					//	//std::wcout << a[4]<<std::endl;
					//std::sort(RankData.begin(), RankData.end(), [](vector<std::wstring>& a, vector<std::wstring>& b)->bool {
					//	
					//	//return 1;
					//	return a[4]> b[4];
					//	});
					//for (vector<std::wstring>& a : RankData)
					//	std::wcout << a[4] << std::endl;

					///////////////////////////////////

				int R = number - 1;
				int L = 1;

				while (L < R) {
					for (int i = L; i < R; i++) {
						if (stof(RankData[i][4]) < stof(RankData[i + 1][4])) {
							swap(RankData[i], RankData[i + 1]);
						}

					}

					R--;
					for (int i = R; i > L; i--) {
						if (stof(RankData[i][4]) > stof(RankData[i - 1][4])) {
							swap(RankData[i], RankData[i - 1]);
						}
					}

					L++;
				}



				RankTable.setData(RankData);

			}

			if (allgridBtn.mouseClick(msg)) {

				int R = number - 1;
				int L = 1;

				while (L < R) {
					for (int i = L; i < R; i++) {
						if (stof(RankData[i][5]) < stof(RankData[i + 1][5])) {
							swap(RankData[i], RankData[i + 1]);
						}

					}

					R--;
					for (int i = R; i > L; i--) {
						if (stof(RankData[i][5]) > stof(RankData[i - 1][5])) {
							swap(RankData[i], RankData[i - 1]);
						}
					}

					L++;
				}

				RankTable.setData(RankData);
			}

			if (mustscoreBtn.mouseClick(msg)) {

				int R = number - 1;
				int L = 1;

				while (L < R) {
					for (int i = L; i < R; i++) {
						if (stof(RankData[i][6]) < stof(RankData[i + 1][6])) {
							swap(RankData[i], RankData[i + 1]);
						}

					}

					R--;
					for (int i = R; i > L; i--) {
						if (stof(RankData[i][6]) > stof(RankData[i - 1][6])) {
							swap(RankData[i], RankData[i - 1]);
						}
					}

					L++;
				}

				RankTable.setData(RankData);
			}

			if (mustgridBtn.mouseClick(msg)) {

				int R = number - 1;
				int L = 1;

				while (L < R) {
					for (int i = L; i < R; i++) {
						if (stof(RankData[i][7]) < stof(RankData[i + 1][7])) {
							swap(RankData[i], RankData[i + 1]);
						}

					}

					R--;
					for (int i = R; i > L; i--) {
						if (stof(RankData[i][7]) > stof(RankData[i - 1][7])) {
							swap(RankData[i], RankData[i - 1]);
						}
					}

					L++;
				}

				RankTable.setData(RankData);
			}

			if (backButton.mouseClick(msg)) {
				return;
				allStuUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}

			//�����껬������
			RankTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
			searchInput2Box.onMessage(msg);
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


void swap(vector<wstring>* a, vector<wstring>* b) {
	vector<wstring> c;
	c.push_back(L"");
	c = *a;
	*a = *b;
	*b = c;


}

