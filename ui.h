#pragma once
#pragma warning(disable:28159)

#ifndef _UI_H_
#define _UI_H_

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
#include"quality.h"
#include "student.h"
#include "course.h"
#include "file.h"
#include "io.h"
//#define backgroundColor RGB(55, 61, 53)
//#define defaulteColoe WHITE
//#define tableSelectedColor RGB(GetRValue(bkColor) + 30, GetGValue(bkColor) + 30, GetBValue(bkColor) + 30)
//
//
//#define buttonType1BkColor RGB(191, 202, 185)
//#define buttonType1HovColor RGB(GetRValue(bkColor) + 30, GetGValue(bkColor) + 30, GetBValue(bkColor) + 30)
//#define buttonType1PressColor RGB(GetRValue(bkColor) + 50, GetGValue(bkColor) + 50, GetBValue(bkColor) + 50)
//#define buttonType1TxtColor RGB(42, 51, 40)
//
//#define buttonType2BkColor RGB(73, 78, 70)
//#define buttonType2HovColor RGB(GetRValue(bkColor) + 30, GetGValue(bkColor) + 30, GetBValue(bkColor) + 30)
//#define buttonType2PressColor RGB(GetRValue(bkColor) + 50, GetGValue(bkColor) + 50, GetBValue(bkColor) + 50)
//#define buttonType2TxtColor RGB(200, 198, 195)
//
//#define textTxtColor RGB(228, 226, 223)
//
//#define BoxdefaultColor RGB(33, 39, 32);
//#define BoxinputColor RGB(55, 61, 53);
//#define BoxhoveredColor RGB(69, 73, 67);
//#define BoxborderColor RGB(191, 202, 185);

//主题颜色
#define backgroundColor RGB(255, 255, 255)
#define defaulteColoe RGB(31, 31, 31)
#define tableSelectedColor RGB(216, 216, 217)


#define buttonType1BkColor RGB(211, 227, 253)
#define buttonType1HovColor RGB(201, 216, 240)
#define buttonType1PressColor RGB(178, 202, 242)
#define buttonType1TxtColor RGB(4, 30, 73)

#define buttonType2BkColor RGB(220, 220, 221)
#define buttonType2HovColor RGB(232, 232, 232)
#define buttonType2PressColor RGB(204, 204, 204)
#define buttonType2TxtColor RGB(30, 30, 30)

#define textTxtColor RGB(31, 31, 31)

#define BoxdefaultColor RGB(236, 239, 247);
#define BoxinputColor RGB(255, 255, 255);
#define BoxhoveredColor RGB(224, 227, 234);
#define BoxborderColor RGB(11, 87, 208);




using namespace std;



class Button {
private:
	int x, y;
	int width, height;
	const wchar_t* text;
	COLORREF bkColor;
	COLORREF textColor;
	COLORREF hovColor;
	COLORREF pressColor;
	bool hovered;
	bool pressed;

public:
	Button(int _x, int _y, int _width, int _height, const wchar_t* _text, int style) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		text = _text;
		if (style == 1) {
			bkColor = buttonType1BkColor;
			hovColor = buttonType1HovColor;
			pressColor = buttonType1PressColor;
			textColor = buttonType1TxtColor;
		}
		else if (style == 0) {
			bkColor = buttonType2BkColor;
			hovColor = buttonType2HovColor;
			pressColor = buttonType2PressColor;
			textColor = buttonType2TxtColor;
		}
		hovered = false;
		pressed = false;
		settextstyle(height / 2, 0, L"微软雅黑");
		draw();
	}

	void draw() {
		settextstyle(height / 2, 0, L"微软雅黑");
		setfillcolor(bkColor); //设置按钮背景
		if (hovered) {
			setfillcolor(hovColor); //按钮悬停背景
			if (pressed) {
				setfillcolor(pressColor); //按钮按下背景
			}
		}
		solidroundrect(x, y, x + width, y + height, height, height); //绘制按钮
		int textX = x + (width - textwidth(text)) / 2;
		int textY = y + (height - textheight(text)) / 2;
		settextcolor(textColor); //文本颜色
		setbkmode(TRANSPARENT); //文本背景透明
		outtextxy(textX, textY, text); //绘制文本
	}

	bool mouseClick(const ExMessage& msg) {
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (isHovered(msg.x, msg.y)) {
				hovered = true;
			}
			else {
				hovered = false;
			}
			break;
		case WM_LBUTTONDOWN:
			if (isHovered(msg.x, msg.y)) {
				pressed = true;
			}
			break;
		case WM_LBUTTONUP:
			if (isHovered(msg.x, msg.y) && pressed == true) {
				pressed = false;
				draw();
				return true;
			}
			pressed = false;
			break;
		default:
			break;
		}
		draw();
		return false;
	}

	void move(int _x, int _y) {
		setfillcolor(getbkcolor());
		solidrectangle(x, y, x + width, y + height);
		x = _x;
		y = _y;
		draw();
	}

private:
	bool isHovered(int mouseX, int mouseY) const {
		return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
	}
};


class Text {
private:
	int x;
	int y;
	wchar_t text[512];
public:
	int size;
	COLORREF color;
	Text(int _x, int _y, const wchar_t* _text, int _size) {
		x = _x;
		y = _y;
		_tcscpy(text, _text);
		size = _size;
		color = textTxtColor;
		settextstyle(size, 0, L"微软雅黑");
		draw();
	}
	void draw() {
		setbkmode(TRANSPARENT);
		settextcolor(color);
		settextstyle(size, 0, L"微软雅黑");
		outtextxy(x, y, text);

	}
	void setText(const wchar_t* _text) {
		setfillcolor(getbkcolor());
		settextstyle(size, 0, L"微软雅黑");
		solidrectangle(x, y, x + textwidth(text), y + textheight(text));
		_tcscpy(text, _text);
		draw();
	}

	void move(int _x, int _y) {
		setfillcolor(getbkcolor());
		settextstyle(size, 0, L"微软雅黑");
		solidrectangle(x, y, x + textwidth(text), y + textheight(text));
		x = _x;
		y = _y;
		draw();
	}
	void setTextSize(int _size) {
		size = _size;
		draw();
	}
};


class TextBox {
private:
	int x, y;
	int width, height;
	wchar_t hintText[512];
	COLORREF defaultColor;
	COLORREF inputColor;
	COLORREF hoveredColor;
	COLORREF borderColor;
	COLORREF textColor;
	wchar_t pwdText[1024];

public:
	wchar_t text[1024];
	bool isInput;
	bool hovered;
	TextBox(int _x, int _y, int _width, const wchar_t* _hintText, const wchar_t* _text) {
		x = _x;
		y = _y;
		width = _width;
		height = 50;
		_tcscpy(text, _text);
		_tcscpy(hintText, _hintText);
		isInput = false;
		hovered = false;
		defaultColor = BoxdefaultColor;
		inputColor = BoxinputColor;
		hoveredColor = BoxhoveredColor;
		borderColor = BoxborderColor;
		textColor = defaulteColoe;
		if (wcscmp(_text, L"") == NULL) {
			settextstyle(22, 0, L"微软雅黑");
		}
		else {
			settextstyle((int)(height / 2.2), 0, L"微软雅黑");
		}
		//draw();
	}
	void draw() {
		//while (true) {

		// 文本框
		settextstyle(22, 0, L"微软雅黑");
		int textHeight = textheight(L"|");
		clearrectangle(x, y, x + width, y + height);
		setlinecolor(borderColor); //边框颜色
		if (isInput) {
			setfillcolor(inputColor); //输入时填充颜色
		}
		else if (hovered) {
			setfillcolor(hoveredColor); //鼠标悬浮时填充颜色
		}
		else {
			setfillcolor(defaultColor); //默认填充颜色
		}
		fillroundrect(x, y, x + width, y + height, height - 3, height - 3); //绘制

		// 文本
		if (wcscmp(hintText, L"密码") == 0 || wcscmp(hintText, L"请输入新密码") == 0 || wcscmp(hintText, L"请确认新密码") == 0) {
			for (int i = 0; i < wcslen(text); i++) {
				pwdText[i] = L'●';
			}
			pwdText[wcslen(text)] = L'\0';
			settextcolor(textColor);
			settextstyle(30, 0, L"微软雅黑");
			setbkmode(TRANSPARENT);
			if (!_tcscmp(text, L"")) {
				settextstyle((int)(height / 2.2), 0, L"微软雅黑");
				outtextxy(x + 20, y + (height - textHeight) / 2, hintText);
			}
			else {
				outtextxy(x + 15, y + (height - textHeight) / 2 - 5, pwdText);
			}

		}
		else
		{
			settextcolor(textColor);
			settextstyle((int)(height / 2.2), 0, L"微软雅黑");
			setbkmode(TRANSPARENT);
			if (!_tcscmp(text, L"")) {
				outtextxy(x + 20, y + (height - textHeight) / 2, hintText);
			}
			else {
				outtextxy(x + 15, y + (height - textHeight) / 2, text);
			}
		}

		// 光标
		if (isInput) {
			DWORD clock = GetTickCount();
			if (clock % 1000 < 500) {
				setlinecolor(defaulteColoe); //光标颜色
				if (wcscmp(hintText, L"密码") == 0 || wcscmp(hintText, L"请输入新密码") == 0 || wcscmp(hintText, L"请确认新密码") == 0) {
					line(x + 16 + textwidth(pwdText), y - 2 + (height - textHeight) / 2, x + 16 + textwidth(pwdText), y + 2 + height - (height - textHeight) / 2);
				}
				else {
					line(x + 16 + textwidth(text), y - 2 + (height - textHeight) / 2, x + 16 + textwidth(text), y + 2 + height - (height - textHeight) / 2);
				}
			}
			else {
				setlinecolor(inputColor);
				if (wcscmp(hintText, L"密码") == 0 || wcscmp(hintText, L"请输入新密码") == 0 || wcscmp(hintText, L"请确认新密码") == 0) {
					line(x + 16 + textwidth(pwdText), y - 2 + (height - textHeight) / 2, x + 16 + textwidth(pwdText), y + 2 + height - (height - textHeight) / 2);
				}
				else {
					line(x + 16 + textwidth(text), y - 2 + (height - textHeight) / 2, x + 16 + textwidth(text), y + 2 + height - (height - textHeight) / 2);
				}

			}
		}
		//}

	}
	void onMessage(ExMessage& msg) {
		size_t len = _tcslen(text);
		size_t pwdLen = _tcslen(pwdText);
		switch (msg.message)
		{
		case WM_MOUSEMOVE:
			if (isHovered(msg.x, msg.y)) {
				hovered = true;
			}
			else {
				hovered = false;
			}
			break;
		case WM_LBUTTONDOWN:
			if (isHovered(msg.x, msg.y)) {
				isInput = true;
			}
			else {
				isInput = false;
			}
			break;
		case WM_CHAR:
			if (isInput) {
				switch (msg.ch)
				{

				case '\b':
					if (len > 0) {
						text[len - 1] = '\0';
					}
					break;
				case '\r':
				case '\n':
					isInput = false;
					break;
				default:
					//printf(L"press:%c\n", msg.ch);
					settextstyle((int)(height / 2.2), 0, L"微软雅黑");
					if ((len < 512 - 1 && textwidth(text) < width - 35) || (pwdLen < 512 - 1 && textwidth(pwdText) < width - 35)) {
						text[len++] = msg.ch;
						text[len] = '\0';
						//printf(L"%d\n", textwidth(text));
					}
					break;
				}
			}
		default:
			break;
		}

	}
	void move(int _x, int _y) {
		setfillcolor(getbkcolor());
		solidrectangle(x, y, x + width, y + height);
		x = _x;
		y = _y;
		draw();
	}
	void clear() {
		wcscpy(text, L"");
		draw();
	}
	void setText(const wchar_t* _text) {
		wcscpy(text, _text);
		draw();
	}
private:
	bool isHovered(int mouseX, int mouseY) const {
		return (mouseX >= x && mouseX <= x + width && mouseY >= y && mouseY <= y + height);
	}

};


class Table {
private:
	int x, y;
	int width, height;
	int offset;
	int maxRow;
	vector<int> colWidth;
	int selectedRow;
	vector<vector<wstring>> data;
	COLORREF bkColor;
	COLORREF textColor;
	COLORREF borderColor;
	int scollBarHeight;

public:
	bool canChange;
	Table(int _x, int _y, int _width, int _height, const vector<vector<wstring>>& _data) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		canChange = true;
		data = _data;
		bkColor = backgroundColor;
		textColor = defaulteColoe;
		borderColor = BoxborderColor;
		offset = 0;
		selectedRow = 0;
		maxRow = 0;
		calculateColWidth();
		calculateMaxRow();
		//printf("%d\n", maxRow);
		scollBarHeight = (data.size() > maxRow) ? 1.0 * maxRow / data.size() * height : height;
		draw();
	}

	void draw() {

		setfillcolor(bkColor);
		setlinecolor(defaulteColoe);
		if (scollBarHeight != height) {
			setlinecolor(borderColor);
			fillroundrect(x + width + 5, y, x + width + 15, y + height, 10, 10); // 滚动条外框

			// 滚动条
			setfillcolor(defaulteColoe);
			fillroundrect(x + width + 8,
				3 + y + 1.0 * offset / data.size() * height,
				x + width + 12,
				-3 + y + 1.0 * offset / data.size() * height + scollBarHeight,
				4, 4);
		}
		else {
			solidrectangle(x + width + 5, y, x + width + 15, y + height); // 清除滚动条
		}
		setlinecolor(borderColor);
		setfillcolor(bkColor);
		fillroundrect(x, y, x + width, y + height, 10, 10); // 表格外框

		//int textHeight = textheight(data[0][0].c_str());
		int textHeight = height / maxRow;


		// 选中行高亮
		if (offset < selectedRow && offset + maxRow > selectedRow) {
			setfillcolor(tableSelectedColor);
			fillrectangle(x + 1, 1 + y + (selectedRow - offset) * textHeight, x + width - 1, -1 + y + (selectedRow - offset + 1) * textHeight);
		}

		setlinecolor(defaulteColoe);

		// 行
		int ry = y;
		setlinecolor(borderColor);
		for (int r = 0; r < min(maxRow, (int)data.size() - offset); r++) {

			ry += textHeight;
			if (r != min(maxRow, (int)data.size() - offset) - 1) {
				line(x, ry, x + width, ry);
			}

			// 列
			int cx = x;
			if (!r) {
				// 表头（默认表头最长）
				for (int c = 0; c < data[0].size(); c++) {
					cx += colWidth[c];
					if (c != data[0].size() - 1) {
						line(cx, y, cx, y + height);
					}
					setbkmode(TRANSPARENT);
					settextcolor(textColor);
					settextstyle(30, 0, L"微软雅黑");
					outtextxy(cx - colWidth[c] + 5, ry - textHeight + (textHeight - textheight(data[0][0].c_str())) / 2, data[0][c].c_str());
				}
			}
			else {
				// 数据
				for (int c = 0; c < data[r + offset].size(); c++) {
					cx += colWidth[c];
					setbkmode(TRANSPARENT);
					settextcolor(textColor);
					int textSize = 28;
					//while (colWidth[c] < textwidth(data[r + offset][c].c_str())) {
					//	textSize -= 10;
					//	settextstyle(textSize, 0, L"微软雅黑");
					//}
					//settextstyle(textSize, 0, L"微软雅黑");
					//if (textwidth(data[r + offset][c].c_str()) > colWidth[c]) {
					//	wstring tempText = data[r + offset][c].substr(0, colWidth[c] / textwidth(L"一" - 4)) + L"...";
					//	outtextxy(cx - colWidth[c] + 5, ry - textHeight + (textHeight - textheight(data[0][0].c_str())) / 2, tempText.c_str());
					//}
					//else {
					outtextxy(cx - colWidth[c] + 5, ry - textHeight + (textHeight - textheight(data[0][0].c_str())) / 2, data[r + offset][c].c_str());
					//}
				}
			}
		}
	}
	void calculateColWidth() { //计算每列宽度
		colWidth.clear();
		if (!data.empty()) {
			colWidth.resize(data[0].size(), 0);
			for (vector<wstring> rowData : data) {
				for (int colNum = 0; colNum < rowData.size(); colNum++) {
					int maxWidth = textwidth(rowData[colNum].c_str());
					if (maxWidth > colWidth[colNum]) {
						colWidth[colNum] = maxWidth;
					}
				}
			}

			int sumWidth = 0;
			for (auto it : colWidth) {
				sumWidth += it;
			}
			for (auto& it : colWidth) {
				it = (float)it / sumWidth * width;
			}
		}
	}
	void calculateMaxRow() { // 计算最大行数
		settextstyle(30, 0, L"微软雅黑");
		//int times = 0;
		//for (int r = 0; r < data.size(); r++) {
		//	for (int c = 0; c < data[r].size(); c++) {
		//		times = max(times, textwidth(data[r][c].c_str()) / colWidth[c]);
		//		printf("%d\n", times);
		//	}
		//}
		maxRow = height / ((textheight(L"测")));
		height = maxRow * ((textheight(L"测")));
	}
	void onMouse(ExMessage& msg) {
		if (isHovered(msg.x, msg.y)) {
			switch (msg.message)
			{
			case WM_MOUSEWHEEL:
				if (msg.wheel > 0 && offset > 0) { //向上滑
					offset--;
				}
				else if (msg.wheel < 0 && offset < (int)data.size() - maxRow) { //向下滑
					offset++;
				}
				break;
			case WM_LBUTTONDOWN: {
				if (canChange) {
					int Rselect = int(1.0 * (msg.y - y) / height * maxRow);
					if (Rselect != 0) {
						if (selectedRow == Rselect + offset) {
							selectedRow = 0;
						}
						else {
							selectedRow = Rselect + offset;
						}
					}
					//printf("%d\n", selectedRow);
				}
				break;
			}
			default:
				break;
			}
		}
		draw();
	}
	int getSelectedRow() {
		return (selectedRow < data.size()) ? selectedRow : 0;
	}
	void setData(const vector<vector<wstring>>& _data) {
		if (canChange) {
			data = _data;
			offset = 0;
			selectedRow = 0;
			calculateColWidth();
			//calculateMaxRow();
			scollBarHeight = (data.size() > maxRow) ? 1.0 * maxRow / data.size() * height : height;
			draw();
		}
	}
	void move(int _x, int _y) {
		setfillcolor(getbkcolor());
		solidrectangle(x, y, x + width, y + height + 20);
		x = _x;
		y = _y;
		draw();
	}

private:
	bool isHovered(int mouseX, int mouseY) const {
		return (mouseX >= x && mouseX <= x + width + 15 && mouseY >= y && mouseY <= y + height);
	}
};


class Chart {
private:
	int x, y;
	int width, height;
	vector<vector<wstring>> data;
	COLORREF bkColor;
	int colWidth;
	int rowHeight;

public:
	Chart(int _x, int _y, int _width, int _height, const vector<vector<wstring>>& _data) {
		x = _x;
		y = _y;
		width = _width;
		height = _height;
		data = _data;
		bkColor = getbkcolor();
		if (data[0].size() != 0 && data[0].size() != 1) {
			data[0].push_back(L"预测下一个值");
			data[1].push_back(to_wstring(preditc()));
			data[1][data[1].size() - 1] = data[1][data[1].size() - 1].substr(0, data[1][data[1].size() - 1].find('.') + 3);
		}

		draw();
	}
	void draw() {
		setfillcolor(bkColor);
		setlinecolor(defaulteColoe);
		setfillcolor(defaulteColoe);

		setbkmode(TRANSPARENT);
		settextcolor(defaulteColoe);
		settextstyle(24, 0, L"微软雅黑");
		//fillroundrect(x, y, x + width, y + height, 10, 10); // 图表外框

		drawYandLine();
		drawCol();

		if (data[0].size() != 0) {
			if (data[0].size() == 1) {
				// 小圆点
				solidroundrect(x + colWidth / 2 + textwidth(L"测") / 2 - 5, y + height - stof(data[1][0]) / 10.0 * rowHeight - 5,
					x + colWidth / 2 + textwidth(L"测") / 2 + 5, y + height - stof(data[1][0]) / 10.0 * rowHeight + 5,
					10, 10);
				outtextxy(x + colWidth / 2 + textwidth(L"测") / 2 - 5 - textwidth(data[1][0].c_str()) / 2, y + height - stof(data[1][0]) / 10.0 * rowHeight - 25, data[1][0].c_str());

			}
			for (int i = 0; i < data[1].size() - 1; i++) {
				line(x + i * colWidth + colWidth / 2 + textwidth(L"测") / 2, y + height - stof(data[1][i]) / 10.0 * rowHeight,
					x + (i + 1) * colWidth + colWidth / 2 + textwidth(L"测") / 2, y + height - stof(data[1][i + 1]) / 10.0 * rowHeight
				);
				// 小圆点
				solidroundrect(x + i * colWidth + colWidth / 2 + textwidth(L"测") / 2 - 5, y + height - stof(data[1][i]) / 10.0 * rowHeight - 5,
					x + i * colWidth + colWidth / 2 + textwidth(L"测") / 2 + 5, y + height - stof(data[1][i]) / 10.0 * rowHeight + 5,
					10, 10);
				outtextxy(x + i * colWidth + colWidth / 2 + textwidth(L"测") / 2 - 5 - textwidth(data[1][i].c_str()) / 2, y + height - stof(data[1][i]) / 10.0 * rowHeight - 25, data[1][i].c_str());
				// 小圆点
				solidroundrect(x + (i + 1) * colWidth + colWidth / 2 + textwidth(L"测") / 2 - 5, y + height - stof(data[1][i + 1]) / 10.0 * rowHeight - 5,
					x + (i + 1) * colWidth + colWidth / 2 + textwidth(L"测") / 2 + 5, y + height - stof(data[1][i + 1]) / 10.0 * rowHeight + 5,
					10, 10);
				outtextxy(x + (i + 1) * colWidth + colWidth / 2 + textwidth(L"测") / 2 - 5 - textwidth(data[1][i + 1].c_str()) / 2, y + height - stof(data[1][i + 1]) / 10.0 * rowHeight - 25, data[1][i + 1].c_str());
			}
		}


	}
	void drawText(int _x, int _y, wstring _text) { // 竖直绘制文字
		for (int i = 0; i < _text.length(); i++) {
			outtextxy(_x, _y + i * textheight(L"测"), _text[i]);
		}
	}
	void drawCol() { //画每列
		int cnt = (data[0].size()) ? (data[0].size()) : 1;
		colWidth = width / (cnt);
		//width = colWidth * cnt;
		line(x, y + height, x + width, y + height);
		for (int i = 0; i < data[0].size(); i++) {
			drawText(x + i * colWidth + colWidth / 2, y + height + 5, data[0][i]);

		}
	}
	void drawYandLine() { // 画y轴
		int maxNum = 1;
		for (auto& numStr : data[1]) {
			maxNum = max(maxNum, stof(numStr));
		}
		//int maxNum = 100;
		rowHeight = 10.0 * height / maxNum;
		line(x, y, x, y + height);
		int num = 0;
		for (int i = y + height; i >= y; i -= rowHeight) {
			line(x - 5, i, x + 10, i);
			outtextxy(x - 40, i - textheight(L"1") / 2, to_wstring(num).c_str());
			num += 10;
		}



	}

	double preditc() {
		// 回归参数
		double a, b, c, d;

		// 计算回归
		//cubic_regression(data[1], data[1].size(), &a, &b, &c, &d);
		//quadratic_regression(data[1], data[1].size(), &a, &b, &c);
		linear_regression(data[1], data[1].size(), &a, &b);

		// 预测新数据点
		double new_x = data[1].size();

		double prediction = (a * new_x + b <= 100) ? (a * new_x + b >= 0) ? a * new_x + b : 0 : 100;
		//double prediction = a * pow(new_x, 3) + b * pow(new_x, 2) + c * new_x + d;
		//double prediction = a * pow(new_x, 2) + b * pow(new_x, 1) + c;
		printf("预测值: %.2f\n", prediction);
		return prediction;
	}

	// 实现二阶多项式回归函数
	void quadratic_regression(vector<wstring> y, int n, double* a, double* b, double* c) {
		double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_y = 0, sum_xy = 0, sum_x2y = 0;

		// 计算各种和
		for (int i = 0; i < n; i++) {
			double x2 = (i + 1) * (i + 1);
			double x3 = x2 * (i + 1);
			double x4 = x3 * (i + 1);
			sum_x += (i + 1);
			sum_x2 += x2;
			sum_x3 += x3;
			sum_x4 += x4;
			sum_y += stod(y[i]);
			sum_xy += (i + 1) * stod(y[i]);
			sum_x2y += x2 * stod(y[i]);
		}

		// 构建方程组并解出参数
		double denominator = n * sum_x2 * sum_x4 + 2 * sum_x * sum_x2 * sum_x3 - sum_x * sum_x * sum_x4 - n * sum_x3 * sum_x3 - sum_x2 * sum_x2 * n;
		double a_numerator = sum_y * sum_x2 * sum_x4 + sum_x * sum_x2y * sum_x4 + sum_x2 * sum_xy * sum_x3 - sum_x * sum_x2 * sum_x2y - sum_x * sum_x3 * sum_xy - sum_x2 * sum_x2 * sum_y;
		double b_numerator = sum_y * sum_x3 * sum_x4 + sum_x * sum_x2 * sum_x2y + sum_x2 * sum_x * sum_xy - sum_x * sum_x2 * sum_x2y - sum_x * sum_x3 * sum_y - sum_x2 * sum_x2 * sum_xy;
		double c_numerator = sum_y * sum_x2 * sum_x3 + sum_x * sum_x3 * sum_xy + sum_x2 * sum_x * sum_x2y - sum_x * sum_x2 * sum_x3 - sum_x * sum_x2 * sum_xy - sum_x2 * sum_x2 * sum_y;

		*a = a_numerator / denominator;
		*b = b_numerator / denominator;
		*c = c_numerator / denominator;
	}


	void linear_regression(vector<wstring> y, int n, double* slope, double* intercept) {
		double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x_squared = 0;

		// 计算各种和
		for (int i = 0; i < n; i++) {
			sum_x += (i + 1);
			sum_y += stod(y[i]);
			sum_xy += (i + 1) * stod(y[i]);
			sum_x_squared += (i + 1) * (i + 1);
		}

		// 计算斜率和截距
		*slope = (n * sum_xy - sum_x * sum_y) / (n * sum_x_squared - sum_x * sum_x);
		*intercept = (sum_y - *slope * sum_x) / n;
	}

	// 实现三阶多项式回归函数
	void cubic_regression(vector<wstring> y, int n, double* a, double* b, double* c, double* d) {
		double sum_x = 0, sum_x2 = 0, sum_x3 = 0, sum_x4 = 0, sum_x5 = 0, sum_x6 = 0, sum_y = 0, sum_xy = 0, sum_x2y = 0, sum_x3y = 0;


		// 计算各种和
		for (int i = 0; i < n; i++) {
			double x2 = (i + 1) * (i + 1);
			double x3 = x2 * (i + 1);
			double x4 = x3 * (i + 1);
			double x5 = x4 * (i + 1);
			double x6 = x5 * (i + 1);
			sum_x += (i + 1);
			sum_x2 += x2;
			sum_x3 += x3;
			sum_x4 += x4;
			sum_x5 += x5;
			sum_x6 += x6;
			sum_y += stod(y[i]);
			sum_xy += (i + 1) * stod(y[i]);
			sum_x2y += x2 * stod(y[i]);
			sum_x3y += x3 * stod(y[i]);
		}

		// 构建方程组并解出参数
		long long denominator = n * sum_x2 * sum_x4 * sum_x6 - sum_x * sum_x2 * sum_x4 * sum_x4 - sum_x2 * sum_x2 * sum_x4 * sum_x4 - sum_x2 * sum_x4 * sum_x4 * n - n * sum_x * sum_x6 * sum_x6 + sum_x * sum_x * sum_x4 * sum_x6 + sum_x2 * sum_x2 * sum_x6 * sum_x6 + sum_x * sum_x2 * sum_x2 * sum_x6 + sum_x * sum_x2 * sum_x4 * sum_x4 + n * sum_x * sum_x2 * sum_x2 * sum_x4 - n * sum_x2 * sum_x2 * sum_x2 * sum_x4 - n * sum_x * sum_x * sum_x6 * sum_x6 + n * sum_x * sum_x2 * sum_x4 * sum_x4 + n * sum_x2 * sum_x2 * sum_x2 * sum_x2 * sum_x4 - n * sum_x2 * sum_x2 * sum_x2 * sum_x4 * sum_x4 - n * sum_x * sum_x * sum_x2 * sum_x6 * sum_x6;
		long long a_numerator = sum_y * sum_x2 * sum_x4 * sum_x6 + sum_x * sum_x2y * sum_x4 * sum_x6 + sum_x2 * sum_xy * sum_x4 * sum_x6 + sum_x3y * sum_x2 * sum_x4 * sum_x6 - sum_x * sum_x2 * sum_x2y * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x3y * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_xy * sum_x2 * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x3y * sum_x4 - sum_x * sum_x3 * sum_xy * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x2 * sum_x2y * sum_x4 + sum_x * sum_x3 * sum_x2 * sum_x3y * sum_x4 + sum_x * sum_x3 * sum_x3y * sum_x2 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x3y * sum_x2 * sum_x4 * sum_x4 - sum_x * sum_x3 * sum_x3y * sum_x3 * sum_x2 * sum_x4 - sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 * sum_x4 - sum_x2 * sum_x2 * sum_x2 * sum_x2y * sum_x4 * sum_x4 - sum_x2 * sum_x2 * sum_x3 * sum_x3y * sum_x4 * sum_x4 + sum_x2 * sum_x2 * sum_x3y * sum_x3y * sum_x4 * sum_x4 + n * sum_x * sum_x2 * sum_x4 * sum_x4 * sum_x6 - n * sum_x * sum_x2 * sum_x2 * sum_x4 * sum_x6 - n * sum_x * sum_x2 * sum_x4 * sum_x6 * sum_x6 + n * sum_x * sum_x2 * sum_x2 * sum_x4 * sum_x4 * sum_x6;
		long long b_numerator = sum_y * sum_x3 * sum_x4 * sum_x6 + sum_x * sum_x2 * sum_x2y * sum_x4 * sum_x6 + sum_x2 * sum_x * sum_x3y * sum_x4 * sum_x6 + sum_x2 * sum_x * sum_x2 * sum_xy * sum_x4 * sum_x6 - sum_x * sum_x2 * sum_x3 * sum_x2y * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x3 * sum_x3y * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x3y * sum_x4 * sum_x4 - sum_x * sum_x3 * sum_x2 * sum_x2 * sum_x2y * sum_x4 + sum_x * sum_x3 * sum_x2 * sum_x3y * sum_x4 + sum_x * sum_x3 * sum_x3y * sum_x2 * sum_x2 * sum_x4 - sum_x * sum_x3 * sum_x3y * sum_x2 * sum_x4 * sum_x4 - sum_x * sum_x3 * sum_x3y * sum_x3 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x3y * sum_x3 * sum_x4 * sum_x4 - sum_x2 * sum_x2 * sum_x2 * sum_x3y * sum_x4 * sum_x6 - sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 * sum_x6 + sum_x2 * sum_x2 * sum_x3 * sum_x3y * sum_x4 * sum_x6 + n * sum_x * sum_x2 * sum_x2 * sum_x2 * sum_x4 - n * sum_x * sum_x2 * sum_x3 * sum_x3 * sum_x4 - n * sum_x * sum_x2 * sum_x2 * sum_x2 * sum_x2 * sum_x4 + n * sum_x * sum_x2 * sum_x2 * sum_x3 * sum_x3 * sum_x4;
		long long c_numerator = sum_y * sum_x2 * sum_x4 * sum_x6 + sum_x * sum_x2 * sum_x3y * sum_x4 * sum_x6 + sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 * sum_x6 + sum_x3 * sum_x * sum_x2 * sum_x2y * sum_x4 * sum_x6 - sum_x * sum_x2 * sum_x3 * sum_x3y * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x3y * sum_x4 * sum_x4 - sum_x * sum_x3 * sum_x2 * sum_x2 * sum_x2 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x2 * sum_x2 * sum_x3 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x3 * sum_x2 * sum_x2 * sum_x2 * sum_x4 - sum_x * sum_x3 * sum_x3 * sum_x3y * sum_x2 * sum_x4 * sum_x4 + n * sum_x * sum_x2 * sum_x3 * sum_x4 * sum_x4 * sum_x6 - n * sum_x * sum_x2 * sum_x3 * sum_x3 * sum_x4 * sum_x6 - n * sum_x * sum_x3 * sum_x3 * sum_x3 * sum_x2 * sum_x2 * sum_x4 + n * sum_x * sum_x3 * sum_x3 * sum_x3y * sum_x2 * sum_x4 * sum_x4;
		long long d_numerator = sum_y * sum_x2 * sum_x3 * sum_x4 + sum_x * sum_x3 * sum_x3y * sum_x4 + sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 + sum_x3 * sum_x * sum_x2 * sum_x2y * sum_x4 - sum_x * sum_x2 * sum_x3 * sum_x3y * sum_x4 - sum_x * sum_x2 * sum_x2 * sum_x2 * sum_xy * sum_x4 - sum_x * sum_x3 * sum_x2 * sum_x2 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x2 * sum_x2 * sum_x3 * sum_x4 - sum_x * sum_x3 * sum_x3 * sum_x2 * sum_x2 * sum_x4 + sum_x * sum_x3 * sum_x3 * sum_x3y * sum_x2 * sum_x4 - sum_x2 * sum_x2 * sum_x2 * sum_x3y * sum_x4 - sum_x2 * sum_x2 * sum_x3 * sum_x2 * sum_x2 * sum_x4 + sum_x2 * sum_x2 * sum_x3 * sum_x3y * sum_x2 * sum_x4 + n * sum_x * sum_x2 * sum_x3 * sum_x4 - n * sum_x * sum_x2 * sum_x2 * sum_x2 * sum_x4 - n * sum_x * sum_x2 * sum_x3 * sum_x3 * sum_x2 * sum_x4 + n * sum_x * sum_x2 * sum_x2 * sum_x3 * sum_x3 * sum_x4;

		*a = 1.0 * a_numerator / denominator;
		*b = 1.0 * b_numerator / denominator;
		*c = 1.0 * c_numerator / denominator;
		*d = 1.0 * d_numerator / denominator;
	}

};






void showxy(ExMessage& msg);
void testUI(Node*, List, int, Node* admin, List Admin_List);

void loginUI();

void menuUI_Tch(Node*, List, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);
void menuUI_Administrator(Node*, List, List allStuList, Cpnode allCrsList);

void allStuUI(Node*, List, int, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);
void StuUI(Node* Crs, List allStuList, wchar_t* pname, int* pid, Node*, List, int, Node* admin, List Admin_List, Cpnode allCrsList);
void RankUI(List StuList, Node*, List, int, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);

void allCrsUI(Node*, List, int, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);
void CrsUI(Cpnode cphead, Cpnode cplist, Node*, List, int, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);

void allQualityUI(Node*, List, int, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);
void QualityUI(Node* Stu, List allStuList, Node*, List, int, Node* admin, List Admin_List, Cpnode allCrsList);
void allTchUI(Node* admin, List adminList, List allStuList, Cpnode allCrsList);
void manageUI(Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);//管理员端改密码
void Modify_Stu_or_Tch_Password_UI(const wchar_t* account, Node* Stu, int judge, List StuList, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);//学生教师改密码

void changeMajorUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);

void chartUI(vector<vector<wstring>> _data, int row1, int row2, int stuID, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);
void stuAccountUI(int stuID, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);

void chooseCrsUI(int stuID, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList);


void logUI(Node* admin, List adminList, List allStuList, Cpnode allCrsList);


void showLog(vector<vector<wstring>> data, wchar_t* searchTerm);





void printStu(const List StuList);


void printCrs(const Cpnode CrsList);


bool showAllStuTest(const List StuList, vector<vector<std::wstring>>& data, const wchar_t* searchTerm);





double preditcGrid(vector<vector<wstring>> _data, int col1, int col2);

void linear_regression(vector<wstring> y, int n, double* slope, double* intercept);







#endif
