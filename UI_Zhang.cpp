#pragma warning(disable:4996)

#include "main.h"
#define STU_FILE ".\\data\\Student.txt"
#define CRS_FILE ".\\data\\Course.txt"

//������ʱ������Է������ڣ�����ô�죻��ʱ��Ļ�������������



//����1��Ϊʲôû��titleText->move(-500, 50);�Ͳ���
//����2��Ϊʲô��ʱ��Ҫ�����غ���ı�����У�����allCrsUI�е�if (screenCrsBtn.mouseClick(msg))֮��
void modifyTitleText(Text* titleText, const wchar_t* text, int y)
{
	titleText->move(-500, 50);
	int areaWidth = 280;
	int size = 64;
	settextstyle(size, 0, L"΢���ź�");
	int textWidth = textwidth(text);
	while (textWidth > areaWidth)
	{
		size -= 2;
		settextstyle(size, 0, L"΢���ź�");
		textWidth = textwidth(text);
	}
	int x = 10 + (290 - textWidth) / 2;
	titleText->setTextSize(size);
	titleText->setText(text);
	titleText->move(x, y);
	return;
}

int mainZ(void)
{

	setlocale(LC_ALL, ""); //ʹ����̨֧�ֿ��ַ����

	// ��ʼ��ͼ�δ���
	initgraph(1500, 810);
	BeginBatchDraw(); //��ʼ������ͼ
	setbkcolor(RGB(55, 61, 53)); //������ɫ
	cleardevice();

	loginUI();

	EndBatchDraw(); //����������ͼ
	closegraph(); // �ر�ͼ�δ���
	return 0;
}

void allCrsUI(Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList)
{
	cleardevice();
	//Cpnode allCrsList = readCrs(CRS_FILE);
	vector<vector<std::wstring>> allCrsData;
	showAllCrs(allCrsList, allCrsData, L"", 0, 0, 0);

	//List allStuList = readStu(STU_FILE);

	Table allCrsTable(310, 90, 940 + 220, 700, allCrsData);

	Text titleText(40, 10, L"���пγ�", 64);

	TextBox searchInputBox(310, 20, 820 + 220 - 120, L"����", L"");
	TextBox cnameBox(-500, 0, 290, L"�γ�����", L"");
	TextBox cnumBox(-500, 0, 290, L"�γ̺�", L"");
	TextBox characterBox(-500, 0, 290, L"�γ�����", L"");
	TextBox creditBox(-500, 0, 290, L"ѧ��", L"");
	TextBox SchYearBox(-500, 0, 290, L"ѧ��", L"");
	TextBox minBox(-500, 0, 290, L"��Сֵ", L"");
	TextBox maxBox(-500, 0, 290, L"���ֵ", L"");

	Button searchBtn(1150 + 220 - 120, 20, 100, 50, L"����", 1);
	Button drawBtn(1150 + 220, 20, 100, 50, L"��ͼ", 1);

	int y = 90 - 80, dy = 80;//�����λ��,����˵������������Ctrl+C���͡�Ctrl+V���ı��˼��
	Button viewCrsBtn(-50, y += dy, 330, 60, L"   �鿴", 1);
	Button addCrsBtn(-50, y += dy, 330, 60, L"   ���", 1);
	Button modifyCrsBtn(-50, y += dy, 330, 60, L"   �޸�", 1);
	Button deleteCrsBtn(-50, y += dy, 330, 60, L"   ɾ��", 1);
	Button sortCrsBtn(-50, y += dy, 330, 60, L"   ����", 1);
	Button screenCrsBtn(-50, y += dy, 330, 60, L"   ɸѡ", 1);
	Button screenCancelBtn(-500, 0, 330, 60, L"   ȡ��ɸѡ", 1);
	Button exportBtn(-50, y += dy, 330, 60, L"   ����", 1);
	Button inportBtn(-50, y += dy, 330, 60, L"   ����", 1);
	Button backButton(-50, y += dy, 330, 60, L"   ����", 0);

	Button sortByCnumBtn(-500, 0, 290, 60, L"���γ̺�����", 1);
	Button sortBySchYearBtn(-500, 0, 290, 60, L"��ѧ������", 1);
	Button sortByHeadcountBtn(-500, 0, 290, 60, L"������������", 1);
	Button sortByAverscoreBtn(-500, 0, 290, 60, L"��ƽ���ɼ�����", 1);
	Button sortByAverGPABtn(-500, 0, 290, 60, L"��ƽ����������", 1);
	Button sortByPassRateBtn(-500, 0, 290, 60, L"������������", 1);
	Button sortByExcelRateGPABtn(-500, 0, 290, 60, L"������������", 1);
	Button AscendingOrderBtn(-500, 0, 290, 60, L"����", 1);
	Button DescendingOrderBtn(-500, 0, 290, 60, L"����", 1);

	Button screenBySchYearBtn(-500, 0, 290, 60, L"��ѧ��ɸѡ", 1);
	Button screenByHeadcountBtn(-500, 0, 290, 60, L"��������ɸѡ", 1);
	Button screenByAverscoreBtn(-500, 0, 290, 60, L"��ƽ���ɼ�ɸѡ", 1);
	Button screenByAverGPABtn(-500, 0, 290, 60, L"��ƽ������ɸѡ", 1);
	Button screenByPassRateBtn(-500, 0, 290, 60, L"��������ɸѡ", 1);
	Button screenByExcelRateBtn(-500, 0, 290, 60, L"��������ɸѡ", 1);

	Button addOKButton(-500, 0, 290, 60, L"ȷ�����", 1);
	Button modifyOKButton(-500, 0, 290, 60, L"ȷ���޸�", 1);
	Button screenOKButton(-500, 0, 290, 60, L"ȷ��ɸѡ", 1);
	Button cancelButton(-500, 0, 290, 60, L"ȡ��", 0);


	// ��������¼�
	ExMessage msg;
	int sortOption = 0;//��������
	wchar_t searchTerm[512] = L"";
	bool IsInScreen = false;
	int screenOption = 0;
	double screenMin = 0;
	double screenMax = 0;
	while (!_kbhit())
	{
		ULONGLONG start_time = GetTickCount();
		//->

		searchInputBox.draw();
		cnameBox.draw();
		cnumBox.draw();
		characterBox.draw();
		creditBox.draw();
		SchYearBox.draw();
		minBox.draw();
		maxBox.draw();

		if (peekmessage(&msg, -1, true))
		{

			if (drawBtn.mouseClick(msg))
			{
				chartUI(allCrsData, 0, 6, 0, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);

				cleardevice();
				allCrsTable.draw();
				titleText.draw();
				searchInputBox.draw();
				searchBtn.draw();
				drawBtn.draw();
				y = 90 - 80, dy = 80;//�����λ��,����˵������������Ctrl+C���͡�Ctrl+V���ı��˼��
				viewCrsBtn.draw();
				addCrsBtn.draw();
				modifyCrsBtn.draw();
				deleteCrsBtn.draw();
				sortCrsBtn.draw();
				screenCrsBtn.draw();
				screenCancelBtn.draw();
				exportBtn.draw();
				inportBtn.draw();
				backButton.draw();

			}
			if (cancelButton.mouseClick(msg)) {

				sortOption = 0;
				if (IsInScreen)
				{
					screenOption = 0;
					IsInScreen = false;
				}

				// ������������
				cnameBox.clear();
				cnumBox.clear();
				characterBox.clear();
				SchYearBox.clear();
				creditBox.clear();
				minBox.clear();
				maxBox.clear();

				// ʹ���ɱ仯
				allCrsTable.canChange = true;

				// ����
				cnameBox.move(-500, 0);
				cnumBox.move(-500, 0);
				characterBox.move(-500, 0);
				creditBox.move(-500, 0);
				SchYearBox.move(-500, 0);
				minBox.move(-500, 0);
				maxBox.move(-500, 0);


				sortByCnumBtn.move(-500, 0);
				sortBySchYearBtn.move(-500, 0);
				sortByHeadcountBtn.move(-500, 0);
				sortByAverscoreBtn.move(-500, 0);
				sortByAverGPABtn.move(-500, 0);
				sortByPassRateBtn.move(-500, 0);
				sortByExcelRateGPABtn.move(-500, 0);
				AscendingOrderBtn.move(-500, 0);
				DescendingOrderBtn.move(-500, 0);

				screenBySchYearBtn.move(-500, 0);
				screenByHeadcountBtn.move(-500, 0);
				screenByAverscoreBtn.move(-500, 0);
				screenByAverGPABtn.move(-500, 0);
				screenByPassRateBtn.move(-500, 0);
				screenByExcelRateBtn.move(-500, 0);

				addOKButton.move(-500, 0);
				modifyOKButton.move(-500, 0);
				screenOKButton.move(-500, 0);
				cancelButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"���пγ�", 10);

				// ��ʾ
				y = 90 - 80, dy = 80;
				viewCrsBtn.move(-50, y += dy);
				addCrsBtn.move(-50, y += dy);
				modifyCrsBtn.move(-50, y += dy);
				deleteCrsBtn.move(-50, y += dy);
				sortCrsBtn.move(-50, y += dy);
				if (!screenOption)
					screenCrsBtn.move(-50, y += dy);
				else
					screenCancelBtn.move(-50, y += dy);
				exportBtn.move(-50, y += dy);
				inportBtn.move(-50, y += dy);
				backButton.move(-50, y += dy);

			}

			if (searchBtn.mouseClick(msg))
			{
				wcscpy(searchTerm, searchInputBox.text);
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);
			}

			if (viewCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��γ�", L"����!", MB_ICONERROR);
				}
				else
				{
					// ��ȡ�γ̽ڵ���Ϣ
					int cnum;
					int SchYear;
					int selectedRow = allCrsTable.getSelectedRow(); // ��ȡ��ǰ��
					getNumberInBox(99999, &cnum, allCrsData[selectedRow][1].c_str());
					getNumberInBox(99999, &SchYear, allCrsData[selectedRow][4].c_str());
					Cpnode cplist = searchCrs(allCrsList, cnum, SchYear);
					CrsUI(allCrsList, cplist, tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);


					cleardevice();
					allCrsTable.draw();
					titleText.draw();
					searchInputBox.draw();
					searchBtn.draw();
					drawBtn.draw();
					y = 90 - 80, dy = 80;//�����λ��,����˵������������Ctrl+C���͡�Ctrl+V���ı��˼��
					viewCrsBtn.draw();
					addCrsBtn.draw();
					modifyCrsBtn.draw();
					deleteCrsBtn.draw();
					sortCrsBtn.draw();
					screenCrsBtn.draw();
					screenCancelBtn.draw();
					exportBtn.draw();
					inportBtn.draw();
					backButton.draw();

				}
			}

			if (addCrsBtn.mouseClick(msg))
			{
				// ����
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"��ӿγ�", 10);

				// ��ʾ
				y = 150 - 80, dy = 80;
				cnameBox.move(10, y += dy);
				cnumBox.move(10, y += dy);
				characterBox.move(10, y += dy);
				creditBox.move(10, y += dy);
				SchYearBox.move(10, y += dy);
				addOKButton.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (addOKButton.mouseClick(msg))
			{
				wchar_t cname[30];
				int cnum;
				wchar_t character[5];
				double credit;
				int SchYear;

				// �ж������ʽ
				if (
					getTextInBox(cname, cnameBox.text) &&
					getNumberInBox(99999, &cnum, cnumBox.text) &&
					getTextInBox(character, characterBox.text) &&
					getDoubleInBox(10, &credit, creditBox.text) &&
					getNumberInBox(99999, &SchYear, SchYearBox.text) &&
					cnum > 9999 && credit > 0
					)
				{

					// �γ���ͬ�����,��������
					if (!addCrs(allCrsList, cname, cnum, character, credit, SchYear))
					{
						MessageBox(GetHWnd(), L"�ÿγ̺��Ѿ�����,�����ظ����!", L"����!", MB_ICONERROR);
					}
					else
					{
						// ����
						saveCrs(allCrsList, CRS_FILE);

						writeLog(judge, tch_or_admin, wstring(L"��ӿγ�:") + to_wstring(cnum));


						// ˢ�±��
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);

						// ������������
						cnameBox.clear();
						cnumBox.clear();
						characterBox.clear();
						creditBox.clear();
						SchYearBox.clear();

						// ����
						cnameBox.move(-500, 0);
						cnumBox.move(-500, 0);
						characterBox.move(-500, 0);
						creditBox.move(-500, 0);
						SchYearBox.move(-500, 0);
						addOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// ���ı���
						modifyTitleText(&titleText, L"���пγ�", 10);

						// ��ʾ
						y = 90 - 80, dy = 80;
						viewCrsBtn.move(-50, y += dy);
						addCrsBtn.move(-50, y += dy);
						modifyCrsBtn.move(-50, y += dy);
						deleteCrsBtn.move(-50, y += dy);
						sortCrsBtn.move(-50, y += dy);
						if (!screenOption)
							screenCrsBtn.move(-50, y += dy);
						else
							screenCancelBtn.move(-50, y += dy);
						exportBtn.move(-50, y += dy);
						inportBtn.move(-50, y += dy);
						backButton.move(-50, y += dy);
					}


				}
				// �������
				else
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (modifyCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��γ�", L"����!", MB_ICONERROR);
				}
				else
				{
					// ����
					viewCrsBtn.move(-500, 0);
					addCrsBtn.move(-500, 0);
					modifyCrsBtn.move(-500, 0);
					deleteCrsBtn.move(-500, 0);
					sortCrsBtn.move(-500, 0);
					screenCrsBtn.move(-500, 0);
					screenCancelBtn.move(-500, 0);
					exportBtn.move(-500, 0);
					inportBtn.move(-500, 0);
					backButton.move(-500, 0);

					// ���ı���
					modifyTitleText(&titleText, L"�޸Ŀγ�", 10);

					// ʹ��񲻿ɱ仯
					allCrsTable.canChange = false;

					// ��ȡ��ǰ��
					int selectedRow = allCrsTable.getSelectedRow();
					vector<std::wstring> selectedData = allCrsData[selectedRow];

					// �ı���Ĭ������
					cnameBox.setText(selectedData[0].c_str());
					cnumBox.setText(selectedData[1].c_str());
					characterBox.setText(selectedData[2].c_str());
					creditBox.setText(selectedData[3].c_str());
					SchYearBox.setText(selectedData[4].c_str());


					// ��ʾ
					y = 150 - 80, dy = 80;
					cnameBox.move(10, y += dy);
					cnumBox.move(10, y += dy);
					characterBox.move(10, y += dy);
					creditBox.move(10, y += dy);
					SchYearBox.move(10, y += dy);
					modifyOKButton.move(10, y += dy);
					cancelButton.move(10, y += dy);
				}

			}

			//�����ſε�ѧ����Ϣ��Ҫ�޸�
			if (modifyOKButton.mouseClick(msg))
			{
				wchar_t cname[30];
				int cnum;
				wchar_t character[5];
				double credit;
				int SchYear;

				// ��ȷ�����γ̽ڵ�
				int original_cnum;
				int original_SchYear;
				int selectedRow = allCrsTable.getSelectedRow(); // ��ȡ��ǰ��
				getNumberInBox(99999, &original_cnum, allCrsData[selectedRow][1].c_str());
				getNumberInBox(99999, &original_SchYear, allCrsData[selectedRow][4].c_str());
				Cpnode modifyingCrs = searchCrs(allCrsList, original_cnum, original_SchYear);

				// �ж������ʽ
				if (
					getTextInBox(cname, cnameBox.text) &&
					getNumberInBox(99999, &cnum, cnumBox.text) &&
					getTextInBox(character, characterBox.text) &&
					getDoubleInBox(10, &credit, creditBox.text) &&
					getNumberInBox(99999, &SchYear, SchYearBox.text) &&
					cnum > 9999 && credit > 0 && SchYear > 0&&
					(wcscmp(character,L"����")==0|| wcscmp(character, L"ѡ��") == 0)
					)
				{
					if (searchCrs(allCrsList, cnum, SchYear))
					{
						MessageBox(GetHWnd(), L"�γ̳�ͻ", L"����!", MB_ICONWARNING);
					}
					else
					{
						Node* StuNode = allStuList->next;
						while (StuNode)
						{
							wchar_t wch_cnum[10];
							swprintf(wch_cnum, 10, L"%d", modifyingCrs->cnum);
							Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, modifyingCrs->cname);
							if (CrsNode)
							{
								swprintf(wch_cnum, 10, L"%d", cnum);
								int digit_character = wcscmp(character, L"����") ? 0 : 1;//������1
								modifyCrsInStu(CrsNode, wch_cnum, cname, CrsNode->score.score, SchYear, digit_character, credit, CrsNode->score.grid);
							}
							StuNode = StuNode->next;
						}

						// �޸�
						modifyCrs(modifyingCrs, cname, cnum, character, credit, SchYear);

						// ����
						saveCrs(allCrsList, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"�޸Ŀγ�:") + to_wstring(cnum));

						// ʹ���ɱ仯
						allCrsTable.canChange = true;

						// ˢ�±��
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);

						// ������������
						cnameBox.clear();
						cnumBox.clear();
						characterBox.clear();
						creditBox.clear();
						SchYearBox.clear();

						// ����
						cnameBox.move(-500, 0);
						cnumBox.move(-500, 0);
						characterBox.move(-500, 0);
						creditBox.move(-500, 0);
						SchYearBox.move(-500, 0);
						modifyOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// ���ı���
						modifyTitleText(&titleText, L"���пγ�", 10);

						// ��ʾ
						y = 90, dy = 80;
						viewCrsBtn.move(-50, y);
						addCrsBtn.move(-50, y += dy);
						modifyCrsBtn.move(-50, y += dy);
						deleteCrsBtn.move(-50, y += dy);
						sortCrsBtn.move(-50, y += dy);
						if (!screenOption)
							screenCrsBtn.move(-50, y += dy);
						else
							screenCancelBtn.move(-50, y += dy);
						exportBtn.move(-50, y += dy);
						inportBtn.move(-50, y += dy);
						backButton.move(-50, y += dy);
					}

				}
				// �������
				else
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			//�����ſε�ѧ����Ϣ��Ҫ�޸�
			if (deleteCrsBtn.mouseClick(msg))
			{
				if (allCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��γ�", L"����!", MB_ICONERROR);
				}
				else
				{
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ�����ſγ���?", L"ɾ���γ�", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{ // ���ȷ��

						// ��ȡ�γ̽ڵ���Ϣ
						wchar_t cname[30];
						int cnum;
						int selectedRow = allCrsTable.getSelectedRow(); // ��ȡ��ǰ��
						getTextInBox(cname, allCrsData[selectedRow][0].c_str());
						getNumberInBox(99999, &cnum, allCrsData[selectedRow][1].c_str());

						Node* StuNode = allStuList->next;
						while (StuNode)
						{
							wchar_t wch_cnum[10];
							swprintf(wch_cnum, 10, L"%d", cnum);
							Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cname);
							if (CrsNode)
								deleteCrsInStu(StuNode, CrsNode);
							StuNode = StuNode->next;
						}

						// ɾ��
						deleteCrs(allCrsList, cname, cnum);

						// ����
						saveCrs(allCrsList, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"ɾ���γ�:") + to_wstring(cnum));



						// ˢ�±��
						showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
						allCrsTable.setData(allCrsData);
					}
				}
			}

			if (sortCrsBtn.mouseClick(msg))
			{
				//Ҫ�����غ���ı��⣬�����bug����֪��Ϊɶ

				// ����
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"����", 50);

				// ��ʾ
				y = 150 - 80, dy = 80;
				sortByCnumBtn.move(10, y += dy);
				sortBySchYearBtn.move(10, y += dy);
				sortByHeadcountBtn.move(10, y += dy);
				sortByAverscoreBtn.move(10, y += dy);
				sortByAverGPABtn.move(10, y += dy);
				sortByPassRateBtn.move(10, y += dy);
				sortByExcelRateGPABtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (sortByCnumBtn.mouseClick(msg))
				sortOption = 1;
			if (sortBySchYearBtn.mouseClick(msg))
				sortOption = 3;
			if (sortByHeadcountBtn.mouseClick(msg))
				sortOption = 5;
			if (sortByAverscoreBtn.mouseClick(msg))
				sortOption = 7;
			if (sortByAverGPABtn.mouseClick(msg))
				sortOption = 9;
			if (sortByPassRateBtn.mouseClick(msg))
				sortOption = 11;
			if (sortByExcelRateGPABtn.mouseClick(msg))
				sortOption = 13;

			if (sortOption)
			{
				// ����
				sortByCnumBtn.move(-500, 0);
				sortBySchYearBtn.move(-500, 0);
				sortByHeadcountBtn.move(-500, 0);
				sortByAverscoreBtn.move(-500, 0);
				sortByAverGPABtn.move(-500, 0);
				sortByPassRateBtn.move(-500, 0);
				sortByExcelRateGPABtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// ���ı���
				wchar_t titletext[512];
				switch (sortOption)
				{
				case 1:
					wcscpy(titletext, L"���γ̺�����");
					break;
				case 3:
					wcscpy(titletext, L"��ѧ������");
					break;
				case 5:
					wcscpy(titletext, L"������������");
					break;
				case 7:
					wcscpy(titletext, L"��ƽ���ɼ�����");
					break;
				case 9:
					wcscpy(titletext, L"��ƽ����������");
					break;
				case 11:
					wcscpy(titletext, L"������������");
					break;
				case 13:
					wcscpy(titletext, L"������������");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				// ��ʾ
				y = 150 - 80, dy = 80;
				AscendingOrderBtn.move(10, y += dy);
				DescendingOrderBtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			bool flag_AscendingOrderBtn = AscendingOrderBtn.mouseClick(msg);//����ô����AscendingOrderBtn.mouseClick(msg)��һ��ѭ����ֻ�ᱻ���һ��
			bool flag_DescendingOrderBtn = DescendingOrderBtn.mouseClick(msg);
			if (flag_DescendingOrderBtn)
				sortOption++;

			if (flag_AscendingOrderBtn || flag_DescendingOrderBtn)
			{
				//��������
				sortCrs(allCrsList, sortOption);

				// ˢ�±��
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				// ����
				AscendingOrderBtn.move(-500, 0);
				DescendingOrderBtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"���пγ�", 10);

				// ��ʾ
				y = 90 - 80, dy = 80;
				viewCrsBtn.move(-50, y += dy);
				addCrsBtn.move(-50, y += dy);
				modifyCrsBtn.move(-50, y += dy);
				deleteCrsBtn.move(-50, y += dy);
				sortCrsBtn.move(-50, y += dy);
				if (!screenOption)
					screenCrsBtn.move(-50, y += dy);
				else
					screenCancelBtn.move(-50, y += dy);
				exportBtn.move(-50, y += dy);
				inportBtn.move(-50, y += dy);
				backButton.move(-50, y += dy);

				sortOption = 0;
			}

			if (screenCrsBtn.mouseClick(msg))
			{
				// ����
				viewCrsBtn.move(-500, 0);
				addCrsBtn.move(-500, 0);
				modifyCrsBtn.move(-500, 0);
				deleteCrsBtn.move(-500, 0);
				sortCrsBtn.move(-500, 0);
				screenCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				exportBtn.move(-500, 0);
				inportBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"ɸѡ", 50);

				// ��ʾ
				y = 150 - 80, dy = 80;
				screenBySchYearBtn.move(10, y += dy);
				screenByHeadcountBtn.move(10, y += dy);
				screenByAverscoreBtn.move(10, y += dy);
				screenByAverGPABtn.move(10, y += dy);
				screenByPassRateBtn.move(10, y += dy);
				screenByExcelRateBtn.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (screenBySchYearBtn.mouseClick(msg))
			{
				screenOption = 1;
				IsInScreen = true;
			}
			if (screenByHeadcountBtn.mouseClick(msg))
			{
				screenOption = 2;
				IsInScreen = true;
			}
			if (screenByAverscoreBtn.mouseClick(msg))
			{
				screenOption = 3;
				IsInScreen = true;
			}
			if (screenByAverGPABtn.mouseClick(msg))
			{
				screenOption = 4;
				IsInScreen = true;
			}
			if (screenByPassRateBtn.mouseClick(msg))
			{
				screenOption = 5;
				IsInScreen = true;
			}
			if (screenByExcelRateBtn.mouseClick(msg))
			{
				screenOption = 6;
				IsInScreen = true;
			}

			if (IsInScreen)
			{
				// ����
				screenBySchYearBtn.move(-500, 0);
				screenByHeadcountBtn.move(-500, 0);
				screenByAverscoreBtn.move(-500, 0);
				screenByAverGPABtn.move(-500, 0);
				screenByPassRateBtn.move(-500, 0);
				screenByExcelRateBtn.move(-500, 0);

				// ���ı���
				wchar_t titletext[512];
				switch (screenOption)
				{
				case 1:
					wcscpy(titletext, L"��ѧ��ɸѡ");
					break;
				case 2:
					wcscpy(titletext, L"��������ɸѡ");
					break;
				case 3:
					wcscpy(titletext, L"��ƽ���ɼ�ɸѡ");
					break;
				case 4:
					wcscpy(titletext, L"��ƽ������ɸѡ");
					break;
				case 5:
					wcscpy(titletext, L"��������ɸѡ");
					break;
				case 6:
					wcscpy(titletext, L"��������ɸѡ");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				//��ʾ
				y = 150 - 80, dy = 80;
				minBox.move(10, y += dy);
				maxBox.move(10, y += dy);
				screenOKButton.move(10, y += dy);
				cancelButton.move(10, y += dy);
			}

			if (screenOKButton.mouseClick(msg))
			{
				double MAX;
				switch (screenOption)
				{
				case 1://��ѧ��ɸѡ
				case 2://��������ɸѡ
					MAX = 99999;//�������
					break;
				case 3://��ƽ���ɼ�
					MAX = 100;
					break;
				case 4://��ƽ������
					MAX = 4;
					break;
				case 5://��������ɸѡ
				case 6://��������ɸѡ
					MAX = 1;
					break;

				}
				if (
					getDoubleInBox(MAX, &screenMin, minBox.text) &&
					getDoubleInBox(MAX, &screenMax, maxBox.text) &&
					screenMin >= 0 && screenMax >= 0 && screenMin <= screenMax
					)
				{
					// ˢ�±��
					showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
					allCrsTable.setData(allCrsData);

					// ������������
					minBox.clear();
					maxBox.clear();

					// ����
					minBox.move(-500, 0);
					maxBox.move(-500, 0);
					screenOKButton.move(-500, 0);
					cancelButton.move(-500, 0);

					// ���ı���
					modifyTitleText(&titleText, L"���пγ�", 10);

					// ��ʾ
					y = 90 - 80, dy = 80;
					viewCrsBtn.move(-50, y += dy);
					addCrsBtn.move(-50, y += dy);
					modifyCrsBtn.move(-50, y += dy);
					deleteCrsBtn.move(-50, y += dy);
					sortCrsBtn.move(-50, y += dy);
					if (!screenOption)
						screenCrsBtn.move(-50, y += dy);
					else
						screenCancelBtn.move(-50, y += dy);
					exportBtn.move(-50, y += dy);
					inportBtn.move(-50, y += dy);
					backButton.move(-50, y += dy);

					IsInScreen = false;
				}
				else// �������
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}
			}

			if (screenCancelBtn.mouseClick(msg))
			{
				screenOption = 0;
				screenMin = 0;
				screenMax = 0;

				// ˢ�±��
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				screenCancelBtn.move(-500, 0);
				screenCrsBtn.move(-50, 490);
			}



			if (exportBtn.mouseClick(msg))
			{
				if (exportCrs(allCrsList, ".\\export\\Crs.csv"))
				{
					MessageBox(GetHWnd(), L"�����ɹ�", L"�����γ�", 0);
					writeLog(judge, tch_or_admin, wstring(L"�������пγ���Ϣ"));
				}
				else {
					MessageBox(GetHWnd(), L"����ʧ��", L"�����γ�", MB_ICONERROR);
				}

				////// ����
				////saveCrs(allCrsList, CRS_FILE);
				////�Ȳ����棬��Ȼ�����һ��֮�������ͬ����, �ڶ��ξ͵��벻����

				////ˢ�±��
				//showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				//allCrsTable.setData(allCrsData);
			}
			if (inportBtn.mouseClick(msg))
			{
				importCrs(allCrsList, ".\\import\\Crs.csv");


				// ˢ�±��
				showAllCrs(allCrsList, allCrsData, searchTerm, screenOption, screenMin, screenMax);
				allCrsTable.setData(allCrsData);

				// ����
				saveCrs(allCrsList, CRS_FILE);

				writeLog(judge, tch_or_admin, wstring(L"����γ���Ϣ"));
			}
			if (backButton.mouseClick(msg))
			{
				return;
				if (judge == 1)
					menuUI_Tch(tch_or_admin, Tch_or_Admin_List, admin, Admin_List, allStuList, allCrsList);
				else
					menuUI_Administrator(tch_or_admin, Tch_or_Admin_List, allStuList, allCrsList);
			}

			//�����껬������
			allCrsTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
			cnameBox.onMessage(msg);
			cnumBox.onMessage(msg);
			characterBox.onMessage(msg);
			creditBox.onMessage(msg);
			SchYearBox.onMessage(msg);
			minBox.onMessage(msg);
			maxBox.onMessage(msg);
		}

		//showxy(msg);

		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1)
		{
			Sleep(1);
		}

	}

}

void CrsUI(Cpnode cphead, Cpnode cplist, Node* tch_or_admin, List Tch_or_Admin_List, int judge, Node* admin, List Admin_List, List allStuList, Cpnode allCrsList)
{
	//List allStuList = readStu(STU_FILE);
	cleardevice();
	Spnode allStuInCrsList = cplist->sphead;
	vector<vector<std::wstring>>allStuInCrsData;
	showAllStuInCrs(cplist, allStuInCrsData, L"", 0, 0, 0);

	Table allStuInCrsTable(310, 90, 940 + 220, 700, allStuInCrsData);


	settextstyle(64, 0, L"΢���ź�");
	int TextWidth = textwidth(cplist->cname);
	int x = 0 + (276 - TextWidth) / 2;
	Text titleText(x, 50, cplist->cname, 64);
	modifyTitleText(&titleText, cplist->cname, 50);

	Text GPAText(-500, 370, L"", 32);

	TextBox searchInputBox(310, 20, 820 + 220, L"����", L"");

	TextBox snameBox(-500, 0, 290, L"ѧ������", L"");
	TextBox snumBox(-500, 0, 290, L"ѧ��", L"");
	TextBox scoreBox(-500, 0, 290, L"�ɼ�", L"");
	TextBox minBox(-500, 0, 290, L"��Сֵ", L"");
	TextBox maxBox(-500, 0, 290, L"���ֵ", L"");


	Button searchBtn(1150 + 220, 20, 100, 50, L"����", 1);

	Button addStuInCrsBtn(-50, 220, 330, 60, L"   ���", 1);
	Button modifyStuInCrsBtn(-50, 300, 330, 60, L"   ¼��/�޸ĳɼ�", 1);
	Button deleteStuInCrsBtn(-50, 380, 330, 60, L"   ɾ��", 1);
	Button sortStuInCrsBtn(-50, 460, 330, 60, L"   ����", 1);
	Button screenStuInCrsBtn(-50, 540, 330, 60, L"   ɸѡ", 1);
	Button screenCancelBtn(-500, 540, 330, 60, L"   ȡ��ɸѡ", 1);
	Button backButton(-50, 620, 330, 60, L"   ����", 0);

	Button upsortBySnumBtn(-500, 220, 290, 60, L"��ѧ������", 1);
	Button downsortBySnumBtn(-500, 300, 290, 60, L"��ѧ�Ž���", 1);
	Button upsortByScoreBtn(-500, 380, 290, 60, L"���ɼ�����", 1);
	Button downsortByScoreBtn(-500, 460, 290, 60, L"���ɼ�����", 1);
	Button upsortByGPABtn(-500, 540, 290, 60, L"��GPA����", 1);
	Button downsortByGPABtn(-500, 620, 290, 60, L"��GPA����", 1);

	Button screenByScoreBtn(-500, 220, 290, 60, L"���ɼ�ɸѡ", 1);
	Button screenByGPABtn(-500, 300, 290, 60, L"��GPAɸѡ", 1);

	Button addOKButton(-500, 580, 290, 60, L"ȷ�����", 1);
	Button modifyOKButton(-500, 580, 290, 60, L"ȷ���޸�", 1);
	Button screenOKButton(-500, 580, 290, 60, L"ȷ��ɸѡ", 1);
	Button cancelButton(-500, 660, 290, 60, L"ȡ��", 0);

	// ��������¼�
	ExMessage msg;
	int sortOption = 0;//��������
	wchar_t searchTerm[512] = L"";
	bool IsInScreen = false;
	int screenOption = 0;
	double screenMin = 0;
	double screenMax = 0;
	while (!_kbhit())
	{
		ULONGLONG start_time = GetTickCount();
		//->

		//������
		searchInputBox.draw();
		snameBox.draw();
		snumBox.draw();
		scoreBox.draw();
		minBox.draw();
		maxBox.draw();

		if (peekmessage(&msg, -1, true))
		{
			if (cancelButton.mouseClick(msg))
			{
				sortOption = 0;
				if (IsInScreen)
				{
					screenOption = 0;
					IsInScreen = false;
				}

				// ������������
				//snameBox.clear();
				//snumBox.clear();
				scoreBox.clear();
				minBox.clear();
				maxBox.clear();

				// ʹ���ɱ仯
				allStuInCrsTable.canChange = true;



				// ����
				snameBox.move(-500, 0);
				snumBox.move(-500, 0);
				scoreBox.move(-500, 0);
				minBox.move(-500, 0);
				maxBox.move(-500, 0);

				addOKButton.move(-500, 0);
				modifyOKButton.move(-500, 0);
				cancelButton.move(-500, 0);

				upsortBySnumBtn.move(-500, 0);
				downsortBySnumBtn.move(-500, 0);
				upsortByScoreBtn.move(-500, 0);
				downsortByScoreBtn.move(-500, 0);
				upsortByGPABtn.move(-500, 0);
				downsortByGPABtn.move(-500, 0);

				screenByScoreBtn.move(-500, 0);
				screenByGPABtn.move(-500, 0);
				screenOKButton.move(-500, 0);
				screenCancelBtn.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, cplist->cname, 50);

				// ��ʾ
				addStuInCrsBtn.move(-50, 220);
				modifyStuInCrsBtn.move(-50, 300);
				deleteStuInCrsBtn.move(-50, 380);
				sortStuInCrsBtn.move(-50, 460);
				if (!screenOption)
					screenStuInCrsBtn.move(-50, 540);
				else
					screenCancelBtn.move(-50, 540);
				backButton.move(-50, 620);

			}

			if (searchBtn.mouseClick(msg))
			{
				wcscpy(searchTerm, searchInputBox.text);
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);
			}

			if (addStuInCrsBtn.mouseClick(msg))
			{
				// ����
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"���ѧ��", 50);

				// ��ʾ
				snameBox.move(10, 140);
				snumBox.move(10, 220);
				scoreBox.move(10, 300);

				addOKButton.move(10, 380);
				cancelButton.move(10, 460);
			}

			//�ڶ�Ӧѧ���Ŀγ�ҳ��ӿγ�
			if (addOKButton.mouseClick(msg))
			{
				wchar_t sname[30];
				int snum;
				double score;

				// �ж������ʽ

				if (
					getTextInBox(sname, snameBox.text) &&
					getNumberInBox(99999999, &snum, snumBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					snum > 9999999 && score >= 0
					)
				{


					Node* StuNode = searchStu(&allStuList, sname, snum);
					if (StuNode == NULL) {
						MessageBox(GetHWnd(), L"�Ҳ������ѧ����", L"����!", MB_ICONERROR);
					}
					else if (!addStuInCrs(cplist, sname, snum, score))
					{
						MessageBox(GetHWnd(), L"��ѧ���Ѿ�����,�����ظ����!", L"����!", MB_ICONERROR);
					}
					else
					{
						wchar_t wch_cnum[10];
						swprintf(wch_cnum, 10, L"%d", cplist->cnum);
						double GPA = CalculGPA(score);
						int character = wcscmp(cplist->character, L"����") ? 0 : 1;//������1
						addCrsToStu(StuNode, wch_cnum, cplist->cname, score, cplist->SchYear, character, cplist->credit, GPA);

						// ����
						saveCrs(cphead, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊ�γ�:") + to_wstring(cplist->cnum) + L"���ѧ��:" + to_wstring(snum));

						// ˢ�±��
						showAllStuInCrs(cplist, allStuInCrsData, L"", screenOption, screenMin, screenMax);
						allStuInCrsTable.setData(allStuInCrsData);

						// ������������
						snameBox.clear();
						snumBox.clear();
						scoreBox.clear();




						// ����
						snameBox.move(-500, 0);
						snumBox.move(-500, 0);
						scoreBox.move(-500, 0);
						addOKButton.move(-500, 0);
						cancelButton.move(-500, 0);

						// ���ı���
						modifyTitleText(&titleText, cplist->cname, 50);

						// ��ʾ
						addStuInCrsBtn.move(-50, 220);
						modifyStuInCrsBtn.move(-50, 300);
						deleteStuInCrsBtn.move(-50, 380);
						sortStuInCrsBtn.move(-50, 460);
						if (!screenOption)
							screenStuInCrsBtn.move(-50, 540);
						else
							screenCancelBtn.move(-50, 540);
						backButton.move(-50, 620);
					}


				}
				// �������
				else
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			if (modifyStuInCrsBtn.mouseClick(msg))
			{
				if (allStuInCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��ѧ��", L"����!", MB_ICONERROR);
				}
				else
				{
					// ����
					addStuInCrsBtn.move(-500, 0);
					modifyStuInCrsBtn.move(-500, 0);
					deleteStuInCrsBtn.move(-500, 0);
					sortStuInCrsBtn.move(-500, 0);
					screenStuInCrsBtn.move(-500, 0);
					screenCancelBtn.move(-500, 0);
					backButton.move(-500, 0);

					// ���ı���
					modifyTitleText(&titleText, L"¼��/�޸ĳɼ�", 50);

					// ʹ��񲻿ɱ仯
					allStuInCrsTable.canChange = false;

					// ��ȡ��ǰ��
					int selectedRow = allStuInCrsTable.getSelectedRow();
					vector<std::wstring> selectedData = allStuInCrsData[selectedRow];

					// �ı���Ĭ������
					snameBox.setText(selectedData[0].c_str());
					snumBox.setText(selectedData[1].c_str());
					scoreBox.setText(selectedData[2].c_str());

					// ��ʾ
					//snameBox.move(10, 220);
					//snumBox.move(10, 300);
					scoreBox.move(10, 380);
					modifyOKButton.move(10, 460);
					cancelButton.move(10, 540);
				}

			}

			//�ڶ�Ӧѧ���Ŀγ�ҳ�޸Ķ�Ӧ�γ̵���Ϣ
			if (modifyOKButton.mouseClick(msg))
			{
				//wchar_t sname[30];
				//int snum;
				double score;

				// ��ȷ�����γ̽ڵ�
				int original_snum;
				wchar_t original_sname[30];
				int selectedRow = allStuInCrsTable.getSelectedRow(); // ��ȡ��ǰ��
				getTextInBox(original_sname, allStuInCrsData[selectedRow][0].c_str());
				getNumberInBox(99999999, &original_snum, allStuInCrsData[selectedRow][1].c_str());
				Spnode modifyingStu = searchStuInCrs(cplist, original_snum);

				// �ж������ʽ
				if (
					//getTextInBox(sname, snameBox.text) &&
					//getNumberInBox(99999999, &snum, snumBox.text) &&
					getDoubleInBox(100, &score, scoreBox.text) &&
					//snum > 9999999 && score >= 0
					score >= 0
					)
				{

					// �޸�
					modifyStuInCrs(cplist, modifyingStu, original_sname, original_snum, score);


					Node* StuNode = searchStu(&allStuList, original_sname, original_snum);
					wchar_t wch_cnum[10];
					swprintf(wch_cnum, 10, L"%d", cplist->cnum);
					int character = wcscmp(cplist->character, L"����") ? 0 : 1;//������1
					Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cplist->cname);
					modifyCrsInStu(CrsNode, wch_cnum, cplist->cname, score, cplist->SchYear, character, cplist->credit, modifyingStu->GPA);

					// ����
					saveCrs(cphead, CRS_FILE);
					saveStu(allStuList, STU_FILE);

					writeLog(judge, tch_or_admin, wstring(L"Ϊ�γ�:") + to_wstring(cplist->cnum) + L"�޸�ѧ��:" + to_wstring(original_snum));

					// ʹ���ɱ仯
					allStuInCrsTable.canChange = true;

					// ˢ�±��
					showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
					allStuInCrsTable.setData(allStuInCrsData);

					// ������������
					//snameBox.clear();
					//snumBox.clear();
					scoreBox.clear();


					// ����
					//snameBox.move(-500, 220);
					//snumBox.move(-500, 300);
					scoreBox.move(-500, 380);
					modifyOKButton.move(-500, 460);
					cancelButton.move(-500, 540);

					// ���ı���
					modifyTitleText(&titleText, cplist->cname, 50);

					// ��ʾ
					addStuInCrsBtn.move(-50, 220);
					modifyStuInCrsBtn.move(-50, 300);
					deleteStuInCrsBtn.move(-50, 380);
					sortStuInCrsBtn.move(-50, 460);
					if (!screenOption)
						screenStuInCrsBtn.move(-50, 540);
					else
						screenCancelBtn.move(-50, 540);
					backButton.move(-50, 620);

				}
				// �������
				else
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}

			}

			//�ڶ�Ӧѧ���Ŀγ�ҳɾ����Ӧ�γ̵���Ϣ
			if (deleteStuInCrsBtn.mouseClick(msg))
			{
				if (allStuInCrsTable.getSelectedRow() == 0)
				{
					MessageBox(GetHWnd(), L"��ѡ��ѧ��", L"����!", MB_ICONERROR);
				}
				else
				{
					int result = MessageBox(GetHWnd(), L"ȷ��ɾ������ѧ����?", L"ɾ��ѧ��", MB_YESNO | MB_ICONQUESTION);

					if (result == IDYES)
					{ // ���ȷ��

						wchar_t sname[30];
						int snum;
						int selectedRow = allStuInCrsTable.getSelectedRow(); // ��ȡ��ǰ��
						getTextInBox(sname, allStuInCrsData[selectedRow][0].c_str());
						getNumberInBox(99999999, &snum, allStuInCrsData[selectedRow][1].c_str());

						// ɾ��
						deleteStuInCrs(cplist, sname, snum);

						Node* StuNode = searchStu(&allStuList, sname, snum);
						wchar_t wch_cnum[10];
						swprintf(wch_cnum, 10, L"%d", cplist->cnum);
						int character = wcscmp(cplist->character, L"����") ? 0 : 1;//������1
						Crsnode* CrsNode = searchCrsInStu(StuNode, wch_cnum, cplist->cname);
						deleteCrsInStu(StuNode, CrsNode);

						// ����
						saveCrs(cphead, CRS_FILE);
						saveStu(allStuList, STU_FILE);

						writeLog(judge, tch_or_admin, wstring(L"Ϊ�γ�:") + to_wstring(cplist->cnum) + L"ɾ��ѧ��:" + to_wstring(snum));

						// ˢ�±��
						showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
						allStuInCrsTable.setData(allStuInCrsData);
					}
				}
			}

			if (sortStuInCrsBtn.mouseClick(msg))//��ʾsort����
			{

				// ����
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				screenCancelBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"����", 50);

				// ��ʾ
				upsortBySnumBtn.move(10, 220);
				downsortBySnumBtn.move(10, 300);
				upsortByScoreBtn.move(10, 380);
				downsortByScoreBtn.move(10, 460);
				upsortByGPABtn.move(10, 540);
				downsortByGPABtn.move(10, 620);
				cancelButton.move(10, 700);
			}

			if (downsortBySnumBtn.mouseClick(msg))
				sortOption = 1;
			if (upsortBySnumBtn.mouseClick(msg))
				sortOption = 2;
			if (downsortByScoreBtn.mouseClick(msg))
				sortOption = 3;
			if (upsortByScoreBtn.mouseClick(msg))
				sortOption = 4;
			if (downsortByGPABtn.mouseClick(msg))
				sortOption = 5;
			if (upsortByGPABtn.mouseClick(msg))
				sortOption = 6;

			if (sortOption)
			{
				//��������
				sortStuInCrs(cplist, sortOption);

				// ˢ�±��
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);


				// ����
				cancelButton.move(-500, 620);
				upsortBySnumBtn.move(-500, 220);
				downsortBySnumBtn.move(-500, 300);
				upsortByScoreBtn.move(-500, 380);
				downsortByScoreBtn.move(-500, 460);
				upsortByGPABtn.move(-500, 540);
				downsortByGPABtn.move(-500, 620);

				// ���ı���
				modifyTitleText(&titleText, cplist->cname, 50);

				// ��ʾ
				addStuInCrsBtn.move(-50, 220);
				modifyStuInCrsBtn.move(-50, 300);
				deleteStuInCrsBtn.move(-50, 380);
				sortStuInCrsBtn.move(-50, 460);
				if (!screenOption)
					screenStuInCrsBtn.move(-50, 540);
				else
					screenCancelBtn.move(-50, 540);
				backButton.move(-50, 620);

				sortOption = 0;
			}

			if (screenStuInCrsBtn.mouseClick(msg))
			{

				// ����
				addStuInCrsBtn.move(-500, 0);
				modifyStuInCrsBtn.move(-500, 0);
				deleteStuInCrsBtn.move(-500, 0);
				sortStuInCrsBtn.move(-500, 0);
				screenStuInCrsBtn.move(-500, 0);
				backButton.move(-500, 0);

				// ���ı���
				modifyTitleText(&titleText, L"ɸѡ", 50);

				// ��ʾ
				screenByScoreBtn.move(10, 220);
				screenByGPABtn.move(10, 300);
				cancelButton.move(10, 380);
			}

			if (screenByScoreBtn.mouseClick(msg))
			{
				screenOption = 1;
				IsInScreen = true;
			}
			if (screenByGPABtn.mouseClick(msg))
			{
				screenOption = 2;
				IsInScreen = true;
			}

			if (IsInScreen)
			{
				// ����
				screenByScoreBtn.move(-500, 0);
				screenByGPABtn.move(-500, 0);
				cancelButton.move(-500, 0);

				// ���ı���
				wchar_t titletext[512];
				switch (screenOption)
				{
				case 1:
					wcscpy(titletext, L"���ɼ�ɸѡ");
					break;
				case 2:
					wcscpy(titletext, L"������ɸѡ");
					break;
				}
				modifyTitleText(&titleText, titletext, 50);

				// ��ʾ
				minBox.move(10, 220);
				maxBox.move(10, 300);
				screenOKButton.move(10, 380);
				cancelButton.move(10, 460);
			}

			if (screenOKButton.mouseClick(msg))
			{
				double MAX;
				switch (screenOption)
				{
				case 1://���ɼ�ɸѡ
					MAX = 100;
					break;
				case -1://��GPA
					MAX = 4;
					break;
				}
				if (
					getDoubleInBox(MAX, &screenMin, minBox.text) &&
					getDoubleInBox(MAX, &screenMax, maxBox.text) &&
					screenMin >= 0 && screenMax >= 0 && screenMin <= screenMax
					)
				{
					// ˢ�±��
					showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
					allStuInCrsTable.setData(allStuInCrsData);

					// ������������
					minBox.clear();
					maxBox.clear();


					// ����
					minBox.move(-500, 0);
					maxBox.move(-500, 0);
					screenOKButton.move(-500, 0);
					cancelButton.move(-500, 0);

					// ���ı���
					modifyTitleText(&titleText, cplist->cname, 50);

					// ��ʾ
					addStuInCrsBtn.move(-50, 220);
					modifyStuInCrsBtn.move(-50, 300);
					deleteStuInCrsBtn.move(-50, 380);
					sortStuInCrsBtn.move(-50, 460);
					screenCancelBtn.move(-50, 540);
					backButton.move(-50, 620);

					IsInScreen = false;
				}
				else// �������
				{
					MessageBox(GetHWnd(), L"�����������������������ݼ���ʽ", L"����!", MB_ICONWARNING);
				}
			}

			if (screenCancelBtn.mouseClick(msg))
			{
				screenOption = 0;
				screenMin = 0;
				screenMax = 0;
				showAllStuInCrs(cplist, allStuInCrsData, searchTerm, screenOption, screenMin, screenMax);
				allStuInCrsTable.setData(allStuInCrsData);

				screenCancelBtn.move(-500, 0);
				screenStuInCrsBtn.move(-50, 540);
			}

			if (backButton.mouseClick(msg))
			{
				//return;����ֱ��return
				return;
				allCrsUI(tch_or_admin, Tch_or_Admin_List, judge, admin, Admin_List, allStuList, allCrsList);
			}

			//�����껬������
			allStuInCrsTable.onMouse(msg);

			// �ı�������
			searchInputBox.onMessage(msg);
			snameBox.onMessage(msg);
			snumBox.onMessage(msg);
			scoreBox.onMessage(msg);
			minBox.onMessage(msg);
			maxBox.onMessage(msg);
		}

		//showxy(msg);

		FlushBatchDraw(); //������ͼ

		ULONGLONG end_time = GetTickCount();
		if (end_time - start_time < 1)
		{
			Sleep(1);
		}

	}
	return;
}






