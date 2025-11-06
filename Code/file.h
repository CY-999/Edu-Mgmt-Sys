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


List readStu(const char* file_name); //读取学生文件

List readTch(const char* file_name); //读取教师文件

List readAdmin(const char* file_name);//读取管理员端文件

Cpnode readCrs(const char* file_name); //读取课程文件


bool saveStu(List StuList, const char* file_name); //保存学生文件

bool saveTch(List TchList, const char* file_name);//保存教师文件


bool saveCrs(Cpnode CrsList, const char* file_name); //保存课程文件


bool exportStu(List StuList, const char* file_name); //导出学生信息


bool exportCrs(Cpnode CrsList, const char* file_name); //导出课程信息


void importStu(List StuList, const char* file_name); //导入学生信息


void importCrs(Cpnode CrsList, const char* file_name); //导入课程信息


void writeLog(int operatorPeople, Node* person, wstring log); //写入日志



bool exportTch(List TchList, const char* file_name); //导出教师信息


void importTch(List TchList, const char* file_name); //导入教师信息


void freeStu(List StuList);

void freeCrs(Cpnode CrsList);






#endif
