#pragma warning(disable:4996)

#include"quality.h"


bool showAllTch(const List TchList, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pCurrent = TchList->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(4, L"")); //增加一行(每行4列)

	//初始化表头
	data[0][0] = L"工号";
	data[0][1] = L"姓名";
	data[0][2] = L"性别";
	data[0][3] = L"学院";
	
	int row = 1;
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(4, L"")); //增加一行(每行4列)

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = (pCurrent->item.data.gender) ? L"男" : L"女";
			data[row][3] = pCurrent->item.data.college;


			row++; // 行数+1
		}

		pCurrent = pCurrent->next; // 移向下一个节点

	}

	return true;

}

bool ShowStu_Password(const List Sp_List, vector<vector<wstring>>& data, const wchar_t* searchTerm){
	List pCurrent = Sp_List->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(3, L"")); //增加一行(每行3列)

	//初始化表头
	data[0][0] = L"学号";
	data[0][1] = L"姓名";
	data[0][2] = L"密码";


	int row = 1;
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(3, L"")); //增加一行(每行3列)

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = pCurrent->item.data.password;


			row++; // 行数+1
		}

		pCurrent = pCurrent->next; // 移向下一个节点

	}

	return true;
}

bool ShowTch_Password(const List Tp_List, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pCurrent = Tp_List->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(3, L"")); //增加一行(每行3列)

	//初始化表头
	data[0][0] = L"工号";
	data[0][1] = L"姓名";
	data[0][2] = L"密码";


	int row = 1;
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(3, L"")); //增加一行(每行3列)

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = pCurrent->item.data.password;


			row++; // 行数+1
		}

		pCurrent = pCurrent->next; // 移向下一个节点

	}
	return true;
}

bool ShowAllStu_with_quality(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pStu_Current = StuList->next;
	Rnode* pR_Current;
	Cnode* pC_Current;//考虑学生主链表以及素质类链表均有哨兵节点

	data.clear(); // 清空数组
	data.push_back(vector<wstring>(6, L"")); //增加一行(每行6列)

	//初始化表头
	data[0][0] = L"学号";
	data[0][1] = L"姓名";
	data[0][2] = L"性别";
	data[0][3] = L"年级";
	data[0][4] = L"学院";
	data[0][5] = L"专业";


	int row = 1;

	while (pStu_Current != NULL) { //遍历链表
		
		pR_Current = pStu_Current->item.rlist->rnext;
		pC_Current = pStu_Current->item.clist->cnext;

		if (((pR_Current != NULL) || (pC_Current != NULL)) && (wcsstr(std::to_wstring(pStu_Current->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pStu_Current->item.data.name, searchTerm) != NULL
			|| wcsstr(std::to_wstring(pStu_Current->item.data.grade).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pStu_Current->item.data.college, searchTerm) != NULL
			|| wcsstr(pStu_Current->item.data.major, searchTerm) != NULL
			)) {

			data.push_back(vector<std::wstring>(6, L"")); //增加一行(每行6列)

			//每行的内容
			data[row][0] = std::to_wstring(pStu_Current->item.data.ID); //数字转为字符串
			data[row][1] = pStu_Current->item.data.name;
			data[row][2] = (pStu_Current->item.data.gender) ? L"男" : L"女";
			data[row][3] = std::to_wstring(pStu_Current->item.data.grade); //数字转为字符串
			data[row][4] = pStu_Current->item.data.college;
			data[row][5] = pStu_Current->item.data.major;

			row++; // 行数+1
		}

		pStu_Current = pStu_Current->next; // 移向下一个节点

	}

	return true;

}

bool ShowStu_Research(const Node* Stu, vector<vector<wstring>>& data) {

	Rnode* pR_Current = Stu->item.rlist->rnext;

	data.clear(); // 清空数组
	data.push_back(vector<wstring>(8, L"")); //增加一行(每行8列)

	//初始化表头
	data[0][0] = L"论文名称";
	data[0][1] = L"期刊名";
	data[0][2] = L"作者情况";
	data[0][3] = L"时间";
	data[0][4] = L"卷数";
	data[0][5] = L"刊号";
	data[0][6] = L"页码";
	data[0][7] = L"加绩";

	int row = 1;

	while (pR_Current != NULL) { //遍历科研支链表

		data.push_back(vector<std::wstring>(8, L"")); //增加一行(每行8列)

		//每行的内容
		data[row][0] = pR_Current->research.paper_name;
		data[row][1] = pR_Current->research.journal_or_conference_name;
		data[row][2] = pR_Current->research.author;
		data[row][3] = pR_Current->research.date;
		data[row][4] = pR_Current->research.volume_num;
		data[row][5] = pR_Current->research.issue_num;
		data[row][6] = pR_Current->research.page;
		
		wchar_t tmpGPA[6];
		swprintf(tmpGPA, L"%.2lf", pR_Current->research.GPA_bonus);

		data[row][7] = tmpGPA;

		row++; // 行数+1

		pR_Current = pR_Current->rnext; // 移向下一个节点

	}

	return true;

}

bool ShowStu_Competition(const Node* Stu, vector<vector<wstring>>& data) {

	Cnode* pC_Current = Stu->item.clist->cnext;

	data.clear(); // 清空数组
	data.push_back(vector<wstring>(5, L"")); //增加一行(每行5列)
	
	wchar_t competition_name[200];//竞赛名称
	wchar_t organizer[200];//举办单位
	wchar_t category[200];//获奖类别
	wchar_t date[200];//获奖时间 年月
	double GPA_bonus;

	//初始化表头
	data[0][0] = L"竞赛名称";
	data[0][1] = L"举办单位";
	data[0][2] = L"获奖类别";
	data[0][3] = L"获奖时间";
	data[0][4] = L"绩点加分";

	int row = 1;

	while (pC_Current != NULL) { //遍历竞赛支链表

		data.push_back(vector<std::wstring>(5, L"")); //增加一行(每行5列)

		//每行的内容
		data[row][0] = pC_Current->competition.competition_name;
		data[row][1] = pC_Current->competition.organizer;
		data[row][2] = pC_Current->competition.category;
		data[row][3] = pC_Current->competition.date;

		wchar_t tmpGPA[6];
		swprintf(tmpGPA, L"%.2lf", pC_Current->competition.GPA_bonus);
		
		data[row][4] = tmpGPA;

		row++; // 行数+1

		pC_Current = pC_Current->cnext; // 移向下一个节点

	}

	return true;

}

Node* searchStu_InQuality(List phead,wchar_t* str) { // 在总链表中搜索学生(lzy调试专用
	Node* ptmp = phead->next;//别忘了考虑哨兵节点
	while (ptmp!=NULL)
	{
		if (wcscmp(str, ptmp->item.data.name) == 0)
			break;
		ptmp = ptmp->next;
	}
	if (ptmp == NULL)	return NULL;
	return ptmp;
}

 
bool addQuality_rlist(Node* Stu,wchar_t* paper_name,
	wchar_t * journal_or_conference_name,
	wchar_t* author, 
	wchar_t* date, 
	wchar_t* volume_num, 
	wchar_t* issue_num,
	wchar_t* page,
	double GPA_bonus){
	
	Rnode* rtmp = Stu->item.rlist;//素质类rlist链表亦有哨兵节点
	
	while (rtmp->rnext != NULL) {
		if (wcscmp(rtmp->rnext->research.paper_name, paper_name) == 0)
			return false;
		rtmp = rtmp->rnext;//尾插法
	}

	Rnode* rnew = (Rnode*)malloc(sizeof(Rnode));
	if (rnew == NULL)
		return false;//节点空间分配失败

	wcscpy(rnew->research.paper_name, paper_name);
	wcscpy(rnew->research.journal_or_conference_name, journal_or_conference_name);
	wcscpy(rnew->research.author, author);
	wcscpy(rnew->research.date, date);
	wcscpy(rnew->research.volume_num, volume_num);
	wcscpy(rnew->research.issue_num, issue_num);
	wcscpy(rnew->research.page, page);
	rnew->research.GPA_bonus = GPA_bonus;

	rnew->rnext = NULL;
	rtmp->rnext = rnew;
	return true;
} 

bool addQuality_clist(Node* Stu,
	wchar_t* competition_name,
	wchar_t* organizer, 
	wchar_t* category,
	wchar_t* date,
	double GPA_bonus) {

	Cnode* ctmp = Stu->item.clist;//素质类clist链表亦有哨兵节点
	
	while (ctmp->cnext != NULL) {
		if (wcscmp(ctmp->cnext->competition.competition_name, competition_name) == 0)
			return false;
		ctmp = ctmp->cnext;//尾插法
	}

	Cnode* cnew = (Cnode*)malloc(sizeof(Cnode));
	if (cnew == NULL)
		return false;//节点空间分配失败
	
	wcscpy(cnew->competition.competition_name, competition_name);
	wcscpy(cnew->competition.organizer, organizer);
	wcscpy(cnew->competition.category, category);
	wcscpy(cnew->competition.date, date);
	cnew->competition.GPA_bonus = GPA_bonus;

	cnew->cnext = NULL;
	ctmp->cnext = cnew;
	return true;
}

/*void show_Research_menu(const wchar_t* title, Rnode* rhead) {//方便修改函数确认所需处理的科研项目节点
		wprintf(L"%s\n\n", title);
		Rnode* rtmp = rhead->rnext;
		while (rtmp != NULL) {
			Research_num++;
			wprintf(L"%2d:%s\n", Research_num, rtmp->research.paper_name);
			rtmp = rtmp->rnext;
		}
}
void show_Competition_menu(const wchar_t* title, Cnode* chead) {//方便修改函数确认所需处理的竞赛获奖节点
	wprintf(L"%s\n\n", title);
	Cnode* ctmp = chead->cnext;
	while (ctmp != NULL) {
		Competition_num++;
		wprintf(L"%2d:%s\n", Competition_num, ctmp->competition.competition_name);
		ctmp = ctmp->cnext;
	}
}*/
/*Node* searchStu_with_thisRnode(List* StuList, wchar_t* paper_name) {//找出待修改的素质类项目节点
	Node* Stu = (*StuList)->next;
	while (Stu != NULL) {
		Rnode* rtmp = Stu->item.rlist->rnext;//别忘了考虑哨兵节点
		while (rtmp != NULL){
			if (wcscmp(paper_name, rtmp->research.paper_name) == 0)
				break;
			rtmp = rtmp->rnext;
		}
		if (rtmp == NULL)
			Stu = Stu->next;
		else
			break;
	}
	return Stu;
}// 找出此学生待修改的素质类项目节点
*/
Rnode* searchRnode_in_thisStu(Node* Stu,  wchar_t* paper_name) {
	Rnode* pR_Current = Stu->item.rlist->rnext;

	while (pR_Current != NULL) {
		if (wcscmp(paper_name, pR_Current->research.paper_name) == 0)
			break;
		pR_Current = pR_Current->rnext;
	}
	return pR_Current;

}
Cnode* searchCnode_in_thisStu(Node* Stu,wchar_t* competition_name) {
	Cnode* pC_Current = Stu->item.clist->cnext;

	while (pC_Current != NULL) {
		if (wcscmp(competition_name, pC_Current->competition.competition_name) == 0)
			break;
		pC_Current = pC_Current->cnext;
	}
	return pC_Current;
}

bool modifyQuality_rlist(Rnode* rmod,	// 修改素质类项目节点
	wchar_t* paper_name,
	wchar_t* journal_or_conference_name,
	wchar_t* author,
	wchar_t* date,
	wchar_t* volume_num,
	wchar_t* issue_num,
	wchar_t* page,
	double GPA_bonus){ // 修改素质类项目之科研成果

	wcscpy(rmod->research.paper_name, paper_name);
	wcscpy(rmod->research.journal_or_conference_name, journal_or_conference_name);
	wcscpy(rmod->research.author, author);
	wcscpy(rmod->research.date, date);
	wcscpy(rmod->research.volume_num, volume_num);
	wcscpy(rmod->research.issue_num, issue_num);
	wcscpy(rmod->research.page, page);
	rmod->research.GPA_bonus = GPA_bonus;
	 
	return true;
}
bool modifyQuality_clist(Cnode* cmod,
	wchar_t* competition_name,
	wchar_t* organizer,
	wchar_t* category,
	wchar_t* date,
	double GPA_bonus) { // 修改素质类项目之竞赛获奖

	wcscpy(cmod->competition.competition_name, competition_name);
	wcscpy(cmod->competition.organizer, organizer);
	wcscpy(cmod->competition.category , category);
	wcscpy(cmod->competition.date, date);
	cmod->competition.GPA_bonus = GPA_bonus;
	
	return true;
}


bool deleteQuality_rlist(Node* Stu, wchar_t* paper_name) {	// 删除素质类项目之科研成果
	Rnode* rhead = Stu->item.rlist;
	
	Rnode* rpre = rhead;
	Rnode* rtmp = rhead->rnext;
	
	while (rtmp != NULL) {
		if (wcscmp(rtmp->research.paper_name, paper_name) == 0) {
			rpre->rnext = rtmp->rnext;
			free(rtmp);
			break;
		}
		else {
			rpre = rtmp;
			rtmp = rtmp->rnext;
		}
	}

	return true;

}
bool deleteQuality_clist(Node* Stu, wchar_t* competition_name) {	// 删除素质类项目之竞赛获奖
	Cnode* chead = Stu->item.clist;

	Cnode* cpre = chead;
	Cnode* ctmp = chead->cnext;

	while (ctmp != NULL) {
		if (wcscmp(ctmp->competition.competition_name, competition_name) == 0) {
			cpre->cnext = ctmp->cnext;
			free(ctmp);
			break;
		}
		else {
			cpre = ctmp;
			ctmp = ctmp->cnext;
		}
	}

	return true;

}



