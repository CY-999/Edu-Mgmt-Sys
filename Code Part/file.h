#pragma once

#ifndef _FILE_H_
#define _FILE_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <tchar.h>
#include <time.h>
#include "student.h"
#include "course.h"


List readStu(const char* file_name); //��ȡѧ���ļ�

List readTch(const char* file_name); //��ȡ��ʦ�ļ�

List readAdmin(const char* file_name);//��ȡ����Ա���ļ�

Cpnode readCrs(const char* file_name); //��ȡ�γ��ļ�


bool saveStu(List StuList, const char* file_name); //����ѧ���ļ�

bool saveTch(List TchList, const char* file_name);//�����ʦ�ļ�


bool saveCrs(Cpnode CrsList, const char* file_name); //����γ��ļ�


bool exportStu(List StuList, const char* file_name); //����ѧ����Ϣ


bool exportCrs(Cpnode CrsList, const char* file_name); //�����γ���Ϣ


void importStu(List StuList, const char* file_name); //����ѧ����Ϣ


void importCrs(Cpnode CrsList, const char* file_name); //����γ���Ϣ


void writeLog(int operatorPeople, Node* person, wstring log); //д����־



bool exportTch(List TchList, const char* file_name); //������ʦ��Ϣ


void importTch(List TchList, const char* file_name); //�����ʦ��Ϣ


void freeStu(List StuList);

void freeCrs(Cpnode CrsList);






#endif
