#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <iterator>
#include <chrono>
#include <Windows.h>
#include <conio.h>
#include <iterator>
#include <functional>
#include <algorithm>

using namespace std;
using namespace chrono;


#define GSH GetStdHandle(STD_OUTPUT_HANDLE)
#define GREEN   SetConsoleTextAttribute(GSH, 0x00a);
#define BLUE   SetConsoleTextAttribute(GSH, 0x00b);
#define RED   SetConsoleTextAttribute(GSH, 0x00c);
#define PUPPLE   SetConsoleTextAttribute(GSH, 0x00d);
#define YELLOW    SetConsoleTextAttribute(GSH, 0x000e);
#define WHITE    SetConsoleTextAttribute(GSH, 0x000f);


using Data = pair < char, double >;

void Menu()
{
	YELLOW;
	cout << "-----------------------------" << endl;
	cout << " 1. 입력하기" << endl;
	cout << " 2. Replay (전체) " << endl;
	cout << " 3. Replay (단계) " << endl;
	cout << "-----------------------------" << endl;
	WHITE;
	cout << " 원하는 메뉴 : ";
	
}

int main()
{

	const char iSpace{ 0 };
	const char iEnter{ 1 };
	char szMenu;

	while (1)
	{
		system("cls");
		Menu();
		cin >> szMenu;
		

		switch (szMenu)
		{
		case '1':
		{
			system("cls");
			ofstream out("리플레이.txt");

			vector<Data> vReplay;

			char szCode;
			double dTime{ 0 };

			BLUE;
			cout << "-----------------------------" << endl;
			cout << "입력 시작" << endl << endl;
		
			cout << "입력을 마치시면 ESC를 눌러주세요" << endl;
			cout << "-----------------------------" << endl << endl;
			WHITE;
			auto start = chrono::system_clock::now();

			while ((szCode = _getch()) != 27)
			{
				auto end = chrono::system_clock::now();
				auto diff = end - start;
				auto msec = chrono::duration_cast<chrono::microseconds>(diff);

				if (szCode == 8)
				{
					cout << "\b" << " ";
				}
				if (szCode == 13)
				{
					cout << endl;
				}

				vReplay.push_back(make_pair(szCode, msec.count()));
				cout << szCode;
			}

			cout << endl;

			auto end = chrono::system_clock::now();
			auto diff = end - start;
			auto msec = chrono::duration_cast<chrono::microseconds>(diff);
			vReplay.push_back(make_pair(szCode, msec.count()));

			for (auto i = vReplay.begin(); i != vReplay.end(); ++i)
			{
				if (i < vReplay.end() - 1)
				{
					if (i->first == 32)
					{
						out << iSpace << "\t" << i->second - vReplay.begin()->second << endl;
					}
					else if (i->first == 13)
					{
						out << iEnter << "\t" << i->second - vReplay.begin()->second << endl;
					}
					else
					{
						out << i->first << "\t" << i->second - vReplay.begin()->second << endl;
					}
				}

				if (i == vReplay.end() - 1)
				{
					if (i->first == 32)
					{
						out << iSpace << "\t" << i->second - vReplay.begin()->second << endl;
					}
					else if (i->first == 13)
					{
						out << iEnter << "\t" << i->second - vReplay.begin()->second << endl;
					}
					else
					{
						out << i->first << "\t" << i->second - vReplay.begin()->second << endl;
					}
				}
			}

			out.close();
			BLUE;
			cout << endl << "-----------------------------" << endl;
			cout << "저장 완료  		  " << endl;
			cout << "-----------------------------" << endl;
			Sleep(2000);
			break;
		}
		case '2':
		{
			system("cls");
			BLUE;
			cout << "-----------------------------" << endl;
			cout << "Replay 시작  	  " << endl;
			cout << "-----------------------------" << endl << endl;
			//system_clock::time_point end;
			WHITE;
			vector<Data> vReplay;

			char szCode;
			double iTime{ 0 };

			ifstream in("리플레이.txt");

			while (in >> szCode >> iTime)
			{
				vReplay.push_back(make_pair(szCode, iTime));
			}

			auto start = chrono::system_clock::now();

			for (auto i = vReplay.begin(); i != vReplay.end();)
			{
				auto end = chrono::system_clock::now();
				auto diff = end - start;
				auto msec = chrono::duration_cast<chrono::microseconds>(diff);

				if (msec.count() >= i->second)
				{
					if (i->first == 8)
					{
						cout << "\b" << " ";
					}
					if (i->first == 27)
						break;
					if (i->first == iEnter)
					{
						cout << endl;
					}
					else if (i->first == iSpace)
					{
						cout << " ";
					}
					else
					{
						cout << i->first;
					}
					++i;

				}
			}

			cout << endl << endl;
			BLUE;
			cout << "-----------------------------" << endl;
			cout << "Replay 끝  		  " << endl;
			cout << "-----------------------------" << endl;
			in.close();
			Sleep(2000);
			break;
		}
		case '3':
		{
			system("cls");
			BLUE;
			cout << "-----------------------------" << endl;
			cout << "Replay 시작 		  " << endl;
			cout << " -> 키를 누르면 0.1초씩 진행" << endl;
			cout << "-----------------------------" << endl << endl;

			WHITE;
			vector<Data> vStep;
			vector<Data> vTemp;

			char szOder;
			char szCode;
			double iTime{ 0 };
			int dTimePoint{ 100000 };
			int iCount{ 1 };


			ifstream in("리플레이.txt");
			while (in >> szCode >> iTime)
			{
				vStep.push_back(make_pair(szCode, iTime));
			}

			for (auto i = vStep.begin(); i != vStep.end();)
			{
				chrono::microseconds s(dTimePoint);
				if ((szOder = _getch()) == 77)
				{
					auto msec = chrono::duration_cast<chrono::microseconds>(s);
					while ((i->second <= msec.count()))
					{
						if (i->first == 8)
						{
							cout << "\b" << " ";

						}
						if (i->first == 27)
							break;
						if (i->first == iEnter)
						{
							cout << endl;
						}
						else if (i->first == iSpace)
						{
							cout << " ";
						}
						else
						{
							cout << i->first;
						}

						++i;
					}
					dTimePoint += 100000;

				}

				if (i + 1 == vStep.end())
					break;

				if (szOder == 27)
					break;
			}




			cout << endl << endl;
			BLUE;
			cout << "-----------------------------" << endl;
			cout << "Replay 끝  		  " << endl;
			cout << "-----------------------------" << endl;
			in.close();
			Sleep(2000);
			break;
		}
		}
	}
}
