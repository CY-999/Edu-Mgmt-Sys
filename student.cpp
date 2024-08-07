#include "student.h"


#pragma warning(disable:4996)


// 显示所有学生信息（不包含课程）返回一个链表
bool showAllStu(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	List pCurrent = StuList->next; //从第一个有数据节点开始
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
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if (wcsstr(std::to_wstring(pCurrent->item.data.ID).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.name, searchTerm) != NULL
			|| wcsstr(std::to_wstring(pCurrent->item.data.grade).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(pCurrent->item.data.college, searchTerm) != NULL
			|| wcsstr(pCurrent->item.data.major, searchTerm) != NULL
			) {

			data.push_back(vector<std::wstring>(6, L"")); //增加一行(每行6列)

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = (pCurrent->item.data.gender) ? L"男" : L"女";
			data[row][3] = std::to_wstring(pCurrent->item.data.grade); //数字转为字符串
			data[row][4] = pCurrent->item.data.college;
			data[row][5] = pCurrent->item.data.major;

			row++; // 行数+1
		}

		pCurrent = pCurrent->next; // 移向下一个节点

	}

	return true;
}

// 显示单个学生信息（包含其课程成绩）	
void showStu(const Node* stu, vector<vector<wstring>>& data, const wchar_t* searchTerm) {
	Crsnode* crstmp = stu->item.crslist->crs_next;
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(7, L"")); //增加一行(每行7列)

	//初始化
	data[0][0] = L"课程号";
	data[0][1] = L"课程名";
	data[0][2] = L"成绩";
	data[0][3] = L"学年";
	data[0][4] = L"学分";
	data[0][5] = L"绩点";
	data[0][6] = L"课程性质";

	int row = 1;
	while (crstmp != NULL) {
		data.push_back(vector<std::wstring>(7, L"")); //增加一行(每行7列)

		// 检测是否有搜索词
		if (wcsstr(crstmp->score.course_id, searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(crstmp->score.course_name, searchTerm) != NULL
			|| wcsstr(std::to_wstring(crstmp->score.score).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			|| wcsstr(std::to_wstring(crstmp->score.semester).c_str(), searchTerm) != NULL
			|| wcsstr(std::to_wstring(crstmp->score.credit).c_str(), searchTerm) != NULL
			|| wcsstr(std::to_wstring(crstmp->score.grid).c_str(), searchTerm) != NULL
			|| wcsstr(std::to_wstring(crstmp->score.course_nature).c_str(), searchTerm) != NULL
			) {
			//每行的内容
			data[row][0] = crstmp->score.course_id;
			data[row][1] = crstmp->score.course_name;
			data[row][2] = (crstmp->score.score == 0) ? L"" : to_wstring(crstmp->score.score); //数字转为字符串
			data[row][3] = std::to_wstring(crstmp->score.semester); //数字转为字符串
			data[row][4] = std::to_wstring(crstmp->score.credit);//数字转为字符串
			data[row][5] = (crstmp->score.score == 0) ? L"" : to_wstring(crstmp->score.grid);//数字转为字符串
			data[row][6] = (crstmp->score.course_nature == 1) ? L"必修" : L"选修"; //数字转为字符串


			data[row][2] = data[row][2].substr(0, data[row][2].find('.') + 2);
			data[row][4] = data[row][4].substr(0, data[row][4].find('.') + 2);
			data[row][5] = data[row][5].substr(0, data[row][5].find('.') + 2);

			row++; // 行数+1
		}
		crstmp = crstmp->crs_next;
	}


}

//排序界面！
void Rank(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm, const wchar_t* searchTerm2, int* number) {

	List pCurrent = StuList->next; //从第一个有数据节点开始
	data.clear(); // 清空数组
	data.push_back(vector<wstring>(8, L"")); //增加一行(每行8列)

	//初始化表头
	data[0][0] = L"学号";
	data[0][1] = L"姓名";///
	data[0][2] = L"年级";///
	data[0][3] = L"专业";///
	data[0][4] = L"平均成绩";
	data[0][5] = L"平均绩点";
	data[0][6] = L"平均成绩(必修)";
	data[0][7] = L"平均绩点(必修)";


	int row = 1;
	while (pCurrent != NULL) { //遍历链表

		// 检测是否有搜索词
		if ( //wcsstr(std::to_wstring(pCurrent->item.data.grade).c_str(), searchTerm) != NULL // 数字转为字符串再转为wchar_t来进行比较
			wcsstr(pCurrent->item.data.major, searchTerm) != NULL
			&& wcsstr(std::to_wstring(pCurrent->item.data.grade).c_str(), searchTerm2) != NULL // 数字转为字符串再转为wchar_t来进行比较
			// wcsstr(pCurrent->item.data.major, searchTerm2) != NULL
			) {

			data.push_back(vector<std::wstring>(8, L"")); //增加一行(每行8列)

			//成绩计算
			pCurrent->item.data.all_avg_score = AllScore(pCurrent);
			pCurrent->item.data.all_avg_grid = MustGrid(pCurrent);
			pCurrent->item.data.req_avg_score = AllScore(pCurrent);
			pCurrent->item.data.req_avg_grid = MustGrid(pCurrent);

			//每行的内容
			data[row][0] = std::to_wstring(pCurrent->item.data.ID); //数字转为字符串
			data[row][1] = pCurrent->item.data.name;
			data[row][2] = std::to_wstring(pCurrent->item.data.grade); //数字转为字符串
			data[row][3] = pCurrent->item.data.major;

			data[row][4] = std::to_wstring(pCurrent->item.data.all_avg_score); //数字转为字符串
			data[row][5] = std::to_wstring(pCurrent->item.data.all_avg_grid); //数字转为字符串
			data[row][6] = std::to_wstring(pCurrent->item.data.req_avg_score); //数字转为字符串
			data[row][7] = std::to_wstring(pCurrent->item.data.req_avg_grid); //数字转为字符串

			//保留小数
			data[row][4] = data[row][4].substr(0, data[row][4].find('.') + 3);
			data[row][5] = data[row][5].substr(0, data[row][5].find('.') + 5);
			data[row][6] = data[row][6].substr(0, data[row][6].find('.') + 3);
			data[row][7] = data[row][7].substr(0, data[row][7].find('.') + 5);

			row++; // 行数+1
		}

		*number = row;
		pCurrent = pCurrent->next; // 移向下一个节点

	}
}



//平均绩点(所有）
double AllGrid(Node* Crs) {
	double allcredit = 0;
	double result = 0;
	Crsnode* tmp1 = Crs->item.crslist->crs_next;


	char judge[99999] = { 0 };
	int maxhhh = 0;


	for (; tmp1 != NULL; tmp1 = tmp1->crs_next) {
		if (judge[stoi(tmp1->score.course_id)] == 0 && tmp1->score.score != 0) {

			judge[stoi(tmp1->score.course_id)] = 1;
			maxhhh = tmp1->score.grid;

			for (Crsnode* tmp2 = tmp1; tmp2 != NULL; tmp2 = tmp2->crs_next) {
				if (wcscmp(tmp1->score.course_id, tmp2->score.course_id) == 0) {
					maxhhh = max(tmp2->score.grid, maxhhh);
				}
			}

			result += maxhhh * tmp1->score.credit;
			allcredit += tmp1->score.credit;
		}
	}


	double maxm = 0;
	double maxn = 0;
	Rnode* tmp3 = Crs->item.rlist->rnext;
	while (tmp3 != NULL) {
		maxn = max(tmp3->research.GPA_bonus, maxn);
		tmp3 = tmp3->rnext;
	}

	Cnode* tmp4 = Crs->item.clist->cnext;
	while (tmp4 != NULL) {
		maxm = max(tmp4->competition.GPA_bonus, maxm);
		tmp4 = tmp4->cnext;
	}

	if (allcredit == 0) {
		return maxn + maxm;
	}
	else {
		return result / allcredit + maxn + maxm;
	}
}

double MustGrid(Node* Crs) {
	double allcredit = 0;
	double result = 0;
	Crsnode* tmp1 = Crs->item.crslist->crs_next;


	char judge[99999] = { 0 };
	int maxhhh = 0;


	for (; tmp1 != NULL; tmp1 = tmp1->crs_next) {
		if (judge[stoi(tmp1->score.course_id)] == 0 && tmp1->score.course_nature == 1 && tmp1->score.score != 0) {

			judge[stoi(tmp1->score.course_id)] = 1;
			maxhhh = tmp1->score.grid;

			for (Crsnode* tmp2 = tmp1; tmp2 != NULL; tmp2 = tmp2->crs_next) {
				if (wcscmp(tmp1->score.course_id, tmp2->score.course_id) == 0) {
					maxhhh = max(tmp2->score.grid, maxhhh);
				}
			}

			result += maxhhh * tmp1->score.credit;
			allcredit += tmp1->score.credit;
		}
	}


	double maxm = 0;
	double maxn = 0;
	Rnode* tmp3 = Crs->item.rlist->rnext;
	while (tmp3 != NULL) {
		maxn = max(tmp3->research.GPA_bonus, maxn);
		tmp3 = tmp3->rnext;
	}

	Cnode* tmp4 = Crs->item.clist->cnext;
	while (tmp4 != NULL) {
		maxm = max(tmp4->competition.GPA_bonus, maxm);
		tmp4 = tmp4->cnext;

		if (allcredit == 0) {
			return maxn + maxm;
		}
		else {
			return result / allcredit + maxn + maxm;
		}
	}
}

double AllScore(Node* Crs) {
	double allcredit = 0;
	double result = 0;
	Crsnode* tmp1 = Crs->item.crslist->crs_next;


	char judge[99999] = { 0 };
	int maxhhh = 0;


	for (; tmp1 != NULL; tmp1 = tmp1->crs_next) {
		if (judge[stoi(tmp1->score.course_id)] == 0 && tmp1->score.score != 0) {

			judge[stoi(tmp1->score.course_id)] = 1;
			maxhhh = tmp1->score.score;

			for (Crsnode* tmp2 = tmp1; tmp2 != NULL; tmp2 = tmp2->crs_next) {
				if (wcscmp(tmp1->score.course_id, tmp2->score.course_id) == 0) {
					maxhhh = max(tmp2->score.score, maxhhh);
				}
			}

			result += maxhhh * tmp1->score.credit;
			allcredit += tmp1->score.credit;
		}
	}


	double maxm = 0;
	double maxn = 0;
	Rnode* tmp3 = Crs->item.rlist->rnext;
	while (tmp3 != NULL) {
		maxn = max(Crs->item.rlist->research.GPA_bonus, maxn);
		tmp3 = tmp3->rnext;
	}

	Rnode* tmp4 = Crs->item.rlist->rnext;
	while (tmp4 != NULL) {
		maxm = max(Crs->item.clist->competition.GPA_bonus, maxm);
		tmp4 = tmp4->rnext;
	}

	if (allcredit == 0) {
		return maxn + maxm;
	}
	else {
		return result / allcredit + maxn + maxm;
	}

}

double MustScore(Node* Crs) {
	double allcredit = 0;
	double result = 0;
	Crsnode* tmp1 = Crs->item.crslist->crs_next;


	char judge[99999] = { 0 };
	int maxhhh = 0;


	for (; tmp1 != NULL; tmp1 = tmp1->crs_next) {
		if (judge[stoi(tmp1->score.course_id)] == 0 && tmp1->score.course_nature == 1 && tmp1->score.score != 0) {

			judge[stoi(tmp1->score.course_id)] = 1;
			maxhhh = tmp1->score.score;

			for (Crsnode* tmp2 = tmp1; tmp2 != NULL; tmp2 = tmp2->crs_next) {
				if (wcscmp(tmp1->score.course_id, tmp2->score.course_id) == 0) {
					maxhhh = max(tmp2->score.score, maxhhh);
				}
			}

			result += maxhhh * tmp1->score.credit;
			allcredit += tmp1->score.credit;
		}
	}


	double maxm = 0;
	double maxn = 0;
	Rnode* tmp3 = Crs->item.rlist->rnext;
	while (tmp3 != NULL) {
		maxn = max(Crs->item.rlist->research.GPA_bonus, maxn);
		tmp3 = tmp3->rnext;
	}

	Rnode* tmp4 = Crs->item.rlist->rnext;
	while (tmp4 != NULL) {
		maxm = max(Crs->item.clist->competition.GPA_bonus, maxm);
		tmp4 = tmp4->rnext;
	}

	if (allcredit == 0) {
		return maxn + maxm;
	}
	else {
		return result / allcredit + maxn + maxm;
	}
}

// 排序总学生链表(按照学号来排序）
void sortStuaccID(List* plist) {
	Node* p, * p0, * r, * r0, * q;
	p = p0 = r = r0 = q = NULL;
	p = *plist;
	while (p) {
		r = *plist;
		while (r->item.data.ID < p->item.data.ID && r != p) {
			r0 = r;
			r = r->next;
		}//找位置

		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r != *plist) {
				r0->next = q;
				q->next = r;
			}
			else {
				q->next = *plist;
				*plist = q;
			}
		}
		p0 = p;
		p = p->next;
	}
}


// 排序学生课程链表(按照学年来排序）
void sortStuCrsYear(Crsnode* plist) {
	Crsnode* p, * p0, * r, * r0, * q;
	p = p0 = r = r0 = q = NULL;
	p = plist;
	while (p) {
		r = plist;
		while (r->score.semester < p->score.semester && r != p) {
			r0 = r;
			r = r->crs_next;
		}//找位置

		if (r != p) {
			q = p;
			p0->crs_next = p->crs_next;
			p = p0;
			if (r != plist) {
				r0->crs_next = q;
				q->crs_next = r;
			}
			else {
				q->crs_next = plist;
				plist = q;
			}
		}
		p0 = p;
		p = p->crs_next;
	}
}



// 排序总学生链表(按照入学年份来排序）
void sortStuaccyear(List* plist) {
	Node* p, * p0, * r, * r0, * q;
	p = p0 = r = r0 = q = NULL;
	p = *plist;
	while (p) {
		r = *plist;
		while (r->item.data.grade < p->item.data.grade && r != p) {
			r0 = r;
			r = r->next;
		}//找位置

		if (r != p) {
			q = p;
			p0->next = p->next;
			p = p0;
			if (r != *plist) {
				r0->next = q;
				q->next = r;
			}
			else {
				q->next = *plist;
				*plist = q;
			}
		}
		p0 = p;
		p = p->next;
	}
}


// 添加学生（不包含课程）
bool addStu(List* plist, wchar_t* pname, int pID, int pgender, int pgrade, wchar_t* pcollege, wchar_t* pmajor) {
	Node* ptmp = *plist;
	while (ptmp->next != NULL) {
		if (ptmp->next->item.data.ID == pID)
			return false;
		ptmp = ptmp->next;
	}

	Node* pnew = (Node*)malloc(sizeof(Node));
	pnew->next = NULL;
	pnew->item.crslist = (Crsnode*)malloc(sizeof(Crsnode));
	pnew->item.crslist->crs_next = NULL;
	pnew->item.rlist = (Rnode*)malloc(sizeof(Rnode));
	pnew->item.rlist->rnext = NULL;
	pnew->item.clist = (Cnode*)malloc(sizeof(Cnode));
	pnew->item.clist->cnext = NULL;

	wcscpy(pnew->item.data.name, pname);
	pnew->item.data.ID = pID;
	pnew->item.data.gender = pgender;
	pnew->item.data.grade = pgrade;
	wcscpy(pnew->item.data.college, pcollege);
	wcscpy(pnew->item.data.major, pmajor);
	wcscpy(pnew->item.data.original_college, pcollege);
	wcscpy(pnew->item.data.original_major, pmajor);
	wcscpy(pnew->item.data.password, to_wstring(pnew->item.data.ID).c_str());
	pnew->item.data.all_avg_score = 0;
	pnew->item.data.all_avg_grid = 0;
	pnew->item.data.req_avg_score = 0;
	pnew->item.data.req_avg_grid = 0;


	ptmp->next = pnew;
	return true;
}

//为某个学生添加某课程及成绩
bool addCrsToStu(Node* chastu, const wchar_t* pcourse_id, const wchar_t* pcourse_name, double pscore, int psemester, int pcourse_nature, double pcredit, double pgrid) {
	if (searchCrsInStu(chastu, pcourse_id, pcourse_name)) {
		return false;
	}
	Crsnode* crs_tmp = chastu->item.crslist;//课程链表头节点
	while (crs_tmp->crs_next != NULL)
		crs_tmp = crs_tmp->crs_next;
	Crsnode* crs_new = (Crsnode*)malloc(sizeof(Crsnode));//创建新节点
	if (crs_new == NULL)
		return false;
	crs_new->crs_next = NULL;

	wcscpy(crs_new->score.course_id, pcourse_id);
	wcscpy(crs_new->score.course_name, pcourse_name);
	crs_new->score.score = pscore;
	crs_new->score.semester = psemester;
	crs_new->score.course_nature = pcourse_nature;
	crs_new->score.credit = pcredit;
	crs_new->score.grid = pgrid;

	crs_tmp->crs_next = crs_new;//添加新节点
	return true;
}


//修改学生信息（不修改课程）
bool modifyStu(List* plist, Node* chastu, wchar_t* pname, int pID, int pgender, int pgrade, wchar_t* pcollege, wchar_t* pmajor) {
	Node* ptmp = *plist;
	while (ptmp != chastu)
		ptmp = ptmp->next;

	wcscpy(ptmp->item.data.name, pname);
	ptmp->item.data.ID = pID;
	ptmp->item.data.gender = pgender;
	ptmp->item.data.grade = pgrade;
	wcscpy(ptmp->item.data.college, pcollege);
	wcscpy(ptmp->item.data.major, pmajor);
	return true;
}

// 修改某个学生的某课程及成绩
bool modifyCrsInStu(Crsnode* chacrs, wchar_t* pcourse_id, wchar_t* pcourse_name, double pscore, int psemester, int pcourse_nature, double pcredit, double pgrid) {
	wcscpy(chacrs->score.course_id, pcourse_id);
	wcscpy(chacrs->score.course_name, pcourse_name);
	chacrs->score.score = pscore;
	chacrs->score.semester = psemester;
	chacrs->score.course_nature = pcourse_nature;
	chacrs->score.credit = pcredit;
	chacrs->score.grid = pgrid;

	return true; //不加这行会报错没有返回值
}

// 删除学生
bool deleteStu(List* plist, Node* delstu) {
	Node* ptmp = *plist;
	while (ptmp->next != delstu)
		ptmp = ptmp->next;
	ptmp->next = delstu->next;
	free(delstu);
	return true;
}

// 删除某个学生的某课程及成绩
bool deleteCrsInStu(Node* delstu, Crsnode* delcrs) {
	Node* ptmp = delstu;//学生节点
	Crsnode* crs_tmp = ptmp->item.crslist;//课程头节点
	while (crs_tmp != NULL && crs_tmp->crs_next != delcrs) {//寻找被删除课程节点的前节点
		crs_tmp = crs_tmp->crs_next;
	}
	crs_tmp->crs_next = delcrs->crs_next;
	free(delcrs);
	return true;
}


// 在总学生链表中通过学号和名字搜索学生 
Node* searchStu(List* plist, wchar_t* pname, int pID)
{
	Node* ptmp = *plist;
	while (ptmp && (ptmp->item.data.ID != pID || _tcscmp(ptmp->item.data.name, pname) != 0))//通过姓名或学号来检索
		ptmp = ptmp->next;
	return (ptmp);//返回这个学生信息的节点地址
}

// 在单个学生中搜索的课程
Crsnode* searchCrsInStu(Node* stu, const wchar_t* pcourse_id, const wchar_t* pcourse_name) {
	Crsnode* crstmp = stu->item.crslist->crs_next;
	//首先要判断是否空，合并时别搞没了
	while (crstmp && (_tcscmp(crstmp->score.course_id, pcourse_id) != 0 || _tcscmp(crstmp->score.course_name, pcourse_name) != 0))//通过课程编号和课程名来检索
		crstmp = crstmp->crs_next;
	return crstmp;
}

//初始化每个学生的课程链表并添加哨兵节点
/*bool Initialize_Stu_Crslist(List phead) {
		List Ltmp = phead->next;
		while (Ltmp != NULL) {
			Crsnode* crs_head = (Crsnode*)malloc(sizeof(Crsnode));
			if (crs_head == NULL)
				return false;
			crs_head->crs_next = NULL;
			Ltmp->item.crslist = crs_head;
			Ltmp = Ltmp->next;
		}
		return true;
}
*/

//Crsnode* tmp2 = Crs->item.crslist->crs_next;
//for (; tmp1 != NULL; ) {
//	allcredit += tmp1->score.credit;
//	tmp1 = tmp1->crs_next;
//}

////防止课程不够
//if (allcredit == 0) {
//	return 0;
//}


//double result = 0;
//for (; tmp2 != NULL; ) {
//	result += tmp2->score.grid * (tmp2->score.credit);
//	tmp2 = tmp2->crs_next;
//}