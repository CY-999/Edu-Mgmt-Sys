#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define TCH_FILE ".\\data\\Teacher.txt"
#define ADMIN_FILE ".\\data\\Administrator.txt"
#define CRS_FILE ".\\data\\Course.txt"


int mainLin() {
	setlocale(LC_ALL, ""); //使控制台支持宽字符输出

	// 初始化图形窗口
	initgraph(1500, 810);
	BeginBatchDraw(); //开始批量绘图
	setbkcolor(RGB(55, 61, 53)); //背景颜色
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




	EndBatchDraw(); //结束批量绘图
	closegraph(); // 关闭图形窗口



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

	Text titleText(400, 120, L"你好，欢迎登陆 JLU 成绩管理系统!", 64);
	TextBox accountBox(200, 330, 1100, L"账号", L"");
	TextBox passwordBox(200, 430, 1100, L"密码", L"");
	Button loginButton(200, 530, 530, 60, L"登录", 1);
	Button exitButton(770, 530, 530, 60, L"退出", 0);
	//Button modify_password_Button(860, 600, 220, 50, L"修改密码", 1);

	// 处理鼠标事件
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

				if (Stu == NULL && Tch == NULL && Admin == NULL) { //没有学生ID/教师工号/管理员id 与之对应
					MessageBox(GetHWnd(), L"不存在这个账号！请重新输入！", L"错误!", MB_ICONWARNING);
					accountBox.clear();
					passwordBox.clear();
				}
				else if (wcscmp(tmp_password.c_str(), (const wchar_t*)passwordBox.text) == 0) {//把这个对应的正确密码和输入的密码进行比较
					if (Stu != NULL) {//说明登录的是学生的账号
						writeLog(0, Stu, wstring(L"登入系统"));
						stuAccountUI(Stu->item.data.ID, Stu, allAdminList, allStuList, allCrsList);
					}
					else if (Tch != NULL) {
						writeLog(1, Tch, wstring(L"登入系统"));
						menuUI_Tch(Tch, allTchList, Tch, allAdminList, allStuList, allCrsList);
					}
					else {
						writeLog(2, Admin, wstring(L"登入系统"));
						menuUI_Administrator(Admin, allAdminList, allStuList, allCrsList);
					}
				}
				else {
					MessageBox(GetHWnd(), L"密码错误！请重新输入！", L"错误!", MB_ICONWARNING);
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
					MessageBox(GetHWnd(), L"不存在这个账号！无法修改密码！", L"错误！", MB_ICONWARNING);
					accountBox.clear();
					passwordBox.clear();
				}
				else if (wcscmp(tmp_password.c_str(), passwordBox.text) == 0) {//把这个学生/教师对应的正确密码和输入的密码进行比较
					if (Stu != NULL)//说明改的是学生账号的密码
						Modify_Password_UI(accountBox.text, Stu, 0, StuList);
					else
						Modify_Password_UI(accountBox.text, Tch, 1, TchList);
				}
					else {
						MessageBox(GetHWnd(), L"原密码错误！无法修改密码！", L"错误！", MB_ICONWARNING);
						passwordBox.clear();
					}
				}*/

				// 文本框输入
			accountBox.onMessage(msg);
			passwordBox.onMessage(msg);

		}

		//showxy(msg);



		FlushBatchDraw(); //批量绘图

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}
	}

}

void manageUI(Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {	//管理员管理密码界面

	cleardevice();

	//List allStuList = readStu(STU_FILE);
	List allTchList = readTch(TCH_FILE);

	vector<vector<std::wstring>>Stu_Password_Data;
	vector<vector<std::wstring>>Tch_Password_Data;

	ShowStu_Password(allStuList, Stu_Password_Data, L"");
	ShowTch_Password(allTchList, Tch_Password_Data, L"");

	Table Stu_ptable(310, 90, 580 - 15, 700, Stu_Password_Data);
	Table Tch_ptable(905, 90, 580 - 15, 700, Tch_Password_Data);


	Text titleText(10, 90, L"全部密码管理", 63);
	TextBox searchStuInputBox(310, 20, 450, L"搜索学生", L"");
	TextBox searchTchInputBox(905, 20, 450, L"搜索教师", L"");


	Button searchStuBtn(775, 20, 100, 50, L"搜索", 1);
	Button searchTchBtn(1370, 20, 100, 50, L"搜索", 1);
	Button sortBtn(30, 210, 200, 60, L"<按学号/工号排序>", 1);
	Button modify_Stu_Btn(-50, 300, 330, 60, L"   修改学生密码", 1);
	Button modify_Tch_Btn(-50, 380, 330, 60, L"   修改教师密码", 1);
	Button backButton(-50, 620, 330, 60, L"   返回", 0);


	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//->
		// 输入框绘制(必须)
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

				// 刷新表格
				ShowStu_Password(allStuList, Stu_Password_Data, L"");
				Stu_ptable.setData(Stu_Password_Data);

				ShowTch_Password(allTchList, Tch_Password_Data, L"");
				Tch_ptable.setData(Tch_Password_Data);

			}

			if (modify_Stu_Btn.mouseClick(msg)) {
				// 未选择学生
				if (Stu_ptable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个学生", L"错误!", MB_ICONERROR);
				}
				else {
					// 精确搜索学生节点
					int tempID;
					int selectedRow = Stu_ptable.getSelectedRow(); // 获取当前列
					getNumberInBox(99999999, &tempID, Stu_Password_Data[selectedRow][0].c_str());
					Node* modifyingStu = searchStu(&allStuList, (wchar_t*)Stu_Password_Data[selectedRow][1].c_str(), tempID);
					Modify_Stu_or_Tch_Password_UI(to_wstring(modifyingStu->item.data.ID).c_str(), modifyingStu, 3, allStuList, admin, Admin_List, allStuList, allCrsList);
					//返回 manageUI时 自动保存自动刷新				

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
				// 未选择教师
				if (Tch_ptable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个教师", L"错误!", MB_ICONERROR);
				}
				else {
					// 精确搜索教师节点
					int tempID;
					int selectedRow = Tch_ptable.getSelectedRow(); // 获取当前列
					getNumberInBox(99999999, &tempID, Tch_Password_Data[selectedRow][0].c_str());
					Node* modifyingTch = searchStu(&allTchList, (wchar_t*)Tch_Password_Data[selectedRow][1].c_str(), tempID);
					Modify_Stu_or_Tch_Password_UI(to_wstring(modifyingTch->item.data.ID).c_str(), modifyingTch, 4, allTchList, admin, Admin_List, allStuList, allCrsList);
					//返回 manageUI时 自动保存自动刷新				


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


			//表格鼠标滑动与点击
			Stu_ptable.onMouse(msg);
			Tch_ptable.onMouse(msg);


			// 文本框输入
			searchStuInputBox.onMessage(msg);
			searchTchInputBox.onMessage(msg);



		}

		//showxy(msg);



		//<-
		FlushBatchDraw(); //批量绘图

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}


}

void Modify_Stu_or_Tch_Password_UI(const wchar_t* account, Node* Stu, int judge, List StuList, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList) {//judge： 0为从学生端进入改密码 1为从教师端进入改密码 3为从管理员端进入修改学生 4为从管理员端进入修改老师

	cleardevice();


	//drawLine();


	Text titleText(300, 100, L"你好，请修改你的密码！", 64);

	TextBox accountBox(300, 300, 900, L"账号", L"");
	TextBox old_passwordBox(300, 380, 900, L"原密码", L"");
	TextBox new_passwordBox(300, 460, 900, L"请输入新密码", L"");
	TextBox confirm_passwordBox(300, 540, 900, L"请确认新密码", L"");
	Button modify_OK_Button(585, 620, 330, 60, L"确认修改", 1);
	Button backButton(585, 700, 330, 60, L"取消修改", 0);

	if (judge == 0 || judge == 3) {
		Text IDText(300, 200, L"", 32);
		wstring show_ID = L"学号：" + to_wstring(Stu->item.data.ID);
		IDText.setText(show_ID.c_str());
	}
	if (judge == 1 || judge == 4) {
		Text IDText(300, 200, L"", 32);
		wstring show_ID = L"工号：" + to_wstring(Stu->item.data.ID);
		IDText.setText(show_ID.c_str());
	}

	Text nameText(300, 230, L"", 32);
	wstring tmp_name = Stu->item.data.name;
	wstring show_name = L"姓名：" + tmp_name;
	nameText.setText(show_name.c_str());

	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		accountBox.draw();
		old_passwordBox.draw();
		new_passwordBox.draw();
		confirm_passwordBox.draw();

		//文本框默认内容
		wstring show_account = L"账号：" + (wstring)account;
		accountBox.setText(show_account.c_str());
		wstring show_old_password = L"原密码：" + (wstring)Stu->item.data.password;
		old_passwordBox.setText(show_old_password.c_str());

		if (peekmessage(&msg, -1, true)) {

			if (modify_OK_Button.mouseClick(msg)) {

				if (wcscmp(new_passwordBox.text, confirm_passwordBox.text) == 0) {

					wcscpy(Stu->item.data.password, new_passwordBox.text);

					if (judge == 0 || judge == 3) {
						saveStu(StuList, STU_FILE);
						if (judge == 0) {
							writeLog(judge, Stu, wstring(L"修改学生") + to_wstring(Stu->item.data.ID) + L"的密码");
						}
						else {
							writeLog(judge, admin, wstring(L"修改学生") + to_wstring(Stu->item.data.ID) + L"的密码");
						}
					}

					if (judge == 1 || judge == 4) {
						saveTch(StuList, TCH_FILE);
						if (judge == 1) {
							writeLog(judge, Stu, wstring(L"修改教师") + to_wstring(Stu->item.data.ID) + L"的密码");
						}
						else {
							writeLog(judge, admin, wstring(L"修改教师") + to_wstring(Stu->item.data.ID) + L"的密码");
						}
					}

					// 清除输入框内容
					accountBox.clear();
					old_passwordBox.clear();
					new_passwordBox.clear();
					confirm_passwordBox.clear();

					//自动返回
					return;
					if (judge == 0)
						stuAccountUI(Stu->item.data.ID, admin, Admin_List, allStuList, allCrsList);
					else if (judge == 1)
						menuUI_Tch(Stu, StuList, admin, Admin_List, allStuList, allCrsList);
					else
						manageUI(admin, Admin_List, allStuList, allCrsList);

				}
				else {
					MessageBox(GetHWnd(), L"两次输入的密码不一致！", L"错误!", MB_ICONWARNING);
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


			// 文本框输入
			new_passwordBox.onMessage(msg);
			confirm_passwordBox.onMessage(msg);

		}

		//showxy(msg);



		FlushBatchDraw(); //批量绘图

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

	Text titleText(10, 100, L"素质类项目管理", 50);
	//Text IDText(-500, 200, L"", 32);

	TextBox searchInputBox(310, 20, 1040, L"搜索", L"");

	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);
	Button sortBtn(30, 270, 200, 60, L"<按学号/年级排序>", 1);
	Button search_for_quality_Btn(-50, 360, 330, 60, L"   查询", 1);
	Button exportBtn(-50, 440, 330, 60, L"   导出", 1);
	Button inportBtn(-50, 520, 330, 60, L"   导入", 1);
	Button backButton(-50, 600, 330, 60, L"   返回", 0);

	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//->
		// 输入框绘制(必须)
		searchInputBox.draw();

		if (peekmessage(&msg, -1, true)) {

			// 鼠标点击事件
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

				// 保存
				saveStu(allStuList, STU_FILE);

				// 刷新表格
				showAllStu(allStuList, allQuality_Data, L"");
				allQuality_Table.setData(allQuality_Data);

			}

			if (search_for_quality_Btn.mouseClick(msg)) {
				if (allQuality_Table.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个学生", L"错误!", MB_ICONERROR);
				}
				else {
					// 精确搜索学生节点
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
					MessageBox(GetHWnd(), L"导出成功", L"导出学生", 0);
					writeLog(judge, tch_or_admin, wstring(L"导出学生信息"));
				}
				else {
					MessageBox(GetHWnd(), L"导出失败", L"导出学生", MB_ICONERROR);
				}
			}

			if (inportBtn.mouseClick(msg)) {
				importStu(allStuList, ".\\import\\Stu.csv");


				// 刷新表格
				showAllStu(allStuList, allQuality_Data, L"");
				allQuality_Table.setData(allQuality_Data);

				// 保存
				saveStu(allStuList, STU_FILE);
				writeLog(judge, tch_or_admin, wstring(L"导入学生信息"));


			}

			if (backButton.mouseClick(msg)) {
				return;
				if (judge == 1)
					menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				else
					menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}


			//表格鼠标滑动与点击
			allQuality_Table.onMouse(msg);

			// 文本框输入
			searchInputBox.onMessage(msg);

		}


		//showxy(msg);



		//<-
		FlushBatchDraw(); //批量绘图

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


	//TextBox searchInputBox(310, 20, 820, L"搜索", L"");
	Text titleText(5, 30, L"该学生素质类项目", 50);
	Text IDText(500, 45, L"", 32);
	wstring show_ID = L"学号：" + to_wstring(Stu->item.data.ID);
	IDText.setText(show_ID.c_str());

	Text nameText(850, 45, L"", 32);
	wstring tmp_name = Stu->item.data.name;
	wstring show_name = L"姓名：" + tmp_name;
	nameText.setText(show_name.c_str());

	TextBox paper_nameBox(-500, 200, 290, L"论文名称", L"");
	TextBox journal_or_conference_nameBox(-500, 270, 290, L"发表的期刊/会议名称", L"");
	TextBox authorBox(-500, 340, 290, L"作者情况", L"");
	TextBox dateBox(-500, 410, 290, L"发表时间", L"");
	TextBox volume_numBox(-500, 480, 290, L"卷数", L"");
	TextBox issue_numBox(-500, 550, 290, L"刊号", L"");
	TextBox pageBox(-500, 620, 290, L"页码范围", L"");
	TextBox GPA_bonusBox(-500, 690, 290, L"绩点加分", L"");

	TextBox competition_nameBox(-500, 200, 290, L"竞赛名称", L"");
	TextBox organizerBox(-500, 270, 290, L"举办单位", L"");
	TextBox categoryBox(-500, 340, 290, L"获奖类别", L"");
	TextBox C_dateBox(-500, 410, 290, L"获奖时间", L"");
	TextBox C_GPA_bonusBox(-500, 690, 290, L"绩点加分", L"");



	//进入单个学生的素质类界面后 一开始显示的

	Button sort_Btn(30, 120, 200, 60, L"<按绩点加分排序>", 1);

	Button add_Research_Btn(-50, 200, 330, 60, L"   科研成果添加", 1);
	Button modify_Research_Btn(-50, 280, 330, 60, L"   科研成果修改", 1);
	Button delete_Research_Btn(-50, 360, 330, 60, L"   科研成果删除", 1);
	Button add_Competition_Btn(-50, 460, 330, 60, L"   竞赛获奖添加", 1);
	Button modify_Competition_Btn(-50, 540, 330, 60, L"   竞赛获奖修改", 1);
	Button delete_Competition_Btn(-50, 620, 330, 60, L"   竞赛获奖删除", 1);


	Button backButton(-50, 700, 330, 60, L"返回", 0);


	Button modify_ResearchOK_Btn(-500, 580, 290, 60, L"确定修改", 1);
	Button add_ResearchOK_Btn(-500, 640, 290, 60, L"确定添加", 1);
	Button modify_CompetitionOK_Btn(-500, 580, 290, 60, L"确定修改", 1);
	Button add_CompetitionOK_Btn(-500, 640, 290, 60, L"确定添加", 1);

	Button cancel_modifyResearch_Btn(-500, 720, 290, 60, L"取消修改", 0);
	Button cancel_addResearch_Btn(-500, 720, 290, 60, L"取消添加", 0);
	Button cancel_modifyCompetition_Btn(-500, 720, 290, 60, L"取消修改", 0);
	Button cancel_addCompetition_Btn(-500, 720, 290, 60, L"取消添加", 0);


	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// 输入框绘制(必须)
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

				titleText.setText(L"  科研成果添加");
				titleText.move(10, 3);
				//隐藏
				sort_Btn.move(-500, 120);
				add_Research_Btn.move(-500, 200);
				modify_Research_Btn.move(-500, 280);
				delete_Research_Btn.move(-500, 360);
				add_Competition_Btn.move(-500, 460);
				modify_Competition_Btn.move(-500, 540);
				delete_Competition_Btn.move(-500, 620);
				backButton.move(-500, 700);

				//显示
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

				wchar_t paper_name[200];//论文名称
				wchar_t journal_or_conference_name[200];//所发表的期刊或会议名称
				wchar_t author[200];// 作者情况（是否为通讯作者及作者排序）
				wchar_t date[200];// 发表年月
				wchar_t volume_num[200];// 卷数
				wchar_t issue_num[200];// 刊号
				wchar_t page[200];// 页码范围
				double GPA_bonus;

				// 判断输入格式
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
						MessageBox(GetHWnd(), L"该科研成果已经存在,请勿重复添加!", L"错误!", MB_ICONERROR);


						// 清除输入框内容
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
						// 保存
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"添加素质类项目");

						// 使表格可变化
						Stu_Rtable.canChange = true;

						// 刷新表格
						ShowStu_Research(Stu, ResearchData);
						Stu_Rtable.setData(ResearchData);

						// 清除输入框内容
						paper_nameBox.clear();
						journal_or_conference_nameBox.clear();
						authorBox.clear();
						dateBox.clear();
						volume_numBox.clear();
						issue_numBox.clear();
						pageBox.clear();
						GPA_bonusBox.clear();

						// 更改标题
						titleText.setText(L"该学生素质类项目");

						//隐藏
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

						//显示
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
				// 输入错误
				else {
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}
			}

			if (cancel_addResearch_Btn.mouseClick(msg)) {
				// 更改标题
				titleText.setText(L"该学生素质类项目");

				// 清除输入框内容
				paper_nameBox.clear();
				journal_or_conference_nameBox.clear();
				authorBox.clear();
				dateBox.clear();
				volume_numBox.clear();
				issue_numBox.clear();
				pageBox.clear();
				GPA_bonusBox.clear();


				//隐藏
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

				//显示
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

				titleText.setText(L" 竞赛获奖添加");

				//隐藏
				sort_Btn.move(-500, 120);
				add_Research_Btn.move(-500, 200);
				modify_Research_Btn.move(-500, 280);
				delete_Research_Btn.move(-500, 360);
				add_Competition_Btn.move(-500, 460);
				modify_Competition_Btn.move(-500, 540);
				delete_Competition_Btn.move(-500, 620);
				backButton.move(-500, 700);

				//显示
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

				wchar_t competition_name[200];//竞赛名称
				wchar_t organizer[200];//举办单位
				wchar_t category[200];//获奖类别
				wchar_t C_date[200];//获奖时间 年月
				double C_GPA_bonus;

				// 判断输入格式
				if (
					getTextInBox(competition_name, competition_nameBox.text) &&
					getTextInBox(organizer, organizerBox.text) &&
					getTextInBox(category, categoryBox.text) &&
					getTextInBox(C_date, C_dateBox.text) &&
					getDoubleInBox(10, &C_GPA_bonus, C_GPA_bonusBox.text)
					) {

					if (!addQuality_clist(Stu, competition_name, organizer, category, C_date, C_GPA_bonus)) {
						MessageBox(GetHWnd(), L"该竞赛获奖已经存在,请勿重复添加!", L"错误!", MB_ICONERROR);

						// 清除输入框内容
						competition_nameBox.clear();
						organizerBox.clear();
						categoryBox.clear();
						C_dateBox.clear();
						C_GPA_bonusBox.clear();


					}
					else {
						// 保存
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"添加素质类项目");


						// 使表格可变化
						Stu_Ctable.canChange = true;

						// 刷新表格
						ShowStu_Competition(Stu, CompetitionData);
						Stu_Ctable.setData(CompetitionData);

						// 清除输入框内容
						competition_nameBox.clear();
						organizerBox.clear();
						categoryBox.clear();
						C_dateBox.clear();
						C_GPA_bonusBox.clear();

						// 更改标题
						titleText.setText(L"该学生素质类项目");

						//隐藏
						competition_nameBox.move(-500, 200);
						organizerBox.move(-500, 270);
						categoryBox.move(-500, 340);
						C_dateBox.move(-500, 410);
						C_GPA_bonusBox.move(-500, 690);
						add_CompetitionOK_Btn.move(-500, 640);
						cancel_addCompetition_Btn.move(-500, 720);

						//显示
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
				// 输入错误
				else {
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}
			}

			if (cancel_addCompetition_Btn.mouseClick(msg)) {
				// 更改标题
				titleText.setText(L"该学生素质类项目");

				// 清除输入框内容
				competition_nameBox.clear();
				organizerBox.clear();
				categoryBox.clear();
				C_dateBox.clear();
				C_GPA_bonusBox.clear();


				//隐藏
				competition_nameBox.move(-500, 200);
				organizerBox.move(-500, 270);
				categoryBox.move(-500, 340);
				C_dateBox.move(-500, 410);
				C_GPA_bonusBox.move(-500, 690);
				add_CompetitionOK_Btn.move(-500, 640);
				cancel_addCompetition_Btn.move(-500, 720);

				//显示
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
				//选择一个要更改的科研成果
				if (Stu_Rtable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个科研成果", L"错误!", MB_ICONERROR);
				}
				else {
					// 更改标题
					titleText.setText(L"修改此科研成果");

					//隐藏
					sort_Btn.move(-500, 120);
					add_Research_Btn.move(-500, 200);
					modify_Research_Btn.move(-500, 280);
					delete_Research_Btn.move(-500, 360);
					add_Competition_Btn.move(-500, 460);
					modify_Competition_Btn.move(-500, 540);
					delete_Competition_Btn.move(-500, 620);
					backButton.move(-500, 700);

					//显示
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


					// 使表格不可变化
					Stu_Rtable.canChange = false;

					// 获取当前行
					int selectedRow = Stu_Rtable.getSelectedRow();
					vector<std::wstring> selectedResearch_Data = ResearchData[selectedRow];

					// 文本框默认内容
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

				wchar_t paper_name[200];//论文名称
				wchar_t journal_or_conference_name[200];//所发表的期刊或会议名称
				wchar_t author[200];// 作者情况（是否为通讯作者及作者排序）
				wchar_t date[200];// 发表年月
				wchar_t volume_num[200];// 卷数
				wchar_t issue_num[200];// 刊号
				wchar_t page[200];// 页码范围
				double GPA_bonus;

				// 精确搜索素质类项目节点
				wchar_t temp[200];
				int selectedRow = Stu_Rtable.getSelectedRow();
				getTextInBox(temp, ResearchData[selectedRow][0].c_str());
				Rnode* modifying_Rnode = searchRnode_in_thisStu(Stu, temp);

				// 判断输入格式
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

					// 修改
					modifyQuality_rlist(modifying_Rnode, paper_name, journal_or_conference_name, author, date, volume_num, issue_num, page, GPA_bonus);

					// 保存
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"修改素质类项目");

					// 使表格可变化
					Stu_Rtable.canChange = true;

					// 刷新表格
					ShowStu_Research(Stu, ResearchData);
					Stu_Rtable.setData(ResearchData);

					// 清除输入框内容
					paper_nameBox.clear();
					journal_or_conference_nameBox.clear();
					authorBox.clear();
					dateBox.clear();
					volume_numBox.clear();
					issue_numBox.clear();
					pageBox.clear();
					GPA_bonusBox.clear();


					// 更改标题
					titleText.setText(L"该学生素质类项目");

					//隐藏
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

					//显示
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
				// 输入错误
				else {
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			if (cancel_modifyResearch_Btn.mouseClick(msg)) {
				// 更改标题
				titleText.setText(L"该学生素质类项目");

				// 清除输入框内容
				paper_nameBox.clear();
				journal_or_conference_nameBox.clear();
				authorBox.clear();
				dateBox.clear();
				volume_numBox.clear();
				issue_numBox.clear();
				pageBox.clear();
				GPA_bonusBox.clear();


				//隐藏
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

				//显示
				sort_Btn.move(30, 120);
				add_Research_Btn.move(-50, 200);
				modify_Research_Btn.move(-50, 280);
				delete_Research_Btn.move(-50, 360);
				add_Competition_Btn.move(-50, 460);
				modify_Competition_Btn.move(-50, 540);
				delete_Competition_Btn.move(-50, 620);
				backButton.move(-50, 700);
				titleText.move(5, 30);

				// 使表格可变化
				Stu_Rtable.canChange = true;
			}

			if (modify_Competition_Btn.mouseClick(msg)) {
				//选择一个要更改的竞赛获奖
				if (Stu_Ctable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个竞赛获奖", L"错误!", MB_ICONERROR);
				}
				else {
					// 更改标题
					titleText.setText(L"修改此竞赛获奖");

					//隐藏
					sort_Btn.move(-500, 120);
					add_Research_Btn.move(-500, 200);
					modify_Research_Btn.move(-500, 280);
					delete_Research_Btn.move(-500, 360);
					add_Competition_Btn.move(-500, 460);
					modify_Competition_Btn.move(-500, 540);
					delete_Competition_Btn.move(-500, 620);
					backButton.move(-500, 700);

					//显示
					modify_CompetitionOK_Btn.move(10, 570);
					cancel_modifyCompetition_Btn.move(10, 650);

					competition_nameBox.move(10, 200);
					organizerBox.move(10, 270);
					categoryBox.move(10, 340);
					C_dateBox.move(10, 410);
					C_GPA_bonusBox.move(10, 480);
					titleText.move(10, 100);


					// 使表格不可变化
					Stu_Ctable.canChange = false;

					// 获取当前行
					int selectedRow = Stu_Ctable.getSelectedRow();
					vector<std::wstring> selectedCompetition_Data = CompetitionData[selectedRow];

					// 文本框默认内容
					competition_nameBox.setText(selectedCompetition_Data[0].c_str());
					organizerBox.setText(selectedCompetition_Data[1].c_str());
					categoryBox.setText(selectedCompetition_Data[2].c_str());
					C_dateBox.setText(selectedCompetition_Data[3].c_str());
					C_GPA_bonusBox.setText(selectedCompetition_Data[4].c_str());

				}
			}

			if (modify_CompetitionOK_Btn.mouseClick(msg)) {
				wchar_t competition_name[200];//竞赛名称
				wchar_t organizer[200];//举办单位
				wchar_t category[200];//获奖类别
				wchar_t C_date[200];//获奖时间 年月
				double C_GPA_bonus;

				// 精确搜索素质类项目节点
				wchar_t temp[200];
				int selectedRow = Stu_Ctable.getSelectedRow();
				getTextInBox(temp, CompetitionData[selectedRow][0].c_str());
				Cnode* modifying_Cnode = searchCnode_in_thisStu(Stu, temp);

				// 判断输入格式
				if (
					getTextInBox(competition_name, competition_nameBox.text) &&
					getTextInBox(organizer, organizerBox.text) &&
					getTextInBox(category, categoryBox.text) &&
					getTextInBox(C_date, C_dateBox.text) &&
					getDoubleInBox(10, &C_GPA_bonus, C_GPA_bonusBox.text)
					) {

					// 修改
					modifyQuality_clist(modifying_Cnode, competition_name, organizer, category, C_date, C_GPA_bonus);

					// 保存
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"修改素质类项目");

					// 使表格可变化
					Stu_Ctable.canChange = true;

					// 刷新表格
					ShowStu_Competition(Stu, CompetitionData);
					Stu_Ctable.setData(CompetitionData);


					// 清除输入框内容
					competition_nameBox.clear();
					organizerBox.clear();
					categoryBox.clear();
					C_dateBox.clear();
					C_GPA_bonusBox.clear();

					// 更改标题
					titleText.setText(L"该学生素质类项目");

					//隐藏
					competition_nameBox.move(-500, 200);
					organizerBox.move(-500, 270);
					categoryBox.move(-500, 340);
					C_dateBox.move(-500, 410);
					C_GPA_bonusBox.move(-500, 690);
					modify_CompetitionOK_Btn.move(-500, 640);
					cancel_modifyCompetition_Btn.move(-500, 720);

					//显示
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
				// 输入错误
				else {
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			if (cancel_modifyCompetition_Btn.mouseClick(msg)) {
				// 更改标题
				titleText.setText(L"该学生素质类项目");

				// 清除输入框内容
				competition_nameBox.clear();
				organizerBox.clear();
				categoryBox.clear();
				C_dateBox.clear();
				C_GPA_bonusBox.clear();


				//隐藏
				competition_nameBox.move(-500, 200);
				organizerBox.move(-500, 270);
				categoryBox.move(-500, 340);
				C_dateBox.move(-500, 410);
				C_GPA_bonusBox.move(-500, 690);
				modify_CompetitionOK_Btn.move(-500, 640);
				cancel_modifyCompetition_Btn.move(-500, 720);

				//显示
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
					MessageBox(GetHWnd(), L"请选择一个科研成果", L"错误!", MB_ICONERROR);
				}
				else {
					int result = MessageBox(GetHWnd(), L"确定删除这个科研成果吗?", L"删除科研成果", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) { // 点击确定

						// 精确搜索素质类项目节点
						wchar_t temp[200];
						int selectedRow = Stu_Rtable.getSelectedRow();
						getTextInBox(temp, ResearchData[selectedRow][0].c_str());
						Rnode* modifying_Rnode = searchRnode_in_thisStu(Stu, temp);

						// 删除
						deleteQuality_rlist(Stu, temp);

						// 保存
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"删除素质类项目");


						// 刷新表格
						ShowStu_Research(Stu, ResearchData);
						Stu_Rtable.setData(ResearchData);
					}
				}
			}

			if (delete_Competition_Btn.mouseClick(msg)) {
				if (Stu_Ctable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个竞赛获奖", L"错误!", MB_ICONERROR);
				}
				else {
					int result = MessageBox(GetHWnd(), L"确定删除这个竞赛获奖吗?", L"删除竞赛获奖", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES) { // 点击确定

						// 精确搜索素质类项目节点
						wchar_t temp[200];
						int selectedRow = Stu_Ctable.getSelectedRow();
						getTextInBox(temp, CompetitionData[selectedRow][0].c_str());
						Cnode* modifying_Cnode = searchCnode_in_thisStu(Stu, temp);

						// 删除
						deleteQuality_clist(Stu, temp);

						// 保存
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为学生") + to_wstring(Stu->item.data.ID) + L"删除素质类项目");


						// 刷新表格
						ShowStu_Competition(Stu, CompetitionData);
						Stu_Ctable.setData(CompetitionData);
					}
				}
			}

			if (backButton.mouseClick(msg)) {
				return;
				allQualityUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}

			//表格鼠标滑动与点击
			Stu_Rtable.onMouse(msg);
			Stu_Ctable.onMouse(msg);


			// 文本框输入
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


		FlushBatchDraw(); //批量绘图

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

	//输入框
	TextBox searchInputBox(400, 20, 960, L"搜索", L"");


	//按钮
	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);


	Text idBtn(40, 100, (wstring(L"学号：") + to_wstring(stuID)).c_str(), 32);
	Text nameBtn(40, 150, (wstring(L"姓名：") + pstu->item.data.name).c_str(), 32);
	Text titleText(30, 20, (wstring(L"欢迎您  ") + pstu->item.data.name).c_str(), 56);


	//计算绩点
	double all, must, alls, musts;

	all = AllGrid(pstu);
	must = MustGrid(pstu);
	alls = AllScore(pstu);
	musts = MustScore(pstu);
	Text allCrsGridText(40, 220, (wstring(L"平均绩点: ") + to_wstring(all).substr(0, to_wstring(all).find(L'.') + 5)).c_str(), 32);
	Text allCrsScoreText(40, 260, (wstring(L"平均分: ") + to_wstring(alls).substr(0, to_wstring(alls).find(L'.') + 3)).c_str(), 32);
	Text reqCrsGridText(40, 300, (wstring(L"平均绩点(必修): ") + to_wstring(must).substr(0, to_wstring(must).find(L'.') + 5)).c_str(), 32);
	Text reqCrsScoreText(40, 340, (wstring(L"平均分(必修): ") + to_wstring(musts).substr(0, to_wstring(musts).find(L'.') + 3)).c_str(), 32);
	Text predictGridText(40, 380, (wstring(L"预测下一学年绩点：") + to_wstring(preditcGrid(allCrsINStuData, 1, 5)).substr(0, to_wstring(preditcGrid(allCrsINStuData, 1, 5)).find(L'.') + 5)).c_str(), 32);


	Button chooseCrsBtn(-50, 450, 330, 60, L"   选退课", 1);
	Button drawBtn(-50, 530, 330, 60, L"   查看课程图表", 1);
	Button modify_password_Btn(-50, 610, 330, 60, L"   修改密码", 1);
	Button backButton(-50, 700, 330, 60, L"   退出登录", 0);





	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		searchInputBox.draw();



		if (peekmessage(&msg, -1, true)) {
			//鼠标点击事件

			//搜索
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
				writeLog(0, admin, wstring(L"退出系统"));
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



			//表格鼠标滑动与点击
			allCrsINStuTable.onMouse(msg);
			Stu_Rtable.onMouse(msg);
			Stu_Ctable.onMouse(msg);



			// 文本框输入
			searchInputBox.onMessage(msg);
		}


		//-------------------------------------------------
		FlushBatchDraw(); //批量绘图

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

	Text titleText(40, 50, L"所有教师", 64);

	TextBox searchInputBox(310, 20, 1040, L"搜索", L"");

	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);
	Button sortBtn(30, 210, 200, 60, L"<按工号排序>", 1);
	Button inportBtn(-50, 300, 330, 60, L"   导入", 1);
	Button exportBtn(-50, 380, 330, 60, L"   导出", 1);
	Button backButton(-50, 460, 330, 60, L"   返回", 0);

	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// 输入框绘制(必须)
		searchInputBox.draw();
		if (peekmessage(&msg, -1, true)) {

			// 鼠标点击事件
			if (searchBtn.mouseClick(msg)) {
				showAllTch(TchList, allTchData, searchInputBox.text);
				allTchTable.setData(allTchData);
			}

			if (sortBtn.mouseClick(msg)) {

				sortStuaccID(&TchList);

				// 刷新表格

				showAllTch(TchList, allTchData, L"");
				allTchTable.setData(allTchData);
			}

			if (exportBtn.mouseClick(msg)) {
				if (exportTch(TchList, ".\\export\\Tch.csv")) {
					MessageBox(GetHWnd(), L"导出成功", L"导出教师", 0);
					writeLog(2, admin, wstring(L"导出教师信息"));

				}
				else {
					MessageBox(GetHWnd(), L"导出失败", L"导出教师", MB_ICONERROR);
				}
			}

			if (inportBtn.mouseClick(msg)) {
				importTch(TchList, ".\\import\\Tch.csv");


				// 刷新表格
				showAllTch(TchList, allTchData, L"");
				allTchTable.setData(allTchData);

				// 保存
				saveTch(TchList, TCH_FILE);

				writeLog(2, admin, wstring(L"导入教师信息"));
			}

			if (backButton.mouseClick(msg)) {
				return;
				menuUI_Administrator(admin, adminList, allStuList, allCrsList);
			}

			//表格鼠标滑动与点击
			allTchTable.onMouse(msg);

			// 文本框输入
			searchInputBox.onMessage(msg);
		}

		//showxy(msg); // 显示坐标



		//-------------------------------------------------
		FlushBatchDraw(); //批量绘图

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1) {
			Sleep(1);
		}

	}

}

