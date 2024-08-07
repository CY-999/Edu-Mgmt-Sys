#pragma once

#ifndef _STUDENT_H_
#define _STUDENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <graphics.h>
#include <string>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <sysinfoapi.h>
#include <tchar.h>
#include <math.h>
#include <time.h>
#include "io.h"

using namespace std;



struct student_data
{
	wchar_t name[30];//����
	int ID;//ѧ��
	int gender;//�Ա�
	int grade;//�꼶
	wchar_t college[100];//ѧԺ
	wchar_t major[100];//רҵ

	wchar_t original_college[100];//ԭѧԺ(�½�ѧ���Ļ���college��ͬ)
	wchar_t original_major[100]; //ԭרҵ(�½�ѧ���Ļ���major��ͬ)

	double all_avg_score; //���м�Ȩƽ����
	double all_avg_grid; //���м�Ȩƽ������
	double req_avg_score; //���޼�Ȩƽ����
	double req_avg_grid; //���޼�Ȩƽ������

	wchar_t password[100]; //����(�½�ѧ���Ļ�Ϊѧ��,Ҫת������)
};

struct score_info {
	wchar_t course_id[10];//�γ̺�
	wchar_t course_name[100];//�γ���
	double score;//�γ̳ɼ�
	int semester;//ѧ��ѧ��
	//wchar_t course_category[50]; //�γ����
	int course_nature;//�γ�����
	double credit;//ѧ��
	double grid;//����
	//int score_type;//�ɼ�����
	//wchar_t remark[1024];//��ע
	//struct score_info* sco_next;
};

struct quality_projects_research {//���гɹ�
	wchar_t paper_name[200];//��������
	wchar_t journal_or_conference_name[200];//��������ڿ����������
	wchar_t author[200];// ����������Ƿ�ΪͨѶ���߼���������
	wchar_t date[200];// ��������
	wchar_t volume_num[200];// ����
	wchar_t issue_num[200];// ����
	wchar_t page[200];// ҳ�뷶Χ
	double GPA_bonus;
};

struct quality_projects_competition {//������
	wchar_t competition_name[200];//��������
	wchar_t organizer[200];//�ٰ쵥λ
	wchar_t category[200];//�����
	wchar_t date[200];//��ʱ�� ����
	double GPA_bonus;
};


typedef struct student_data Data;
typedef struct score_info Score;
typedef struct quality_projects_research Research;
typedef struct quality_projects_competition Competition;


typedef struct course_list{//ѧ���γ�����ڵ�
	Score score;
	struct course_list* crs_next;
}Crsnode;

typedef struct research_list {//���гɹ�����ڵ�
	Research research;
	struct research_list* rnext;
}Rnode;

typedef struct competition_list {//����������ڵ�
	Competition competition;
	struct competition_list* cnext;
}Cnode;

typedef struct item {//һ��ѧ������߱���ȫ����Ϣ��������� ��������Ŀ�ɹ��������С�飩
	Data data;

	Crsnode* crslist;//�γ�����

	Rnode* rlist; //���гɹ�����
	Cnode* clist;//����������
}Item;


typedef struct node {  //�ڵ�
	Item item;
	struct node* next;
}Node;
typedef Node* List; //����



bool showAllStu(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm); // ��ʾ����ѧ����Ϣ���������γ̣�

void showStu(const Node* stu, vector<vector<wstring>>& data, const wchar_t* searchTerm); // ��ʾ����ѧ����Ϣ��������γ̳ɼ���

void Rank(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm, const wchar_t* searchTerm2, int* number);

//bool Initialize_Stu_Crslist(List);//��ʼ��ÿ��ѧ���Ŀγ�����

double AllGrid(Node* crss);

double MustGrid(Node* crss);

double AllScore(Node* Crs);

double MustScore(Node* Crs);

bool addStu(List* plist,wchar_t* pname, int pID, int pgender, int pgrade, wchar_t* pcollege, wchar_t* pmajor); // ���ѧ�����������γ̣�

bool addCrsToStu(Node* chastu, const wchar_t* pcourse_id, const wchar_t* pcourse_name, double pscore, int psemester, int pcourse_nature, double pcredit, double pgrid);// Ϊĳ��ѧ�����ĳ�γ̼��ɼ�

void sortStuaccID(List* plist);// ������ѧ������

void sortStuCrsYear(Crsnode* plist);

void sortStuaccyear(List* plist);

bool modifyStu(List* plist, Node* chastu, wchar_t* pname, int pID, int pgender, int pgrade, wchar_t* pcollege, wchar_t* pmajor);// �޸�ѧ����Ϣ�����޸Ŀγ̣�

bool modifyCrsInStu(Crsnode* chacrs, wchar_t* pcourse_id, wchar_t* pcourse_name, double pscore, int psemester, int pcourse_nature, double pcredit, double pgrid); // �޸�ĳ��ѧ����ĳ�γ̼��ɼ�


bool deleteStu(List* plist,Node* delstu); // ɾ��ѧ��


bool deleteCrsInStu(Node* delstu, Crsnode* delcrs); // ɾ��ĳ��ѧ����ĳ�γ̼��ɼ�


Node* searchStu(List* plist, wchar_t* pname, int pID); // ����ѧ������������ѧ��


Crsnode* searchCrsInStu(Node* stu, const wchar_t* pcourse_id,const wchar_t* pcourse_name); // �ڵ���ѧ����������γ�











#endif
