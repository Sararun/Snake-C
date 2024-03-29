﻿#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

bool gamewover;
const int width = 50;
const int height = 20;
const int wdth = 100;
const int heght = 20;
int x, y, fruitx, fruity, score, j, d;
int tailx[100], taily[100];
int nTail;
bool itMoves;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
int level;
string name;
int t;




void setup()/*данные с которыми начинается игра*/
{
	gamewover = false;
	dir = STOP;
	x = width / 2 - 1;//Центрирование
	y = height / 2 - 1;
	fruitx = rand() % (width - 2) + 1;
	fruity = rand() % (height - 2) + 1;
	score = 0;
	nTail = 0;

}

void setcur(int x, int y)//установка курсора на позицию x y
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

class main_scr /*главный экран*/
{
public:
	void Main_screen()
	{
		cout << "######@@@@@@@@@@@@@@@@@@@@@##############################" << "\n";
		cout << "########@@@@@@@@@@@@@@@@@###################*############" << "\n";
		cout << "##########@@@@@@@@@@@@@#####################/############" << "\n";
		cout << "############@@@@@@@@@###############*****##/#############" << "\n";
		cout << "##############@@@@@#############************#############" << "\n";
		cout << "################@##############***()*****()**############" << "\n";
		cout << "##############################***************############" << "\n";
		cout << "###############################*************#############" << "\n";
		cout << "#############################**********##################" << "\n";
		cout << "###########################*********#################====" << "\n";
		cout << "#########################********##################======" << "\n";
		cout << "#######################*******###################========" << "\n";
		cout << "#####################*******###################==========" << "\n";
		cout << "+###################******####################===========" << "\n";
		cout << "++##################*******###################===========" << "\n";
		cout << "++++################********##################===========" << "\n";
		cout << "++++++###############*********#################==========" << "\n";
		cout << "++++++++##############**********###############==========" << "\n";
		cout << "++++++++++##############**********##############=========" << "\n";
		cout << "++++++++++++##############*********##############========" << "\n";
		cout << "++++++++++++++##############********################=====" << "\n";
		cout << "++++++++++++#################********####################" << "\n";
		cout << "++++++++++##################********#####################" << "\n";
		cout << "++++++++##################*********######################" << "\n";
		cout << "+++++++#################**********#######################" << "\n";
		cout << "++++##################**********########+++++++++########" << "\n";
		cout << "++##################**********########+++++++++++++######" << "\n";
		cout << "###############[Please push any key]#####################" << "\n";

		_getch();
		system("cls");
	}
};

void palyer_name()
{
	system("cls");
	cout << "Введите имя" << "\n";
	cin >> name;
}

void draw()
{

	setcur(0, 0);

	for (int i = 0; i < width + 1; i++)/*потолок*/
		cout << "#";
	cout << "\n";


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {/*стены*/
			if (j == 0 || j == width - 1)
				cout << "#";

			if (i == y && j == x)/*голова*/
				cout << "0";
			else if (i == fruity && j == fruitx)/*фрукт*/
				cout << "F";
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++)/*хвост*/
					if (tailx[k] == j && taily[k] == i) {
						print = true;
						cout << "o";
					}
				if (!print)
					cout << " ";
			}
		}
		if (i == 0) cout << "Клавиши управления";
		if (i == 2) cout << "Esc-выход из игры";
		if (i == 3) cout << "Стрелка вверх-вверх";
		if (i == 4) cout << "Стрелка влево-влево";
		if (i == 5) cout << "Стрелка вправо-вправо";
		if (i == 6) cout << "Стрелка вниз-вниз";
		cout << "\n";
	}

	for (int i = 0; i < width + 1; i++)/*пол*/
		cout << "#";
	cout << "\n";
	cout << "Имя " << name << "\n";
	cout << "Очки " << score << "\n";


}


void move()
{
	itMoves = true;
	switch (dir) {/*если выбран сторона, то змейка двигается в ту сторону с помощью +1*/
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
}


void input(int c)
{
	setcur(0, 0);
	switch (c) {/*управление через стрелки и выход на esc*/
	case 75:
		if (dir != RIGHT)
			dir = LEFT;
		break;
	case 77:
		if (dir != LEFT)
			dir = RIGHT;
		break;
	case 72:
		if (dir != DOWN)
			dir = UP;
		break;
	case 80:
		if (dir != UP)
			dir = DOWN;
		break;
	case 27:
		gamewover = true;
		break;
	}
}


void logic()
{
	if (_kbhit())
		input(_getch());
	setcur(0, 0);
	int prefx = tailx[0]; /*первое положение по координате*/
	int prefy = taily[0];
	int pref2x, pref2y; /*второе положение по координате*/
	tailx[0] = x;
	taily[0] = y;

	move();

	for (int i = 1; i < nTail; i++) {
		pref2x = tailx[i];
		pref2y = taily[i];
		tailx[i] = prefx;
		taily[i] = prefy;
		prefx = pref2x;
		prefy = pref2y;
	}


	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < nTail; i++) {
		if (tailx[i] == x && taily[i] == y)
			gamewover = true;
	}

	if (x == fruitx && y == fruity) {
		score += 10;
		fruitx = rand() % (width - 2) + 1;
		fruity = rand() % (height - 2) + 1;

		nTail++;
	}

	if (_kbhit())
		input(_getch());

}

void gamePause()
{
	t = 100 - (nTail * 3);
	if (t < 0) t = 0;
	switch (level) {
	case 1:Sleep(t);
		break;
	case 2:Sleep(50);
		break;
	case 3:Sleep(0);
		break;
		cin.ignore();
	}
}

void play()
{
	palyer_name();
	while (!gamewover) {
		setcur;
		hidecursor();
		logic();
		draw();
		gamePause();


	}
	system("cls");

	string names[10]
		;
	int scores[10];

	string path = "Рекорд.txt";
	ifstream f(path);
	ofstream fs;


	for (int i = 0; i < 10; i++)
	{
		f >> names[i];
	}
	for (int i = 0; i < 10; i++)
	{
		f >> scores[i];
	}

	int q = 10;
	while (score > scores[q - 1])
	{
		q--;
		if (q == -1)
		{
			q = 0;
			break;
		}
	}
	if (q < 10)
	{
		for (int i = q; i < 10; i++)
		{
			int t = scores[i];
			string s = names[i];
			names[i] = name;
			scores[i] = score;
			name = s;
			score = t;
		}
	}

	fs.open(path);
	for (int i = 0; i < 10; i++)
	{
		fs << names[i] << "\n";
	}
	for (int i = 0; i < 10; i++)
	{
		fs << scores[i] << "\n";
	}
	fs.close();



	cout << "##############################" << "\n";
	cout << "#                            #" << "\n";
	cout << "# Ты проиграл                #" << "\n";



	for (int i = 0; i < 10; i++)
	{
		cout << names[i] << " " << scores[i] << "\n";
	}

	cout << "#                            #" << "\n";
	cout << "# Нажми Enter, начни сначала #" << "\n";
	cout << "# Нажми Esc, чтобы закрыть   #" << "\n";
	cout << "##############################" << "\n" << "\n";

}

void menu()
{

	setup();

	cout << "#############################" << "\n";
	cout << "# Введите уровень сложности #" << "\n";
	cout << "# 1-Легко                   #" << "\n";
	cout << "# 2-Просто                  #" << "\n";
	cout << "# 3-Сложно                  #" << "\n";
	cout << "# 4-Авторы                  #" << "\n";
	cout << "#############################" << "\n" << "\n";
	cout << "Чтобы выйть, нажмите Esc" << "\n";

	switch (_getch()) {
	case '1':
		level = 1;
		play();
		break;
	case '2':
		level = 2;
		play();
		break;
	case '3':
		level = 3;
		play();
		break;
	case '4':
		system("cls");
		cout << "Разработчик проекта" << "\n";
		cout << "Саросек Влад 007 св2." << "\n";
		cout << " " << "\n";
		cout << "((((Люди, которым я хочу вырозить наивысшую благодарность:))))" << "\n";
		cout << "((((Кирилл Огнев 803 г1                                   ))))" << "\n";
		cout << "((((Николай Кошуляну 803 в2                               ))))" << "\n";
		cout << "((((Павел Охотников г2                                    ))))" << "\n";
		cout << " " << "\n";
		cout << "Нажмите на Enter, чтобы вернуться в меню." << "\n";
		cout << "Нажмите Esc, чтобы закрыть программу." << "\n";

		break;
	}

}

int main()
{
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	main_scr scr;
	scr.Main_screen();
	do {
		system("cls");
		menu();

	} while (_getch() != 27);

	system("cls");
	cout << "Увидимся позже" << endl;

	return 0;
}