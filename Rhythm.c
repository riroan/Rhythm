#include<good.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

/*================================================================================*/

#define A 97
#define S 115
#define D 100
#define F 102
#define LEVEL 6

/*================================================================================*/

void Loading();
void Height();
void Block();
void Key();
void DrawEnemy(int i);
void EraseEnemy(int i);
void CreateEnemy();
void ActionEnemy();
void KillEnemy();
void GameOver();
void Interface();

/*================================================================================*/

struct
{
	BOOL exist;
	int x, y;
	int nFrame;
	int nStay;
}Enemy[LEVEL];

struct
{
	BOOL exist;
}Touch[LEVEL];

int score = 0;
int Life = 100;

/*================================================================================*/

int main()
{
	int frame=10000;
	setcursortype(NOCURSOR);
	Loading();
	system("mode con: lines=40");
	Height();
	Block();
	randomize();
	//PlaySound(TEXT("TT.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	while (1) {
		Interface();
		Key();
		CreateEnemy();
		ActionEnemy();
		KillEnemy();
		GameOver();

		delay(1000 / frame);
	}
	getch();
}

/*================================================================================*/

void Loading()
{
	int i;
	for (i = 22; i < 46; i += 2)
	{
		SetColor(WHITE);
		gotoxy(i, 4);	printf("─");
		delay(20);
	}

	gotoxy(46, 4);	printf("┐");
	for (i = 5; i < 10; i++)
	{
		SetColor(SKYBLUE);
		gotoxy(46, i);	printf("│");
		delay(40);
	}

	gotoxy(46, 10);	printf("┘");
	for (i = 44; i > 20; i -= 2)
	{
		SetColor(YELLOW);
		gotoxy(i, 10);	printf("─");
		delay(20);
	}

	gotoxy(20, 10);	printf("└");
	for (i = 9; i > 4; i--)
	{
		SetColor(VIOLET);
		gotoxy(20, i);	printf("│");
		delay(40);
	}

	gotoxy(20, 4);	printf("┌");
	delay(1000);

	SetColor(GREEN);
	gotoxy(23, 7);	printf("R");	delay(300);
	gotoxy(27, 7);	printf("H");	delay(300);
	gotoxy(31, 7);	printf("Y");	delay(300);
	gotoxy(35, 7);	printf("T");	delay(300);
	gotoxy(39, 7);	printf("H");	delay(700);
	gotoxy(43, 7);	printf("M");	delay(300);
	
	SetColor(WHITE);
	gotoxy(20, 13);	printf("시작하려면 아무키나 누르세요!!");
	gotoxy(27, 15);	printf("제작자 : 김명기");
	getch();
}

/*================================================================================*/

void Height()
{
	int i;
	for (i = 0; i < 40; i++) {
		SetColor(WHITE);
		gotoxy(46,i);	printf("│");
	}
}

/*================================================================================*/

void Block()
{
	int i;
	for (i = 0; i < 4; i++) 
	{
		gotoxy(4 + 10 * i, 2);	printf("■■■■");
		gotoxy(4 + 10 * i, 36);	printf("■■■■");
		gotoxy(4 + 10 * i, 37);	printf("■■■■");
	}
	for (i = 3; i <= 14; i++)
	{
		SetColor(DARK_GRAY);
		gotoxy(2, i);	printf("■");
		gotoxy(12, i);	printf("■");
		gotoxy(22, i);	printf("■");
		gotoxy(32, i);	printf("■");
		gotoxy(42, i);	printf("■");
	}
	for (i = 15; i <= 36; i++)
	{
		SetColor(GRAY);
		gotoxy(2, i);	printf("■");
		gotoxy(12, i);	printf("■");
		gotoxy(22, i);	printf("■");
		gotoxy(32, i);	printf("■");
		gotoxy(42, i);	printf("■");
	}
}

/*================================================================================*/

void Key()
{
	int i;
	for (i = 0; i < LEVEL; i++)
	{
		Touch[i].exist = FALSE;
	}
	gotoxy(7, 38);	printf("A");
	gotoxy(17, 38);	printf("S");
	gotoxy(27, 38); printf("D");
	gotoxy(37, 38);	printf("F");
	if (GetAsyncKeyState(65)<0) {
		SetColor(DARK_RED);
		gotoxy(4, 32);	printf("■■■■");
		gotoxy(4, 33);	printf("■■■■");
		gotoxy(4, 34);	printf("■■■■");
		gotoxy(4, 35);	printf("■■■■");
		SetColor(RED);
		gotoxy(4, 36);	printf("■■■■");
		gotoxy(4, 37);	printf("■■■■");
		Touch[0].exist = TRUE;
		//delay(30);
		SetColor(WHITE);
		gotoxy(4, 32);	printf("        ");
		gotoxy(4, 33);	printf("        ");
		gotoxy(4, 34);	printf("        ");
		gotoxy(4, 35);	printf("        ");
		gotoxy(4, 36);	printf("■■■■");
		gotoxy(4, 37);	printf("■■■■");
	}
	if (GetAsyncKeyState(83)<0) {
		SetColor(DARK_YELLOW);
		gotoxy(14, 32);	printf("■■■■");
		gotoxy(14, 33);	printf("■■■■");
		gotoxy(14, 34);	printf("■■■■");
		gotoxy(14, 35);	printf("■■■■");
		SetColor(YELLOW);
		gotoxy(14, 36);	printf("■■■■");
		gotoxy(14, 37);	printf("■■■■");
		Touch[1].exist = TRUE;
		//delay(30);
		SetColor(WHITE);
		gotoxy(14, 32);	printf("        ");
		gotoxy(14, 33);	printf("        ");
		gotoxy(14, 34);	printf("        ");
		gotoxy(14, 35);	printf("        ");
		gotoxy(14, 36);	printf("■■■■");
		gotoxy(14, 37);	printf("■■■■");
	}
	if (GetAsyncKeyState(68)<0) {
		SetColor(DARK_GREEN);
		gotoxy(24, 32);	printf("■■■■");
		gotoxy(24, 33);	printf("■■■■");
		gotoxy(24, 34);	printf("■■■■");
		gotoxy(24, 35);	printf("■■■■");
		SetColor(GREEN);
		gotoxy(24, 36);	printf("■■■■");
		gotoxy(24, 37);	printf("■■■■");
		Touch[2].exist = TRUE;
		//delay(30);
		SetColor(WHITE);
		gotoxy(24, 32);	printf("        ");
		gotoxy(24, 33);	printf("        ");
		gotoxy(24, 34);	printf("        ");
		gotoxy(24, 35);	printf("        ");
		gotoxy(24, 36);	printf("■■■■");
		gotoxy(24, 37);	printf("■■■■");
	}
	if (GetAsyncKeyState(70)<0) {
		SetColor(DARK_SKYBLUE);
		gotoxy(34, 32);	printf("■■■■");
		gotoxy(34, 33);	printf("■■■■");
		gotoxy(34, 34);	printf("■■■■");
		gotoxy(34, 35);	printf("■■■■");
		SetColor(SKYBLUE);
		gotoxy(34, 36);	printf("■■■■");
		gotoxy(34, 37);	printf("■■■■");
		Touch[3].exist = TRUE;
		//delay(30);
		SetColor(WHITE);
		gotoxy(34, 32);	printf("        ");
		gotoxy(34, 33);	printf("        ");
		gotoxy(34, 34);	printf("        ");
		gotoxy(34, 35);	printf("        ");
		gotoxy(34, 36);	printf("■■■■");
		gotoxy(34, 37);	printf("■■■■");
	}
}

/*================================================================================*/

void DrawEnemy(int i)
{
	SetColor(WHITE);
	gotoxy(Enemy[i].x, Enemy[i].y);	printf("■■■■");
}

/*================================================================================*/

void EraseEnemy(int i)
{
	gotoxy(Enemy[i].x, Enemy[i].y);	printf("        ");
}

/*================================================================================*/

void CreateEnemy()
{
	int i;
	if (random(2) == 0) {
		i = random(LEVEL);
		switch (i%4)
		{
		case 0:
			if (Enemy[i].exist == FALSE) {
				Enemy[i].exist = TRUE;
				Enemy[i].x = 4;
				Enemy[i].y = 4;
				DrawEnemy(i);
				break;
			}
		case 1:
			if (Enemy[i].exist == FALSE) {
				Enemy[i].exist = TRUE;
				Enemy[i].x = 14;
				Enemy[i].y = 4;
				DrawEnemy(i);
				break;
			}
		case 2:
			if (Enemy[i].exist == FALSE) {
				Enemy[i].exist = TRUE;
				Enemy[i].x = 24;
				Enemy[i].y = 4;
				DrawEnemy(i);
				break;
			}
		case 3:
			if (Enemy[i].exist == FALSE) {
				Enemy[i].exist = TRUE;
				Enemy[i].x = 34;
				Enemy[i].y = 4;
				DrawEnemy(i);
				break;
			}
		}
	}
}

/*================================================================================*/

void ActionEnemy()
{
	int i;
	for (i = 0; i < LEVEL; i++)
	{
		if (Enemy[i].exist == TRUE)
		{
			EraseEnemy(i);
			if (Enemy[i].y == 35)
			{
				Enemy[i].exist = FALSE;
				Life -= 5;
			}
			else
			{
				Enemy[i].y++;
				DrawEnemy(i);
				delay(10);
			}
		}
	}
}

/*================================================================================*/

void KillEnemy()
{
	int i;
	for (i = 0; i < LEVEL; i++) {
		if (Enemy[i].exist == TRUE && Touch[i%4].exist == TRUE && Enemy[i].y >= 25)
		{
			EraseEnemy(i);
			//printf("\a");
			Enemy[i].exist = FALSE;
			score += 5;
		}
	}
}

/*================================================================================*/

void GameOver()
{
	if (Life == 0)
	{
		delay(2000);
		clrscr();
		gotoxy(20, 20);
		printf("Game Over!");
		delay(1000);
		exit(0);
	}
}

/*================================================================================*/

void Interface()
{
	gotoxy(48, 20);	printf("점수 : ");
	gotoxy(55, 20);	printf("%d", score);
	gotoxy(48, 24);	printf("Life Point");
	gotoxy(48, 25);	printf("├ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┼ ─ ┤");
	SetColor(GREEN);
	if (Life <= 30)	SetColor(RED);
	gotoxy(48 + Life * 2 / 5 + 2, 26);	printf("  ");
	gotoxy(48 + Life * 2 / 5, 26);	printf("↑");
	SetColor(WHITE);
	gotoxy(48, 27);	printf("0                   50                 100");
}