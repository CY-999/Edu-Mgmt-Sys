#include "io.h"


int getNumber(int max) { //0��ͷ���� TODO
	wprintf(L">>> ");//��ʾ����

	wchar_t line[1024];
	fgetws(line, sizeof(line) / sizeof(line[0]), stdin);
	line[_tcslen(line) - 1] = '\0';

	if (!_tcscmp(line, L"\0")) {
		return getNumber(max);
	}//û����Ͱ��˻س�

	//wchar_t ch;
	int command = 0;
	int err = 1;
	int is_num = 0;
	int is_continue = 1;
	int is_all_space = 1;

	for (int i = 0; i < _tcslen(line); i++) {
		//for (int i = 0; line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'); i++) {
		err = 0;
		if (!(line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'))) {
			err = 1;
			is_all_space = 0;
			break;
		}//������ֱ�Ӵ���
		if (line[i] == ' ') {
			if (is_num == 0) {
				continue;
			}
			is_continue = 0;
			continue;
		}//ȥ���ո�
		if (is_continue == 1) {
			command = command * 10 + line[i] - '0';//ƴ������
			is_num = 1;
			is_all_space = 0;
		}
		else {
			err = 1;
			break;
		}
		if (command > max) {
			err = 1;
			break;
		}//������
	}

	if (is_all_space == 1)
	{
		return getNumber(max);
	}//��������ȫ�ǿո�

	if (err == 0) {
		return command;
	}
	else {
		//printf(L"�������ݲ��Ϸ������������룡\n");
		wprintf(L"\"%s\" �������ݲ��Ϸ������������룡\n", line);
		return getNumber(max);
	}

}


double getDouble(double max) //�⺯���е�bug����֮��ĸ�
{
	fflush(stdin);
	wprintf(L">>> ");//��ʾ����

	wchar_t line[1024];
	fgetws(line, sizeof(line) / sizeof(line[0]), stdin);
	line[_tcslen(line) - 1] = '\0';

	if (!_tcscmp(line, L"\0")) {
		return getDouble(max);
	}//û����Ͱ��˻س�

	//wchar_t ch;
	int command = 0;
	int err = 1;
	int is_num = 0;
	int is_continue = 1;
	int is_all_space = 1;
	int is_dot = 0;
	int dot = 0;

	for (int i = 0; i < _tcslen(line); i++) {
		//for (int i = 0; line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'); i++) {
		err = 0;
		if (!(line[i] == ' ' || (line[i] >= '0' && line[i] <= '9') || line[i] == '.')) {
			err = 1;
			is_all_space = 0;
			break;
		}//������ֱ�Ӵ���
		if (line[i] == ' ') {
			if (is_num == 0) {
				continue;
			}
			is_continue = 0;
			continue;
		}//ȥ���ո�
		if (line[i] == '.') {
			if (is_dot == 0) {
				is_dot = 1;
				continue;
			}
			else {
				err = 1; // ���С����
				is_all_space = 0;
				break;
			}
		}
		if (is_continue == 1) {
			if (is_dot == 1) {
				dot++;
				if (dot > 2) {
					err = 1; // С��λ��̫��
					is_all_space = 0;
					break;
				}
			}
			command = command * 10 + line[i] - '0';//ƴ������
			is_num = 1;
			is_all_space = 0;
		}
		else {
			err = 1;
			break;
		}
		if (command / pow(10, dot) > max) {
			err = 1;
			break;
		}//������
	}

	if (is_all_space == 1) {
		return getDouble(max);
	}//��������ȫ�ǿո�

	if (err == 0) {
		return command / pow(10, dot);
	}
	else {
		//wprintf(L"�������ݲ��Ϸ������������룡\n");
		wprintf(L"\"%s\" �������ݲ��Ϸ������������룡\n", line);
		return getDouble(max);
	}

}

void getText(wchar_t* str)
{
	fflush(stdin);
	wprintf(L">>> ");//��ʾ����

	wchar_t line[1024];
	fgetws(line, sizeof(line) / sizeof(line[0]), stdin);
	line[_tcslen(line) - 1] = '\0';// ��ȡһ����

	if (!_tcscmp(line, L"\0")) {
		getText(str);
	}//û����Ͱ��˻س�

	//int start_space = 1;
	//int end_space = 1;
	int len = 0;
	int is_all_space = 1;
	for (int i = 0; line[i]; i++) {// ����ַ�����
		if (line[i] == ' ') {
			continue;
		}// ȥ���ո�
		str[len++] = line[i];
		is_all_space = 0;
	}
	str[len] = '\0';

	if (is_all_space == 1) {
		getText(str);
	}// ���ȫ�ǿո�

}



bool getNumberInBox(int max, int* target, const wchar_t* line) {

	if (!_tcscmp(line, L"\0")) {
		return false;
	}//û����

	//wchar_t ch;
	int command = 0;
	int err = 1;
	int is_num = 0;
	int is_continue = 1;
	int is_all_space = 1;

	for (int i = 0; i < _tcslen(line); i++) {
		//for (int i = 0; line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'); i++) {
		err = 0;
		if (!(line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'))) {
			err = 1;
			is_all_space = 0;
			break;
		}//������ֱ�Ӵ���
		if (line[i] == ' ') {
			if (is_num == 0) {
				continue;
			}
			is_continue = 0;
			continue;
		}//ȥ���ո�
		if (is_continue == 1) {
			command = command * 10 + line[i] - '0';//ƴ������
			is_num = 1;
			is_all_space = 0;
		}
		else {
			err = 1;
			break;
		}
		if (command > max) {
			err = 1;
			break;
		}//������
	}

	if (is_all_space == 1)
	{
		return false;
	}//��������ȫ�ǿո�

	if (err == 0) {
		*target = command;
		return true;
	}
	else {
		return false;
	}

}


bool getDoubleInBox(double max, double* target,  wchar_t* line) //�⺯���е�bug����֮��ĸ�
{

	if (!_tcscmp(line, L"\0")) {
		return false;
	}//û����

	if (line[wcslen(line) - 1] == L'\n') {
		line[wcslen(line) - 1] = L'\0';
	}

	int command = 0;
	int err = 1;
	int is_num = 0;
	int is_continue = 1;
	int is_all_space = 1;
	int is_dot = 0;
	int dot = 0;

	for (int i = 0; i < _tcslen(line); i++) {
		//for (int i = 0; line[i] == ' ' || (line[i] >= '0' && line[i] <= '9'); i++) {
		err = 0;
		if (!(line[i] == ' ' || (line[i] >= '0' && line[i] <= '9') || line[i] == '.')) {
			err = 1;
			is_all_space = 0;
			break;
		}//������ֱ�Ӵ���
		if (line[i] == ' ') {
			if (is_num == 0) {
				continue;
			}
			is_continue = 0;
			continue;
		}//ȥ���ո�
		if (line[i] == '.') {
			if (is_dot == 0) {
				is_dot = 1;
				continue;
			}
			else {
				err = 1; // ���С����
				is_all_space = 0;
				break;
			}
		}
		if (is_continue == 1) {
			if (is_dot == 1) {
				dot++;
				if (dot > 4) {
					err = 1; // С��λ��̫��
					is_all_space = 0;
					break;
				}
			}
			command = command * 10 + line[i] - '0';//ƴ������
			is_num = 1;
			is_all_space = 0;
		}
		else {
			err = 1;
			break;
		}
		if (command / pow(10, dot) > max) {
			err = 1;
			break;
		}//������
	}

	if (is_all_space == 1) {
		return false;
	}//��������ȫ�ǿո�

	if (err == 0) {
		*target = command / pow(10, dot);
		return true;
	}
	else {
		return false;
	}
}

bool getTextInBox(wchar_t* target, const wchar_t* line)
{

	if (!_tcscmp(line, L"\0")) {
		return false;
	}//û����

	//int start_space = 1;
	//int end_space = 1;
	int len = 0;
	int is_all_space = 1;
	for (int i = 0; line[i]; i++) {// ����ַ�����
		if (line[i] == ' ') {
			continue;
		}// ȥ���ո�
		target[len++] = line[i];
		is_all_space = 0;
	}
	target[len] = '\0';

	if (is_all_space == 1) {
		return false;
	}// ���ȫ�ǿո�
	return true;

}




int showMenu(const wchar_t* title, int optNum, ...) {
	wprintf(L"%s\n\n", title);

	va_list args;
	va_start(args, optNum);

	for (int i = 1; i <= optNum; i++) {
		wprintf(L"%2d:%s\n", i, va_arg(args, const wchar_t*));
	}
	va_end(args);
	return 1;
}




