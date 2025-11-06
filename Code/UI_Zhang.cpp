#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"

//在联动时，如果对方不存在，该怎么办；有时间的话，解决这个问题



//问题1：为什么没有titleText->move(-500, 50);就不行
//问题2：为什么有时候要在隐藏后更改标题才行（比如allCrsUI中的if (screenCrsBtn.mouseClick(msg))之后）
void modifyTitleText(Text* titleText, const wchar_t* text, int y)
{
	titleText->move(-500, 50);
	int areaWidth = 280;
	int size = 64;
	settextstyle(size, 0, L"微软雅黑");
	int textWidth = textwidth(text);
	while (textWidth > areaWidth)
	{
		size -= 2;
		settextstyle(size, 0, L"微软雅黑");
		textWidth = textwidth(text);
	}
	int x = 10 + (290 - textWidth) / 2;
	titleText->setTextSize(size);
	titleText->setText(text);
	titleText->move(x, y);
	return;
}

int mainZ(void)
{

	setlocale(LC_ALL, ""); //使控制台支持宽字符输出

	// 初始化图形窗口
	initgraph(1500, 810);
	BeginBatchDraw(); //开始批量绘图
	setbkcolor(RGB(55, 61, 53)); //背景颜色
	cleardevice();

	loginUI();

	EndBatchDraw(); //结束批量绘图
	closegraph(); // 关闭图形窗口
	return 0;
}

void allCrsUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList)
{
	cleardevice();
	//Cpnode allCrsList = readCrs(CRS_FILE);
	vector<vector<std::wstring>> allCrsData;
	showAllCrs(allCrsList, allCrsData, L"", 0, 0, 0);

	//List allStuList = readStu(STU_FILE);

	Table allCrsTable(310, 90, 940 + 220, 700, allCrsData);

	Text titleText(40, 10, L"所有课程", 64);

	TextBox searchInputBox(310, 20, 820 + 220 - 120, L"搜索", L"");
	TextBox cnameBox(-500, 0, 290, L"课程名称", L"");
	TextBox cnumBox(-500, 0, 290, L"课程号", L"");
	TextBox characterBox(-500, 0, 290, L"课程性质", L"");
	TextBox creditBox(-500, 0, 290, L"学分", L"");
	TextBox SchYearBox(-500, 0, 290, L"学年", L"");
	TextBox minBox(-500, 0, 290, L"最小值", L"");
	TextBox maxBox(-500, 0, 290, L"最大值", L"");

	Button searchBtn(1150 + 220 - 120, 20, 100, 50, L"搜索", 1);
	Button drawBtn(1150 + 220, 20, 100, 50, L"绘图", 1);

	int y = 90 - 80, dy = 80;//方便调位置,或者说，更契合面向“Ctrl+C”和“Ctrl+V”的编程思想
	Button viewCrsBtn(-50, y += dy, 330, 60, L"   查看", 1);
	Button addCrsBtn(-50, y += dy, 330, 60, L"   添加", 1);
	Button modifyCrsBtn(-50, y += dy, 330, 60, L"   修改", 1);
	Button deleteCrsBtn(-50, y += dy, 330, 60, L"   删除", 1);
	Button sortCrsBtn(-50, y += dy, 330, 60, L"   排序", 1);
	Button screenCrsBtn(-50, y += dy, 330, 60, L"   筛选", 1);
	Button screenCancelBtn(-500, 0, 330, 60, L"   取消筛选", 1);
	Button exportBtn(-50, y += dy, 330, 60, L"   导出", 1);
	Button inportBtn(-50, y += dy, 330, 60, L"   导入", 1);
	Button backButton(-50, y += dy, 330, 60, L"   返回", 0);

	Button sortByCnumBtn(-500, 0, 290, 60, L"按课程号排序", 1);
	Button sortBySchYearBtn(-500, 0, 290, 60, L"按学年排序", 1);
	Button sortByHeadcountBtn(-500, 0, 290, 60, L"按总人数排序", 1);
	Button sortByAverscoreBtn(-500, 0, 290, 60, L"按平均成绩排序", 1);
	Button sortByAverGPABtn(-500, 0, 290, 60, L"按平均绩点排序", 1);
	Button sortByPassRateBtn(-500, 0, 290, 60, L"按及格率排序", 1);
	Button sortByExcelRateGPABtn(-500, 0, 290, 60, L"按优秀率排序", 1);
	Button AscendingOrderBtn(-500, 0, 290, 60, L"升序", 1);
	Button DescendingOrderBtn(-500, 0, 290, 60, L"降序", 1);

	Button screenBySchYearBtn(-500, 0, 290, 60, L"按学年筛选", 1);
	Button screenByHeadcountBtn(-500, 0, 290, 60, L"按总人数筛选", 1);
	Button screenByAverscoreBtn(-500, 0, 290, 60, L"按平均成绩筛选", 1);
	Button screenByAverGPABtn(-500, 0, 290, 60, L"按平均绩点筛选", 1);
	Button screenByPassRateBtn(-500, 0, 290, 60, L"按及格率筛选", 1);
	Button screenByExcelRateBtn(-500, 0, 290, 60, L"按优秀率筛选", 1);

	Button addOKButton(-500, 0, 290, 60, L"确定添加", 1);
	Button modifyOKButton(-500, 0, 290, 60, L"确定修改", 1);
	Button screenOKButton(-500, 0, 290, 60, L"确定筛选", 1);
	Button cancelButton(-500, 0, 290, 60, L"取消", 0);


	// 处理鼠标事件
	ExMessage msg;
	int sortOption = 0;//用来排序
	wchar_t searchTerm[512] = L"";
	bool IsInScreen = false;
	int screenOption = 0;
	double screenMin = 0;
	double screenMax = 0;
	while (!_kbhit())
	{
		ULONGLONG start_time = GetTickCount();
		//->

		searchInputBox.draw();
		cnameBox.draw();
		cnumBox.draw();
		characterBox.draw();
		creditBox.draw();
		SchYearBox.draw();
		minBox.draw();
		maxBox.draw();

		if (peekmessage(&msg, -1, true))
		{

			if (drawBtn.mouseClick(msg))
			{
				chartUI(allCrsData, 0, 6, 0, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				allCrsTable.draw();
				titleText.draw();
				searchInputBox.draw();
				searchBtn.draw();
				drawBtn.draw();
				y = 90 - 80, dy = 80;//方便调位置,或者说，更契合面向“Ctrl+C”和“Ctrl+V”的编程思想
				viewCrsBtn.draw();
				addCrsBtn.draw();
				modifyCrsBtn.draw();
				deleteCrsBtn.draw();
				sortCrsBtn.draw();
				screenCrsBtn.draw();
				screenCancelBtn.draw();
				exportBtn.draw();
				inportBtn.draw();
				backButton.draw();

			}
			if (cancelButton.mouseClick(msg)) {

				sortOption = 0;
				if (IsInScreen)
				{
					screenOption = 0;
					IsInScreen = false;
				}

				// 清除输入框内容
				cnameBox.clear();
				cnumBox.clear();
				characterBox.clear();
				SchYearBox.clear();
				creditBox.clear();
				minBox.clear();
				maxBox.clear();

				// 使表格可变化
				allCrsTable.canChange = true;

				// 隐藏
				cnameBox.move(-500, 0);
				cnumBox.move(-500, 0);
				characterBox.move(-500, 0);
				creditBox.move(-500, 0);
				SchYearBox.move(-500, 0);
				minBox.move(-500, 0);
				maxBox.move(-500, 0);


				sortByCnumBtn.move(-500, 0);
				sortBySchYearBtn.move(-500, 0);
				sortByHeadcountBtn.move(-500, 0);
				sortByAverscoreBtn.move(-500, 0);
				sortByAverGPABtn.move(-500, 0);
				sortByPassRateBtn.move(-500, 0);
				sortByExcelRateGPABtn.move(-500, 0);
				AscendingOrderBtn.move(-500, 0);
				DescendingOrderBtn.move(-500, 0);

				screenBySchYearBtn.move(-500, 0);
				screenByHeadcountBtn.move(-500, 0);
				screenByAverscoreBtn.move(-500, 0);
				screenByAverGPABtn.move(-500, 0);
				screenByPassRateBtn.move(-500, 0);
				screenByExcelRateBtn.move(-500, 0);

				addOKButton.move(-500, 0);
				modifyOKButton.move(-500, 0);
				screenOKButton.move(-500, 0);
				cancelButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"所有课程", 10);

				// 显示
				y = 90 - 80, dy = 80;
				viewCrsBtn.move(-50, y += dy);
				addCrsBtn.move(-50, y += dy);
				modifyCrsBtn.move(-50, y += dy);
				deleteCrsBtn.move(-50, y += dy);
				sortCrsBtn.move(-50, y += dy);
				if (!screenOption)
					screenCrsBtn.move(-50, y += dy);
				else
					screenCancelBtn.move(-50, y += dy);
				exportBtn.move(-50, y += dy);
				inportBtn.move(-50, y += dy);
				backButton.move(-50, y += dy);

			}

			if (searchBtn.mouseClick(msg))
			{
				wcscpy(searchTerm, searchInputBox.text);
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);
			}

			if (viewCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"请选择课程", L"错误!", MB_ICONERROR);
				}
				else
				{
					// 获取课程节点信息
					int cnum;
					int SchYear;
					int selectedRow = allCrsTable.getSelectedRow(); // 获取当前行
					getNumberInBox(99999, &cnum, allCrsData[selectedRow][1].c_str());
					getNumberInBox(99999, &SchYear, allCrsData[selectedRow][4].c_str());
					Cpnode cplist = searchCrs(allCrsList, cnum, SchYear);
					CrsUI(allCrsList, cplist, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);


					cleardevice();
					allCrsTable.draw();
					titleText.draw();
					searchInputBox.draw();
					searchBtn.draw();
					drawBtn.draw();
					y = 90 - 80, dy = 80;//方便调位置,或者说，更契合面向“Ctrl+C”和“Ctrl+V”的编程思想
					viewCrsBtn.draw();
					addCrsBtn.draw();
					modifyCrsBtn.draw();
					deleteCrsBtn.draw();
					sortCrsBtn.draw();
					screenCrsBtn.draw();
					screenCancelBtn.draw();
					exportBtn.draw();
					inportBtn.draw();
					backButton.draw();

				}
			}

			if (addCrsBtn.mouseClick(msg))
			{
				// 隐藏
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"添加课程", 10);

				// 显示
				y = 150 - 80, dy = 80;
				cnameBox.move(10, y += dy);
				cnumBox.move(10, y += dy);
				characterBox.move(10, y += dy);
				creditBox.move(10, y += dy);
				SchYearBox.move(10, y += dy);
				addOKButton.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (addOKButton.mouseClick(msg))
			{
				wchar_t cname[30];
				int cnum;
				wchar_t character[5];
				double credit;
				int SchYear;

				// 判断输入格式
				if (
					getTextInBox(cname, cnameBox.text) &&
					getNumberInBox(99999, &cnum, cnumBox.text) &&
					getTextInBox(character, characterBox.text) &&
					getDoubleInBox(10, &credit, creditBox.text) &&
					getNumberInBox(99999, &SchYear, SchYearBox.text) &&
					cnum > 9999 && credit > 0
					)
				{

					// 课程相同的情况,报错提醒
					if (!addCrs(allCrsList, cname, cnum, character, credit, SchYear))
					{
						MessageBox(GetHWnd(), L"该课程号已经存在,请勿重复添加!", L"错误!", MB_ICONERROR);
					}
					else
					{
						// 保存
						saveCrs(allCrsList, CRS_FILE);

						writeLog(judge, tch_or_admin, wstring(L"添加课程:") + to_wstring(cnum));


						// 刷新表格
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);

						// 清除输入框内容
						cnameBox.clear();
						cnumBox.clear();
						characterBox.clear();
						creditBox.clear();
						SchYearBox.clear();

						// 隐藏
						cnameBox.move(-500, 0);
						cnumBox.move(-500, 0);
						characterBox.move(-500, 0);
						creditBox.move(-500, 0);
						SchYearBox.move(-500, 0);
						addOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// 更改标题
						modifyTitleText(&titleText, L"所有课程", 10);

						// 显示
						y = 90 - 80, dy = 80;
						viewCrsBtn.move(-50, y += dy);
						addCrsBtn.move(-50, y += dy);
						modifyCrsBtn.move(-50, y += dy);
						deleteCrsBtn.move(-50, y += dy);
						sortCrsBtn.move(-50, y += dy);
						if (!screenOption)
							screenCrsBtn.move(-50, y += dy);
						else
							screenCancelBtn.move(-50, y += dy);
						exportBtn.move(-50, y += dy);
						inportBtn.move(-50, y += dy);
						backButton.move(-50, y += dy);
					}


				}
				// 输入错误
				else
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			if (modifyCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"请选择课程", L"错误!", MB_ICONERROR);
				}
				else
				{
					// 隐藏
					viewCrsBtn.move(-500, 0);
					addCrsBtn.move(-500, 0);
					modifyCrsBtn.move(-500, 0);
					deleteCrsBtn.move(-500, 0);
					sortCrsBtn.move(-500, 0);
					screenCrsBtn.move(-500, 0);
					screenCancelBtn.move(-500, 0);
					exportBtn.move(-500, 0);
					inportBtn.move(-500, 0);
					backButton.move(-500, 0);

					// 更改标题
					modifyTitleText(&titleText, L"修改课程", 10);

					// 使表格不可变化
					allCrsTable.canChange = false;

					// 获取当前行
					int selectedRow = allCrsTable.getSelectedRow();
					vector<std::wstring> selectedData = allCrsData[selectedRow];

					// 文本框默认内容
					cnameBox.setText(selectedData[0].c_str());
					cnumBox.setText(selectedData[1].c_str());
					characterBox.setText(selectedData[2].c_str());
					creditBox.setText(selectedData[3].c_str());
					SchYearBox.setText(selectedData[4].c_str());


					// 显示
					y = 150 - 80, dy = 80;
					cnameBox.move(10, y += dy);
					cnumBox.move(10, y += dy);
					characterBox.move(10, y += dy);
					creditBox.move(10, y += dy);
					SchYearBox.move(10, y += dy);
					modifyOKButton.move(10, y += dy);
					cancelButton.move(10, y += dy);
				}

			}

			//有这门课的学生信息都要修改
			if (modifyOKButton.mouseClick(msg))
			{
				wchar_t cname[30];
				int cnum;
				wchar_t character[5];
				double credit;
				int SchYear;

				// 精确搜索课程节点
				int original_cnum;
				int original_SchYear;
				int selectedRow = allCrsTable.getSelectedRow(); // 获取当前行
				getNumberInBox(99999, &original_cnum, allCrsData[selectedRow][1].c_str());
				getNumberInBox(99999, &original_SchYear, allCrsData[selectedRow][4].c_str());
				Cpnode modifyingCrs = searchCrs(allCrsList, original_cnum, original_SchYear);

				// 判断输入格式
				if (
					getTextInBox(cname, cnameBox.text) &&
					getNumberInBox(99999, &cnum, cnumBox.text) &&
					getTextInBox(character, characterBox.text) &&
					getDoubleInBox(10, &credit, creditBox.text) &&
					getNumberInBox(99999, &SchYear, SchYearBox.text) &&
					cnum > 9999 && credit > 0 && SchYear > 0&&
					(wcscmp(character,L"必修")==0|| wcscmp(character, L"选修") == 0)
					)
				{
					if (searchCrs(allCrsList, cnum, SchYear))
					{
						MessageBox(GetHWnd(), L"课程冲突", L"错误!", MB_ICONWARNING);
					}
					else
					{
						Node* StuNode = allStuList->next;
						while (StuNode)
						{
							wchar_t wch_cnum[10];
							swprintf(wch_cnum, 10, L"%d", modifyingCrs->cnum);
							Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, modifyingCrs->cname);
							if (CrsNode)
							{
								swprintf(wch_cnum, 10, L"%d", cnum);
								int digit_character = wcscmp(character, L"必修") ? 0 : 1;//必修是1
								modifyCrsInStu(CrsNode, wch_cnum, cname, CrsNode->score.score, SchYear, digit_character, credit, CrsNode->score.grid);
							}
							StuNode = StuNode->next;
						}

						// 修改
						modifyCrs(modifyingCrs, cname, cnum, character, credit, SchYear);

						// 保存
						saveCrs(allCrsList, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"修改课程:") + to_wstring(cnum));

						// 使表格可变化
						allCrsTable.canChange = true;

						// 刷新表格
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);

						// 清除输入框内容
						cnameBox.clear();
						cnumBox.clear();
						characterBox.clear();
						creditBox.clear();
						SchYearBox.clear();

						// 隐藏
						cnameBox.move(-500, 0);
						cnumBox.move(-500, 0);
						characterBox.move(-500, 0);
						creditBox.move(-500, 0);
						SchYearBox.move(-500, 0);
						modifyOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// 更改标题
						modifyTitleText(&titleText, L"所有课程", 10);

						// 显示
						y = 90, dy = 80;
						viewCrsBtn.move(-50, y);
						addCrsBtn.move(-50, y += dy);
						modifyCrsBtn.move(-50, y += dy);
						deleteCrsBtn.move(-50, y += dy);
						sortCrsBtn.move(-50, y += dy);
						if (!screenOption)
							screenCrsBtn.move(-50, y += dy);
						else
							screenCancelBtn.move(-50, y += dy);
						exportBtn.move(-50, y += dy);
						inportBtn.move(-50, y += dy);
						backButton.move(-50, y += dy);
					}

				}
				// 输入错误
				else
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			//有这门课的学生信息都要修改
			if (deleteCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"请选择课程", L"错误!", MB_ICONERROR);
				}
				else
				{
					int result = MessageBox(GetHWnd(), L"确定删除这门课程吗?", L"删除课程", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{ // 点击确定

						// 获取课程节点信息
						wchar_t cname[30];
						int cnum;
						int selectedRow = allCrsTable.getSelectedRow(); // 获取当前行
						getTextInBox(cname, allCrsData[selectedRow][0].c_str());
						getNumberInBox(99999, &cnum, allCrsData[selectedRow][1].c_str());

						Node* StuNode = allStuList->next;
						while (StuNode)
						{
							wchar_t wch_cnum[10];
							swprintf(wch_cnum, 10, L"%d", cnum);
							Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cname);
							if (CrsNode)
								deleteCrsInStu(StuNode, CrsNode);
							StuNode = StuNode->next;
						}

						// 删除
						deleteCrs(allCrsList, cname, cnum);

						// 保存
						saveCrs(allCrsList, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"删除课程:") + to_wstring(cnum));



						// 刷新表格
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);
					}
				}
			}

			if (sortCrsBtn.mouseClick(msg))
			{
				//要先隐藏后更改标题，否侧会出bug，不知道为啥

				// 隐藏
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"排序", 50);

				// 显示
				y = 150 - 80, dy = 80;
				sortByCnumBtn.move(10, y += dy);
				sortBySchYearBtn.move(10, y += dy);
				sortByHeadcountBtn.move(10, y += dy);
				sortByAverscoreBtn.move(10, y += dy);
				sortByAverGPABtn.move(10, y += dy);
				sortByPassRateBtn.move(10, y += dy);
				sortByExcelRateGPABtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (sortByCnumBtn.mouseClick(msg))
				sortOption = 1;
			if (sortBySchYearBtn.mouseClick(msg))
				sortOption = 3;
			if (sortByHeadcountBtn.mouseClick(msg))
				sortOption = 5;
			if (sortByAverscoreBtn.mouseClick(msg))
				sortOption = 7;
			if (sortByAverGPABtn.mouseClick(msg))
				sortOption = 9;
			if (sortByPassRateBtn.mouseClick(msg))
				sortOption = 11;
			if (sortByExcelRateGPABtn.mouseClick(msg))
				sortOption = 13;

			if (sortOption)
			{
				// 隐藏
				sortByCnumBtn.move(-500, 0);
				sortBySchYearBtn.move(-500, 0);
				sortByHeadcountBtn.move(-500, 0);
				sortByAverscoreBtn.move(-500, 0);
				sortByAverGPABtn.move(-500, 0);
				sortByPassRateBtn.move(-500, 0);
				sortByExcelRateGPABtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// 更改标题
				wchar_t titletext[512];
				switch (sortOption)
				{
				case 1:
					wcscpy(titletext, L"按课程号排序");
					break;
				case 3:
					wcscpy(titletext, L"按学年排序");
					break;
				case 5:
					wcscpy(titletext, L"按总人数排序");
					break;
				case 7:
					wcscpy(titletext, L"按平均成绩排序");
					break;
				case 9:
					wcscpy(titletext, L"按平均绩点排序");
					break;
				case 11:
					wcscpy(titletext, L"按及格率排序");
					break;
				case 13:
					wcscpy(titletext, L"按优秀率排序");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				// 显示
				y = 150 - 80, dy = 80;
				AscendingOrderBtn.move(10, y += dy);
				DescendingOrderBtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			bool flag_AscendingOrderBtn = AscendingOrderBtn.mouseClick(msg);//不这么做，AscendingOrderBtn.mouseClick(msg)在一个循环中只会被检测一次
			bool flag_DescendingOrderBtn = DescendingOrderBtn.mouseClick(msg);
			if (flag_DescendingOrderBtn)
				sortOption++;

			if (flag_AscendingOrderBtn || flag_DescendingOrderBtn)
			{
				//链表排序
				sortCrs(allCrsList, sortOption);

				// 刷新表格
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				// 隐藏
				AscendingOrderBtn.move(-500, 0);
				DescendingOrderBtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"所有课程", 10);

				// 显示
				y = 90 - 80, dy = 80;
				viewCrsBtn.move(-50, y += dy);
				addCrsBtn.move(-50, y += dy);
				modifyCrsBtn.move(-50, y += dy);
				deleteCrsBtn.move(-50, y += dy);
				sortCrsBtn.move(-50, y += dy);
				if (!screenOption)
					screenCrsBtn.move(-50, y += dy);
				else
					screenCancelBtn.move(-50, y += dy);
				exportBtn.move(-50, y += dy);
				inportBtn.move(-50, y += dy);
				backButton.move(-50, y += dy);

				sortOption = 0;
			}

			if (screenCrsBtn.mouseClick(msg))
			{
				// 隐藏
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"筛选", 50);

				// 显示
				y = 150 - 80, dy = 80;
				screenBySchYearBtn.move(10, y += dy);
				screenByHeadcountBtn.move(10, y += dy);
				screenByAverscoreBtn.move(10, y += dy);
				screenByAverGPABtn.move(10, y += dy);
				screenByPassRateBtn.move(10, y += dy);
				screenByExcelRateBtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (screenBySchYearBtn.mouseClick(msg))
			{
				screenOption = 1;
				IsInScreen = true;
			}
			if (screenByHeadcountBtn.mouseClick(msg))
			{
				screenOption = 2;
				IsInScreen = true;
			}
			if (screenByAverscoreBtn.mouseClick(msg))
			{
				screenOption = 3;
				IsInScreen = true;
			}
			if (screenByAverGPABtn.mouseClick(msg))
			{
				screenOption = 4;
				IsInScreen = true;
			}
			if (screenByPassRateBtn.mouseClick(msg))
			{
				screenOption = 5;
				IsInScreen = true;
			}
			if (screenByExcelRateBtn.mouseClick(msg))
			{
				screenOption = 6;
				IsInScreen = true;
			}

			if (IsInScreen)
			{
				// 隐藏
				screenBySchYearBtn.move(-500, 0);
				screenByHeadcountBtn.move(-500, 0);
				screenByAverscoreBtn.move(-500, 0);
				screenByAverGPABtn.move(-500, 0);
				screenByPassRateBtn.move(-500, 0);
				screenByExcelRateBtn.move(-500, 0);

				// 更改标题
				wchar_t titletext[512];
				switch (screenOption)
				{
				case 1:
					wcscpy(titletext, L"按学年筛选");
					break;
				case 2:
					wcscpy(titletext, L"按总人数筛选");
					break;
				case 3:
					wcscpy(titletext, L"按平均成绩筛选");
					break;
				case 4:
					wcscpy(titletext, L"按平均绩点筛选");
					break;
				case 5:
					wcscpy(titletext, L"按及格率筛选");
					break;
				case 6:
					wcscpy(titletext, L"按优秀率筛选");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				//显示
				y = 150 - 80, dy = 80;
				minBox.move(10, y += dy);
				maxBox.move(10, y += dy);
				screenOKButton.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (screenOKButton.mouseClick(msg))
			{
				double MAX;
				switch (screenOption)
				{
				case 1://按学年筛选
				case 2://按总人数筛选
					MAX = 99999;//随便多大都行
					break;
				case 3://按平均成绩
					MAX = 100;
					break;
				case 4://按平均绩点
					MAX = 4;
					break;
				case 5://按及格率筛选
				case 6://按优秀率筛选
					MAX = 1;
					break;

				}
				if (
					getDoubleInBox(MAX, &screenMin, minBox.text) &&
					getDoubleInBox(MAX, &screenMax, maxBox.text) &&
					screenMin >= 0 && screenMax >= 0 && screenMin <= screenMax
					)
				{
					// 刷新表格
					showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
					allCrsTable.setData(allCrsData);

					// 清除输入框内容
					minBox.clear();
					maxBox.clear();

					// 隐藏
					minBox.move(-500, 0);
					maxBox.move(-500, 0);
					screenOKButton.move(-500, 0);
					cancelButton.move(-500, 0);

					// 更改标题
					modifyTitleText(&titleText, L"所有课程", 10);

					// 显示
					y = 90 - 80, dy = 80;
					viewCrsBtn.move(-50, y += dy);
					addCrsBtn.move(-50, y += dy);
					modifyCrsBtn.move(-50, y += dy);
					deleteCrsBtn.move(-50, y += dy);
					sortCrsBtn.move(-50, y += dy);
					if (!screenOption)
						screenCrsBtn.move(-50, y += dy);
					else
						screenCancelBtn.move(-50, y += dy);
					exportBtn.move(-50, y += dy);
					inportBtn.move(-50, y += dy);
					backButton.move(-50, y += dy);

					IsInScreen = false;
				}
				else// 输入错误
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}
			}

			if (screenCancelBtn.mouseClick(msg))
			{
				screenOption = 0;
				screenMin = 0;
				screenMax = 0;

				// 刷新表格
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				screenCancelBtn.move(-500, 0);
				screenCrsBtn.move(-50, 490);
			}



			if (exportBtn.mouseClick(msg))
			{
				if (exportCrs(allCrsList, ".\\export\\Crs.csv"))
				{
					MessageBox(GetHWnd(), L"导出成功", L"导出课程", 0);
					writeLog(judge, tch_or_admin, wstring(L"导出所有课程信息"));
				}
				else {
					MessageBox(GetHWnd(), L"导出失败", L"导出课程", MB_ICONERROR);
				}

				////// 保存
				////saveCrs(allCrsList, CRS_FILE);
				////先不保存，不然导入过一遍之后就有相同数据, 第二次就导入不了了

				////刷新表格
				//showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				//allCrsTable.setData(allCrsData);
			}
			if (inportBtn.mouseClick(msg))
			{
				importCrs(allCrsList, ".\\import\\Crs.csv");


				// 刷新表格
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				// 保存
				saveCrs(allCrsList, CRS_FILE);

				writeLog(judge, tch_or_admin, wstring(L"导入课程信息"));
			}
			if (backButton.mouseClick(msg))
			{
				return;
				if (judge == 1)
					menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				else
					menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}

			//表格鼠标滑动与点击
			allCrsTable.onMouse(msg);

			// 文本框输入
			searchInputBox.onMessage(msg);
			cnameBox.onMessage(msg);
			cnumBox.onMessage(msg);
			characterBox.onMessage(msg);
			creditBox.onMessage(msg);
			SchYearBox.onMessage(msg);
			minBox.onMessage(msg);
			maxBox.onMessage(msg);
		}

		//showxy(msg);

		FlushBatchDraw(); //批量绘图

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1)
		{
			Sleep(1);
		}

	}

}

void CrsUI(Cpnode cphead, Cpnode cplist, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList)
{
	//List allStuList = readStu(STU_FILE);
	cleardevice();
	Spnode allStuInCrsList = cplist->sphead;
	vector<vector<std::wstring>>allStuInCrsData;
	showAllStuInCrs(cplist, allStuInCrsData, L"", 0, 0, 0);

	Table allStuInCrsTable(310, 90, 940 + 220, 700, allStuInCrsData);


	settextstyle(64, 0, L"微软雅黑");
	int TextWidth = textwidth(cplist->cname);
	int x = 0 + (276 - TextWidth) / 2;
	Text titleText(x, 50, cplist->cname, 64);
	modifyTitleText(&titleText, cplist->cname, 50);

	Text GPAText(-500, 370, L"", 32);

	TextBox searchInputBox(310, 20, 820 + 220, L"搜索", L"");

	TextBox snameBox(-500, 0, 290, L"学生姓名", L"");
	TextBox snumBox(-500, 0, 290, L"学号", L"");
	TextBox scoreBox(-500, 0, 290, L"成绩", L"");
	TextBox minBox(-500, 0, 290, L"最小值", L"");
	TextBox maxBox(-500, 0, 290, L"最大值", L"");


	Button searchBtn(1150 + 220, 20, 100, 50, L"搜索", 1);

	Button addStuInCrsBtn(-50, 220, 330, 60, L"   添加", 1);
	Button modifyStuInCrsBtn(-50, 300, 330, 60, L"   录入/修改成绩", 1);
	Button deleteStuInCrsBtn(-50, 380, 330, 60, L"   删除", 1);
	Button sortStuInCrsBtn(-50, 460, 330, 60, L"   排序", 1);
	Button screenStuInCrsBtn(-50, 540, 330, 60, L"   筛选", 1);
	Button screenCancelBtn(-500, 540, 330, 60, L"   取消筛选", 1);
	Button backButton(-50, 620, 330, 60, L"   返回", 0);

	Button upsortBySnumBtn(-500, 220, 290, 60, L"按学号升序", 1);
	Button downsortBySnumBtn(-500, 300, 290, 60, L"按学号降序", 1);
	Button upsortByScoreBtn(-500, 380, 290, 60, L"按成绩升序", 1);
	Button downsortByScoreBtn(-500, 460, 290, 60, L"按成绩降序", 1);
	Button upsortByGPABtn(-500, 540, 290, 60, L"按GPA升序", 1);
	Button downsortByGPABtn(-500, 620, 290, 60, L"按GPA降序", 1);

	Button screenByScoreBtn(-500, 220, 290, 60, L"按成绩筛选", 1);
	Button screenByGPABtn(-500, 300, 290, 60, L"按GPA筛选", 1);

	Button addOKButton(-500, 580, 290, 60, L"确定添加", 1);
	Button modifyOKButton(-500, 580, 290, 60, L"确定修改", 1);
	Button screenOKButton(-500, 580, 290, 60, L"确定筛选", 1);
	Button cancelButton(-500, 660, 290, 60, L"取消", 0);

	// 处理鼠标事件
	ExMessage msg;
	int sortOption = 0;//用来排序
	wchar_t searchTerm[512] = L"";
	bool IsInScreen = false;
	int screenOption = 0;
	double screenMin = 0;
	double screenMax = 0;
	while (!_kbhit())
	{
		ULONGLONG start_time = GetTickCount();
		//->

		//必须有
		searchInputBox.draw();
		snameBox.draw();
		snumBox.draw();
		scoreBox.draw();
		minBox.draw();
		maxBox.draw();

		if (peekmessage(&msg, -1, true))
		{
			if (cancelButton.mouseClick(msg))
			{
				sortOption = 0;
				if (IsInScreen)
				{
					screenOption = 0;
					IsInScreen = false;
				}

				// 清除输入框内容
				//snameBox.clear();
				//snumBox.clear();
				scoreBox.clear();
				minBox.clear();
				maxBox.clear();

				// 使表格可变化
				allStuInCrsTable.canChange = true;



				// 隐藏
				snameBox.move(-500, 0);
				snumBox.move(-500, 0);
				scoreBox.move(-500, 0);
				minBox.move(-500, 0);
				maxBox.move(-500, 0);

				addOKButton.move(-500, 0);
				modifyOKButton.move(-500, 0);
				cancelButton.move(-500, 0);

				upsortBySnumBtn.move(-500, 0);
				downsortBySnumBtn.move(-500, 0);
				upsortByScoreBtn.move(-500, 0);
				downsortByScoreBtn.move(-500, 0);
				upsortByGPABtn.move(-500, 0);
				downsortByGPABtn.move(-500, 0);

				screenByScoreBtn.move(-500, 0);
				screenByGPABtn.move(-500, 0);
				screenOKButton.move(-500, 0);
				screenCancelBtn.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, cplist->cname, 50);

				// 显示
				addStuInCrsBtn.move(-50, 220);
				modifyStuInCrsBtn.move(-50, 300);
				deleteStuInCrsBtn.move(-50, 380);
				sortStuInCrsBtn.move(-50, 460);
				if (!screenOption)
					screenStuInCrsBtn.move(-50, 540);
				else
					screenCancelBtn.move(-50, 540);
				backButton.move(-50, 620);

			}

			if (searchBtn.mouseClick(msg))
			{
				wcscpy(searchTerm, searchInputBox.text);
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);
			}

			if (addStuInCrsBtn.mouseClick(msg))
			{
				// 隐藏
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"添加学生", 50);

				// 显示
				snameBox.move(10, 140);
				snumBox.move(10, 220);
				scoreBox.move(10, 300);

				addOKButton.move(10, 380);
				cancelButton.move(10, 460);
			}

			//在对应学生的课程页添加课程
			if (addOKButton.mouseClick(msg))
			{
				wchar_t sname[30];
				int snum;
				double score;

				// 判断输入格式

				if (
					getTextInBox(sname, snameBox.text) &&
					getNumberInBox(99999999, &snum, snumBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					snum > 9999999 && score >= 0
					)
				{


					Node* StuNode = searchStu(&allStuList, sname, snum);
					if (StuNode == NULL) {
						MessageBox(GetHWnd(), L"找不到这个学生！", L"错误!", MB_ICONERROR);
					}
					else if (!addStuInCrs(cplist, sname, snum, score))
					{
						MessageBox(GetHWnd(), L"该学生已经存在,请勿重复添加!", L"错误!", MB_ICONERROR);
					}
					else
					{
						wchar_t wch_cnum[10];
						swprintf(wch_cnum, 10, L"%d", cplist->cnum);
						double GPA = CalculGPA(score);
						int character = wcscmp(cplist->character, L"必修") ? 0 : 1;//必修是1
						addCrsToStu(StuNode, wch_cnum, cplist->cname, score, cplist->SchYear, character, cplist->credit, GPA);

						// 保存
						saveCrs(cphead, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为课程:") + to_wstring(cplist->cnum) + L"添加学生:" + to_wstring(snum));

						// 刷新表格
						showAllStuInCrs(cplist, allStuInCrsData, L"", screenOption, screenMin, screenMax);
						allStuInCrsTable.setData(allStuInCrsData);

						// 清除输入框内容
						snameBox.clear();
						snumBox.clear();
						scoreBox.clear();




						// 隐藏
						snameBox.move(-500, 0);
						snumBox.move(-500, 0);
						scoreBox.move(-500, 0);
						addOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// 更改标题
						modifyTitleText(&titleText, cplist->cname, 50);

						// 显示
						addStuInCrsBtn.move(-50, 220);
						modifyStuInCrsBtn.move(-50, 300);
						deleteStuInCrsBtn.move(-50, 380);
						sortStuInCrsBtn.move(-50, 460);
						if (!screenOption)
							screenStuInCrsBtn.move(-50, 540);
						else
							screenCancelBtn.move(-50, 540);
						backButton.move(-50, 620);
					}


				}
				// 输入错误
				else
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			if (modifyStuInCrsBtn.mouseClick(msg))
			{
				if (allStuInCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"请选择学生", L"错误!", MB_ICONERROR);
				}
				else
				{
					// 隐藏
					addStuInCrsBtn.move(-500, 0);
					modifyStuInCrsBtn.move(-500, 0);
					deleteStuInCrsBtn.move(-500, 0);
					sortStuInCrsBtn.move(-500, 0);
					screenStuInCrsBtn.move(-500, 0);
					screenCancelBtn.move(-500, 0);
					backButton.move(-500, 0);

					// 更改标题
					modifyTitleText(&titleText, L"录入/修改成绩", 50);

					// 使表格不可变化
					allStuInCrsTable.canChange = false;

					// 获取当前行
					int selectedRow = allStuInCrsTable.getSelectedRow();
					vector<std::wstring> selectedData = allStuInCrsData[selectedRow];

					// 文本框默认内容
					snameBox.setText(selectedData[0].c_str());
					snumBox.setText(selectedData[1].c_str());
					scoreBox.setText(selectedData[2].c_str());

					// 显示
					//snameBox.move(10, 220);
					//snumBox.move(10, 300);
					scoreBox.move(10, 380);
					modifyOKButton.move(10, 460);
					cancelButton.move(10, 540);
				}

			}

			//在对应学生的课程页修改对应课程的信息
			if (modifyOKButton.mouseClick(msg))
			{
				//wchar_t sname[30];
				//int snum;
				double score;

				// 精确搜索课程节点
				int original_snum;
				wchar_t original_sname[30];
				int selectedRow = allStuInCrsTable.getSelectedRow(); // 获取当前行
				getTextInBox(original_sname, allStuInCrsData[selectedRow][0].c_str());
				getNumberInBox(99999999, &original_snum, allStuInCrsData[selectedRow][1].c_str());
				Spnode modifyingStu = searchStuInCrs(cplist, original_snum);

				// 判断输入格式
				if (
					//getTextInBox(sname, snameBox.text) &&
					//getNumberInBox(99999999, &snum, snumBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					//snum > 9999999 && score >= 0
					score >= 0
					)
				{

					// 修改
					modifyStuInCrs(cplist, modifyingStu, original_sname, original_snum, score);


					Node* StuNode = searchStu(&allStuList, original_sname, original_snum);
					wchar_t wch_cnum[10];
					swprintf(wch_cnum, 10, L"%d", cplist->cnum);
					int character = wcscmp(cplist->character, L"必修") ? 0 : 1;//必修是1
					Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cplist->cname);
					modifyCrsInStu(CrsNode, wch_cnum, cplist->cname, score, cplist->SchYear, character, cplist->credit, modifyingStu->GPA);

					// 保存
					saveCrs(cphead, CRS_FILE);
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"为课程:") + to_wstring(cplist->cnum) + L"修改学生:" + to_wstring(original_snum));

					// 使表格可变化
					allStuInCrsTable.canChange = true;

					// 刷新表格
					showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
					allStuInCrsTable.setData(allStuInCrsData);

					// 清除输入框内容
					//snameBox.clear();
					//snumBox.clear();
					scoreBox.clear();


					// 隐藏
					//snameBox.move(-500, 220);
					//snumBox.move(-500, 300);
					scoreBox.move(-500, 380);
					modifyOKButton.move(-500, 460);
					cancelButton.move(-500, 540);

					// 更改标题
					modifyTitleText(&titleText, cplist->cname, 50);

					// 显示
					addStuInCrsBtn.move(-50, 220);
					modifyStuInCrsBtn.move(-50, 300);
					deleteStuInCrsBtn.move(-50, 380);
					sortStuInCrsBtn.move(-50, 460);
					if (!screenOption)
						screenStuInCrsBtn.move(-50, 540);
					else
						screenCancelBtn.move(-50, 540);
					backButton.move(-50, 620);

				}
				// 输入错误
				else
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}

			}

			//在对应学生的课程页删除对应课程的信息
			if (deleteStuInCrsBtn.mouseClick(msg))
			{
				if (allStuInCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"请选择学生", L"错误!", MB_ICONERROR);
				}
				else
				{
					int result = MessageBox(GetHWnd(), L"确定删除这名学生吗?", L"删除学生", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{ // 点击确定

						wchar_t sname[30];
						int snum;
						int selectedRow = allStuInCrsTable.getSelectedRow(); // 获取当前行
						getTextInBox(sname, allStuInCrsData[selectedRow][0].c_str());
						getNumberInBox(99999999, &snum, allStuInCrsData[selectedRow][1].c_str());

						// 删除
						deleteStuInCrs(cplist, sname, snum);

						Node* StuNode = searchStu(&allStuList, sname, snum);
						wchar_t wch_cnum[10];
						swprintf(wch_cnum, 10, L"%d", cplist->cnum);
						int character = wcscmp(cplist->character, L"必修") ? 0 : 1;//必修是1
						Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cplist->cname);
						deleteCrsInStu(StuNode, CrsNode);

						// 保存
						saveCrs(cphead, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"为课程:") + to_wstring(cplist->cnum) + L"删除学生:" + to_wstring(snum));

						// 刷新表格
						showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
						allStuInCrsTable.setData(allStuInCrsData);
					}
				}
			}

			if (sortStuInCrsBtn.mouseClick(msg))//显示sort界面
			{

				// 隐藏
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"排序", 50);

				// 显示
				upsortBySnumBtn.move(10, 220);
				downsortBySnumBtn.move(10, 300);
				upsortByScoreBtn.move(10, 380);
				downsortByScoreBtn.move(10, 460);
				upsortByGPABtn.move(10, 540);
				downsortByGPABtn.move(10, 620);
				cancelButton.move(10, 700);
			}

			if (downsortBySnumBtn.mouseClick(msg))
				sortOption = 1;
			if (upsortBySnumBtn.mouseClick(msg))
				sortOption = 2;
			if (downsortByScoreBtn.mouseClick(msg))
				sortOption = 3;
			if (upsortByScoreBtn.mouseClick(msg))
				sortOption = 4;
			if (downsortByGPABtn.mouseClick(msg))
				sortOption = 5;
			if (upsortByGPABtn.mouseClick(msg))
				sortOption = 6;

			if (sortOption)
			{
				//链表排序
				sortStuInCrs(cplist, sortOption);

				// 刷新表格
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);


				// 隐藏
				cancelButton.move(-500, 620);
				upsortBySnumBtn.move(-500, 220);
				downsortBySnumBtn.move(-500, 300);
				upsortByScoreBtn.move(-500, 380);
				downsortByScoreBtn.move(-500, 460);
				upsortByGPABtn.move(-500, 540);
				downsortByGPABtn.move(-500, 620);

				// 更改标题
				modifyTitleText(&titleText, cplist->cname, 50);

				// 显示
				addStuInCrsBtn.move(-50, 220);
				modifyStuInCrsBtn.move(-50, 300);
				deleteStuInCrsBtn.move(-50, 380);
				sortStuInCrsBtn.move(-50, 460);
				if (!screenOption)
					screenStuInCrsBtn.move(-50, 540);
				else
					screenCancelBtn.move(-50, 540);
				backButton.move(-50, 620);

				sortOption = 0;
			}

			if (screenStuInCrsBtn.mouseClick(msg))
			{

				// 隐藏
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				backButton.move(-500, 0);

				// 更改标题
				modifyTitleText(&titleText, L"筛选", 50);

				// 显示
				screenByScoreBtn.move(10, 220);
				screenByGPABtn.move(10, 300);
				cancelButton.move(10, 380);
			}

			if (screenByScoreBtn.mouseClick(msg))
			{
				screenOption = 1;
				IsInScreen = true;
			}
			if (screenByGPABtn.mouseClick(msg))
			{
				screenOption = 2;
				IsInScreen = true;
			}

			if (IsInScreen)
			{
				// 隐藏
				screenByScoreBtn.move(-500, 0);
				screenByGPABtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// 更改标题
				wchar_t titletext[512];
				switch (screenOption)
				{
				case 1:
					wcscpy(titletext, L"按成绩筛选");
					break;
				case 2:
					wcscpy(titletext, L"按绩点筛选");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				// 显示
				minBox.move(10, 220);
				maxBox.move(10, 300);
				screenOKButton.move(10, 380);
				cancelButton.move(10, 460);
			}

			if (screenOKButton.mouseClick(msg))
			{
				double MAX;
				switch (screenOption)
				{
				case 1://按成绩筛选
					MAX = 100;
					break;
				case -1://按GPA
					MAX = 4;
					break;
				}
				if (
					getDoubleInBox(MAX, &screenMin, minBox.text) &&
					getDoubleInBox(MAX, &screenMax, maxBox.text) &&
					screenMin >= 0 && screenMax >= 0 && screenMin <= screenMax
					)
				{
					// 刷新表格
					showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
					allStuInCrsTable.setData(allStuInCrsData);

					// 清除输入框内容
					minBox.clear();
					maxBox.clear();


					// 隐藏
					minBox.move(-500, 0);
					maxBox.move(-500, 0);
					screenOKButton.move(-500, 0);
					cancelButton.move(-500, 0);

					// 更改标题
					modifyTitleText(&titleText, cplist->cname, 50);

					// 显示
					addStuInCrsBtn.move(-50, 220);
					modifyStuInCrsBtn.move(-50, 300);
					deleteStuInCrsBtn.move(-50, 380);
					sortStuInCrsBtn.move(-50, 460);
					screenCancelBtn.move(-50, 540);
					backButton.move(-50, 620);

					IsInScreen = false;
				}
				else// 输入错误
				{
					MessageBox(GetHWnd(), L"输入内容有误，请检查输入内容及格式", L"错误!", MB_ICONWARNING);
				}
			}

			if (screenCancelBtn.mouseClick(msg))
			{
				screenOption = 0;
				screenMin = 0;
				screenMax = 0;
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);

				screenCancelBtn.move(-500, 0);
				screenStuInCrsBtn.move(-50, 540);
			}

			if (backButton.mouseClick(msg))
			{
				//return;不能直接return
				return;
				allCrsUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}

			//表格鼠标滑动与点击
			allStuInCrsTable.onMouse(msg);

			// 文本框输入
			searchInputBox.onMessage(msg);
			snameBox.onMessage(msg);
			snumBox.onMessage(msg);
			scoreBox.onMessage(msg);
			minBox.onMessage(msg);
			maxBox.onMessage(msg);
		}

		//showxy(msg);

		FlushBatchDraw(); //批量绘图

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1)
		{
			Sleep(1);
		}

	}
	return;
}






