#include"course.h"
//֮��GPA���øĸģ������ǰٷֱȻ���
//������Σ�ʵ�ֶ����ε�ά��
//ɸѡ����������Ĳ��ң���߳ɼ�����ͳɼ�������Щ���ܿ��Լ���
//���԰�int�ĳ�bool
//һ����˵�������������ͬС������ȵ��������������ȴû�У���֪��Ϊʲô�����־���
//ɸѡ������ҲҪ��ѧ�֣�֮�����
//Ҫ�ǻ���ʱ�䣬���ɹ鲢����

void showAllCrs(const Cpnode cphead, vector<vector<wstring>>& data, const wchar_t* searchTerm, int op, int min, int max)
{
	Cpnode cplist = cphead->next; //�ӵ�һ�������ݽڵ㿪ʼ
	data.clear(); // �������
	data.push_back(vector<wstring>(10, L""));

	//��ʼ����ͷ
	data[0][0] = L"�γ�����";
	data[0][1] = L"�γ̺�";
	data[0][2] = L"�γ�����";
	data[0][3] = L"ѧ��";
	data[0][4] = L"ѧ��";
	data[0][5] = L"������";
	data[0][6] = L"ƽ���ɼ�";
	data[0][7] = L"ƽ������";
	data[0][8] = L"������";
	data[0][9] = L"������";


	int row = 1;
	while (cplist != NULL)//��������
	{
		// ����Ƿ���������
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

				//ÿ�е�����
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

				//����С��
				data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);
				data[row][6] = data[row][6].substr(0, data[row][6].find('.') + 3);
				data[row][7] = data[row][7].substr(0, data[row][7].find('.') + 5);
				data[row][8] = data[row][8].substr(0, data[row][8].find('.') + 3);
				data[row][9] = data[row][9].substr(0, data[row][9].find('.') + 3);

				row++; // ����+1
			}
		}
		cplist = cplist->next; // ������һ���ڵ�
	}

	return;
}

void showAllStuInCrs(const Cpnode cplist, vector<vector<wstring>>& data, const wchar_t* searchTerm, int op, int min, int max) // ��ʾ�����γ���Ϣ�������ÿγ�����ѧ���ĳɼ���
{
	Spnode splist = cplist->sphead->next; //�ӵ�һ�������ݽڵ㿪ʼ
	data.clear(); // �������
	data.push_back(vector<wstring>(4, L"")); //����һ��(ÿ��6��)

	//��ʼ����ͷ
	data[0][0] = L"ѧ������";
	data[0][1] = L"ѧ��";
	data[0][2] = L"ѧ���ɼ�";
	data[0][3] = L"GPA";


	int row = 1;
	while (splist != NULL)//��������w
	{
		// ����Ƿ���������
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
				data.push_back(vector<std::wstring>(4, L"")); //����һ��(ÿ��6��)
				//ÿ�е�����
				data[row][0] = splist->sname;
				data[row][1] = std::to_wstring(splist->snum);
				data[row][2] = (splist->score == 0) ? L"" : to_wstring(splist->score);
				data[row][3] = (splist->score == 0) ? L"" : to_wstring(splist->GPA);

				// ����С��
				data[row][2] = data[row][2].substr(0, data[row][2].find('.') + 2);
				data[row][3] = data[row][3].substr(0, data[row][3].find('.') + 2);


				row++; // ����+1
			}
		}

		splist = splist->next; // ������һ���ڵ�

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
//		showMenu(L"��ѡ����", 8, L"�˳�", L"�鿴", L"��ӿγ�", L"Ϊĳ�γ����ĳѧ���ɼ�", L"�޸Ŀγ�", L"�޸�ĳ���γ̵�ĳѧ���ɼ�", L"ɾ���γ�", L"ɾ��ĳ���γ̵�ĳѧ���ɼ�");
//		int op = getNumber(10);
//		switch (op)
//		{
//		case 1://�˳�
//			return;
//		case 2://�鿴
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			look(cplist);
//
//			break;
//		}
//		case 3://��ӿγ�
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wchar_t Character[10];
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			wcout << L"�γ����ʣ�"; wcin >> Character;
//			wcout << endl;
//
//			int flag = addCrs(cphead, Cname, Cnum, Character,0);////////////////////////////////////////////////
//			if (flag == -1)
//			{
//				wcout << L"���д˿γ�" << endl;
//				system("pause");
//				break;
//			}
//			else if (flag == 0)
//			{
//				wcout << L"�ڴ����ʧ��" << endl;
//				system("pause");
//				exit(0);
//			}
//			else if (flag == 1)
//			{
//				wcout << L"��ӳɹ�" << endl;
//				system("pause");
//				break;
//			}
//		}
//		case 4://Ϊĳ�γ����ĳѧ���ɼ�
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Sname[10];
//			int Snum;
//			double Score;
//			wcout << L"ѧ��������"; wcin >> Sname;
//			wcout << endl;
//			wcout << L"ѧ�ţ�"; wcin >> Snum;
//			wcout << endl;
//			wcout << L"�ɼ���"; wcin >> Score;
//			wcout << endl;
//
//			int flag = addStuInCrs(cplist, Sname, Snum, Score);
//			if (flag == -1)
//			{
//				wcout << L"���д���" << endl;
//				system("pause");
//				break;
//			}
//			else if (flag == 0)
//			{
//				wcout << L"�ڴ����ʧ��" << endl;
//				system("pause");
//				exit(0);
//			}
//			else if (flag == 1)
//			{
//				wcout << L"��ӳɹ�" << endl;
//				system("pause");
//				break;
//			}
//		}
//		case 5://�޸Ŀγ�
//		{
//			system("CLS");
//			wchar_t original_Cname[10];
//			int original_Cnum;
//			wcout << L"ԭ�γ����ƣ�"; wcin >> original_Cname;
//			wcout << endl;
//			wcout << L"ԭ�γ̺ţ�"; wcin >> original_Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, original_Cname, original_Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Cname[10];
//			int Cnum;
//			wchar_t Character[10];
//			wcout << L"ԭ�γ����ƣ�" << cplist->cname;
//			wcout << endl;
//			wcout << L"�¿γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"ԭ�γ̺ţ�" << cplist->cnum;
//			wcout << endl;
//			wcout << L"�¿γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			wcout << L"ԭ�γ����ʣ�" << cplist->character;
//			wcout << endl;
//			wcout << L"�¿γ����ʣ�"; wcin >> Character;
//			wcout << endl;
//
//			//modifyCrs(cplist, Cname, Cnum, Character��0��0);
//
//			wcout << L"�޸ĳɹ�" << endl;
//			system("pause");
//			break;
//		}
//		case 6://�޸�ĳ���γ̵�ĳѧ���ɼ�
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t original_Sname[10];
//			int original_Snum;
//			wcout << L"ԭѧ��������"; wcin >> original_Sname;
//			wcout << endl;
//			wcout << L"ԭѧ�ţ�"; wcin >> original_Snum;
//			wcout << endl;
//			Spnode splist = searchStuInCrs(cplist, original_Sname, original_Snum);
//			if (!splist)
//			{
//				wcout << L"���޴���" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t Sname[10];
//			int Snum;
//			double Score;
//			wcout << L"ԭѧ��������" << splist->sname;
//			wcout << endl;
//			wcout << L"��ѧ��������"; wcin >> Sname;
//			wcout << endl;
//			wcout << L"ԭѧ�ţ�" << splist->snum;
//			wcout << endl;
//			wcout << L"��ѧ�ţ�"; wcin >> Snum;
//			wcout << endl;
//			wcout << L"ԭ�ɼ���" << splist->score;
//			wcout << endl;
//			wcout << L"�³ɼ���"; wcin >> Score;
//			wcout << endl;
//
//			modifyStuInCrs(cplist, splist, Sname, Snum, Score);
//
//			wcout << L"�޸ĳɹ�" << endl;
//			system("pause");
//			break;
//		}
//		case 7://ɾ���γ�
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			deleteCrs(cphead, Cname, Cnum);
//
//			wcout << L"ɾ���ɹ�" << endl;
//			system("pause");
//			break;
//		}
//		case 8://ɾ��ĳ���γ̵�ĳѧ���ɼ�
//		{
//			system("CLS");
//			wchar_t Cname[10];
//			int Cnum;
//			wcout << L"�γ����ƣ�"; wcin >> Cname;
//			wcout << endl;
//			wcout << L"�γ̺ţ�"; wcin >> Cnum;
//			wcout << endl;
//			Cpnode cplist = searchCrs(cphead, Cname, Cnum);
//			if (!cplist)
//			{
//				wcout << L"���޴˿γ�" << endl;
//				system("pause");
//				break;
//			}
//
//			wchar_t sname[10];
//			int snum;
//			wcout << L"ѧ��������"; wcin >> sname;
//			wcout << endl;
//			wcout << L"ѧ�ţ�"; wcin >> snum;
//			wcout << endl;
//			Spnode splist = searchStuInCrs(cplist, sname, snum);
//			if (!splist)
//			{
//				wcout << L"���޴���" << endl;
//				system("pause");
//				break;
//			}
//
//			deleteStuInCrs(cplist, sname, snum);
//
//			wcout << L"ɾ���ɹ�" << endl;
//			system("pause");
//			break;
//		}
//		}
//	}
//}

int look(Cpnode cplist)
{
	system("CLS");
	wprintf(L"�γ�����:%s\t�γ̺�:%d\t�γ�����:%s\n", cplist->cname, cplist->cnum, cplist->character);
	wprintf(L"������:%d\t�ܳɼ�:%.2f\tƽ���ɼ�:%.2f\t��GPA:%.3f\tƽ��GPA:%.3f\n", cplist->headcount, cplist->totscore, cplist->averscore, cplist->totGPA, cplist->averGPA);
	Spnode splist = cplist->sphead->next;
	while (splist)
	{
		wprintf(L"����:%s\tѧ��:%d\t�ɼ�:%.2f\tGPA:%.3f\n", splist->sname, splist->snum, splist->score, splist->GPA);
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

int CalculNumOfCrs(int op)//����γ���
{
	static int NumOfCrs;
	switch (op)
	{
	case 1://���
		NumOfCrs++;
		break;
	case 2://ɾ��
		NumOfCrs--;
		break;
	case 3://�鿴�γ���
		return NumOfCrs;
	}
}

int addCrs(Cpnode cphead, const wchar_t* cname, int cnum, const wchar_t* character, double credit, int SchYear) // ��ӿγ�
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

	//��ʼ��
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

	//ͷ��
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

int addStuInCrs(Cpnode cplist, const wchar_t* sname, int snum, double score)// Ϊĳ�γ����ĳѧ���ɼ�
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

int modifyCrs(Cpnode cplist, const wchar_t* Cname, int Cnum, const wchar_t* Character, double credit, int SchYear) // �޸Ŀγ���Ϣ
{
	wcscpy(cplist->cname, Cname);
	cplist->cnum = Cnum;
	wcscpy(cplist->character, Character);
	cplist->credit = credit;
	cplist->SchYear = SchYear;
	return 1;
}

int modifyStuInCrs(Cpnode cplist, Spnode splist, const wchar_t* sname, int snum, double score) // �޸�ĳ���γ̵�ĳѧ����Ϣ
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

int deleteCrs(Cpnode cphead, wchar_t* cname, int cnum) // ɾ���γ�
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

	//��ʵ������Բ�����
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

int deleteStuInCrs(Cpnode cplist, const wchar_t* sname, int snum) // ɾ��ĳ���γ̵�ĳѧ���ɼ�
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
	//��ʵ������Բ�����
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
//	case 1://��ѧ�Ž���
//		return splist->snum > splist->next->snum;
//	case 2://��ѧ������
//		return splist->snum < splist->next->snum;
//	case 3://���ɼ�����
//		return splist->score > splist->next->score;
//	case 4://���ɼ�����
//		return splist->score < splist->next->score;
//	case 5://��GPA����
//		return splist->GPA > splist->next->GPA;
//	case 6://��GPA����
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
//				pre_splist = pre_splist->next;//����
//				flag = true;
//				continue;
//			}
//			pre_splist = pre_splist->next;
//			splist = splist->next;
//		}
//	}
//	return;
//}


//�����������Ͳ�������ͷ�ļ�����
bool cmp_sortStuInCrs(Spnode splist1, Spnode splist2, int op)
{
	switch (op)
	{
	case 1://��ѧ�Ž���
		return splist1->snum > splist2->snum;
	case 2://��ѧ������
		return splist1->snum < splist2->snum;
	case 3://���ɼ�����
		return splist1->score > splist2->score;
	case 4://���ɼ�����
		return splist1->score < splist2->score;
	case 5://��GPA����
		return splist1->GPA > splist2->GPA;
	case 6://��GPA����
		return splist1->GPA < splist2->GPA;
	}
}
// �ָ������������صڶ����������ͷָ��
Spnode split_sortStuInCrs(Spnode splist, int size)
{
	Spnode pre_mid = NULL;//�м�ڵ��ǰ���ڵ㣬�����Ͽ�
	while (splist && size--)
	{
		pre_mid = splist;
		splist = splist->next;
	}
	if (pre_mid)
		pre_mid->next = NULL;//�Ͽ�
	return splist;
}
// �ϲ������������غϲ���������β��
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
// ʹ�õ����ķ�ʽʵ�ֹ鲢����
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
			right = split_sortStuInCrs(left, size);  // �ָ� left
			splist = split_sortStuInCrs(right, size);  // �ָ� right
			sptail = merge_sortStuInCrs(left, right, sptail, op); // �ϲ� left �� right
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
//				pre_cplist = pre_cplist->next;//����
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

//�����������Ͳ�������ͷ�ļ�����
bool cmp_sortCrs(Cpnode cplist1, Cpnode cplist2, int op)
{
	switch (op)
	{
	case 1://���γ̺�����
		return cplist1->cnum < cplist2->cnum;
	case 2://���γ̺Ž���
		return cplist1->cnum > cplist2->cnum;
	case 3://��ѧ������
		return cplist1->SchYear < cplist2->SchYear;
	case 4://��ѧ�꽵��
		return cplist1->SchYear > cplist2->SchYear;
	case 5://������������
		return cplist1->headcount < cplist2->headcount;
	case 6://������������
		return cplist1->headcount > cplist2->headcount;
	case 7://��ƽ���ɼ�����
		return cplist1->averscore < cplist2->averscore;
	case 8://��ƽ���ɼ�����
		return cplist1->averscore > cplist2->averscore;
	case 9://��ƽ����������
		return cplist1->averGPA < cplist2->averGPA;
	case 10://��ƽ�����㽵��
		return cplist1->averGPA > cplist2->averGPA;
	case 11://������������
		return cplist1->PassRate < cplist2->PassRate;
	case 12://�������ʽ���
		return cplist1->PassRate > cplist2->PassRate;
	case 13://������������
		return cplist1->ExcelRate < cplist2->ExcelRate;
	case 14://�������ʽ���
		return cplist1->ExcelRate > cplist2->ExcelRate;
	}
}
// �ָ������������صڶ����������ͷָ��
Cpnode split_sortCrs(Cpnode cplist, int size)
{
	Cpnode pre_mid = NULL;//�м�ڵ��ǰ���ڵ㣬�����Ͽ�
	while (cplist && size--)
	{
		pre_mid = cplist;
		cplist = cplist->next;
	}
	if (pre_mid)
		pre_mid->next = NULL;//�Ͽ�
	return cplist;
}
// �ϲ������������غϲ���������β��
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
// ʹ�õ����ķ�ʽʵ�ֹ鲢����
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
			right = split_sortCrs(left, size);  // �ָ� left
			cplist = split_sortCrs(right, size);  // �ָ� right
			cptail = merge_sortCrs(left, right, cptail, op); // �ϲ� left �� right
		}
	}
}




Cpnode searchCrs(Cpnode cphead, int Cnum, int SchYear)// �ڿγ������������γ�
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

Spnode searchStuInCrs(Cpnode cplist, int Snum) // �ڵ����γ����������µ�ѧ��
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


