#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define TCH_FILE ".\\data\\Teacher.txt"
#define ADMIN_FILE ".\\data\\Administrator.txt"
#define CRS_FILE ".\\data\\Course.txt"


int mainLin() {
	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����

	// ��ʼ��ͼ�δ���
	initgraph(1500, 810);
	BeginBatchDraw(); //��ʼ������ͼ
	setbkcolor(RGB(55, 61, 53)); //������ɫ
	cleardevice();

	/*wchar_t paper_name[200];
	wchar_t journal_or_conference_name[200];
	wchar_t author[200];
	wchar_t date[200];
	wchar_t volume_num[200];
	wchar_t issue_num[200];
	wchar_t page[200];
	double GPA_bonus;

	getText(paper_name);
	getText(journal_or_conference_name);
	getText(author);
	getText(date);
	getText(volume_num);
	getText(issue_num);
	getText(page);
	GPA_bonus = getDouble(10);

	List Stu = readStu(STU_FILE);
	wchar_t pn[20] = L"paper1";
	Rnode* tar = searchRnode(&Stu, pn);
	modifyQuality_rlist(tar, paper_name,
		journal_or_conference_name,
		author,
		date,
		volume_num,
		issue_num,
		page,
		GPA_bonus
	);

	printStu(Stu);
	*/

	//List admin_List = readAdmin(ADMIN_FILE);
	//Node* admin = admin_List->next;
	//
	//manageUI(admin, admin_List);
	loginUI();




	EndBatchDraw(); //����������ͼ
	closegraph(); // �ر�ͼ�δ���



	return 0;
}

void loginUI() {
	cleardevice();

	IMAGE Image;
	loadimage(&Image, L".\\res\\logo.jpg", 150, 150, true);
	putimage(200, 75, &Image, SRCCOPY);


	//drawLine();

	List allStuList = readStu(STU_FILE);
	List allTchList = readTch(TCH_FILE);
	Cpnode allCrsList = readCrs(CRS_FILE);
	List allAdminList = readAdmin(ADMIN_FILE);

	/*Node* Stu = StuList->next;
	Node* Tch = TchList->next;
	Node* Admin = AdminList->next;*/

	Text titleText(400, 120, L"��ã���ӭ��½ JLU �ɼ�����ϵͳ!", 64);
	TextBox accountBox(200, 330, 1100, L"�˺�", L"");
	TextBox passwordBox(200, 430, 1100, L"����", L"");
	Button loginButton(200, 530, 530, 60, L"��¼", 1);
	Button exitButton(770, 530, 530, 60, L"�˳�", 0);
	//Button modify_password_Button(860, 600, 220, 50, L"�޸�����", 1);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		accountBox.draw();
		passwordBox.draw();

		if (peekmessage(&msg, -1, true)) {

			if (loginButton.mouseClick(msg)) {

				wstring tmp_password;

				Node* Stu = allStuList->next;
				Node* Tch = allTchList->next;
				Node* Admin = allAdminList->next;

				while (Stu != NULL) {
					if (wcscmp((to_wstring(Stu->item.data.ID)).c_str(), (const wchar_t*)accountBox.text) == 0) {
						tmp_password = wstring(Stu->item.data.password);
						break;
					}
					Stu = Stu->next;
				}

				while (Tch != NULL) {
					if (wcscmp((to_wstring(Tch->item.data.ID)).c_str(), (const wchar_t*)accountBox.text) == 0) {
						tmp_password = wstring(Tch->item.data.password);
						break;
					}
					Tch = Tch->next;
				}

				while (Admin != NULL) {
					if (wcscmp((to_wstring(Admin->item.data.ID)).c_str(), (const wchar_t*)accountBox.text) == 0) {
						tmp_password = wstring(Admin->item.data.password);
						break;
					}
					Admin = Admin->next;
				}

				if (Stu == NULL && Tch == NULL && Admin == NULL) { //û��ѧ��ID/��ʦ����/����Աid ��֮��Ӧ
					MessageBox(GetHWnd(), L"����������˺ţ����������룡", L"����!", MB_ICONWARNING);
					accountBox.clear();
					passwordBox.clear();
				}
				else if (wcscmp(tmp_password.c_str(), (const wchar_t*)passwordBox.text) == 0) {//�������Ӧ����ȷ����������������бȽ�
					if (Stu != NULL) {//˵����¼����ѧ�����˺�
						writeLog(0, Stu, wstring(L"����ϵͳ"));
						stuAccountUI(Stu->item.data.ID, Stu, allAdminList, allStuList, allCrsList);
					}
					else if (Tch != NULL) {
						writeLog(1, Tch, wstring(L"����ϵͳ"));
						menuUI_Tch(Tch, allTchList, Tch, allAdminList, allStuList, allCrsList);
					}
					else {
						writeLog(2, Admin, wstring(L"����ϵͳ"));
						menuUI_Administrator(Admin, allAdminList, allStuList, allCrsList);
					}
				}
				else {
					MessageBox(GetHWnd(), L"����������������룡", L"����!", MB_ICONWARNING);
					passwordBox.clear();
				}
			}

			if (exitButton.mouseClick(msg)) {
				freeStu(allStuList);
				freeCrs(allCrsList);
				exit(0);
			}

			/*if (modify_password_Button.mouseClick(msg)) {

				wstring tmp_password;

				while (Stu != NULL) {
					if (wcscmp((to_wstring(Stu->item.data.ID)).c_str(), accountBox.text) == 0) {
						tmp_password = wstring(Stu->item.data.password);
						break;
					}
					Stu = Stu->next;
				}

				while (Tch != NULL) {
					if (wcscmp((to_wstring(Tch->item.data.ID)).c_str(), accountBox.text) == 0) {
						tmp_password = wstring(Tch->item.data.password);
						break;
					}
					Tch = Tch->next;
				}

				if (Stu == NULL && Tch == NULL) {
					MessageBox(GetHWnd(), L"����������˺ţ��޷��޸����룡", L"����", MB_ICONWARNING);
					accountBox.clear();
					passwordBox.clear();
				}
				else if (wcscmp(tmp_password.c_str(), passwordBox.text) == 0) {//�����ѧ��/��ʦ��Ӧ����ȷ����������������бȽ�
					if (Stu != NULL)//˵���ĵ���ѧ���˺ŵ�����
						Modify_Password_UI(accountBox.text, Stu, 0, StuList);
					else
						Modify_Password_UI(accountBox.text, Tch, 1, TchList);
				}
					else {
						MessageBox(GetHWnd(), L"ԭ��������޷��޸����룡", L"����", MB_ICONWARNING);
						passwordBox.clear();
					}
				}*/

				// �ı�������
			accountBox.onMessage(msg);
			passwordBox.onMessage(msg);

		}

		//showxy(msg);



		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}

}

void manageUI(Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {	//����Ա�����������

	cleardevice();

	//List allStuList = readStu(STU_FILE);
	List allTchList = readTch(TCH_FILE);

	vector<vector<std::wstring>>Stu_Password_Data;
	vector<vector<std::wstring>>Tch_Password_Data;

	ShowStu_Password(allStuList, Stu_Password_Data, L"");
	ShowTch_Password(allTchList, Tch_Password_Data, L"");

	Table Stu_ptable(310, 90, 580 - 15, 700, Stu_Password_Data);
	Table Tch_ptable(905, 90, 580 - 15, 700, Tch_Password_Data);


	Text titleText(10, 90, L"ȫ���������", 63);
	TextBox searchStuInputBox(310, 20, 450, L"����ѧ��", L"");
	TextBox searchTchInputBox(905, 20, 450, L"������ʦ", L"");


	Button searchStuBtn(775, 20, 100, 50, L"����", 1);
	Button searchTchBtn(1370, 20, 100, 50, L"����", 1);
	Button sortBtn(30, 210, 200, 60, L"<��ѧ��/��������>", 1);
	Button modify_Stu_Btn(-50, 300, 330, 60, L"   �޸�ѧ������", 1);
	Button modify_Tch_Btn(-50, 380, 330, 60, L"   �޸Ľ�ʦ����", 1);
	Button backButton(-50, 620, 330, 60, L"   ����", 0);


	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//->
		// ��������(����)
		searchStuInputBox.draw();
		searchTchInputBox.draw();


		if (peekmessage(&msg, -1, true)) {
			if (searchStuBtn.mouseClick(msg)) {
				ShowStu_Password(allStuList, Stu_Password_Data, searchStuInputBox.text);
				Stu_ptable.setData(Stu_Password_Data);
			}

			if (searchTchBtn.mouseClick(msg)) {
				ShowTch_Password(allTchList, Tch_Password_Data, searchTchInputBox.text);
				Tch_ptable.setData(Tch_Password_Data);
			}

			if (sortBtn.mouseClick(msg)) {

				sortStuaccID(&allStuList);
				sortStuaccID(&allTchList);

				// ˢ�±��
				ShowStu_Password(allStuList, Stu_Password_Data, L"");
				Stu_ptable.setData(Stu_Password_Data);

				ShowTch_Password(allTchList, Tch_Password_Data, L"");
				Tch_ptable.setData(Tch_Password_Data);

			}

			if (modify_Stu_Btn.mouseClick(msg)) {
				// δѡ��ѧ��
				if (Stu_ptable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else {
					// ��ȷ����ѧ���ڵ�
					int tempID;
					int selectedRow = Stu_ptable.getSelectedRow(); // ��ȡ��ǰ��
					getNumberInBox(99999999, &tempID, Stu_Password_Data[selectedRow][0].c_str());
					Node* modifyingStu = searchStu(&allStuList, (wchar_t*)Stu_Password_Data[selectedRow][1].c_str(), tempID);
					Modify_Stu_or_Tch_Password_UI(to_wstring(modifyingStu->item.data.ID).c_str(), modifyingStu, 3, allStuList, admin, Admin_List, allStuList, allCrsList);
					//���� manageUIʱ �Զ������Զ�ˢ��				

					cleardevice();
					Stu_ptable.draw();
					Tch_ptable.draw();
					titleText.draw();
					searchStuInputBox.draw();
					searchTchInputBox.draw();
					searchStuBtn.draw();
					searchTchBtn.draw();
					sortBtn.draw();
					modify_Stu_Btn.draw();
					modify_Tch_Btn.draw();
					backButton.draw();

					ShowStu_Password(allStuList, Stu_Password_Data, L"");

					Stu_ptable.setData(Stu_Password_Data);

				}
			}

			if (modify_Tch_Btn.mouseClick(msg)) {
				// δѡ���ʦ
				if (Tch_ptable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ����ʦ", L"����!", MB_ICONERROR);
				}
				else {
					// ��ȷ������ʦ�ڵ�
					int tempID;
					int selectedRow = Tch_ptable.getSelectedRow(); // ��ȡ��ǰ��
					getNumberInBox(99999999, &tempID, Tch_Password_Data[selectedRow][0].c_str());
					Node* modifyingTch = searchStu(&allTchList, (wchar_t*)Tch_Password_Data[selectedRow][1].c_str(), tempID);
					Modify_Stu_or_Tch_Password_UI(to_wstring(modifyingTch->item.data.ID).c_str(), modifyingTch, 4, allTchList, admin, Admin_List, allStuList, allCrsList);
					//���� manageUIʱ �Զ������Զ�ˢ��				


					cleardevice();
					Stu_ptable.draw();
					Tch_ptable.draw();
					titleText.draw();
					searchStuInputBox.draw();
					searchTchInputBox.draw();
					searchStuBtn.draw();
					searchTchBtn.draw();
					sortBtn.draw();
					modify_Stu_Btn.draw();
					modify_Tch_Btn.draw();
					backButton.draw();

					ShowTch_Password(allTchList, Tch_Password_Data, L"");

					Tch_ptable.setData(Tch_Password_Data);
				}

			}


			if (backButton.mouseClick(msg)) {
				return;
				menuUI_Administrator(admin, Admin_List, allStuList, allCrsList);
			}


			//�����껬������
			Stu_ptable.onMouse(msg);
			Tch_ptable.onMouse(msg);


			// �ı�������
			searchStuInputBox.onMessage(msg);
			searchTchInputBox.onMessage(msg);



		}

		//showxy(msg);



		//<-
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}


}

void Modify_Stu_or_Tch_Password_UI(const wchar_t* account, Node* Stu, int judge, List StuList, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {//judge�� 0Ϊ��ѧ���˽�������� 1Ϊ�ӽ�ʦ�˽�������� 3Ϊ�ӹ���Ա�˽����޸�ѧ�� 4Ϊ�ӹ���Ա�˽����޸���ʦ

	cleardevice();


	//drawLine();


	Text titleText(300, 100, L"��ã����޸�������룡", 64);

	TextBox accountBox(300, 300, 900, L"�˺�", L"");
	TextBox old_passwordBox(300, 380, 900, L"ԭ����", L"");
	TextBox new_passwordBox(300, 460, 900, L"������������", L"");
	TextBox confirm_passwordBox(300, 540, 900, L"��ȷ��������", L"");
	Button modify_OK_Button(585, 620, 330, 60, L"ȷ���޸�", 1);
	Button backButton(585, 700, 330, 60, L"ȡ���޸�", 0);

	if (judge == 0 || judge == 3) {
		Text IDText(300, 200, L"", 32);
		wstring show_ID = L"ѧ�ţ�" + to_wstring(Stu->item.data.ID);
		IDText.setText(show_ID.c_str());
	}
	if (judge == 1 || judge == 4) {
		Text IDText(300, 200, L"", 32);
		wstring show_ID = L"���ţ�" + to_wstring(Stu->item.data.ID);
		IDText.setText(show_ID.c_str());
	}

	Text nameText(300, 230, L"", 32);
	wstring tmp_name = Stu->item.data.name;
	wstring show_name = L"������" + tmp_name;
	nameText.setText(show_name.c_str());

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		accountBox.draw();
		old_passwordBox.draw();
		new_passwordBox.draw();
		confirm_passwordBox.draw();

		//�ı���Ĭ������
		wstring show_account = L"�˺ţ�" + (wstring)account;
		accountBox.setText(show_account.c_str());
		wstring show_old_password = L"ԭ���룺" + (wstring)Stu->item.data.password;
		old_passwordBox.setText(show_old_password.c_str());

		if (peekmessage(&msg, -1, true)) {

			if (modify_OK_Button.mouseClick(msg)) {

				if (wcscmp(new_passwordBox.text, confirm_passwordBox.text) == 0) {

					wcscpy(Stu->item.data.password, new_passwordBox.text);

					if (judge == 0 || judge == 3) {
						saveStu(StuList, STU_FILE);
						if (judge == 0) {
							writeLog(judge, Stu, wstring(L"�޸�ѧ��") + to_wstring(Stu->item.data.ID) + L"������");
						}
						else {
							writeLog(judge, admin, wstring(L"�޸�ѧ��") + to_wstring(Stu->item.data.ID) + L"������");
						}
					}

					if (judge == 1 || judge == 4) {
						saveTch(StuList, TCH_FILE);
						if (judge == 1) {
							writeLog(judge, Stu, wstring(L"�޸Ľ�ʦ") + to_wstring(Stu->item.data.ID) + L"������");
						}
						else {
							writeLog(judge, admin, wstring(L"�޸Ľ�ʦ") + to_wstring(Stu->item.data.ID) + L"������");
						}
					}

					// ������������
					accountBox.clear();
					old_passwordBox.clear();
					new_passwordBox.clear();
					confirm_passwordBox.clear();

					//�Զ�����
					return;
					if (judge == 0)
						stuAccountUI(Stu->item.data.ID, admin, Admin_List, allStuList, allCrsList);
					else if (judge == 1)
						menuUI_Tch(Stu, StuList, admin, Admin_List, allStuList, allCrsList);
					else
						manageUI(admin, Admin_List, allStuList, allCrsList);

				}
				else {
					MessageBox(GetHWnd(), L"������������벻һ�£�", L"����!", MB_ICONWARNING);
					new_passwordBox.clear();
					confirm_passwordBox.clear();
				}

			}

			if (backButton.mouseClick(msg)) {
				return;
				if (judge == 0)
					stuAccountUI(Stu->item.data.ID, admin, Admin_List, allStuList, allCrsList);
				else if (judge == 1)
					menuUI_Tch(Stu, StuList, admin, Admin_List, allStuList, allCrsList);
				else
					manageUI(admin, Admin_List, allStuList, allCrsList);

			}


			// �ı�������
			new_passwordBox.onMessage(msg);
			confirm_passwordBox.onMessage(msg);

		}

		//showxy(msg);



		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}

}

void allQualityUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {

	cleardevice();

	//List allStuList = readStu(STU_FILE);

	vector<vector<std::wstring>> allQuality_Data;
	//vector<vector<std::wstring>> Stu_Research_Data;

	showAllStu(allStuList, allQuality_Data, L"");

	Table allQuality_Table(310, 90, 1160, 700, allQuality_Data);
	bool click = false;

	Text titleText(10, 100, L"��������Ŀ����", 50);
	//Text IDText(-500, 200, L"", 32);

	TextBox searchInputBox(310, 20, 1040, L"����", L"");

	Button searchBtn(1370, 20, 100, 50, L"����", 1);
	Button sortBtn(30, 270, 200, 60, L"<��ѧ��/�꼶����>", 1);
	Button search_for_quality_Btn(-50, 360, 330, 60, L"   ��ѯ", 1);
	Button exportBtn(-50, 440, 330, 60, L"   ����", 1);
	Button inportBtn(-50, 520, 330, 60, L"   ����", 1);
	Button backButton(-50, 600, 330, 60, L"   ����", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//->
		// ��������(����)
		searchInputBox.draw();

		if (peekmessage(&msg, -1, true)) {

			// ������¼�
			if (searchBtn.mouseClick(msg)) {
				showAllStu(allStuList, allQuality_Data, searchInputBox.text);
				allQuality_Table.setData(allQuality_Data);
			}

			if (sortBtn.mouseClick(msg)) {
				if (click) {
					sortStuaccID(&allStuList);
					click = false;
				}
				else {
					sortStuaccyear(&allStuList);
					click = true;
				}

				// ����
				saveStu(allStuList, STU_FILE);

				// ˢ�±��
				showAllStu(allStuList, allQuality_Data, L"");
				allQuality_Table.setData(allQuality_Data);

			}

			if (search_for_quality_Btn.mouseClick(msg)) {
				if (allQuality_Table.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��ѧ��", L"����!", MB_ICONERROR);
				}
				else {
					// ��ȷ����ѧ���ڵ�
					int tempID;
					int selectedRow = allQuality_Table.getSelectedRow();
					getNumberInBox(99999999, &tempID, allQuality_Data[selectedRow][0].c_str());
					Node* modifyingStu = searchStu(&allStuList, (wchar_t*)allQuality_Data[selectedRow][1].c_str(), tempID);
					QualityUI(modifyingStu, allStuList, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allCrsList);



					cleardevice();
					allQuality_Table.draw();
					titleText.draw();
					searchInputBox.draw();
					searchBtn.draw();
					sortBtn.draw();
					search_for_quality_Btn.draw();
					exportBtn.draw();
					inportBtn.draw();
					backButton.draw();







				}

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
				showAllStu(allStuList, allQuality_Data, L"");
				allQuality_Table.setData(allQuality_Data);

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
			allQuality_Table.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);

		}


		//showxy(msg);



		//<-
		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}

}

void QualityUI(Node* Stu, List allStuList, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, Cpnode allCrsList) {

	cleardevice();

	vector<vector<std::wstring>>ResearchData;
	vector<vector<std::wstring>>CompetitionData;

	ShowStu_Research(Stu, ResearchData);
	ShowStu_Competition(Stu, CompetitionData);

	Table Stu_Rtable(310, 90, 1160, 350, ResearchData);
	Table Stu_Ctable(310, 450, 1160, 350, CompetitionData);


	//TextBox searchInputBox(310, 20, 820, L"����", L"");
	Text titleText(5, 30, L"��ѧ����������Ŀ", 50);
	Text IDText(500, 45, L"", 32);
	wstring show_ID = L"ѧ�ţ�" + to_wstring(Stu->item.data.ID);
	IDText.setText(show_ID.c_str());

	Text nameText(850, 45, L"", 32);
	wstring tmp_name = Stu->item.data.name;
	wstring show_name = L"������" + tmp_name;
	nameText.setText(show_name.c_str());

	TextBox paper_nameBox(-500, 200, 290, L"��������", L"");
	TextBox journal_or_conference_nameBox(-500, 270, 290, L"������ڿ�/��������", L"");
	TextBox authorBox(-500, 340, 290, L"�������", L"");
	TextBox dateBox(-500, 410, 290, L"����ʱ��", L"");
	TextBox volume_numBox(-500, 480, 290, L"����", L"");
	TextBox issue_numBox(-500, 550, 290, L"����", L"");
	TextBox pageBox(-500, 620, 290, L"ҳ�뷶Χ", L"");
	TextBox GPA_bonusBox(-500, 690, 290, L"����ӷ�", L"");

	TextBox competition_nameBox(-500, 200, 290, L"��������", L"");
	TextBox organizerBox(-500, 270, 290, L"�ٰ쵥λ", L"");
	TextBox categoryBox(-500, 340, 290, L"�����", L"");
	TextBox C_dateBox(-500, 410, 290, L"��ʱ��", L"");
	TextBox C_GPA_bonusBox(-500, 690, 290, L"����ӷ�", L"");



	//���뵥��ѧ�������������� һ��ʼ��ʾ��

	Button sort_Btn(30, 120, 200, 60, L"<������ӷ�����>", 1);

	Button add_Research_Btn(-50, 200, 330, 60, L"   ���гɹ����", 1);
	Button modify_Research_Btn(-50, 280, 330, 60, L"   ���гɹ��޸�", 1);
	Button delete_Research_Btn(-50, 360, 330, 60, L"   ���гɹ�ɾ��", 1);
	Button add_Competition_Btn(-50, 460, 330, 60, L"   ���������", 1);
	Button modify_Competition_Btn(-50, 540, 330, 60, L"   �������޸�", 1);
	Button delete_Competition_Btn(-50, 620, 330, 60, L"   ������ɾ��", 1);


	Button backButton(-50, 700, 330, 60, L"����", 0);


	Button modify_ResearchOK_Btn(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button add_ResearchOK_Btn(-500, 640, 290, 60, L"ȷ�����", 1);
	Button modify_CompetitionOK_Btn(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button add_CompetitionOK_Btn(-500, 640, 290, 60, L"ȷ�����", 1);

	Button cancel_modifyResearch_Btn(-500, 720, 290, 60, L"ȡ���޸�", 0);
	Button cancel_addResearch_Btn(-500, 720, 290, 60, L"ȡ�����", 0);
	Button cancel_modifyCompetition_Btn(-500, 720, 290, 60, L"ȡ���޸�", 0);
	Button cancel_addCompetition_Btn(-500, 720, 290, 60, L"ȡ�����", 0);


	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// ��������(����)
		paper_nameBox.draw();
		journal_or_conference_nameBox.draw();
		authorBox.draw();
		dateBox.draw();
		volume_numBox.draw();
		issue_numBox.draw();
		pageBox.draw();
		GPA_bonusBox.draw();

		competition_nameBox.draw();
		organizerBox.draw();
		categoryBox.draw();
		C_dateBox.draw();
		C_GPA_bonusBox.draw();



		if (peekmessage(&msg, -1, true)) {

			if (sort_Btn.mouseClick(msg)) {


				int R_number = ResearchData.size();
				int C_number = CompetitionData.size();

				int R1 = R_number - 1;
				int L1 = 1;

				int R2 = C_number - 1;
				int L2 = 1;

				while (L1 < R1) {
					for (int i = L1; i < R1; i++) {
						if (stof(ResearchData[i][7]) < stof(ResearchData[i + 1][7])) {
							swap(ResearchData[i], ResearchData[i + 1]);
						}

					}
					R1--;
					for (int i = R1; i > L1; i--) {
						if (stof(ResearchData[i][7]) > stof(ResearchData[i - 1][7])) {
							swap(ResearchData[i], ResearchData[i - 1]);
						}
					}

					L1++;
				}

				while (L2 < R2) {
					for (int i = L2; i < R2; i++) {
						if (stof(CompetitionData[i][4]) < stof(CompetitionData[i + 1][4])) {
							swap(CompetitionData[i], CompetitionData[i + 1]);
						}

					}
					R2--;
					for (int i = R2; i > L2; i--) {
						if (stof(CompetitionData[i][4]) > stof(CompetitionData[i - 1][4])) {
							swap(CompetitionData[i], CompetitionData[i - 1]);
						}
					}

					L2++;
				}

				Stu_Rtable.setData(ResearchData);
				Stu_Ctable.setData(CompetitionData);

			}

			if (add_Research_Btn.mouseClick(msg)) {

				titleText.setText(L"  ���гɹ����");
				titleText.move(10, 3);
				//����
				sort_Btn.move(-500, 120);
				add_Research_Btn.move(-500, 200);
				modify_Research_Btn.move(-500, 280);
				delete_Research_Btn.move(-500, 360);
				add_Competition_Btn.move(-500, 460);
				modify_Competition_Btn.move(-500, 540);
				delete_Competition_Btn.move(-500, 620);
				backButton.move(-500, 700);

				//��ʾ
				add_ResearchOK_Btn.move(10, 640);
				cancel_addResearch_Btn.move(10, 720);

				paper_nameBox.move(10, 70);
				journal_or_conference_nameBox.move(10, 140);
				authorBox.move(10, 210);
				dateBox.move(10, 280);
				volume_numBox.move(10, 350);
				issue_numBox.move(10, 420);
				pageBox.move(10, 490);
				GPA_bonusBox.move(10, 560);

			}

			if (add_ResearchOK_Btn.mouseClick(msg)) {

				wchar_t paper_name[200];//��������
				wchar_t journal_or_conference_name[200];//��������ڿ����������
				wchar_t author[200];// ����������Ƿ�ΪͨѶ���߼���������
				wchar_t date[200];// ��������
				wchar_t volume_num[200];// ����
				wchar_t issue_num[200];// ����
				wchar_t page[200];// ҳ�뷶Χ
				double GPA_bonus;

				// �ж������ʽ
				if (
					getTextInBox(paper_name, paper_nameBox.text) &&
					getTextInBox(journal_or_conference_name, journal_or_conference_nameBox.text) &&
					getTextInBox(author, authorBox.text) &&
					getTextInBox(date, dateBox.text) &&
					getTextInBox(volume_num, volume_numBox.text) &&
					getTextInBox(issue_num, issue_numBox.text) &&
					getTextInBox(page, pageBox.text) &&
					getDoubleInBox(10, &GPA_bonus, GPA_bonusBox.text)
					) {

					if (!addQuality_rlist(Stu, paper_name,
						journal_or_conference_name, author, date,
						volume_num, issue_num, page, GPA_bonus)) {
						MessageBox(GetHWnd(), L"�ÿ��гɹ��Ѿ�����,�����ظ����!", L"����!", MB_ICONERROR);


						// ������������
						paper_nameBox.clear();
						journal_or_conference_nameBox.clear();
						authorBox.clear();
						dateBox.clear();
						volume_numBox.clear();
						issue_numBox.clear();
						pageBox.clear();
						GPA_bonusBox.clear();

					}
					else {
						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"�����������Ŀ");

						// ʹ���ɱ仯
						Stu_Rtable.canChange = true;

						// ˢ�±��
						ShowStu_Research(Stu, ResearchData);
						Stu_Rtable.setData(ResearchData);

						// ������������
						paper_nameBox.clear();
						journal_or_conference_nameBox.clear();
						authorBox.clear();
						dateBox.clear();
						volume_numBox.clear();
						issue_numBox.clear();
						pageBox.clear();
						GPA_bonusBox.clear();

						// ���ı���
						titleText.setText(L"��ѧ����������Ŀ");

						//����
						paper_nameBox.move(-500, 70);
						journal_or_conference_nameBox.move(-500, 140);
						authorBox.move(-500, 210);
						dateBox.move(-500, 280);
						volume_numBox.move(-500, 350);
						issue_numBox.move(-500, 420);
						pageBox.move(-500, 490);
						GPA_bonusBox.move(-500, 560);
						add_ResearchOK_Btn.move(-500, 640);
						cancel_addResearch_Btn.move(-500, 720);

						//��ʾ
						sort_Btn.move(30, 120);
						add_Research_Btn.move(-50, 200);
						modify_Research_Btn.move(-50, 280);
						delete_Research_Btn.move(-50, 360);
						add_Competition_Btn.move(-50, 460);
						modify_Competition_Btn.move(-50, 540);
						delete_Competition_Btn.move(-50, 620);
						backButton.move(-50, 700);
						titleText.move(5, 30);

					}
				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}
			}

			if (cancel_addResearch_Btn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"��ѧ����������Ŀ");

				// ������������
				paper_nameBox.clear();
				journal_or_conference_nameBox.clear();
				authorBox.clear();
				dateBox.clear();
				volume_numBox.clear();
				issue_numBox.clear();
				pageBox.clear();
				GPA_bonusBox.clear();


				//����
				paper_nameBox.move(-500, 70);
				journal_or_conference_nameBox.move(-500, 140);
				authorBox.move(-500, 210);
				dateBox.move(-500, 280);
				volume_numBox.move(-500, 350);
				issue_numBox.move(-500, 420);
				pageBox.move(-500, 490);
				GPA_bonusBox.move(-500, 560);
				add_ResearchOK_Btn.move(-500, 640);
				cancel_addResearch_Btn.move(-500, 720);

				//��ʾ
				sort_Btn.move(30, 120);
				add_Research_Btn.move(-50, 200);
				modify_Research_Btn.move(-50, 280);
				delete_Research_Btn.move(-50, 360);
				add_Competition_Btn.move(-50, 460);
				modify_Competition_Btn.move(-50, 540);
				delete_Competition_Btn.move(-50, 620);
				backButton.move(-50, 700);
				titleText.move(5, 30);


			}

			if (add_Competition_Btn.mouseClick(msg)) {

				titleText.setText(L" ���������");

				//����
				sort_Btn.move(-500, 120);
				add_Research_Btn.move(-500, 200);
				modify_Research_Btn.move(-500, 280);
				delete_Research_Btn.move(-500, 360);
				add_Competition_Btn.move(-500, 460);
				modify_Competition_Btn.move(-500, 540);
				delete_Competition_Btn.move(-500, 620);
				backButton.move(-500, 700);

				//��ʾ
				add_CompetitionOK_Btn.move(10, 570);
				cancel_addCompetition_Btn.move(10, 650);

				competition_nameBox.move(10, 200);
				organizerBox.move(10, 270);
				categoryBox.move(10, 340);
				C_dateBox.move(10, 410);
				C_GPA_bonusBox.move(10, 480);
				titleText.move(10, 100);


			}

			if (add_CompetitionOK_Btn.mouseClick(msg)) {

				wchar_t competition_name[200];//��������
				wchar_t organizer[200];//�ٰ쵥λ
				wchar_t category[200];//�����
				wchar_t C_date[200];//��ʱ�� ����
				double C_GPA_bonus;

				// �ж������ʽ
				if (
					getTextInBox(competition_name, competition_nameBox.text) &&
					getTextInBox(organizer, organizerBox.text) &&
					getTextInBox(category, categoryBox.text) &&
					getTextInBox(C_date, C_dateBox.text) &&
					getDoubleInBox(10, &C_GPA_bonus, C_GPA_bonusBox.text)
					) {

					if (!addQuality_clist(Stu, competition_name, organizer, category, C_date, C_GPA_bonus)) {
						MessageBox(GetHWnd(), L"�þ������Ѿ�����,�����ظ����!", L"����!", MB_ICONERROR);

						// ������������
						competition_nameBox.clear();
						organizerBox.clear();
						categoryBox.clear();
						C_dateBox.clear();
						C_GPA_bonusBox.clear();


					}
					else {
						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"�����������Ŀ");


						// ʹ���ɱ仯
						Stu_Ctable.canChange = true;

						// ˢ�±��
						ShowStu_Competition(Stu, CompetitionData);
						Stu_Ctable.setData(CompetitionData);

						// ������������
						competition_nameBox.clear();
						organizerBox.clear();
						categoryBox.clear();
						C_dateBox.clear();
						C_GPA_bonusBox.clear();

						// ���ı���
						titleText.setText(L"��ѧ����������Ŀ");

						//����
						competition_nameBox.move(-500, 200);
						organizerBox.move(-500, 270);
						categoryBox.move(-500, 340);
						C_dateBox.move(-500, 410);
						C_GPA_bonusBox.move(-500, 690);
						add_CompetitionOK_Btn.move(-500, 640);
						cancel_addCompetition_Btn.move(-500, 720);

						//��ʾ
						sort_Btn.move(30, 120);
						add_Research_Btn.move(-50, 200);
						modify_Research_Btn.move(-50, 280);
						delete_Research_Btn.move(-50, 360);
						add_Competition_Btn.move(-50, 460);
						modify_Competition_Btn.move(-50, 540);
						delete_Competition_Btn.move(-50, 620);
						backButton.move(-50, 700);
						titleText.move(5, 30);

					}
				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}
			}

			if (cancel_addCompetition_Btn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"��ѧ����������Ŀ");

				// ������������
				competition_nameBox.clear();
				organizerBox.clear();
				categoryBox.clear();
				C_dateBox.clear();
				C_GPA_bonusBox.clear();


				//����
				competition_nameBox.move(-500, 200);
				organizerBox.move(-500, 270);
				categoryBox.move(-500, 340);
				C_dateBox.move(-500, 410);
				C_GPA_bonusBox.move(-500, 690);
				add_CompetitionOK_Btn.move(-500, 640);
				cancel_addCompetition_Btn.move(-500, 720);

				//��ʾ
				sort_Btn.move(30, 120);
				add_Research_Btn.move(-50, 200);
				modify_Research_Btn.move(-50, 280);
				delete_Research_Btn.move(-50, 360);
				add_Competition_Btn.move(-50, 460);
				modify_Competition_Btn.move(-50, 540);
				delete_Competition_Btn.move(-50, 620);
				backButton.move(-50, 700);
				titleText.move(5, 30);


			}

			if (modify_Research_Btn.mouseClick(msg)) {
				//ѡ��һ��Ҫ���ĵĿ��гɹ�
				if (Stu_Rtable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ�����гɹ�", L"����!", MB_ICONERROR);
				}
				else {
					// ���ı���
					titleText.setText(L"�޸Ĵ˿��гɹ�");

					//����
					sort_Btn.move(-500, 120);
					add_Research_Btn.move(-500, 200);
					modify_Research_Btn.move(-500, 280);
					delete_Research_Btn.move(-500, 360);
					add_Competition_Btn.move(-500, 460);
					modify_Competition_Btn.move(-500, 540);
					delete_Competition_Btn.move(-500, 620);
					backButton.move(-500, 700);

					//��ʾ
					modify_ResearchOK_Btn.move(10, 640);
					cancel_modifyResearch_Btn.move(10, 720);

					paper_nameBox.move(10, 70);
					journal_or_conference_nameBox.move(10, 140);
					authorBox.move(10, 210);
					dateBox.move(10, 280);
					volume_numBox.move(10, 350);
					issue_numBox.move(10, 420);
					pageBox.move(10, 490);
					GPA_bonusBox.move(10, 560);
					titleText.move(10, 3);


					// ʹ��񲻿ɱ仯
					Stu_Rtable.canChange = false;

					// ��ȡ��ǰ��
					int selectedRow = Stu_Rtable.getSelectedRow();
					vector<std::wstring> selectedResearch_Data = ResearchData[selectedRow];

					// �ı���Ĭ������
					paper_nameBox.setText(selectedResearch_Data[0].c_str());
					journal_or_conference_nameBox.setText(selectedResearch_Data[1].c_str());
					authorBox.setText(selectedResearch_Data[2].c_str());
					dateBox.setText(selectedResearch_Data[3].c_str());
					volume_numBox.setText(selectedResearch_Data[4].c_str());
					issue_numBox.setText(selectedResearch_Data[5].c_str());
					pageBox.setText(selectedResearch_Data[6].c_str());
					GPA_bonusBox.setText(selectedResearch_Data[7].c_str());

				}
			}

			if (modify_ResearchOK_Btn.mouseClick(msg)) {

				wchar_t paper_name[200];//��������
				wchar_t journal_or_conference_name[200];//��������ڿ����������
				wchar_t author[200];// ����������Ƿ�ΪͨѶ���߼���������
				wchar_t date[200];// ��������
				wchar_t volume_num[200];// ����
				wchar_t issue_num[200];// ����
				wchar_t page[200];// ҳ�뷶Χ
				double GPA_bonus;

				// ��ȷ������������Ŀ�ڵ�
				wchar_t temp[200];
				int selectedRow = Stu_Rtable.getSelectedRow();
				getTextInBox(temp, ResearchData[selectedRow][0].c_str());
				Rnode* modifying_Rnode = searchRnode_in_thisStu(Stu, temp);

				// �ж������ʽ
				if (
					getTextInBox(paper_name, paper_nameBox.text) &&
					getTextInBox(journal_or_conference_name, journal_or_conference_nameBox.text) &&
					getTextInBox(author, authorBox.text) &&
					getTextInBox(date, dateBox.text) &&
					getTextInBox(volume_num, volume_numBox.text) &&
					getTextInBox(issue_num, issue_numBox.text) &&
					getTextInBox(page, pageBox.text) &&
					getDoubleInBox(10, &GPA_bonus, GPA_bonusBox.text)
					) {

					// �޸�
					modifyQuality_rlist(modifying_Rnode, paper_name, journal_or_conference_name, author, date, volume_num, issue_num, page, GPA_bonus);

					// ����
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"�޸���������Ŀ");

					// ʹ���ɱ仯
					Stu_Rtable.canChange = true;

					// ˢ�±��
					ShowStu_Research(Stu, ResearchData);
					Stu_Rtable.setData(ResearchData);

					// ������������
					paper_nameBox.clear();
					journal_or_conference_nameBox.clear();
					authorBox.clear();
					dateBox.clear();
					volume_numBox.clear();
					issue_numBox.clear();
					pageBox.clear();
					GPA_bonusBox.clear();


					// ���ı���
					titleText.setText(L"��ѧ����������Ŀ");

					//����
					paper_nameBox.move(-500, 70);
					journal_or_conference_nameBox.move(-500, 140);
					authorBox.move(-500, 210);
					dateBox.move(-500, 280);
					volume_numBox.move(-500, 350);
					issue_numBox.move(-500, 420);
					pageBox.move(-500, 490);
					GPA_bonusBox.move(-500, 560);
					modify_ResearchOK_Btn.move(-500, 640);
					cancel_modifyResearch_Btn.move(-500, 720);

					//��ʾ
					sort_Btn.move(30, 120);
					add_Research_Btn.move(-50, 200);
					modify_Research_Btn.move(-50, 280);
					delete_Research_Btn.move(-50, 360);
					add_Competition_Btn.move(-50, 460);
					modify_Competition_Btn.move(-50, 540);
					delete_Competition_Btn.move(-50, 620);
					backButton.move(-50, 700);
					titleText.move(5, 30);


				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (cancel_modifyResearch_Btn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"��ѧ����������Ŀ");

				// ������������
				paper_nameBox.clear();
				journal_or_conference_nameBox.clear();
				authorBox.clear();
				dateBox.clear();
				volume_numBox.clear();
				issue_numBox.clear();
				pageBox.clear();
				GPA_bonusBox.clear();


				//����
				paper_nameBox.move(-500, 70);
				journal_or_conference_nameBox.move(-500, 140);
				authorBox.move(-500, 210);
				dateBox.move(-500, 280);
				volume_numBox.move(-500, 350);
				issue_numBox.move(-500, 420);
				pageBox.move(-500, 490);
				GPA_bonusBox.move(-500, 560);
				modify_ResearchOK_Btn.move(-500, 640);
				cancel_modifyResearch_Btn.move(-500, 720);

				//��ʾ
				sort_Btn.move(30, 120);
				add_Research_Btn.move(-50, 200);
				modify_Research_Btn.move(-50, 280);
				delete_Research_Btn.move(-50, 360);
				add_Competition_Btn.move(-50, 460);
				modify_Competition_Btn.move(-50, 540);
				delete_Competition_Btn.move(-50, 620);
				backButton.move(-50, 700);
				titleText.move(5, 30);

				// ʹ���ɱ仯
				Stu_Rtable.canChange = true;
			}

			if (modify_Competition_Btn.mouseClick(msg)) {
				//ѡ��һ��Ҫ���ĵľ�����
				if (Stu_Ctable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��������", L"����!", MB_ICONERROR);
				}
				else {
					// ���ı���
					titleText.setText(L"�޸Ĵ˾�����");

					//����
					sort_Btn.move(-500, 120);
					add_Research_Btn.move(-500, 200);
					modify_Research_Btn.move(-500, 280);
					delete_Research_Btn.move(-500, 360);
					add_Competition_Btn.move(-500, 460);
					modify_Competition_Btn.move(-500, 540);
					delete_Competition_Btn.move(-500, 620);
					backButton.move(-500, 700);

					//��ʾ
					modify_CompetitionOK_Btn.move(10, 570);
					cancel_modifyCompetition_Btn.move(10, 650);

					competition_nameBox.move(10, 200);
					organizerBox.move(10, 270);
					categoryBox.move(10, 340);
					C_dateBox.move(10, 410);
					C_GPA_bonusBox.move(10, 480);
					titleText.move(10, 100);


					// ʹ��񲻿ɱ仯
					Stu_Ctable.canChange = false;

					// ��ȡ��ǰ��
					int selectedRow = Stu_Ctable.getSelectedRow();
					vector<std::wstring> selectedCompetition_Data = CompetitionData[selectedRow];

					// �ı���Ĭ������
					competition_nameBox.setText(selectedCompetition_Data[0].c_str());
					organizerBox.setText(selectedCompetition_Data[1].c_str());
					categoryBox.setText(selectedCompetition_Data[2].c_str());
					C_dateBox.setText(selectedCompetition_Data[3].c_str());
					C_GPA_bonusBox.setText(selectedCompetition_Data[4].c_str());

				}
			}

			if (modify_CompetitionOK_Btn.mouseClick(msg)) {
				wchar_t competition_name[200];//��������
				wchar_t organizer[200];//�ٰ쵥λ
				wchar_t category[200];//�����
				wchar_t C_date[200];//��ʱ�� ����
				double C_GPA_bonus;

				// ��ȷ������������Ŀ�ڵ�
				wchar_t temp[200];
				int selectedRow = Stu_Ctable.getSelectedRow();
				getTextInBox(temp, CompetitionData[selectedRow][0].c_str());
				Cnode* modifying_Cnode = searchCnode_in_thisStu(Stu, temp);

				// �ж������ʽ
				if (
					getTextInBox(competition_name, competition_nameBox.text) &&
					getTextInBox(organizer, organizerBox.text) &&
					getTextInBox(category, categoryBox.text) &&
					getTextInBox(C_date, C_dateBox.text) &&
					getDoubleInBox(10, &C_GPA_bonus, C_GPA_bonusBox.text)
					) {

					// �޸�
					modifyQuality_clist(modifying_Cnode, competition_name, organizer, category, C_date, C_GPA_bonus);

					// ����
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"�޸���������Ŀ");

					// ʹ���ɱ仯
					Stu_Ctable.canChange = true;

					// ˢ�±��
					ShowStu_Competition(Stu, CompetitionData);
					Stu_Ctable.setData(CompetitionData);


					// ������������
					competition_nameBox.clear();
					organizerBox.clear();
					categoryBox.clear();
					C_dateBox.clear();
					C_GPA_bonusBox.clear();

					// ���ı���
					titleText.setText(L"��ѧ����������Ŀ");

					//����
					competition_nameBox.move(-500, 200);
					organizerBox.move(-500, 270);
					categoryBox.move(-500, 340);
					C_dateBox.move(-500, 410);
					C_GPA_bonusBox.move(-500, 690);
					modify_CompetitionOK_Btn.move(-500, 640);
					cancel_modifyCompetition_Btn.move(-500, 720);

					//��ʾ
					sort_Btn.move(30, 120);
					add_Research_Btn.move(-50, 200);
					modify_Research_Btn.move(-50, 280);
					delete_Research_Btn.move(-50, 360);
					add_Competition_Btn.move(-50, 460);
					modify_Competition_Btn.move(-50, 540);
					delete_Competition_Btn.move(-50, 620);
					backButton.move(-50, 700);
					titleText.move(5, 30);

				}
				// �������
				else {
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (cancel_modifyCompetition_Btn.mouseClick(msg)) {
				// ���ı���
				titleText.setText(L"��ѧ����������Ŀ");

				// ������������
				competition_nameBox.clear();
				organizerBox.clear();
				categoryBox.clear();
				C_dateBox.clear();
				C_GPA_bonusBox.clear();


				//����
				competition_nameBox.move(-500, 200);
				organizerBox.move(-500, 270);
				categoryBox.move(-500, 340);
				C_dateBox.move(-500, 410);
				C_GPA_bonusBox.move(-500, 690);
				modify_CompetitionOK_Btn.move(-500, 640);
				cancel_modifyCompetition_Btn.move(-500, 720);

				//��ʾ
				sort_Btn.move(30, 120);
				add_Research_Btn.move(-50, 200);
				modify_Research_Btn.move(-50, 280);
				delete_Research_Btn.move(-50, 360);
				add_Competition_Btn.move(-50, 460);
				modify_Competition_Btn.move(-50, 540);
				delete_Competition_Btn.move(-50, 620);
				backButton.move(-50, 700);
				titleText.move(5, 30);

				Stu_Ctable.canChange = true;


			}

			if (delete_Research_Btn.mouseClick(msg)) {
				if (Stu_Rtable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ�����гɹ�", L"����!", MB_ICONERROR);
				}
				else {
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ��������гɹ���?", L"ɾ�����гɹ�", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) { // ���ȷ��

						// ��ȷ������������Ŀ�ڵ�
						wchar_t temp[200];
						int selectedRow = Stu_Rtable.getSelectedRow();
						getTextInBox(temp, ResearchData[selectedRow][0].c_str());
						Rnode* modifying_Rnode = searchRnode_in_thisStu(Stu, temp);

						// ɾ��
						deleteQuality_rlist(Stu, temp);

						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"ɾ����������Ŀ");


						// ˢ�±��
						ShowStu_Research(Stu, ResearchData);
						Stu_Rtable.setData(ResearchData);
					}
				}
			}

			if (delete_Competition_Btn.mouseClick(msg)) {
				if (Stu_Ctable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"��ѡ��һ��������", L"����!", MB_ICONERROR);
				}
				else {
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ�������������?", L"ɾ��������", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) { // ���ȷ��

						// ��ȷ������������Ŀ�ڵ�
						wchar_t temp[200];
						int selectedRow = Stu_Ctable.getSelectedRow();
						getTextInBox(temp, CompetitionData[selectedRow][0].c_str());
						Cnode* modifying_Cnode = searchCnode_in_thisStu(Stu, temp);

						// ɾ��
						deleteQuality_clist(Stu, temp);

						// ����
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊѧ��") + to_wstring(Stu->item.data.ID) + L"ɾ����������Ŀ");


						// ˢ�±��
						ShowStu_Competition(Stu, CompetitionData);
						Stu_Ctable.setData(CompetitionData);
					}
				}
			}

			if (backButton.mouseClick(msg)) {
				return;
				allQualityUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}

			//�����껬������
			Stu_Rtable.onMouse(msg);
			Stu_Ctable.onMouse(msg);


			// �ı�������
			paper_nameBox.onMessage(msg);
			journal_or_conference_nameBox.onMessage(msg);
			authorBox.onMessage(msg);
			dateBox.onMessage(msg);
			volume_numBox.onMessage(msg);
			issue_numBox.onMessage(msg);
			pageBox.onMessage(msg);
			GPA_bonusBox.onMessage(msg);

			competition_nameBox.onMessage(msg);
			organizerBox.onMessage(msg);
			categoryBox.onMessage(msg);
			C_dateBox.onMessage(msg);
			C_GPA_bonusBox.onMessage(msg);



		}
		//showxy(msg);


		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}
}

void stuAccountUI(int stuID, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {
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
	vector<vector<std::wstring>>allCrsINStuData;
	showStu(pstu, allCrsINStuData, L"");


	vector<vector<std::wstring>>ResearchData;
	vector<vector<std::wstring>>CompetitionData;

	ShowStu_Research(pstu, ResearchData);
	ShowStu_Competition(pstu, CompetitionData);

	Table allCrsINStuTable(400, 90, 1070, 360, allCrsINStuData);
	Table Stu_Rtable(400, 470, 1070, 160, ResearchData);
	Table Stu_Ctable(400, 630, 1070, 160, CompetitionData);

	//�����
	TextBox searchInputBox(400, 20, 960, L"����", L"");


	//��ť
	Button searchBtn(1370, 20, 100, 50, L"����", 1);


	Text idBtn(40, 100, (wstring(L"ѧ�ţ�") + to_wstring(stuID)).c_str(), 32);
	Text nameBtn(40, 150, (wstring(L"������") + pstu->item.data.name).c_str(), 32);
	Text titleText(30, 20, (wstring(L"��ӭ��  ") + pstu->item.data.name).c_str(), 56);


	//���㼨��
	double all, must, alls, musts;

	all = AllGrid(pstu);
	must = MustGrid(pstu);
	alls = AllScore(pstu);
	musts = MustScore(pstu);
	Text allCrsGridText(40, 220, (wstring(L"ƽ������: ") + to_wstring(all).substr(0, to_wstring(all).find(L'.') + 5)).c_str(), 32);
	Text allCrsScoreText(40, 260, (wstring(L"ƽ����: ") + to_wstring(alls).substr(0, to_wstring(alls).find(L'.') + 3)).c_str(), 32);
	Text reqCrsGridText(40, 300, (wstring(L"ƽ������(����): ") + to_wstring(must).substr(0, to_wstring(must).find(L'.') + 5)).c_str(), 32);
	Text reqCrsScoreText(40, 340, (wstring(L"ƽ����(����): ") + to_wstring(musts).substr(0, to_wstring(musts).find(L'.') + 3)).c_str(), 32);
	Text predictGridText(40, 380, (wstring(L"Ԥ����һѧ�꼨�㣺") + to_wstring(preditcGrid(allCrsINStuData, 1, 5)).substr(0, to_wstring(preditcGrid(allCrsINStuData, 1, 5)).find(L'.') + 5)).c_str(), 32);


	Button chooseCrsBtn(-50, 450, 330, 60, L"   ѡ�˿�", 1);
	Button drawBtn(-50, 530, 330, 60, L"   �鿴�γ�ͼ��", 1);
	Button modify_password_Btn(-50, 610, 330, 60, L"   �޸�����", 1);
	Button backButton(-50, 700, 330, 60, L"   �˳���¼", 0);





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
				showStu(pstu, allCrsINStuData, searchInputBox.text);
				allCrsINStuTable.setData(allCrsINStuData);
			}

			if (chooseCrsBtn.mouseClick(msg)) {
				chooseCrsUI(stuID, admin, Admin_List, allStuList, allCrsList);

				cleardevice();

				allCrsINStuTable.draw();
				Stu_Rtable.draw();
				Stu_Ctable.draw();
				searchInputBox.draw();
				searchBtn.draw();
				idBtn.draw();
				nameBtn.draw();
				titleText.draw();
				allCrsGridText.draw();
				allCrsScoreText.draw();
				reqCrsGridText.draw();
				reqCrsScoreText.draw();
				predictGridText.draw();
				chooseCrsBtn.draw();
				drawBtn.draw();
				modify_password_Btn.draw();
				backButton.draw();

				showStu(pstu, allCrsINStuData, L"");
				allCrsINStuTable.setData(allCrsINStuData);

			}

			if (modify_password_Btn.mouseClick(msg)) {
				Modify_Stu_or_Tch_Password_UI(to_wstring(pstu->item.data.ID).c_str(), pstu, 0, allStuList, admin, Admin_List, allStuList, allCrsList);

				cleardevice();

				allCrsINStuTable.draw();
				Stu_Rtable.draw();
				Stu_Ctable.draw();
				searchInputBox.draw();
				searchBtn.draw();
				idBtn.draw();
				nameBtn.draw();
				titleText.draw();
				allCrsGridText.draw();
				allCrsScoreText.draw();
				reqCrsGridText.draw();
				reqCrsScoreText.draw();
				predictGridText.draw();
				chooseCrsBtn.draw();
				drawBtn.draw();
				modify_password_Btn.draw();
				backButton.draw();

			}

			if (backButton.mouseClick(msg))
			{
				writeLog(0, admin, wstring(L"�˳�ϵͳ"));
				loginUI();
			}

			if (drawBtn.mouseClick(msg)) {
				chartUI(allCrsINStuData, 1, 2, stuID, NULL, NULL, 0, admin, Admin_List, allStuList, allCrsList);

				cleardevice();

				allCrsINStuTable.draw();
				Stu_Rtable.draw();
				Stu_Ctable.draw();
				searchInputBox.draw();
				searchBtn.draw();
				idBtn.draw();
				nameBtn.draw();
				titleText.draw();
				allCrsGridText.draw();
				allCrsScoreText.draw();
				reqCrsGridText.draw();
				reqCrsScoreText.draw();
				predictGridText.draw();
				chooseCrsBtn.draw();
				drawBtn.draw();
				modify_password_Btn.draw();
				backButton.draw();


			}



			//�����껬������
			allCrsINStuTable.onMouse(msg);
			Stu_Rtable.onMouse(msg);
			Stu_Ctable.onMouse(msg);



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

void allTchUI(Node* admin, List adminList, List allStuList, Cpnode allCrsList) {
	cleardevice();

	List TchList = readTch(TCH_FILE);

	vector<vector<std::wstring>> allTchData;

	showAllTch(TchList, allTchData, L"");

	Table allTchTable(310, 90, 1160, 700, allTchData);

	Text titleText(40, 50, L"���н�ʦ", 64);

	TextBox searchInputBox(310, 20, 1040, L"����", L"");

	Button searchBtn(1370, 20, 100, 50, L"����", 1);
	Button sortBtn(30, 210, 200, 60, L"<����������>", 1);
	Button inportBtn(-50, 300, 330, 60, L"   ����", 1);
	Button exportBtn(-50, 380, 330, 60, L"   ����", 1);
	Button backButton(-50, 460, 330, 60, L"   ����", 0);

	// ��������¼�
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// ��������(����)
		searchInputBox.draw();
		if (peekmessage(&msg, -1, true)) {

			// ������¼�
			if (searchBtn.mouseClick(msg)) {
				showAllTch(TchList, allTchData, searchInputBox.text);
				allTchTable.setData(allTchData);
			}

			if (sortBtn.mouseClick(msg)) {

				sortStuaccID(&TchList);

				// ˢ�±��

				showAllTch(TchList, allTchData, L"");
				allTchTable.setData(allTchData);
			}

			if (exportBtn.mouseClick(msg)) {
				if (exportTch(TchList, ".\\export\\Tch.csv")) {
					MessageBox(GetHWnd(), L"�����ɹ�", L"������ʦ", 0);
					writeLog(2, admin, wstring(L"������ʦ��Ϣ"));

				}
				else {
					MessageBox(GetHWnd(), L"����ʧ��", L"������ʦ", MB_ICONERROR);
				}
			}

			if (inportBtn.mouseClick(msg)) {
				importTch(TchList, ".\\import\\Tch.csv");


				// ˢ�±��
				showAllTch(TchList, allTchData, L"");
				allTchTable.setData(allTchData);

				// ����
				saveTch(TchList, TCH_FILE);

				writeLog(2, admin, wstring(L"�����ʦ��Ϣ"));
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

