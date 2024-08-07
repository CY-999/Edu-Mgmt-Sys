#pragma warning(disable:4996)

#include "file.h"



List readStu(const char* file_name) {
	FILE* fp;
	List StuList = (List)malloc(sizeof(Node));
	StuList->next = NULL;
	//StuList->item.crslist = (Crsnode*)malloc(sizeof(Crsnode));
	//StuList->item.crslist->crs_next = NULL;

	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//��ȡʧ���˳�

	List tnode = (List)malloc(sizeof(Node)); //Ϊtnode�����ڴ�(��ʱ���)
	tnode->next = NULL;
	Crsnode* tcrs = (Crsnode*)malloc(sizeof(Crsnode)); //Ϊtcrs�����ڴ�(��ʱ���)
	tcrs->crs_next = NULL;
	Rnode* trnode = (Rnode*)malloc(sizeof(Rnode)); //Ϊtrnode�����ڴ�(��ʱ���)
	trnode->rnext = NULL;
	Cnode* tcnode = (Cnode*)malloc(sizeof(Cnode)); //Ϊtcnode�����ڴ�(��ʱ���)
	tcnode->cnext = NULL;


	if (tnode == NULL || tcrs == NULL || trnode == NULL || tcnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// ����ʧ��

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') { // ��������
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

		) == 13) { // ��ȡѧ����Ϣ





			tnode->item.crslist = (Crsnode*)malloc(sizeof(Crsnode)); //Ϊһ��crslist�����ڴ�(��ӵ������е�crslist)
			if (tnode->item.crslist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			tnode->item.crslist->crs_next = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // ��������
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
				) == 7) { // ��ȡ�γ���Ϣ

					// ��ӵ�����
					Crsnode* crsnode = (Crsnode*)malloc(sizeof(Crsnode)); //Ϊcrsnode�����ڴ�(��ӵ������е�crsnode)
					if (crsnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// ����ʧ��
					memcpy(crsnode, tcrs, sizeof(Crsnode));
					Crsnode* ptmp = tnode->item.crslist;
					while (ptmp->crs_next != NULL) {
						ptmp = ptmp->crs_next;
					}
					ptmp->crs_next = crsnode;
				}
			}



			tnode->item.rlist = (Rnode*)malloc(sizeof(Rnode)); //Ϊһ��rlist�����ڴ�(��ӵ������е�rlist)
			if (tnode->item.rlist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			tnode->item.rlist->rnext = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // ��������
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
				) == 8) { // ��ȡ���гɹ���Ϣ

					// ��ӵ�����
					Rnode* resnode = (Rnode*)malloc(sizeof(Rnode)); //Ϊresnode�����ڴ�(��ӵ������е�resnode)
					if (resnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// ����ʧ��
					memcpy(resnode, trnode, sizeof(Rnode));
					Rnode* ptmp = tnode->item.rlist;
					while (ptmp->rnext != NULL) {
						ptmp = ptmp->rnext;
					}
					ptmp->rnext = resnode;
				}
			}





			tnode->item.clist = (Cnode*)malloc(sizeof(Cnode)); //Ϊһ��clist�����ڴ�(��ӵ������е�clist)
			if (tnode->item.clist == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			tnode->item.clist->cnext = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
				if (line[0] == '\n') { // ��������
					break;
				}
				if (swscanf(line, L"%s %s %s %s %lf",
					&tcnode->competition.competition_name,
					&tcnode->competition.organizer,
					&tcnode->competition.category,
					&tcnode->competition.date,
					&tcnode->competition.GPA_bonus
				) == 5) { // ��ȡ��������Ϣ

					// ��ӵ�����
					Cnode* cptnode = (Cnode*)malloc(sizeof(Cnode)); //Ϊcptnode�����ڴ�(��ӵ������е�cptnode)
					if (cptnode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// ����ʧ��
					memcpy(cptnode, tcnode, sizeof(Cnode));
					Cnode* ptmp = tnode->item.clist;
					while (ptmp->cnext != NULL) {
						ptmp = ptmp->cnext;
					}
					ptmp->cnext = cptnode;
				}
			}







			// ��ӵ�����
			List Coursenode = (List)malloc(sizeof(Node)); //ΪCoursenode�����ڴ�(��ӵ������е�Coursenode)
			if (Coursenode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
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
	List TchList = (List)malloc(sizeof(Node));//������ʦ����
	TchList->next = NULL;

	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//��ȡʧ���˳�

	Node* Tchnode = (Node*)malloc(sizeof(Node));//�ڱ��ڵ�
	Tchnode->next = NULL;


	if (Tchnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// ����ʧ��

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') {//��������
			continue;
		}

		if (swscanf(line, L"%d %s %d %s %s",
			&Tchnode->item.data.ID,
			&Tchnode->item.data.name,
			&Tchnode->item.data.gender,
			&Tchnode->item.data.college,
			&Tchnode->item.data.password) == 5) { //��ȡ��ʦ��Ϣ

			// ��ӵ�����
			List Tmpnode = (List)malloc(sizeof(Node));
			if (Tmpnode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			memcpy(Tmpnode, Tchnode, sizeof(Node));//��Tchnode�ڵ�ȫ�����ݶ�����һ�ݵ�Tmpnode,����next
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
	List admin_List = (List)malloc(sizeof(Node));//��������Ա����
	admin_List->next = NULL;

	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//��ȡʧ���˳�

	Node* admin_node = (Node*)malloc(sizeof(Node));//�ڱ��ڵ�
	admin_node->next = NULL;


	if (admin_node == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// ����ʧ��

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (line[0] == '\n') {//��������
			continue;
		}

		if (swscanf(line, L"%d %s %s",
			&admin_node->item.data.ID,
			&admin_node->item.data.name,
			&admin_node->item.data.password) == 3) { //��ȡ����Ա��Ϣ

			// ��ӵ�����
			List Tmpnode = (List)malloc(sizeof(Node));
			if (Tmpnode == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			memcpy(Tmpnode, admin_node, sizeof(Node));//��admin_node�ڵ�ȫ�����ݶ�����һ�ݵ�Tmpnode,����next
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

	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Write to \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//��ȡʧ���˳�

	Cpnode tcnode = (Cpnode)malloc(sizeof(_Cnode)); //Ϊtcnode�����ڴ�(�����ʱ��Cpnode)
	tcnode->next = NULL;
	Spnode tsnode = (Spnode)malloc(sizeof(Snode)); //Ϊtsnode�����ڴ�(�����ʱ��Spnode)
	tsnode->next = NULL;
	if (tcnode == NULL || tsnode == NULL) {
		wprintf(L"error!");
		exit(EXIT_FAILURE);
	}// ����ʧ��

	wchar_t line[512];
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL)
	{
		if (line[0] == '\n')
		{ // ��������
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
		{ // ��ȡ�γ���Ϣ

			tcnode->sphead = (Spnode)malloc(sizeof(Snode));//Ϊһ��sphead�����ڴ�(��ӵ������е�sphead)
			if (tcnode->sphead == NULL) {
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			tcnode->sphead->next = NULL;

			while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL)
			{
				if (line[0] == '\n') { // ��������
					break;
				}
				if (swscanf(line, L"%d %s %lf %lf",
					&tsnode->snum,
					&tsnode->sname,
					&tsnode->score,
					&tsnode->GPA
				) == 4) { // ��ȡѧ����Ϣ
					tsnode->next = NULL;

					// ��ӵ�����
					Spnode snode = (Spnode)malloc(sizeof(Snode)); //Ϊsnode�����ڴ�(��ӵ������е�snode)
					if (snode == NULL) {
						wprintf(L"error!");
						exit(EXIT_FAILURE);
					}// ����ʧ��
					memcpy(snode, tsnode, sizeof(Snode));
					Spnode ptmp = tcnode->sphead;
					while (ptmp->next != NULL) {
						ptmp = ptmp->next;
					}
					ptmp->next = snode;


				}
			}

			// ��ӵ�����
			Cpnode cnode = (Cpnode)malloc(sizeof(_Cnode)); //Ϊcnode�����ڴ�(��ӵ������е�cnode)
			if (cnode == NULL)
			{
				wprintf(L"error!");
				exit(EXIT_FAILURE);
			}// ����ʧ��
			memcpy(cnode, tcnode, sizeof(_Cnode));
			Cpnode ptmp = CrsList;
			while (ptmp->next != NULL)
			{
				ptmp = ptmp->next;
			}
			ptmp->next = cnode;

			CalculNumOfCrs(1);//�޸ģ���ɾ;����һ���ж��ٿγ�
		}
	}
	free(tcnode);
	free(tsnode);
	fclose(fp);
	return CrsList;



}

bool saveStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��

	List pStu = StuList->next; // ��ͷ������һ���ڵ㿪ʼ
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

		); // д��

		Crsnode* pcrs = pStu->item.crslist->crs_next; // ����һ���γ̽ڵ㿪ʼ
		while (pcrs != NULL) {
			fwprintf(fp, L"%s %s %.1lf %d %d %.1lf %.1lf\n",
				pcrs->score.course_id,
				pcrs->score.course_name,
				pcrs->score.score,
				pcrs->score.semester,
				pcrs->score.course_nature,
				pcrs->score.credit,
				pcrs->score.grid); // д��

			pcrs = pcrs->crs_next; // �ƶ�����һ���ڵ�
		}
		fwprintf(fp, L"\n");


		Rnode* pres = pStu->item.rlist->rnext; // ����һ�����гɹ��ڵ㿪ʼ
		while (pres != NULL) {
			fwprintf(fp, L"%s %s %s %s %s %s %s %.2lf\n",
				pres->research.paper_name,
				pres->research.journal_or_conference_name,
				pres->research.author,
				pres->research.date,
				pres->research.volume_num,
				pres->research.issue_num,
				pres->research.page,
				pres->research.GPA_bonus); // д��

			pres = pres->rnext; // �ƶ�����һ���ڵ�
		}
		fwprintf(fp, L"\n");


		Cnode* pcpt = pStu->item.clist->cnext; // ����һ�������񽱽ڵ㿪ʼ
		while (pcpt != NULL) {
			fwprintf(fp, L"%s %s %s %s %.2lf\n",
				pcpt->competition.competition_name,
				pcpt->competition.organizer,
				pcpt->competition.category,
				pcpt->competition.date,
				pcpt->competition.GPA_bonus); // д��

			pcpt = pcpt->cnext; // �ƶ�����һ���ڵ�
		}
		fwprintf(fp, L"\n");



		pStu = pStu->next; // �ƶ�����һ���ڵ�
	}
	fclose(fp);
	return true;
}

bool saveTch(List TchList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��

	List pTch = TchList->next; // ��ͷ������һ���ڵ㿪ʼ

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
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��

	Cpnode pCrs = CrsList->next; // ��ͷ������һ���ڵ㿪ʼ
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
		); // д��

		Spnode pstu = pCrs->sphead->next; // ����һ��ѧ���ڵ㿪ʼ
		while (pstu != NULL) {
			fwprintf(fp, L"%d %s %.1lf %.1lf\n",
				pstu->snum,
				pstu->sname,
				pstu->score,
				pstu->GPA); // д��

			pstu = pstu->next; // �ƶ�����һ���ڵ�
		}
		fwprintf(fp, L"\n");
		pCrs = pCrs->next; // �ƶ�����һ���ڵ�
	}
	fclose(fp);
	return true;
}

bool exportStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��


	//��ͷ
	fwprintf(fp, L"ѧ��,����,�Ա�,�꼶,ѧԺ,רҵ,ԭѧԺ,ԭרҵ,���пγ�ƽ����,���пγ�ƽ������,���޿γ�ƽ����,���޿γ�ƽ������\n");

	List pStu = StuList->next; // ��ͷ������һ���ڵ㿪ʼ
	while (pStu != NULL) {
		fwprintf(fp, L"%d,%s,%s,%d,%s,%s,%s,%s,%.2lf,%.4lf,%.2lf,%.4lf\n",
			pStu->item.data.ID,
			pStu->item.data.name,
			(pStu->item.data.gender == 1) ? L"��" : L"Ů",
			pStu->item.data.grade,
			pStu->item.data.college,
			pStu->item.data.major,
			(wcscmp(pStu->item.data.original_college, pStu->item.data.college) == 0 && wcscmp(pStu->item.data.original_major, pStu->item.data.major) == 0) ? L"" : pStu->item.data.original_college,
			(wcscmp(pStu->item.data.original_college, pStu->item.data.college) == 0 && wcscmp(pStu->item.data.original_major, pStu->item.data.major) == 0) ? L"" : pStu->item.data.original_major,

			pStu->item.data.all_avg_score,
			pStu->item.data.all_avg_grid,
			pStu->item.data.req_avg_score,
			pStu->item.data.req_avg_grid

		); // д��
		pStu = pStu->next; // �ƶ�����һ���ڵ�
	}
	fclose(fp);
	return true;

}

bool exportCrs(Cpnode CrsList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��


	//��ͷ
	fwprintf(fp, L"�γ̺�,�γ���,ѧ��,�γ�����,ѧ��,������,ƽ���ɼ�,ƽ������,��������,������,��������,������\n");

	Cpnode pCrs = CrsList->next; // ��ͷ������һ���ڵ㿪ʼ
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
		); // д��

		pCrs = pCrs->next; // �ƶ�����һ���ڵ�
	}
	fclose(fp);
	return true;
}

void importStu(List StuList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"����ʧ��, û���ļ����ļ�����������ռ��!", L"����", MB_ICONERROR);
	}//��ȡʧ���˳�

	int successCnt = 0; //�ɹ�����
	int failCnt = 0; //ʧ�ܴ���
	int failSameIDCnt = 0; //ѧ����ͬ�������
	int failFormatCnt = 0; //��ʽ����������
	int failDataCnt = 0; //���ݴ���������

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

	// ��ȡ��ǰ���(�ж��꼶Ҫ��)
	time_t Current_time = time(NULL);
	int Current_year = localtime(&Current_time)->tm_year + 1900;

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // ������ͷ
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPgender,
			&TMPgrade,
			&TMPcollege,
			&TMPmajor

		) == 6) { // ��ȡѧ����Ϣ
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
				(!wcscmp(gender, L"��") || (!wcscmp(gender, L"Ů")))
				) {

				// ѧ����ͬ�����,����+1
				if (!addStu(&StuList, name, id, wcscmp(gender, L"��") ? 0 : 1, grade, college, major)) {
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
	MessageBox(GetHWnd(), (wstring(L"����ɹ�")
		+ to_wstring(successCnt) + L"����Ϣ��ʧ��"
		+ to_wstring(failCnt) + L"����Ϣ��\n\n�������飺\n������ͬѧ��"
		+ to_wstring(failSameIDCnt) + L"����\n��ʽ����"
		+ to_wstring(failFormatCnt) + L"����\n���ݴ���"
		+ to_wstring(failDataCnt) + L"����"
		).c_str(), L"�����ļ�", MB_SYSTEMMODAL);
}

void importCrs(Cpnode CrsList, const char* file_name) {
	FILE* fp;
	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"����ʧ��, û���ļ����ļ�����������ռ��!", L"����", MB_ICONERROR);
	}//��ȡʧ���˳�

	int successCnt = 0; //�ɹ�����
	int failCnt = 0; //ʧ�ܴ���
	int failSameIDCnt = 0; //�γ̺���ͬ�������
	int failFormatCnt = 0; //��ʽ����������
	int failDataCnt = 0; //���ݴ���������

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

	// ��ȡ��ǰ���(�ж��꼶Ҫ��)
	time_t Current_time = time(NULL);
	int Current_year = localtime(&Current_time)->tm_year + 1900;

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // ������ͷ
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPschYear,
			&TMPcharacter,
			&TMPcredit
		) == 5) { // ��ȡѧ����Ϣ

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

				// �γ̺���ͬ�����,����+1
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
	MessageBox(GetHWnd(), (wstring(L"����ɹ�")
		+ to_wstring(successCnt) + L"����Ϣ��ʧ��"
		+ to_wstring(failCnt) + L"����Ϣ��\n\n�������飺\n������ͬ�γ�"
		+ to_wstring(failSameIDCnt) + L"����\n��ʽ����"
		+ to_wstring(failFormatCnt) + L"����\n���ݴ���"
		+ to_wstring(failDataCnt) + L"����"
		).c_str(), L"�����ļ�", MB_SYSTEMMODAL);
}



bool exportTch(List TchList, const char* file_name) { //������ʦ��Ϣ
	FILE* fp;
	fp = fopen(file_name, "w"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		return false;
		exit(EXIT_FAILURE);
	}//��ʧ��


	//��ͷ
	fwprintf(fp, L"����,����,�Ա�,ѧԺ\n");

	List pTch = TchList->next; // ��ͷ������һ���ڵ㿪ʼ
	while (pTch != NULL) {
		fwprintf(fp, L"%d,%s,%s,%s\n",
			pTch->item.data.ID,
			pTch->item.data.name,
			(pTch->item.data.gender == 1) ? L"��" : L"Ů",
			pTch->item.data.college
		); // д��
		pTch = pTch->next; // �ƶ�����һ���ڵ�
	}
	fclose(fp);
	return true;

}


void importTch(List TchList, const char* file_name) { //�����ʦ��Ϣ
	FILE* fp;
	fp = fopen(file_name, "r");//��ȡ�ļ�
	if (fp == NULL) {
		printf("Read \"%s\" error, please check and reboot the system!", file_name);
		MessageBox(GetHWnd(), L"����ʧ��, û���ļ����ļ�����������ռ��!", L"����", MB_ICONERROR);
		return;
	}//��ȡʧ���˳�

	int successCnt = 0; //�ɹ�����
	int failCnt = 0; //ʧ�ܴ���
	int failSameIDCnt = 0; //ѧ����ͬ�������
	int failFormatCnt = 0; //��ʽ����������
	int failDataCnt = 0; //���ݴ���������

	wchar_t TMPid[100];
	wchar_t TMPname[100];
	wchar_t TMPgender[100];
	wchar_t TMPcollege[100];

	int id;
	wchar_t name[30];
	wchar_t gender[10];
	wchar_t college[100];

	wchar_t line[512];
	fgetws(line, sizeof(line) / sizeof(line[0]), fp); // ������ͷ
	while (fgetws(line, sizeof(line) / sizeof(line[0]), fp) != NULL) {
		if (swscanf(line, L"%[^,],%[^,],%[^,],%[^,]",
			&TMPid,
			&TMPname,
			&TMPgender,
			&TMPcollege

		) == 4) { // ��ȡѧ����Ϣ
			TMPcollege[wcslen(TMPcollege) - 1] = L'\0';

			if (
				getNumberInBox(99999999, &id, TMPid) &&
				getTextInBox(name, TMPname) &&
				getTextInBox(gender, TMPgender) &&
				getTextInBox(college, TMPcollege) &&
				(id > 9999999 && id < 100000000) &&
				(!wcscmp(gender, L"��") || (!wcscmp(gender, L"Ů")))
				) {

				// ������ͬ�����,����+1
				wchar_t noMajor[10] = L"��";
				if (!addStu(&TchList, name, id, wcscmp(gender, L"��") ? 0 : 1, 2024, college, noMajor)) {
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
	MessageBox(GetHWnd(), (wstring(L"����ɹ�")
		+ to_wstring(successCnt) + L"����Ϣ��ʧ��"
		+ to_wstring(failCnt) + L"����Ϣ��\n\n�������飺\n������ͬ��ʦ"
		+ to_wstring(failSameIDCnt) + L"����\n��ʽ����"
		+ to_wstring(failFormatCnt) + L"����\n���ݴ���"
		+ to_wstring(failDataCnt) + L"����"
		).c_str(), L"�����ļ�", MB_SYSTEMMODAL);
}


void writeLog(int operatorPeople, Node* person, wstring log) { //д����־
	FILE* fp;
	char file_name[50] = ".\\log\\Log.log";
	fp = fopen(file_name, "a"); // ���ļ�
	if (fp == NULL) {
		printf("Write \"%s\" error, please check and reboot the system!", file_name);
		exit(EXIT_FAILURE);
	}//��ʧ��

	// ��ȡ��ǰʱ��
	time_t now;
	time(&now);

	// ��ʱ��ת��Ϊ����ʱ��
	struct tm* local_time = localtime(&now);

	// ��ʱ��ת��Ϊ�ַ���
	wchar_t time_str[256]; // ����ʱ���ַ�����󳤶�Ϊ100
	wcsftime(time_str, sizeof(time_str), L"[%Y-%m-%d %H:%M:%S] ", local_time);
	//wprintf(L"��ǰʱ�䣺%s\n", time_str);

	if (operatorPeople == 1) {
		fwprintf(fp, (wstring(time_str) + L"��ʦ " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
	}
	if (operatorPeople == 2 || operatorPeople == 3 || operatorPeople == 4) {
		fwprintf(fp, (wstring(time_str) + L"����Ա " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
	}
	if (operatorPeople == 0) {
		fwprintf(fp, (wstring(time_str) + L"ѧ�� " + to_wstring(person->item.data.ID) + L" (" + person->item.data.name + L") " + log + L"\n").c_str());
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



