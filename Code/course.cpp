#include"course.h"
//之后GPA还得改改，他不是百分比换算
//添加名次，实现对名次的维护
//筛选、排序、特殊的查找（最高成绩、最低成绩），这些功能可以加上
//可以把int改成bool
//一般来说，会出现两个相同小数不相等的情况，但程序中却没有，不知道为什么，保持警惕
//筛选和排序也要按学分，之后加上
//要是还有时间，换成归并排序

void showAllCrs(const Cpnode cphead, vector<vector<wstring>>& data, const wchar_t* searchTerm, int op, int min, int max)
{
	Cpnode cplist = cphead->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(10, L""));

	//初始化表头
	data[0][0] = L"课程名称";
	data[0][1] = L"课程号";
	data[0][2] = L"课程性质";
	data[0][3] = L"学分";
	data[0][4] = L"学年";
	data[0][5] = L"总人数";
	data[0][6] = L"平均成绩";
	data[0][7] = L"平均绩点";
	data[0][8] = L"及格率";
	data[0][9] = L"优秀率";


	int row = 1;
	while (cplist != NULL)//遍历链表
	{
		// 检测是否有搜索词
		if (
			wcsstr(cplist->cname, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->cnum).c_str(), searchTerm) != NULL ||
			wcsstr(cplist->character, searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->credit).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->SchYear).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->headcount).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->averscore).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->averGPA).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->PassRate).c_str(), searchTerm) != NULL ||
			wcsstr(std::to_wstring(cplist->ExcelRate).c_str(), searchTerm) != NULL
			)
		{

			if (
				op == 0 ||
				(op == 1 && cplist->SchYear >= min && cplist->SchYear <= max) ||
				(op == 2 && cplist->headcount >= min && cplist->headcount <= max) ||
				(op == 3 && cplist->averscore >= min && cplist->averscore <= max) ||
				(op == 4 && cplist->averGPA >= min && cplist->averGPA <= max) ||
				(op == 5 && cplist->PassRate >= min && cplist->PassRate <= max) ||
				(op == 6 && cplist->ExcelRate >= min && cplist->ExcelRate <= max)
				)
			{
				data.push_back(vector<std::wstring>(10, L""));

				//每行的内容
				data[row][0] = cplist->cname;
				data[row][1] = std::to_wstring(cplist->cnum);
				data[row][2] = cplist->character;
				data[row][3] = std::to_wstring(cplist->credit);
				data[row][4] = std::to_wstring(cplist->SchYear);
				data[row][5] = std::to_wstring(cplist->headcount);
				data[row][6] = std::to_wstring(cplist->averscore);
				data[row][7] = std::to_wstring(cplist->averGPA);
				data[row][8] = std::to_wstring(cplist->PassRate);
				data[row][9] = std::to_wstring(cplist->ExcelRate);

				//保留小数
				data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
				data[row][6] = data[row][6].substr(0, data[row][6].find('.') + 3);
				data[row][7] = data[row][7].substr(0, data[row][7].find('.') + 5);
				data[row][8] = data[row][8].substr(0, data[row][8].find('.') + 3);
				data[row][9] = data[row][9].substr(0, data[row][9].find('.') + 3);

				row++; // 行数+1
			}
		}
		cplist = cplist->next; // 移向下一个节点
	}

	return;
}

void showAllStuInCrs(const Cpnode cplist, vector<vector<wstring>>& data, const wchar_t* searchTerm, int op, int min, int max) // 显示单个课程信息（包含该课程所有学生的成绩）
{
	Spnode splist = cplist->sphead->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(4, L"")); //增加一行(每行6列)

	//初始化表头
	data[0][0] = L"学生姓名";
	data[0][1] = L"学号";
	data[0][2] = L"学生成绩";
	data[0][3] = L"GPA";


	int row = 1;
	while (splist != NULL)//遍历链表w
	{
		// 检测是否有搜索词
		if (
			wcsstr(splist->sname, searchTerm) != NULL ||
			wcsstr(std::to_wstring(splist->snum).c_str(), searchTerm) != NULL||
			wcsstr(std::to_wstring(splist->score).c_str(), searchTerm) != NULL||
			wcsstr(std::to_wstring(splist->GPA).c_str(), searchTerm) != NULL
			)
		{
			if (
				op == 0 ||
				(op == 1 && splist->score >= min && splist->score <= max) ||
				(op == 2 && splist->GPA >= min && splist->GPA <= max)
				)
			{
				data.push_back(vector<std::wstring>(4, L"")); //增加一行(每行6列)
				//每行的内容
				data[row][0] = splist->sname;
				data[row][1] = std::to_wstring(splist->snum);
				data[row][2] = (splist->score == 0) ? L"" : to_wstring(splist->score);
				data[row][3] = (splist->score == 0) ? L"" : to_wstring(splist->GPA);

				// 保留小数
				data[row][2] = data[row][2].substr(0, data[row][2].find('.') + 2);
				data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);


				row++; // 行数+1
			}
		}

		splist = splist->next; // 移向下一个节点

	}

	return;
}

//void menu()
//{
//	Cpnode cphead = (Cpnode)malloc(sizeof(_Cnode));
//	cphead->next = NULL;
//	while (1)
//	{
//		fflush(stdin);
//		system("CLS");
//		showMenu(L"请选择功能", 8, L"退出", L"查看", L"添加课程", L"为某课程添加某学生成绩", L"修改课程", L"修改某个课程的某学生成绩", L"删除课程", L"删除某个课程的某学生成绩");
//		int op = getNumber(10);
//		switch (op)
//		{
//		case 1://退出
//			return;
//		case 2://查看
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			look(cplist);
//
//			break;
//		}
//		case 3://添加课程
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wchar_t Character[10];
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			wcout << L"课程性质："; wcin >> Character;
//			wcout << endl;
//
//			int flag = addCrs(cphead, Cname, Cnum, Character,0);////////////////////////////////////////////////
//			if (flag == -1)
//			{
//				wcout << L"已有此课程" << endl;
//				system("pause");
//				break;
//			}
//			else if (flag == 0)
//			{
//				wcout << L"内存分配失败" << endl;
//				system("pause");
//				exit(0);
//			}
//			else if (flag == 1)
//			{
//				wcout << L"添加成功" << endl;
//				system("pause");
//				break;
//			}
//		}
//		case 4://为某课程添加某学生成绩
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Sname[10];
//			int Snum;
//			double Score;
//			wcout << L"学生姓名："; wcin >> Sname;
//			wcout << endl;
//			wcout << L"学号："; wcin >> Snum;
//			wcout << endl;
//			wcout << L"成绩："; wcin >> Score;
//			wcout << endl;
//
//			int flag = addStuInCrs(cplist, Sname, Snum, Score);
//			if (flag == -1)
//			{
//				wcout << L"已有此人" << endl;
//				system("pause");
//				break;
//			}
//			else if (flag == 0)
//			{
//				wcout << L"内存分配失败" << endl;
//				system("pause");
//				exit(0);
//			}
//			else if (flag == 1)
//			{
//				wcout << L"添加成功" << endl;
//				system("pause");
//				break;
//			}
//		}
//		case 5://修改课程
//		{
//			system("CLS");
//			wchar_t original_Cname[10];
//			int original_Cnum;
//			wcout << L"原课程名称："; wcin >> original_Cname;
//			wcout << endl;
//			wcout << L"原课程号："; wcin >> original_Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, original_Cname, original_Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Cname[10];
//			int Cnum;
//			wchar_t Character[10];
//			wcout << L"原课程名称：" << cplist->cname;
//			wcout << endl;
//			wcout << L"新课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"原课程号：" << cplist->cnum;
//			wcout << endl;
//			wcout << L"新课程号："; wcin >> Cnum;
//			wcout << endl;
//			wcout << L"原课程性质：" << cplist->character;
//			wcout << endl;
//			wcout << L"新课程性质："; wcin >> Character;
//			wcout << endl;
//
//			//modifyCrs(cplist, Cname, Cnum, Character，0，0);
//
//			wcout << L"修改成功" << endl;
//			system("pause");
//			break;
//		}
//		case 6://修改某个课程的某学生成绩
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t original_Sname[10];
//			int original_Snum;
//			wcout << L"原学生姓名："; wcin >> original_Sname;
//			wcout << endl;
//			wcout << L"原学号："; wcin >> original_Snum;
//			wcout << endl;
//			Spnode splist = searchStuInCrs(cplist, original_Sname, original_Snum);
//			if (!splist)
//			{
//				wcout << L"查无此人" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Sname[10];
//			int Snum;
//			double Score;
//			wcout << L"原学生姓名：" << splist->sname;
//			wcout << endl;
//			wcout << L"新学生姓名："; wcin >> Sname;
//			wcout << endl;
//			wcout << L"原学号：" << splist->snum;
//			wcout << endl;
//			wcout << L"新学号："; wcin >> Snum;
//			wcout << endl;
//			wcout << L"原成绩：" << splist->score;
//			wcout << endl;
//			wcout << L"新成绩："; wcin >> Score;
//			wcout << endl;
//
//			modifyStuInCrs(cplist, splist, Sname, Snum, Score);
//
//			wcout << L"修改成功" << endl;
//			system("pause");
//			break;
//		}
//		case 7://删除课程
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			deleteCrs(cphead, Cname, Cnum);
//
//			wcout << L"删除成功" << endl;
//			system("pause");
//			break;
//		}
//		case 8://删除某个课程的某学生成绩
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"课程名称："; wcin >> Cname;
//			wcout << endl;
//			wcout << L"课程号："; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"查无此课程" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t sname[10];
//			int snum;
//			wcout << L"学生姓名："; wcin >> sname;
//			wcout << endl;
//			wcout << L"学号："; wcin >> snum;
//			wcout << endl;
//			Spnode splist = searchStuInCrs(cplist, sname, snum);
//			if (!splist)
//			{
//				wcout << L"查无此人" << endl;
//				system("pause");
//				break;
//			}
//
//			deleteStuInCrs(cplist, sname, snum);
//
//			wcout << L"删除成功" << endl;
//			system("pause");
//			break;
//		}
//		}
//	}
//}

int look(Cpnode cplist)
{
	system("CLS");
	wprintf(L"课程名称:%s\t课程号:%d\t课程性质:%s\n", cplist->cname, cplist->cnum, cplist->character);
	wprintf(L"总人数:%d\t总成绩:%.2f\t平均成绩:%.2f\t总GPA:%.3f\t平均GPA:%.3f\n", cplist->headcount, cplist->totscore, cplist->averscore, cplist->totGPA, cplist->averGPA);
	Spnode splist = cplist->sphead->next;
	while (splist)
	{
		wprintf(L"姓名:%s\t学号:%d\t成绩:%.2f\tGPA:%.3f\n", splist->sname, splist->snum, splist->score, splist->GPA);
		splist = splist->next;
	}
	system("pause");
	return 1;
}

double CalculGPA(double score)
{
	if (score >= 90 && score <= 100)
		return 4.0;
	else if (score >= 85 && score <90)
		return 3.7;
	else if (score >= 81 && score <85)
		return 3.3;
	else if (score >= 78 && score <81)
		return 3.0;
	else if (score >= 75 && score <78)
		return 2.7;
	else if (score >= 72 && score <75)
		return 2.3;
	else if (score >= 68 && score <72)
		return 2.0;
	else if (score >= 64 && score <68)
		return 1.5;
	else if (score >= 60 && score <64)
		return 1.0;
	else
		return 0;

}

int CalculNumOfCrs(int op)//计算课程数
{
	static int NumOfCrs;
	switch (op)
	{
	case 1://添加
		NumOfCrs++;
		break;
	case 2://删除
		NumOfCrs--;
		break;
	case 3://查看课程数
		return NumOfCrs;
	}
}

int addCrs(Cpnode cphead, const wchar_t* cname, int cnum, const wchar_t* character, double credit, int SchYear) // 添加课程
{
	if (searchCrs(cphead, cnum, SchYear))
		return 0;
	Cpnode cplist = (Cpnode)malloc(sizeof(_Cnode));
	if (cplist == NULL)
	{
		return -1;
	}
	cplist->sphead = (Spnode)malloc(sizeof(Snode));
	if (cplist->sphead == NULL)
	{
		return -1;
	}

	//初始化
	cplist->sphead->next = NULL;
	cplist->headcount = 0;
	cplist->totGPA = 0;
	cplist->totscore = 0;
	cplist->averGPA = 0;
	cplist->averscore = 0;
	cplist->PassNum = 0;
	cplist->PassRate = 0;
	cplist->ExcelNum = 0;
	cplist->ExcelRate = 0;

	//头插
	cplist->next = cphead->next;
	cphead->next = cplist;


	wcscpy(cplist->cname, cname);
	cplist->cnum = cnum;
	wcscpy(cplist->character, character);
	cplist->credit = credit;
	cplist->SchYear = SchYear;
	CalculNumOfCrs(1);
	return 1;
}

int addStuInCrs(Cpnode cplist, const wchar_t* sname, int snum, double score)// 为某课程添加某学生成绩
{
	if (searchStuInCrs(cplist, snum))
		return 0;
	Spnode splist = (Spnode)malloc(sizeof(Snode));
	if (!splist)
	{
		return -1;
	}
	splist->next = cplist->sphead->next;
	cplist->sphead->next = splist;

	wcscpy(splist->sname, sname);
	splist->snum = snum;
	splist->score = score;

	splist->GPA = CalculGPA(score);

	cplist->headcount++;
	cplist->totscore += splist->score;
	cplist->totGPA += splist->GPA;
	if (splist->score >= 90)
	{
		cplist->ExcelNum++;
		cplist->ExcelRate = round(double(cplist->ExcelNum) / cplist->headcount * 10000) / 10000;
	}
	if (splist->score >= 60)
	{
		cplist->PassNum++;
		cplist->PassRate = round(double(cplist->PassNum) / cplist->headcount * 10000) / 10000;
	}
	cplist->averscore = round(cplist->totscore / cplist->headcount * 1000) / 1000;
	cplist->averGPA = round(cplist->totGPA / cplist->headcount * 1000) / 1000;

	return 1;
}

int modifyCrs(Cpnode cplist, const wchar_t* Cname, int Cnum, const wchar_t* Character, double credit, int SchYear) // 修改课程信息
{
	wcscpy(cplist->cname, Cname);
	cplist->cnum = Cnum;
	wcscpy(cplist->character, Character);
	cplist->credit = credit;
	cplist->SchYear = SchYear;
	return 1;
}

int modifyStuInCrs(Cpnode cplist, Spnode splist, const wchar_t* sname, int snum, double score) // 修改某个课程的某学生信息
{
	cplist->totscore -= splist->score;
	cplist->totGPA -= splist->GPA;
	if (splist->score >= 90)
		cplist->ExcelNum--;
	if (splist->score >= 60)
		cplist->PassNum--;

	wcscpy(splist->sname, sname);
	splist->snum = snum;
	splist->score = score;
	splist->GPA = CalculGPA(score);

	cplist->totscore += splist->score;
	cplist->totGPA += splist->GPA;
	if (splist->score >= 90)
		cplist->ExcelNum++;
	if (splist->score >= 60)
		cplist->PassNum++;
	cplist->ExcelRate = round(double(cplist->ExcelNum) / cplist->headcount * 10000) / 10000;
	cplist->PassRate = round(double(cplist->PassNum) / cplist->headcount * 10000) / 10000;
	cplist->averscore = round(cplist->totscore / cplist->headcount * 1000) / 1000;
	cplist->averGPA = round(cplist->totGPA / cplist->headcount * 1000) / 1000;

	return 1;
}

int deleteCrs(Cpnode cphead, wchar_t* cname, int cnum) // 删除课程
{
	Cpnode pre_cplist = cphead;
	Cpnode cplist = pre_cplist->next;

	while (cplist)
	{
		if (wcscmp(cplist->cname, cname) == 0)
			if (cplist->cnum == cnum)
				break;
		pre_cplist = pre_cplist->next;
		cplist = cplist->next;
	}

	//其实这里可以不用了
	//if (!cplist)
	//	return 0;

	Spnode sphead = cplist->sphead;
	Spnode splist = sphead->next;
	while (splist)
	{
		sphead->next = splist->next;
		free(splist);
		splist = sphead->next;
	}
	free(sphead);

	pre_cplist->next = cplist->next;
	free(cplist);

	CalculNumOfCrs(2);
	return 1;
}

int deleteStuInCrs(Cpnode cplist, const wchar_t* sname, int snum) // 删除某个课程的某学生成绩
{
	Spnode pre_splist = cplist->sphead;
	Spnode splist = pre_splist->next;
	while (splist)
	{
		if (wcscmp(splist->sname, sname) == 0)
			if (splist->snum == snum)
				break;
		pre_splist = pre_splist->next;
		splist = splist->next;
	}
	//其实这里可以不用了
	//if (!splist)
	//	return 0;

	cplist->headcount--;
	cplist->totscore -= splist->score;
	cplist->totGPA -= splist->GPA;
	if (splist->score >= 90)
	{
		cplist->ExcelNum--;
		cplist->ExcelRate = round(double(cplist->ExcelNum) / cplist->headcount * 10000) / 10000;
	}
	if (splist->score >= 60)
	{
		cplist->PassNum--;
		cplist->PassRate = round(double(cplist->PassNum) / cplist->headcount * 10000) / 10000;
	}
	if (cplist->headcount)
	{
		cplist->averscore = round(cplist->totscore / cplist->headcount * 1000) / 1000;
		cplist->averGPA = round(cplist->totGPA / cplist->headcount * 1000) / 1000;
	}
	else
	{
		cplist->averscore = 0;
		cplist->averGPA = 0;
	}

	pre_splist->next = splist->next;
	free(splist);

	return 1;
}

//bool cmp_sortStuInCrs(Spnode splist, int op)
//{
//	switch (op)
//	{
//	case 1://按学号降序
//		return splist->snum > splist->next->snum;
//	case 2://按学号升序
//		return splist->snum < splist->next->snum;
//	case 3://按成绩降序
//		return splist->score > splist->next->score;
//	case 4://按成绩升序
//		return splist->score < splist->next->score;
//	case 5://按GPA降序
//		return splist->GPA > splist->next->GPA;
//	case 6://按GPA升序
//		return splist->GPA < splist->next->GPA;
//	}
//}
//void sortStuInCrs(Cpnode cplist, int op)
//{
//	bool flag = true;
//	while (flag)
//	{
//		flag = false;
//		Spnode pre_splist = cplist->sphead;
//		Spnode splist = cplist->sphead->next;
//		if (!splist)
//			return;
//		while (splist->next)
//		{
//			if (cmp_sortStuInCrs(splist, op))
//			{
//				Spnode tmp = splist->next;
//				splist->next = splist->next->next;
//				tmp->next = splist;
//				pre_splist->next = tmp;
//				pre_splist = pre_splist->next;//掉了
//				flag = true;
//				continue;
//			}
//			pre_splist = pre_splist->next;
//			splist = splist->next;
//		}
//	}
//	return;
//}


//辅助函数，就不包含到头文件里了
bool cmp_sortStuInCrs(Spnode splist1, Spnode splist2, int op)
{
	switch (op)
	{
	case 1://按学号降序
		return splist1->snum > splist2->snum;
	case 2://按学号升序
		return splist1->snum < splist2->snum;
	case 3://按成绩降序
		return splist1->score > splist2->score;
	case 4://按成绩升序
		return splist1->score < splist2->score;
	case 5://按GPA降序
		return splist1->GPA > splist2->GPA;
	case 6://按GPA升序
		return splist1->GPA < splist2->GPA;
	}
}
// 分割链表函数，返回第二部分链表的头指针
Spnode split_sortStuInCrs(Spnode splist, int size)
{
	Spnode pre_mid = NULL;//中间节点的前驱节点，用来断开
	while (splist && size--)
	{
		pre_mid = splist;
		splist = splist->next;
	}
	if (pre_mid)
		pre_mid->next = NULL;//断开
	return splist;
}
// 合并两个链表并返回合并后的链表的尾部
Spnode merge_sortStuInCrs(Spnode splist1, Spnode splist2, Spnode ptail, int op)
{
	Spnode cur = ptail;
	while (splist1 && splist2)
	{
		if (cmp_sortStuInCrs(splist1, splist2, op))
		{
			cur->next = splist1;
			splist1 = splist1->next;
		}
		else
		{
			cur->next = splist2;
			splist2 = splist2->next;
		}
		cur = cur->next;
	}
	cur->next = (splist1) ? splist1 : splist2;
	while (cur->next) cur = cur->next;
	return cur;
}
// 使用迭代的方式实现归并排序
void sortStuInCrs(Cpnode cplist, int op)
{
	if (!cplist->sphead || !cplist->sphead->next)
		return;
	Spnode left;
	Spnode right;
	Spnode splist;
	Spnode sptail;
	for (int size = 1; size < cplist->headcount; size *= 2)
	{
		splist = cplist->sphead->next;
		sptail = cplist->sphead;
		while (splist)
		{
			left = splist;
			right = split_sortStuInCrs(left, size);  // 分割 left
			splist = split_sortStuInCrs(right, size);  // 分割 right
			sptail = merge_sortStuInCrs(left, right, sptail, op); // 合并 left 和 right
		}
	}
}


//void sortCrs(Cpnode cphead, int op)
//{
//	bool flag = true;
//	while (flag)
//	{
//		flag = false;
//		Cpnode pre_cplist = cphead;
//		Cpnode cplist = cphead->next;
//		if (!cplist)
//			return;
//		while (cplist->next)
//		{
//			if (cmp_sortCrs(cplist, op))
//			{
//				Cpnode tmp = cplist->next;
//				cplist->next = cplist->next->next;
//				tmp->next = cplist;
//				pre_cplist->next = tmp;
//				pre_cplist = pre_cplist->next;//掉了
//				flag = true;
//				continue;
//			}
//			pre_cplist = pre_cplist->next;
//			cplist = cplist->next;
//		}
//	}
//	return;
//	return;
//}

//辅助函数，就不包含到头文件里了
bool cmp_sortCrs(Cpnode cplist1, Cpnode cplist2, int op)
{
	switch (op)
	{
	case 1://按课程号升序
		return cplist1->cnum < cplist2->cnum;
	case 2://按课程号降序
		return cplist1->cnum > cplist2->cnum;
	case 3://按学年升序
		return cplist1->SchYear < cplist2->SchYear;
	case 4://按学年降序
		return cplist1->SchYear > cplist2->SchYear;
	case 5://按总人数升序
		return cplist1->headcount < cplist2->headcount;
	case 6://按总人数降序
		return cplist1->headcount > cplist2->headcount;
	case 7://按平均成绩升序
		return cplist1->averscore < cplist2->averscore;
	case 8://按平均成绩降序
		return cplist1->averscore > cplist2->averscore;
	case 9://按平均绩点升序
		return cplist1->averGPA < cplist2->averGPA;
	case 10://按平均绩点降序
		return cplist1->averGPA > cplist2->averGPA;
	case 11://按及格率升序
		return cplist1->PassRate < cplist2->PassRate;
	case 12://按及格率降序
		return cplist1->PassRate > cplist2->PassRate;
	case 13://按优秀率升序
		return cplist1->ExcelRate < cplist2->ExcelRate;
	case 14://按优秀率降序
		return cplist1->ExcelRate > cplist2->ExcelRate;
	}
}
// 分割链表函数，返回第二部分链表的头指针
Cpnode split_sortCrs(Cpnode cplist, int size)
{
	Cpnode pre_mid = NULL;//中间节点的前驱节点，用来断开
	while (cplist && size--)
	{
		pre_mid = cplist;
		cplist = cplist->next;
	}
	if (pre_mid)
		pre_mid->next = NULL;//断开
	return cplist;
}
// 合并两个链表并返回合并后的链表的尾部
Cpnode merge_sortCrs(Cpnode cplist1, Cpnode cplist2, Cpnode ptail, int op)
{
	Cpnode cur = ptail;
	while (cplist1 && cplist2)
	{
		if (cmp_sortCrs(cplist1, cplist2, op))
		{
			cur->next = cplist1;
			cplist1 = cplist1->next;
		}
		else
		{
			cur->next = cplist2;
			cplist2 = cplist2->next;
		}
		cur = cur->next;
	}
	cur->next = (cplist1) ? cplist1 : cplist2;
	while (cur->next) cur = cur->next;
	return cur;
}
// 使用迭代的方式实现归并排序
void sortCrs(Cpnode cphead, int op)
{
	if (!cphead || !cphead->next)
		return;
	Cpnode left;
	Cpnode right;
	Cpnode cplist;
	Cpnode cptail;
	int NumOfCrs = CalculNumOfCrs(3);
	for (int size = 1; size < NumOfCrs; size *= 2)
	{
		cplist = cphead->next;
		cptail = cphead;
		while (cplist)
		{
			left = cplist;
			right = split_sortCrs(left, size);  // 分割 left
			cplist = split_sortCrs(right, size);  // 分割 right
			cptail = merge_sortCrs(left, right, cptail, op); // 合并 left 和 right
		}
	}
}




Cpnode searchCrs(Cpnode cphead, int Cnum, int SchYear)// 在课程链表中搜索课程
{
	Cpnode cplist = cphead->next;
	while (cplist)
	{
		if (Cnum == cplist->cnum && SchYear == cplist->SchYear)
			break;
		cplist = cplist->next;
	}
	if (!cplist)
	{
		return NULL;
	}
	return cplist;
}

Spnode searchStuInCrs(Cpnode cplist, int Snum) // 在单个课程中搜索其下的学生
{
	Spnode splist = cplist->sphead->next;
	while (splist)
	{
		if (Snum == splist->snum)
			break;
		splist = splist->next;
	}
	if (!splist)
	{
		return NULL;
	}
	return splist;
}


