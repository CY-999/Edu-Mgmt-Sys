#pragma once
#pragma warning(disable:4996)

#ifndef _QUALITY_H_
#define _QUALITY_H_

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
#include"student.h"
#include"io.h"
#include"ui.h"

using namespace std;

bool showAllTch(const List TchList, vector<vector<wstring>>& data, const wchar_t* searchTerm);

bool ShowStu_Password(const List Sp_List, vector<vector<wstring>>& data, const wchar_t* searchTerm);

bool ShowTch_Password(const List Tp_List, vector<vector<wstring>>& data, const wchar_t* searchTerm);

bool ShowAllStu_with_quality(const List StuList, vector<vector<wstring>>& data, const wchar_t* searchTerm);

bool ShowStu_Research(const Node* Stu, vector<vector<wstring>>& data);
bool ShowStu_Competition(const Node* Stu, vector<vector<wstring>>& data);


Node* searchStu_InQuality(List,wchar_t*);// 在总链表中搜索学生(lzy调试专用


bool addQuality_rlist(Node* Stu,	// 添加素质类项目
	wchar_t* paper_name, 
	wchar_t* journal_or_conference_name, 
	wchar_t* author, 
	wchar_t* date, 
	wchar_t* volume_num, 
	wchar_t* issue_num, 
	wchar_t* page, 
	double GPA_bonus);
bool addQuality_clist(Node* Stu,
	wchar_t* competition_name,
	wchar_t* organizer,
	wchar_t* category,
	wchar_t* date,
	double GPA_bonus);

/*void show_Research_menu(const wchar_t* title, Rnode* rhead);//方便修改时确认所需处理的素质类节点
void show_Competition_menu(const wchar_t* title, Cnode* chead);*/


//Node* searchStu_with_thisRnode(List* StuList,  wchar_t* paper_name);// 找出此学生待修改的素质类项目节点
Rnode* searchRnode_in_thisStu(Node* Stu,  wchar_t* paper_name);

Cnode* searchCnode_in_thisStu(Node* Stu, wchar_t* competition_name);


bool modifyQuality_rlist(Rnode* rmod,// 修改素质类项目
	wchar_t* paper_name,
	wchar_t* journal_or_conference_name,
	wchar_t* author,
	wchar_t* date,
	wchar_t* volume_num,
	wchar_t* issue_num,
	wchar_t* page,
	double GPA_bonus);
bool modifyQuality_clist(Cnode* cmod,
	wchar_t* competition_name,
	wchar_t* organizer,
	wchar_t* category,
	wchar_t* date,
	double GPA_bonus);


bool deleteQuality_rlist(Node* Stu, wchar_t* paper_name);// 删除素质类项目
bool deleteQuality_clist(Node* Stu, wchar_t* competition_name);












#endif
