#pragma warning(disable:4996)

#include "file.h"



List readStu(const char* file_name) {
	FILE* fp;
	List StuList = (List)malloc(sizeof(Node));
	StuList->next = NULL;
	//StuList->item.crslist = (Crsnode*)malloc(sizeof(Crsnode));
	//StuList->item.crslist->crs_next = NULL;

	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//读取失败退出

	List tnode = (List)malloc(sizeof(Node)); //为tnode申请内存(临时存放)
	tnode->next = NULL;
	Crsnode* tcrs = (Crsnode*)malloc(sizeof(Crsnode)); //为tcrs申请内存(临时存放)
	tcrs->crs_next = NULL;
	Rnode* trnode = (Rnode*)malloc(sizeof(Rnode)); //为trnode申请内存(临时存放)
	trnode->rnext = NULL;
	Cnode* tcnode = (Cnode*)malloc(sizeof(Cnode)); //为tcnode申请内存(临时存放)
	tcnode->cnext = NULL;


	if (tnode == NULL || tcrs == NULL || trnode == NULL || tcnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// 分配失败

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') { // 跳过空行
			continue;
		}

		if (swscanf(line, L"%d %s %d %d %s %s %s %s %s %lf %lf %lf %lf",
			&tnode->item.data.ID,
			&tnode->item.data.name,
			&tnode->item.data.gender,
			&tnode->item.data.grade,
			&tnode->item.data.college,
			&tnode->item.data.major,
			&tnode->item.data.original_college,
			&tnode->item.data.original_major,
			&tnode->item.data.password,

			&tnode->item.data.all_avg_score,
			&tnode->item.data.all_avg_grid,
			&tnode->item.data.req_avg_score,
			&tnode->item.data.req_avg_grid

		) == 13) { // 读取学生信息





			tnode->item.crslist = (Crsnode*)malloc(sizeof(Crsnode)); //为一个crslist申请内存(添加到链表中的crslist)
			if (tnode->item.crslist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			tnode->item.crslist->crs_next = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // 跳过空行
					break;
				}
				if (swscanf(line, L"%s %s %lf %d %d %lf %lf",
					&tcrs->score.course_id,
					&tcrs->score.course_name,
					&tcrs->score.score,
					&tcrs->score.semester,
					&tcrs->score.course_nature,
					&tcrs->score.credit,
					&tcrs->score.grid
				) == 7) { // 读取课程信息

					// 添加到链表
					Crsnode* crsnode = (Crsnode*)malloc(sizeof(Crsnode)); //为crsnode申请内存(添加到链表中的crsnode)
					if (crsnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// 分配失败
					memcpy(crsnode, tcrs, sizeof(Crsnode));
					Crsnode* ptmp = tnode->item.crslist;
					while (ptmp->crs_next != NULL) {
						ptmp = ptmp->crs_next;
					}
					ptmp->crs_next = crsnode;
				}
			}



			tnode->item.rlist = (Rnode*)malloc(sizeof(Rnode)); //为一个rlist申请内存(添加到链表中的rlist)
			if (tnode->item.rlist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			tnode->item.rlist->rnext = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // 跳过空行
					break;
				}
				if (swscanf(line, L"%s %s %s %s %s %s %s %lf",
					&trnode->research.paper_name,
					&trnode->research.journal_or_conference_name,
					&trnode->research.author,
					&trnode->research.date,
					&trnode->research.volume_num,
					&trnode->research.issue_num,
					&trnode->research.page,
					&trnode->research.GPA_bonus
				) == 8) { // 读取科研成果信息

					// 添加到链表
					Rnode* resnode = (Rnode*)malloc(sizeof(Rnode)); //为resnode申请内存(添加到链表中的resnode)
					if (resnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// 分配失败
					memcpy(resnode, trnode, sizeof(Rnode));
					Rnode* ptmp = tnode->item.rlist;
					while (ptmp->rnext != NULL) {
						ptmp = ptmp->rnext;
					}
					ptmp->rnext = resnode;
				}
			}





			tnode->item.clist = (Cnode*)malloc(sizeof(Cnode)); //为一个clist申请内存(添加到链表中的clist)
			if (tnode->item.clist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			tnode->item.clist->cnext = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // 跳过空行
					break;
				}
				if (swscanf(line, L"%s %s %s %s %lf",
					&tcnode->competition.competition_name,
					&tcnode->competition.organizer,
					&tcnode->competition.category,
					&tcnode->competition.date,
					&tcnode->competition.GPA_bonus
				) == 5) { // 读取竞赛获奖信息

					// 添加到链表
					Cnode* cptnode = (Cnode*)malloc(sizeof(Cnode)); //为cptnode申请内存(添加到链表中的cptnode)
					if (cptnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// 分配失败
					memcpy(cptnode, tcnode, sizeof(Cnode));
					Cnode* ptmp = tnode->item.clist;
					while (ptmp->cnext != NULL) {
						ptmp = ptmp->cnext;
					}
					ptmp->cnext = cptnode;
				}
			}







			// 添加到链表
			List Coursenode = (List)malloc(sizeof(Node)); //为Coursenode申请内存(添加到链表中的Coursenode)
			if (Coursenode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			memcpy(Coursenode, tnode, sizeof(Node));
			List ptmp = StuList;
			while (ptmp->next != NULL) {
				ptmp = ptmp->next;
			}
			ptmp->next = Coursenode;

		}
	}
	free(tnode);
	free(tcrs);
	free(trnode);
	free(tcnode);
	fclose(fp);
	return StuList;

}

List readTch(const char* file_name) {
	FILE* fp;
	List TchList = (List)malloc(sizeof(Node));//构建教师链表
	TchList->next = NULL;

	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//读取失败退出

	Node* Tchnode = (Node*)malloc(sizeof(Node));//哨兵节点
	Tchnode->next = NULL;


	if (Tchnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// 分配失败

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') {//跳过空行
			continue;
		}

		if (swscanf(line, L"%d %s %d %s %s",
			&Tchnode->item.data.ID,
			&Tchnode->item.data.name,
			&Tchnode->item.data.gender,
			&Tchnode->item.data.college,
			&Tchnode->item.data.password) == 5) { //读取教师信息

			// 添加到链表
			List Tmpnode = (List)malloc(sizeof(Node));
			if (Tmpnode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			memcpy(Tmpnode, Tchnode, sizeof(Node));//把Tchnode内的全部内容都拷贝一份到Tmpnode,包括next
			List ptmp = TchList;
			while (ptmp->next != NULL) {
				ptmp = ptmp->next;
			}
			ptmp->next = Tmpnode;
		}
	}
	free(Tchnode);
	fclose(fp);
	return TchList;

}

List readAdmin(const char* file_name) {
	FILE* fp;
	List admin_List = (List)malloc(sizeof(Node));//构建管理员链表
	admin_List->next = NULL;

	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//读取失败退出

	Node* admin_node = (Node*)malloc(sizeof(Node));//哨兵节点
	admin_node->next = NULL;


	if (admin_node == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// 分配失败

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') {//跳过空行
			continue;
		}

		if (swscanf(line, L"%d %s %s",
			&admin_node->item.data.ID,
			&admin_node->item.data.name,
			&admin_node->item.data.password) == 3) { //读取管理员信息

			// 添加到链表
			List Tmpnode = (List)malloc(sizeof(Node));
			if (Tmpnode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			memcpy(Tmpnode, admin_node, sizeof(Node));//把admin_node内的全部内容都拷贝一份到Tmpnode,包括next
			List ptmp = admin_List;
			while (ptmp->next != NULL) {
				ptmp = ptmp->next;
			}
			ptmp->next = Tmpnode;

		}
	}
	free(admin_node);
	fclose(fp);
	return admin_List;

}


Cpnode readCrs(const char* file_name) {
	FILE* fp;
	Cpnode CrsList = (Cpnode)malloc(sizeof(_Cnode));
	CrsList->next = NULL;
	CrsList->sphead = (Spnode)malloc(sizeof(Snode));
	CrsList->sphead->next = NULL;

	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Write to \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//读取失败退出

	Cpnode tcnode = (Cpnode)malloc(sizeof(_Cnode)); //为tcnode申请内存(存放临时的Cpnode)
	tcnode->next = NULL;
	Spnode tsnode = (Spnode)malloc(sizeof(Snode)); //为tsnode申请内存(存放临时的Spnode)
	tsnode->next = NULL;
	if (tcnode == NULL || tsnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// 分配失败

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL)
	{
		if (line[0] == '\n')
		{ // 跳过空行
			continue;
		}

		if (swscanf(line, L"%d %s %s %lf %d %lf %lf %lf %lf %d %d %lf %d %lf",
			&tcnode->cnum,
			&tcnode->cname,
			&tcnode->character,
			&tcnode->credit,
			&tcnode->headcount,
			&tcnode->totscore,
			&tcnode->averscore,
			&tcnode->totGPA,
			&tcnode->averGPA,
			&tcnode->SchYear,
			&tcnode->PassNum,
			&tcnode->PassRate,
			&tcnode->ExcelNum,
			&tcnode->ExcelRate
		) == 14)
		{ // 读取课程信息

			tcnode->sphead = (Spnode)malloc(sizeof(Snode));//为一个sphead申请内存(添加到链表中的sphead)
			if (tcnode->sphead == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			tcnode->sphead->next = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL)
			{
				if (line[0] == '\n') { // 跳过空行
					break;
				}
				if (swscanf(line, L"%d %s %lf %lf",
					&tsnode->snum,
					&tsnode->sname,
					&tsnode->score,
					&tsnode->GPA
				) == 4) { // 读取学生信息
					tsnode->next = NULL;

					// 添加到链表
					Spnode snode = (Spnode)malloc(sizeof(Snode)); //为snode申请内存(添加到链表中的snode)
					if (snode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// 分配失败
					memcpy(snode, tsnode, sizeof(Snode));
					Spnode ptmp = tcnode->sphead;
					while (ptmp->next != NULL) {
						ptmp = ptmp->next;
					}
					ptmp->next = snode;


				}
			}

			// 添加到链表
			Cpnode cnode = (Cpnode)malloc(sizeof(_Cnode)); //为cnode申请内存(添加到链表中的cnode)
			if (cnode == NULL)
			{
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// 分配失败
			memcpy(cnode, tcnode, sizeof(_Cnode));
			Cpnode ptmp = CrsList;
			while (ptmp->next != NULL)
			{
				ptmp = ptmp->next;
			}
			ptmp->next = cnode;

			CalculNumOfCrs(1);//修改，别删;计算一共有多少课程
		}
	}
	free(tcnode);
	free(tsnode);
	fclose(fp);
	return CrsList;



}

bool saveStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败

	List pStu = StuList->next; // 从头结点的下一个节点开始
	while (pStu != NULL) {
		fwprintf(fp, L"%d %s %d %d %s %s %s %s %s %.2lf %.4lf %.2lf %.4lf\n",
			pStu->item.data.ID,
			pStu->item.data.name,
			pStu->item.data.gender,
			pStu->item.data.grade,
			pStu->item.data.college,
			pStu->item.data.major,
			pStu->item.data.original_college,
			pStu->item.data.original_major,
			pStu->item.data.password,

			pStu->item.data.all_avg_score,
			pStu->item.data.all_avg_grid,
			pStu->item.data.req_avg_score,
			pStu->item.data.req_avg_grid

		); // 写入

		Crsnode* pcrs = pStu->item.crslist->crs_next; // 从下一个课程节点开始
		while (pcrs != NULL) {
			fwprintf(fp, L"%s %s %.1lf %d %d %.1lf %.1lf\n",
				pcrs->score.course_id,
				pcrs->score.course_name,
				pcrs->score.score,
				pcrs->score.semester,
				pcrs->score.course_nature,
				pcrs->score.credit,
				pcrs->score.grid); // 写入

			pcrs = pcrs->crs_next; // 移动到下一个节点
		}
		fwprintf(fp, L"\n");


		Rnode* pres = pStu->item.rlist->rnext; // 从下一个科研成果节点开始
		while (pres != NULL) {
			fwprintf(fp, L"%s %s %s %s %s %s %s %.2lf\n",
				pres->research.paper_name,
				pres->research.journal_or_conference_name,
				pres->research.author,
				pres->research.date,
				pres->research.volume_num,
				pres->research.issue_num,
				pres->research.page,
				pres->research.GPA_bonus); // 写入

			pres = pres->rnext; // 移动到下一个节点
		}
		fwprintf(fp, L"\n");


		Cnode* pcpt = pStu->item.clist->cnext; // 从下一个竞赛获奖节点开始
		while (pcpt != NULL) {
			fwprintf(fp, L"%s %s %s %s %.2lf\n",
				pcpt->competition.competition_name,
				pcpt->competition.organizer,
				pcpt->competition.category,
				pcpt->competition.date,
				pcpt->competition.GPA_bonus); // 写入

			pcpt = pcpt->cnext; // 移动到下一个节点
		}
		fwprintf(fp, L"\n");



		pStu = pStu->next; // 移动到下一个节点
	}
	fclose(fp);
	return true;
}

bool saveTch(List TchList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败

	List pTch = TchList->next; // 从头结点的下一个节点开始

	while (pTch != NULL) {
		fwprintf(fp, L"%d %s %d %s %s\n",
			pTch->item.data.ID,
			pTch->item.data.name,
			pTch->item.data.gender,
			pTch->item.data.college,
			pTch->item.data.password);

		pTch = pTch->next;
	}
	fclose(fp);
	return true;
}

bool saveCrs(Cpnode CrsList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败

	Cpnode pCrs = CrsList->next; // 从头结点的下一个节点开始
	while (pCrs != NULL) {
		fwprintf(fp, L"%d %s %s % .1lf %d %.1lf %.2lf %.1lf %.2lf %d %d %.2lf %d %.2lf\n",
			pCrs->cnum,
			pCrs->cname,
			pCrs->character,
			pCrs->credit,
			pCrs->headcount,
			pCrs->totscore,
			pCrs->averscore,
			pCrs->totGPA,
			pCrs->averGPA,
			pCrs->SchYear,
			pCrs->PassNum,
			pCrs->PassRate,
			pCrs->ExcelNum,
			pCrs->ExcelRate
		); // 写入

		Spnode pstu = pCrs->sphead->next; // 从下一个学生节点开始
		while (pstu != NULL) {
			fwprintf(fp, L"%d %s %.1lf %.1lf\n",
				pstu->snum,
				pstu->sname,
				pstu->score,
				pstu->GPA); // 写入

			pstu = pstu->next; // 移动到下一个节点
		}
		fwprintf(fp, L"\n");
		pCrs = pCrs->next; // 移动到下一个节点
	}
	fclose(fp);
	return true;
}

bool exportStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败


	//表头
	fwprintf(fp, L"学号,姓名,性别,年级,学院,专业,原学院,原专业,所有课程平均分,所有课程平均绩点,必修课程平均分,必修课程平均绩点\n");

	List pStu = StuList->next; // 从头结点的下一个节点开始
	while (pStu != NULL) {
		fwprintf(fp, L"%d,%s,%s,%d,%s,%s,%s,%s,%.2lf,%.4lf,%.2lf,%.4lf\n",
			pStu->item.data.ID,
			pStu->item.data.name,
			(pStu->item.data.gender == 1) ? L"男" : L"女",
			pStu->item.data.grade,
			pStu->item.data.college,
			pStu->item.data.major,
			(wcscmp(pStu->item.data.original_college, pStu->item.data.college) == 0 && wcscmp(pStu->item.data.original_major, pStu->item.data.major) == 0) ? L"" : pStu->item.data.original_college,
			(wcscmp(pStu->item.data.original_college, pStu->item.data.college) == 0 && wcscmp(pStu->item.data.original_major, pStu->item.data.major) == 0) ? L"" : pStu->item.data.original_major,

			pStu->item.data.all_avg_score,
			pStu->item.data.all_avg_grid,
			pStu->item.data.req_avg_score,
			pStu->item.data.req_avg_grid

		); // 写入
		pStu = pStu->next; // 移动到下一个节点
	}
	fclose(fp);
	return true;

}

bool exportCrs(Cpnode CrsList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败


	//表头
	fwprintf(fp, L"课程号,课程名,学年,课程性质,学分,总人数,平均成绩,平均绩点,及格人数,及格率,优秀人数,优秀率\n");

	Cpnode pCrs = CrsList->next; // 从头结点的下一个节点开始
	while (pCrs != NULL) {
		fwprintf(fp, L"%d,%s,%d,%s,%.1lf,%d,%.2lf,%.2lf,%d,%.2lf,%d,%.2lf\n",
			pCrs->cnum,
			pCrs->cname,
			pCrs->SchYear,
			pCrs->character,
			pCrs->credit,
			pCrs->headcount,
			pCrs->averscore,
			pCrs->averGPA,
			pCrs->PassNum,
			pCrs->PassRate,
			pCrs->ExcelNum,
			pCrs->ExcelRate
		); // 写入

		pCrs = pCrs->next; // 移动到下一个节点
	}
	fclose(fp);
	return true;
}

void importStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"导入失败, 没有文件或文件被其他程序占用!", L"导入", MB_ICONERROR);
	}//读取失败退出

	int successCnt = 0; //成功次数
	int failCnt = 0; //失败次数
	int failSameIDCnt = 0; //学号相同错误计数
	int failFormatCnt = 0; //格式错误错误计数
	int failDataCnt = 0; //数据错误错误计数

	wchar_t TMPid[100];
	wchar_t TMPname[100];
	wchar_t TMPgender[100];
	wchar_t TMPgrade[100];
	wchar_t TMPcollege[100];
	wchar_t TMPmajor[100];

	int id;
	wchar_t name[30];
	wchar_t gender[10];
	int grade;
	wchar_t college[100];
	wchar_t major[100];

	// 获取当前年份(判断年级要用)
	time_t Current_time = time(NULL);
	int Current_year = localtime(&Current_time)->tm_year + 1900;

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // 跳过表头
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPgender,
			&TMPgrade,
			&TMPcollege,
			&TMPmajor

		) == 6) { // 读取学生信息
			TMPmajor[wcslen(TMPmajor) - 1] = L'\0';

			if (
				getNumberInBox(99999999, &id, TMPid) &&
				getTextInBox(name, TMPname) &&
				getTextInBox(gender, TMPgender) &&
				getNumberInBox(9999, &grade, TMPgrade) &&
				getTextInBox(college, TMPcollege) &&
				getTextInBox(major, TMPmajor) &&
				(id > 9999999 && id < 100000000) &&
				(grade > 1970 && grade <= Current_year) &&
				(!wcscmp(gender, L"男") || (!wcscmp(gender, L"女")))
				) {

				// 学号相同的情况,错误+1
				if (!addStu(&StuList, name, id, wcscmp(gender, L"男") ? 0 : 1, grade, college, major)) {
					failSameIDCnt++;
					failCnt++;
				}
				else {
					successCnt++;
				}
			}
			else {
				failFormatCnt++;
				failCnt++;
			}
		}
		else {
			failDataCnt++;
			failCnt++;
		}
	}
	fclose(fp);
	MessageBox(GetHWnd(), (wstring(L"导入成功")
		+ to_wstring(successCnt) + L"条信息，失败"
		+ to_wstring(failCnt) + L"条信息。\n\n错误详情：\n已有相同学生"
		+ to_wstring(failSameIDCnt) + L"条；\n格式错误"
		+ to_wstring(failFormatCnt) + L"条；\n数据错误"
		+ to_wstring(failDataCnt) + L"条。"
		).c_str(), L"导入文件", MB_SYSTEMMODAL);
}

void importCrs(Cpnode CrsList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"导入失败, 没有文件或文件被其他程序占用!", L"导入", MB_ICONERROR);
	}//读取失败退出

	int successCnt = 0; //成功次数
	int failCnt = 0; //失败次数
	int failSameIDCnt = 0; //课程号相同错误计数
	int failFormatCnt = 0; //格式错误错误计数
	int failDataCnt = 0; //数据错误错误计数

	wchar_t TMPid[100];
	wchar_t TMPname[100];
	wchar_t TMPschYear[100];
	wchar_t TMPcharacter[100];
	wchar_t TMPcredit[100];

	int id;
	wchar_t name[30];
	int SchYear;
	wchar_t character[5];
	double credit;

	// 获取当前年份(判断年级要用)
	time_t Current_time = time(NULL);
	int Current_year = localtime(&Current_time)->tm_year + 1900;

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // 跳过表头
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPschYear,
			&TMPcharacter,
			&TMPcredit
		) == 5) { // 读取学生信息

			TMPcredit[wcslen(TMPcredit) - 1] = L'\0';

			if (
				getNumberInBox(99999, &id, TMPid) &&
				getTextInBox(name, TMPname) &&
				getTextInBox(character, TMPcharacter) &&
				getNumberInBox(9999, &SchYear, TMPschYear) &&
				getDoubleInBox(10, &credit, TMPcredit) &&
				(id > 9999 && id < 100000) &&
				(SchYear > 1970 && SchYear <= Current_year)
				) {

				// 课程号相同的情况,错误+1
				if (!addCrs(CrsList, name, id, character, credit, SchYear)) {
					failSameIDCnt++;
					failCnt++;
				}
				else {
					successCnt++;
				}
			}
			else {
				failFormatCnt++;
				failCnt++;
			}
		}
		else {
			failDataCnt++;
			failCnt++;
		}
	}
	fclose(fp);
	MessageBox(GetHWnd(), (wstring(L"导入成功")
		+ to_wstring(successCnt) + L"条信息，失败"
		+ to_wstring(failCnt) + L"条信息。\n\n错误详情：\n已有相同课程"
		+ to_wstring(failSameIDCnt) + L"条；\n格式错误"
		+ to_wstring(failFormatCnt) + L"条；\n数据错误"
		+ to_wstring(failDataCnt) + L"条。"
		).c_str(), L"导入文件", MB_SYSTEMMODAL);
}



bool exportTch(List TchList, const char* file_name) { //导出教师信息
	FILE* fp;
	fp = fopen(file_name, "w"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//打开失败


	//表头
	fwprintf(fp, L"工号,姓名,性别,学院\n");

	List pTch = TchList->next; // 从头结点的下一个节点开始
	while (pTch != NULL) {
		fwprintf(fp, L"%d,%s,%s,%s\n",
			pTch->item.data.ID,
			pTch->item.data.name,
			(pTch->item.data.gender == 1) ? L"男" : L"女",
			pTch->item.data.college
		); // 写入
		pTch = pTch->next; // 移动到下一个节点
	}
	fclose(fp);
	return true;

}


void importTch(List TchList, const char* file_name) { //导入教师信息
	FILE* fp;
	fp = fopen(file_name, "r");//读取文件
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"导入失败, 没有文件或文件被其他程序占用!", L"导入", MB_ICONERROR);
		return;
	}//读取失败退出

	int successCnt = 0; //成功次数
	int failCnt = 0; //失败次数
	int failSameIDCnt = 0; //学号相同错误计数
	int failFormatCnt = 0; //格式错误错误计数
	int failDataCnt = 0; //数据错误错误计数

	wchar_t TMPid[100];
	wchar_t TMPname[100];
	wchar_t TMPgender[100];
	wchar_t TMPcollege[100];

	int id;
	wchar_t name[30];
	wchar_t gender[10];
	wchar_t college[100];

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // 跳过表头
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPgender,
			&TMPcollege

		) == 4) { // 读取学生信息
			TMPcollege[wcslen(TMPcollege) - 1] = L'\0';

			if (
				getNumberInBox(99999999, &id, TMPid) &&
				getTextInBox(name, TMPname) &&
				getTextInBox(gender, TMPgender) &&
				getTextInBox(college, TMPcollege) &&
				(id > 9999999 && id < 100000000) &&
				(!wcscmp(gender, L"男") || (!wcscmp(gender, L"女")))
				) {

				// 工号相同的情况,错误+1
				wchar_t noMajor[10] = L"无";
				if (!addStu(&TchList, name, id, wcscmp(gender, L"男") ? 0 : 1, 2024, college, noMajor)) {
					failSameIDCnt++;
					failCnt++;
				}
				else {
					successCnt++;
				}
			}
			else {
				failFormatCnt++;
				failCnt++;
			}
		}
		else {
			failDataCnt++;
			failCnt++;
		}
	}
	fclose(fp);
	MessageBox(GetHWnd(), (wstring(L"导入成功")
		+ to_wstring(successCnt) + L"条信息，失败"
		+ to_wstring(failCnt) + L"条信息。\n\n错误详情：\n已有相同教师"
		+ to_wstring(failSameIDCnt) + L"条；\n格式错误"
		+ to_wstring(failFormatCnt) + L"条；\n数据错误"
		+ to_wstring(failDataCnt) + L"条。"
		).c_str(), L"导入文件", MB_SYSTEMMODAL);
}


void writeLog(int operatorPeople, Node* person, wstring log) { //写入日志
	FILE* fp;
	char file_name[50] = ".\\log\\Log.log";
	fp = fopen(file_name, "a"); // 打开文件
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//打开失败

	// 获取当前时间
	time_t now;
	time(&now);

	// 将时间转换为本地时间
	struct tm* local_time = localtime(&now);

	// 将时间转换为字符串
	wchar_t time_str[256]; // 假设时间字符串最大长度为100
	wcsftime(time_str, sizeof(time_str), L"[%Y-%m-%d %H:%M:%S] ", local_time);
	//wprintf(L"当前时间：%s\n", time_str);

	if (operatorPeople == 1) {
		fwprintf(fp, (wstring(time_str) + L"教师 " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
	}
	if (operatorPeople == 2 || operatorPeople == 3 || operatorPeople == 4) {
		fwprintf(fp, (wstring(time_str) + L"管理员 " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
	}
	if (operatorPeople == 0) {
		fwprintf(fp, (wstring(time_str) + L"学生 " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
	}
	fclose(fp);

}



void freeStu(List StuList) {
	Node* plist = StuList->next;
	Node* freeList = plist;
	while (plist) {

		Crsnode* pcrs = plist->item.crslist;
		Crsnode* freeCrsN = pcrs;
		while (pcrs) {
			pcrs = pcrs->crs_next;
			free(freeCrsN);
			freeCrsN = pcrs;
		}

		Cnode* pc = plist->item.clist;
		Cnode* freeC = pc;
		while (pc) {
			pc = pc->cnext;
			free(freeC);
			freeC = pc;
		}

		Rnode* pr = plist->item.rlist;
		Rnode* freeR = pr;
		while (pr) {
			pr = pr->rnext;
			free(freeR);
			freeR = pr;
		}


		plist = plist->next;
		free(freeList);
		freeList = plist;
	}
}

void freeCrs(Cpnode CrsList) {
	Cpnode plist = CrsList->next;
	Cpnode freeList = plist;
	while (plist) {

		Spnode pstu = plist->sphead;
		Spnode freeStuN = pstu;
		while (pstu) {
			pstu = pstu->next;
			free(freeStuN);
			freeStuN = pstu;
		}

		plist = plist->next;
		free(freeList);
		freeList = plist;
	}
}



