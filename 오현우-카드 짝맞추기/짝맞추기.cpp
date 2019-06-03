#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// E : ����     N : ����     H : �����

int x1, y1, x2, y2; //ī����ǥ �Է½� ���
int coE = 16, coN = 36, coH = 64; //�ո��� ī�� ī��Ʈ(0�Ǹ� ����)
int pan_frE[5][5] = { 0, }; // ���ī�� ���ڸ� 0���� �ʱ�ȭ (����)
int pan_frN[7][7] = { 0, }; // ���ī�� ���ڸ� 0���� �ʱ�ȭ (����)
int pan_frH[9][9] = { 0, }; // ���ī�� ���ڸ� 0���� �ʱ�ȭ (���)
int card_sangE[4][4] = { 0, }; //ī����¸� 0���� �ʱ�ȭ(�޸�)
int card_sangN[6][6] = { 0, }; //ī����¸� 0���� �ʱ�ȭ(�޸�)
int card_sangH[8][8] = { 0, }; //ī����¸� 0���� �ʱ�ȭ(�޸�)
int count = 0; //ī�� ������ Ƚ��

void gotoxy(int x, int y); //������������
void start(); //����ȭ��
void start_nan(); //���̵� ����ȭ��
void pan(); //�׵θ� ���
void pan_prE(), pan_prN(), pan_prH(); //ī���� ���
void reset_E(), reset_N(), reset_H(); //ī���ʱ�ȭ
void pan_anE(), pan_anN(), pan_anH(); //ī��ո鼼�� (�������)
void pan_bnE(), pan_bnN(), pan_bnH(); //ī��޸鼼��
void game_E(), game_N(), game_H(); //���ӽ���
void E1s(), E2s(), E12(); //ī�������,Ȯ�� (����)
void N1s(), N2s(), N12(); //ī�������,Ȯ�� (����)
void H1s(), H2s(), H12(); //ī�������,Ȯ�� (���)
void endE(), endN(), endH(); //��������

int main() {
	system("mode con cols=100 lines=30");
	start();
  }

void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void pan() {
	for (int i = 1;i <= 20;i++) {
		for (int j = 1;j <= 40;j++) {
			if (i == 1 || i == 20 || j == 1 || j == 40)
				printf("��");
			else
				printf("  ");
		}printf("\n");
	}
}

void start() {
	pan();
	gotoxy(20, 5);
	printf("�ʹ��ʹ� ����ִ� ī��¦���߱�!! ��;�");
	gotoxy(25, 10);
	printf("�����̽� ������ ����������");
	gotoxy(0, 20);
	char st_1;
	st_1 = getch();
	switch (st_1)
	{
	case ' ':
		system("cls");
		start_nan();
		break;
	}
}
void start_nan() {
	int nan;
	pan();
	gotoxy(28, 5);
	printf("���̵��� �����غ��ƿ�");
	gotoxy(35, 10); printf("���� : 1\n");
	gotoxy(35, 12); printf("���� : 2\n");
	gotoxy(33, 14); printf("����� : 3\n");
	gotoxy(0, 21);  scanf("%d",&nan);
	if (nan < 1 || nan>3) {
		printf("����� �Է��ϱ� �Ѥ���");
		Sleep(2000);
		system("cls");
		start_nan();
	}
	else
		switch (nan)
		{
		case 1:
			system("cls");
			game_E();
			break;
		case 2:
			system("cls");
			game_N();
			break;
		case 3:
			system("cls");
			game_H();
			break;
		}
}

void pan_prE() {
	for (int x = 1;x <= 4;x++)
	{
		for (int y = 1;y <= 4;y++)
		{
			if (card_sangE[x][y] == 0)
			{
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  ? ��  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangE[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frE[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frE[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0,20); printf("ī������� Ƚ�� : %d", count);
	gotoxy(0,15);
}
void pan_prN() {
	for (int x = 1;x <= 6;x++)
	{
		for (int y = 1;y <= 6;y++)
		{
			if (card_sangN[x][y] == 0)
			{
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  ? ��  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangN[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frN[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frN[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0, 20); printf("ī������� Ƚ�� : %d", count);
	gotoxy(0, 23);
}
void pan_prH() {
	for (int x = 1;x <= 8;x++)
	{
		for (int y = 1;y <= 8;y++)
		{
			if (card_sangH[x][y] == 0)
			{
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  ? ��  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangH[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frH[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ������������  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" ��  %d ��  ", pan_frH[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" ������������  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0, 25); printf("ī������� Ƚ�� : %d", count);
	gotoxy(0, 28);
}

void reset_E() {
	int cardset = 1;
	int cardmax = 16;
	int cardcount;
	srand(time(NULL));
	for (cardcount = 1;cardcount <= cardmax;cardcount += 2) {
		while(1) {
			x1 = rand() % 4 + 1; //x1��ǥ ������ ����
			y1 = rand() % 4 + 1; //y1��ǥ ������ ����
			x2 = rand() % 4 + 1; //x2��ǥ ������ ����
			y2 = rand() % 4 + 1; //y2��ǥ ������ ����
			if ((x1 != x2 || y1 != y2) && //�� ��ġ�� ���������� Ȯ��
				pan_frE[x1][y1] == 0 && pan_frE[x2][y2] == 0) { //�� �� ���ڰ� ���� ������ Ȯ��
				pan_frE[x1][y1] = cardset; //x1y1�� ���ڳֱ�
				pan_frE[x2][y2] = cardset; //x2y2�� ���ڳֱ�
				break;
			}
		}
		cardset++;
	}
}
void reset_N() {
	int cardset = 1;
	int cardmax = 36;
	int cardcount;
	srand(time(NULL));
	for (cardcount = 1;cardcount <= cardmax;cardcount += 2) {
		while (1) {
			x1 = rand() % 6 + 1; //x1��ǥ ������ ����
			y1 = rand() % 6 + 1; //y1��ǥ ������ ����
			x2 = rand() % 6 + 1; //x2��ǥ ������ ����
			y2 = rand() % 6 + 1; //y2��ǥ ������ ����
			if ((x1 != x2 || y1 != y2) && //�� ��ġ�� ������ Ȯ��
				pan_frN[x1][y1] == 0 && pan_frN[x2][y2] == 0) { //�� �� ���ڰ� ���� ������ Ȯ��
				pan_frN[x1][y1] = cardset; //x1y1�� ���ڳֱ�
				pan_frN[x2][y2] = cardset; //x2y2�� ���ڳֱ�
				break;
			}
		}
		if (cardset == 9)
			cardset = 0;
		cardset++;
	}
}
void reset_H() {
	int cardset = 1;
	int cardmax = 64;
	int cardcount;
	srand(time(NULL));
	for (cardcount = 1;cardcount <= cardmax;cardcount += 2) {
		while (1) {
			x1 = rand() % 8 + 1; //x1��ǥ ������ ����
			y1 = rand() % 8 + 1; //y1��ǥ ������ ����
			x2 = rand() % 8 + 1; //x2��ǥ ������ ����
			y2 = rand() % 8 + 1; //y2��ǥ ������ ����
			if ((x1 != x2 || y1 != y2) && //�� ��ġ�� ������ Ȯ��
				pan_frH[x1][y1] == 0 && pan_frH[x2][y2] == 0) { //�� �� ���ڰ� ���� ������ Ȯ��
				pan_frH[x1][y1] = cardset; //x1y1�� ���ڳֱ�
				pan_frH[x2][y2] = cardset; //x2y2�� ���ڳֱ�
				break;
			}
		}
		if (cardset == 9)
			cardset = 0;
		cardset++;
	}
}

void pan_anE() {
	for (int i = 1;i <= 4;i++) {
		for (int j = 1;j <= 4;j++) {
			card_sangE[i][j] = 1;
		}
	}
}
void pan_bnE() {
	for (int i = 1;i <= 4;i++) {
		for (int j = 1;j <= 4;j++) {
			card_sangE[i][j] = 0;
		}
	}
}
void pan_anN() {
	for (int i = 1;i <= 6;i++) {
		for (int j = 1;j <= 6;j++) {
			card_sangN[i][j] = 1;
		}
	}
}
void pan_bnN() {
	for (int i = 1;i <= 6;i++) {
		for (int j = 1;j <= 6;j++) {
			card_sangN[i][j] = 0;
		}
	}
}
void pan_anH() {
	for (int i = 1;i <= 8;i++) {
		for (int j = 1;j <= 8;j++) {
			card_sangH[i][j] = 1;
		}
	}
}
void pan_bnH() {
	for (int i = 1;i <= 8;i++) {
		for (int j = 1;j <= 8;j++) {
			card_sangH[i][j] = 0;
		}
	}
}

void game_E() {
	reset_E();
	pan_anE();
	pan_prE();
	gotoxy(0, 20); printf("3�ʰ� ������� �ҰԿ� ^��^");
	Sleep(3000);
	pan_bnE();
	system("cls");
	pan_prE();
	while (coE) {
		E1s();
 		E2s();
		E12();
	}
	endE();
}
void game_N() {
	reset_N();
	pan_anN();
	pan_prN();
	gotoxy(0, 20); printf("3�ʰ� ������� �ҰԿ� ^��^");
	Sleep(3000);
	pan_bnN();
	system("cls");
	pan_prN();
	while (coN) {
		N1s();
		N2s();
		N12();
	}
	endN();
}
void game_H() {
	reset_H();
	pan_anH();
	pan_prH();
	gotoxy(0, 25); printf("3�ʰ� ������� �ҰԿ� ^��^");
	Sleep(3000);
	pan_bnH();
	system("cls");
	pan_prH();
	while (coH) {
		H1s();
		H2s();
		H12();
	}
	endH();
}

void E1s() {
	while (1) {
		scanf("%d %d", &x1, &y1);
		if (x1 < 1 || x1 > 4 || y1 < 1 || y1 > 4) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else if (card_sangE[x1][y1] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else {
			system("cls");
			card_sangE[x1][y1] = 2;
			pan_prE();
			break;
		}
	}
}
void E2s() {
	while (1) {
		scanf("%d %d", &x2, &y2);
		if (x2 < 1 || x2 > 4 || y2 < 1 || y2 > 4) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else if (card_sangE[x2][y2] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else {
			system("cls");
			card_sangE[x2][y2] = 2;
			pan_prE();
			break;
		}
	}
}
void E12() {
	if (pan_frE[x1][y1] == pan_frE[x2][y2]) {
		card_sangE[x1][y1] = 1;
		card_sangE[x2][y2] = 1;
		coE -= 2;
	}
	else {
		card_sangE[x1][y1] = 0;
		card_sangE[x2][y2] = 0;
	}
	count++;
	Sleep(1000);
	system("cls");
	pan_prE();
}
void N1s() {
	while (1) {
		scanf("%d %d", &x1, &y1);
		if (x1 < 1 || x1 > 6 || y1 < 1 || y1 > 6) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else if (card_sangN[x1][y1] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else {
			system("cls");
			card_sangN[x1][y1] = 2;
			pan_prN();
			break;
		}
	}
}
void N2s() {
	while (1) {
		scanf("%d %d", &x2, &y2);
		if (x2 < 1 || x2 > 6 || y2 < 1 || y2 > 6) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else if (card_sangN[x2][y2] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else {
			system("cls");
			card_sangN[x2][y2] = 2;
			pan_prN();
			break;
		}
	}
}
void N12() {
	if (pan_frN[x1][y1] == pan_frN[x2][y2]) {
		card_sangN[x1][y1] = 1;
		card_sangN[x2][y2] = 1;
		coN -= 2;
	}
	else {
		card_sangN[x1][y1] = 0;
		card_sangN[x2][y2] = 0;
	}
	count++;
	Sleep(1000);
	system("cls");
	pan_prN();
}
void H1s() {
	while (1) {
		scanf("%d %d", &x1, &y1);
		if (x1 < 1 || x1 > 8 || y1 < 1 || y1 > 8) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else if (card_sangH[x1][y1] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else {
			system("cls");
			card_sangH[x1][y1] = 2;
			pan_prH();
			break;
		}
	}
}
void H2s() {
	while (1) {
		scanf("%d %d", &x2, &y2);
		if (x2 < 1 || x2 > 8 || y2 < 1 || y2 > 8) {
			printf("�Է¹����� �ʰ��Ͽ����ϴ�.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else if (card_sangH[x2][y2] != 0) {
			printf("�޸��� ī�带 �������ּ���.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else {
			system("cls");
			card_sangH[x2][y2] = 2;
			pan_prH();
			break;
		}
	}
}
void H12() {
	if (pan_frH[x1][y1] == pan_frH[x2][y2]) {
		card_sangH[x1][y1] = 1;
		card_sangH[x2][y2] = 1;
		coH -= 2;
	}
	else {
		card_sangH[x1][y1] = 0;
		card_sangH[x2][y2] = 0;
	}
	count++;
	Sleep(1000);
	system("cls");
	pan_prH();
}

void endE() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	pan();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(30, 5);
	printf("��������!! ��;�");
	gotoxy(29, 10);
	printf("ī������� Ƚ�� : %d",count);
	gotoxy(0, 20);
}
void endN() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	pan();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(30, 5);
	printf("��������!! ��;�");
	gotoxy(29, 10);
	printf("ī������� Ƚ�� : %d", count);
	gotoxy(0, 20);
}
void endH() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	pan();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(30, 5);
	printf("��������!! ��;�");
	gotoxy(29, 10);
	printf("ī������� Ƚ�� : %d", count);
	gotoxy(0, 20);
}