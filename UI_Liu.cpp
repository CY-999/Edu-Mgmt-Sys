#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"



bool showAllMajor(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm);

int mainLIUTY(void) {
	setlocale(LC_ALL, ""); //使控制台支持宽字符输出



	// 初始化图形窗口
	initgraph(1500, 810);
	BeginBatchDraw(); //开始批量绘图
	setbkcolor(RGB(55, 61, 53)); //背景颜色
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







	EndBatchDraw(); //结束批量绘图
	closegraph(); // 关闭图形窗口





	return 0;
}


// 显示转专业管理专业
bool showAllMajor(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pCurrent = StuList->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(8, L"")); //增加一行(每行8列)

	//初始化表头
	data[0][0] = L"学号";
	data[0][1] = L"姓名";
	data[0][2] = L"性别";
	data[0][3] = L"年级";
	data[0][4] = L"学院";
	data[0][5] = L"专业";
	//data[0][6] = L"原学院";
	data[0][7] = L"原专业";



	int row = 1;
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			|| wcsstr(std::to_wstring(pCurrent->item.data.grade).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.major, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.original_college, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.original_major, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(8, L"")); //增加一行(每行8列)

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = (pCurrent->item.data.gender) ? L"男" : L"女";
			data[row][3] = std::to_wstring(pCurrent->item.data.grade); //数字转为字符串
			data[row][4] = pCurrent->item.data.college;
			data[row][5] = pCurrent->item.data.major;
			if (wcscmp(pCurrent->item.data.college, pCurrent->item.data.original_college) != 0 ||
				wcscmp(pCurrent->item.data.major, pCurrent->item.data.original_major) != 0) {
				//data[row][6] = pCurrent->item.data.original_college;
				data[row][7] = pCurrent->item.data.original_major;
			}

			row++; // 行数+1
		}

		pCurrent = pCurrent->next; // 移向下一个节点

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

	Text titleText(25, 50, L"转专业管理", 64);
	Text IDText(-500, 150, L"", 32);
	Text nameText(-500, 220, L"", 32);
	Text genderText(-500, 290, L"", 32);
	Text gradeText(-500, 360, L"", 32);
	Text collegeText(-500, 430, L"", 32);
	Text majorText(-500, 500, L"", 32);

	TextBox searchInputBox(310, 20, 1040, L"搜索", (judge == 1) ? tch_or_admin->item.data.college : L"");
	TextBox gradeBox(-500, 360, 290, L"年级", L"");
	TextBox collegeBox(-500, 430, 290, L"学院", L"");
	TextBox majorBox(-500, 500, 290, L"专业", L"");

	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);
	Button modifyBtn(-50, 190, 330, 60, L"   转专业", 1);
	Button sortBtn(-50, 280, 330, 60, L"   排序", 1);
	Button exportBtn(-50, 370, 330, 60, L"   导出", 1);
	Button inportBtn(-50, 460, 330, 60, L"   导入", 1);
	Button backButton(-50, 580, 330, 60, L"   返回", 0);
	Button modifyOKButton(-500, 580, 290, 60, L"确定修改", 1);
	Button cancelButton(-500, 660, 290, 60, L"取消", 0);

	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();
		//-------------------------------------------------

		// 输入框绘制(必须)
		searchInputBox.draw();
		gradeBox.draw();
		collegeBox.draw();
		majorBox.draw();

		if (peekmessage(&msg, -1, true)) {

			// 鼠标点击事件
			if (searchBtn.mouseClick(msg)) {
				showAllMajor(allStuList, allStuData, searchInputBox.text);
				allStuTable.setData(allStuData);
			}


			if (cancelButton.mouseClick(msg)) {
				// 更改标题
				titleText.setText(L"转专业管理");

				// 清除输入框内容
				gradeBox.clear();
				collegeBox.clear();
				majorBox.clear();

				// 使表格可变化
				allStuTable.canChange = true;

				// 隐藏
				IDText.move(-500, 150);
				nameText.move(-500, 220);
				genderText.move(-500, 290);
				IDText.move(-500, 150);
				gradeBox.move(-500, 360);
				collegeBox.move(-500, 430);
				majorBox.move(-500, 500);
				modifyOKButton.move(-500, 580);
				cancelButton.move(-500, 660);

				// 显示
				modifyBtn.move(-50, 190);
				sortBtn.move(-50, 280);
				exportBtn.move(-50, 370);
				inportBtn.move(-50, 460);
				backButton.move(-50, 580);

			}


			if (modifyBtn.mouseClick(msg)) {
				// 获取当前行
				int selectedRow = allStuTable.getSelectedRow();
				vector<std::wstring> selectedData = allStuData[selectedRow];

				// 未选择学生
				if (allStuTable.getSelectedRow() == 0) {
					MessageBox(GetHWnd(), L"请选择一个学生", L"错误!", MB_ICONERROR);
				}
				else if (selectedData[7] != L"") {
					MessageBox(GetHWnd(), L"每位学生最多转一次专业，本学生已达最大转专业次数！", L"错误!", MB_ICONERROR);
				}
				else {
					// 更改标题
					titleText.setText(L"转专业管理");
					// 隐藏
					modifyBtn.move(-500, 310);
					sortBtn.move(-500, 470);
					exportBtn.move(-500, 550);
					inportBtn.move(-500, 630);
					backButton.move(-500, 730);


					// 使表格不可变化
					allStuTable.canChange = false;


					//// 获取当前行 //上面写了
					//int selectedRow = allStuTable.getSelectedRow();
					//vector<std::wstring> selectedData = allStuData[selectedRow];


					// 文本框默认内容
					IDText.setText((L"学号: " + selectedData[0]).c_str()); // C++语法
					nameText.setText((L"姓名: " + selectedData[1]).c_str());
					genderText.setText((L"性别: " + selectedData[2]).c_str());
					gradeBox.setText(selectedData[3].c_str());
					collegeBox.setText(selectedData[4].c_str());
					majorBox.setText(selectedData[5].c_str());

					// 显示
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

				// 获取当前年份(判断年级要用)
				time_t Current_time = time(NULL);
				int Current_year = localtime(&Current_time)->tm_year + 1900;

				// 精确搜索学生节点
				int tempID;
				int selectedRow = allStuTable.getSelectedRow(); // 获取当前列
				getNumberInBox(99999999, &tempID, allStuData[selectedRow][0].c_str());
				Node* modifyingStu = searchStu(&allStuList, (wchar_t*)allStuData[selectedRow][1].c_str(), tempID);

				// 判断输入格式
				if (
					getNumberInBox(9999, &grade, gradeBox.text) &&
					getTextInBox(college, collegeBox.text) &&
					getTextInBox(major, majorBox.text) &&
					(grade > 1970 && grade <= Current_year)
					) {
					if (MessageBox(GetHWnd(), (wstring(L"确定将这个学生的专业由\"") + modifyingStu->item.data.original_college + L"\"的\"" + modifyingStu->item.data.original_major + L"\"转为\"" + college + L"\"的\"" + major + L"\"吗？").c_str(), L"转专业确认", MB_YESNO | MB_ICONQUESTION) == IDYES) {
						// 修改
						modifyStu(&allStuList, modifyingStu, modifyingStu->item.data.name, tempID, modifyingStu->item.data.gender, grade, college, major);

						// 保存
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"修改学生:") + to_wstring(tempID) + L"的专业信息");


						//日志
						//writeLog();

						// 使表格可变化
						allStuTable.canChange = true;

						// 刷新表格
						showAllMajor(allStuList, allStuData, searchInputBox.text);
						allStuTable.setData(allStuData);

					}

					// 使表格可变化
					allStuTable.canChange = true;

					// 清除输入框内容
					gradeBox.clear();
					collegeBox.clear();
					majorBox.clear();


					// 更改标题
					titleText.setText(L"转专业管理");

					// 隐藏
					IDText.move(-500, 150);
					nameText.move(-500, 220);
					genderText.move(-500, 290);
					gradeBox.move(-500, 360);
					collegeBox.move(-500, 430);
					majorBox.move(-500, 500);
					modifyOKButton.move(-500, 580);
					cancelButton.move(-500, 660);

					// 显示
					modifyBtn.move(-50, 190);
					sortBtn.move(-50, 280);
					exportBtn.move(-50, 370);
					inportBtn.move(-50, 460);
					backButton.move(-50, 580);



				}
				// 输入错误
				else {
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}


			if (sortBtn.mouseClick(msg)) {
				sortStuaccID(&allStuList);

				// 保存
				saveStu(allStuList, STU_FILE);

				// 刷新表格
				showAllMajor(allStuList, allStuData, L"");
				allStuTable.setData(allStuData);
			}

			if (exportBtn.mouseClick(msg)) {
				if (exportStu(allStuList, ".\\export\\Stu.csv")) {
					MessageBox(GetHWnd(), L"导出成功", L"导出学生", 0);
					writeLog(judge, tch_or_admin, wstring(L"导出所有学生信息"));

				}
				else {
					MessageBox(GetHWnd(), L"导出失败", L"导出学生", MB_ICONERROR);
				}
			}

			if (inportBtn.mouseClick(msg)) {
				importStu(allStuList, ".\\import\\Stu.csv");


				// 刷新表格
				showAllStu(allStuList, allStuData, L"");
				allStuTable.setData(allStuData);

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
			allStuTable.onMouse(msg);

			// 文本框输入
			searchInputBox.onMessage(msg);
			gradeBox.onMessage(msg);
			collegeBox.onMessage(msg);
			majorBox.onMessage(msg);
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




void logUI(Node* admin, List adminList, List allStuList, Cpnode allCrsList) {
	cleardevice();


	FILE* fp;
	char file_name[50] = ".\\log\\Log.log";
	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"日志读取失败，即将退出!", L"错误!", MB_ICONERROR);
		exit(EXIT_FAILURE);
	}//读取失败退出

	vector<vector<std::wstring>> data;
	data.push_back(vector<wstring>(1, L""));
	data[0][0] = L"[时间] : 操作";

	int logRow = 0;
	static wchar_t line[1024][128];
	while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
		if (line[logRow][0] == '\n') {//跳过空行
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

	Text titleText(40, 50, L"所有日志", 64);

	TextBox searchInputBox(310, 20, 1040, L"搜索", L"");

	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);
	Button backButton(-50, 700, 330, 60, L"   返回", 0);

	// 处理鼠标事件
	ExMessage msg;
	while (!_kbhit()) {
		ULONGLONG start_time = GetTickCount();

		// 输入框绘制(必须)
		searchInputBox.draw();
		if (peekmessage(&msg, -1, true)) {

			// 鼠标点击事件
			if (searchBtn.mouseClick(msg)) {

				//fp = fopen(file_name, "r");//读取文件
				//if (fp == NULL) {
				//	printf("Read \"%s\" error, please check and reboot the system!", file_name);
				//	MessageBox(GetHWnd(), L"日志读取失败，即将退出!", L"错误!", MB_ICONERROR);
				//	exit(EXIT_FAILURE);
				//}//读取失败退出

				//data.clear();
				////data.resize(0);
				//data.push_back(vector<wstring>(1, L""));
				//data[0][0] = L"[时间] : 操作";

				//logRow = 0;
				//int trueRow = 0;
				//for (int i = 0; i < 1024; i++) {
				//	line[i][0] == L'\0';
				//}
				//while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
				//	if (line[logRow][0] == '\n') {//跳过空行
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

				fp = fopen(file_name, "r");//读取文件
				if (fp == NULL) {
					printf("Read \"%s\" error, please check and reboot the system!", file_name);
					MessageBox(GetHWnd(), L"日志读取失败，即将退出!", L"错误!", MB_ICONERROR);
					exit(EXIT_FAILURE);
				}//读取失败退出

				vector<vector<std::wstring>> data;
				data.push_back(vector<wstring>(1, L""));
				data[0][0] = L"[时间] : 操作";

				logRow = 0;
				while (fgetws(line[logRow], sizeof(line[logRow]) / sizeof(line[logRow][0]), fp) != NULL) {
					if (line[logRow][0] == '\n') {//跳过空行
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




void showLog(vector<vector<wstring>> data, wchar_t* searchTerm) {
	//data.clear(); // 清空数组
	//data.push_back(vector<wstring>(1, L"")); //增加一行(每行1列)

	////初始化表头
	//data[0][0] = L"[时间] : 操作";

	//int logRow = data.size();
	//while (logRow--) {

	//	// 检测是否有搜索词
	//	if (data[logRow][0] == (wstring)searchTerm) // 数字转为字符串再转为wchar_t来进行比较
	//		|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
	//		|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
	//		) {

	//		data.push_back(vector<std::wstring>(1, L"")); //增加一行(每行1列)

	//		//每行的内容
	//		data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
	//		data[row][1] = pCurrent->item.data.name;
	//		data[row][2] = (pCurrent->item.data.gender) ? L"男" : L"女";
	//		data[row][3] = pCurrent->item.data.college;


	//		row++; // 行数+1
	//	}


	//}
}

void showStuAllCrs(const Cpnode cphead, vector<vector<wstring>>& data, const wchar_t* searchTerm)
{
	Cpnode cplist = cphead->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(5, L""));

	//初始化表头
	data[0][0] = L"课程名称";
	data[0][1] = L"课程号";
	data[0][2] = L"课程性质";
	data[0][3] = L"学分";
	data[0][4] = L"学年";


	int row = 1;
	while (cplist != NULL)//遍历链表
	{
		// 检测是否有搜索词
		if (
			wcsstr(cplist->cname, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->cnum).c_str(), searchTerm) != NULL ||
			wcsstr(cplist->character, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->credit).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->SchYear).c_str(), searchTerm) != NULL
			)
		{
			data.push_back(vector<std::wstring>(5, L""));

			//每行的内容
			data[row][0] = cplist->cname;
			data[row][1] = std::to_wstring(cplist->cnum);
			data[row][2] = cplist->character;
			data[row][3] = std::to_wstring(cplist->credit);
			data[row][4] = std::to_wstring(cplist->SchYear);

			//保留小数
			data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
			row++; // 行数+1
		}
		cplist = cplist->next; // 移向下一个节点
	}
	return;
}


void showStuChooseCrs(const Node* Stu, vector<vector<wstring>>& data)
{
	Crsnode* cplist = Stu->item.crslist->crs_next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(5, L""));

	//初始化表头
	data[0][0] = L"课程名称";
	data[0][1] = L"课程号";
	data[0][2] = L"课程性质";
	data[0][3] = L"学分";
	data[0][4] = L"学年";


	int row = 1;
	while (cplist != NULL)//遍历链表
	{
		// 检测是否有搜索词
		data.push_back(vector<std::wstring>(5, L""));

		//每行的内容
		data[row][0] = cplist->score.course_name;
		data[row][1] = cplist->score.course_id;
		data[row][2] = (cplist->score.course_nature == 1) ? L"必修" : L"选修";
		data[row][3] = std::to_wstring(cplist->score.credit);
		data[row][4] = std::to_wstring(cplist->score.semester);

		//保留小数
		data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
		row++; // 行数+1
		cplist = cplist->crs_next; // 移向下一个节点
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

	//输入
	TextBox searchInputBox(400, 20, 960, L"搜索", L"");


	//按钮
	Button searchBtn(1370, 20, 100, 50, L"搜索", 1);


	Text idBtn(40, 100, (wstring(L"学号：") + to_wstring(stuID)).c_str(), 32);
	Text nameBtn(40, 150, (wstring(L"姓名：") + pstu->item.data.name).c_str(), 32);
	Text titleText(50, 20, (wstring(L"选退课")).c_str(), 56);


	//计算绩点
	Button chooseBtn(-50, 520, 330, 60, L"   选课", 1);
	Button cancelBtn(-50, 600, 330, 60, L"   退课", 1);
	Button backButton(-50, 690, 330, 60, L"   完成", 0);





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
				showStu(pstu, stuAllCrs, searchInputBox.text);
				allCrsTable.setData(stuAllCrs);
			}

			if (chooseBtn.mouseClick(msg)) {
				// 获取当前行
				int selectedRowAll = allCrsTable.getSelectedRow();
				if (selectedRowAll == 0) {
					MessageBox(GetHWnd(), L"请选择一门未选课程", L"错误!", MB_ICONERROR);
				}
				else {
					vector<std::wstring> selectedData = stuAllCrs[selectedRowAll];
					Cpnode addingCrs = searchCrs(allCrsList, stoi(selectedData[1]), stoi(selectedData[4]));


					if (addStuInCrs(addingCrs, pstu->item.data.name, pstu->item.data.ID, 0) == 0) {
						MessageBox(GetHWnd(), L"你已经选择了这门课程", L"错误!", MB_ICONERROR);
					}
					else {
						addCrsToStu(pstu, selectedData[1].c_str(), selectedData[0].c_str(), 0, stoi(selectedData[4]), wcscmp(selectedData[2].c_str(), L"必修") == 0 ? 1 : 0, stod(selectedData[3]), 0);

						//刷新表格
						showStuChooseCrs(pstu, stuChooseCrs);
						chooseCrsTable.setData(stuChooseCrs);

						// 保存
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);

						writeLog(0, pstu, wstring(L"选课:") + selectedData[1]);
					}
				}
			}

			if (cancelBtn.mouseClick(msg)) {
				// 获取当前行
				int selectedRowChoose = chooseCrsTable.getSelectedRow();
				if (selectedRowChoose == 0) {
					MessageBox(GetHWnd(), L"请选择一门已选课程", L"错误!", MB_ICONERROR);
				}
				else {
					vector<std::wstring> selectedData = stuChooseCrs[selectedRowChoose];
					Cpnode deletingCrs = searchCrs(allCrsList, stoi(selectedData[1]), stoi(selectedData[4]));
					Crsnode* tmpcrs = searchCrsInStu(pstu, selectedData[1].c_str(), selectedData[0].c_str());

					if (tmpcrs->score.score != 0) {
						MessageBox(GetHWnd(), L"这门课程你已完成考试，不能退课！", L"错误!", MB_ICONERROR);
					}
					else {
						deleteStuInCrs(deletingCrs, pstu->item.data.name, pstu->item.data.ID);
						deleteCrsInStu(pstu, tmpcrs);
						MessageBox(GetHWnd(), L"退课成功", L"退课!", MB_ICONINFORMATION);

						//刷新表格
						showStuChooseCrs(pstu, stuChooseCrs);
						chooseCrsTable.setData(stuChooseCrs);

						// 保存
						saveStu(allStuList, STU_FILE);
						saveCrs(allCrsList, CRS_FILE);

						writeLog(0, pstu, wstring(L"退课:") + selectedData[1]);
					}
				}
			}

			if (backButton.mouseClick(msg))
			{
				writeLog(0, pstu, wstring(L"选课完成"));
				return;
				loginUI();
			}

			//表格鼠标滑动与点击
			allCrsTable.onMouse(msg);
			chooseCrsTable.onMouse(msg);



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


