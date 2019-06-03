#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

// E : 쉬움     N : 보통     H : 어려움

int x1, y1, x2, y2; //카드좌표 입력시 사용
int coE = 16, coN = 36, coH = 64; //앞면인 카드 카운트(0되면 종료)
int pan_frE[5][5] = { 0, }; // 모든카드 숫자를 0으로 초기화 (쉬움)
int pan_frN[7][7] = { 0, }; // 모든카드 숫자를 0으로 초기화 (보통)
int pan_frH[9][9] = { 0, }; // 모든카드 숫자를 0으로 초기화 (어렵)
int card_sangE[4][4] = { 0, }; //카드상태를 0으로 초기화(뒷면)
int card_sangN[6][6] = { 0, }; //카드상태를 0으로 초기화(뒷면)
int card_sangH[8][8] = { 0, }; //카드상태를 0으로 초기화(뒷면)
int count = 0; //카드 뒤집은 횟수

void gotoxy(int x, int y); //고투엑수와이
void start(); //시작화면
void start_nan(); //난이도 설정화면
void pan(); //테두리 출력
void pan_prE(), pan_prN(), pan_prH(); //카드판 출력
void reset_E(), reset_N(), reset_H(); //카드초기화
void pan_anE(), pan_anN(), pan_anH(); //카드앞면세팅 (정답공개)
void pan_bnE(), pan_bnN(), pan_bnH(); //카드뒷면세팅
void game_E(), game_N(), game_H(); //게임시작
void E1s(), E2s(), E12(); //카드뒤집기,확인 (쉬움)
void N1s(), N2s(), N12(); //카드뒤집기,확인 (보통)
void H1s(), H2s(), H12(); //카드뒤집기,확인 (어렵)
void endE(), endN(), endH(); //게임종료

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
				printf("■");
			else
				printf("  ");
		}printf("\n");
	}
}

void start() {
	pan();
	gotoxy(20, 5);
	printf("너무너무 재미있는 카드짝맞추기!! 우와앙");
	gotoxy(25, 10);
	printf("스페이스 누르면 시작이지룽");
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
	printf("난이도를 설정해보아용");
	gotoxy(35, 10); printf("쉬움 : 1\n");
	gotoxy(35, 12); printf("보통 : 2\n");
	gotoxy(33, 14); printf("어려움 : 3\n");
	gotoxy(0, 21);  scanf("%d",&nan);
	if (nan < 1 || nan>3) {
		printf("제대로 입력하기 ㅡㅅㅡ");
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
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  ? │  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangE[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frE[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frE[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0,20); printf("카드뒤집은 횟수 : %d", count);
	gotoxy(0,15);
}
void pan_prN() {
	for (int x = 1;x <= 6;x++)
	{
		for (int y = 1;y <= 6;y++)
		{
			if (card_sangN[x][y] == 0)
			{
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  ? │  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangN[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frN[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frN[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0, 20); printf("카드뒤집은 횟수 : %d", count);
	gotoxy(0, 23);
}
void pan_prH() {
	for (int x = 1;x <= 8;x++)
	{
		for (int y = 1;y <= 8;y++)
		{
			if (card_sangH[x][y] == 0)
			{
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  ? │  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
			}
			else if (card_sangH[x][y] == 2)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frH[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
				printf(" ┌────┐  "); gotoxy((y - 1) * 8, (x - 1) * 3 + 1);
				printf(" │  %d │  ", pan_frH[x][y]); gotoxy((y - 1) * 8, (x - 1) * 3 + 2);
				printf(" └────┘  "); gotoxy((y) * 8, (x - 1) * 3);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
		}printf("\n"); printf("\n"); printf("\n");
	}
	gotoxy(0, 25); printf("카드뒤집은 횟수 : %d", count);
	gotoxy(0, 28);
}

void reset_E() {
	int cardset = 1;
	int cardmax = 16;
	int cardcount;
	srand(time(NULL));
	for (cardcount = 1;cardcount <= cardmax;cardcount += 2) {
		while(1) {
			x1 = rand() % 4 + 1; //x1좌표 무작위 설정
			y1 = rand() % 4 + 1; //y1좌표 무작위 설정
			x2 = rand() % 4 + 1; //x2좌표 무작위 설정
			y2 = rand() % 4 + 1; //y2좌표 무작위 설정
			if ((x1 != x2 || y1 != y2) && //두 위치가 같지않은지 확인
				pan_frE[x1][y1] == 0 && pan_frE[x2][y2] == 0) { //둘 다 숫자가 들어간적 없는지 확인
				pan_frE[x1][y1] = cardset; //x1y1에 숫자넣기
				pan_frE[x2][y2] = cardset; //x2y2에 숫자넣기
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
			x1 = rand() % 6 + 1; //x1좌표 무작위 설정
			y1 = rand() % 6 + 1; //y1좌표 무작위 설정
			x2 = rand() % 6 + 1; //x2좌표 무작위 설정
			y2 = rand() % 6 + 1; //y2좌표 무작위 설정
			if ((x1 != x2 || y1 != y2) && //두 위치가 같은지 확인
				pan_frN[x1][y1] == 0 && pan_frN[x2][y2] == 0) { //둘 다 숫자가 들어간적 없는지 확인
				pan_frN[x1][y1] = cardset; //x1y1에 숫자넣기
				pan_frN[x2][y2] = cardset; //x2y2에 숫자넣기
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
			x1 = rand() % 8 + 1; //x1좌표 무작위 설정
			y1 = rand() % 8 + 1; //y1좌표 무작위 설정
			x2 = rand() % 8 + 1; //x2좌표 무작위 설정
			y2 = rand() % 8 + 1; //y2좌표 무작위 설정
			if ((x1 != x2 || y1 != y2) && //두 위치가 같은지 확인
				pan_frH[x1][y1] == 0 && pan_frH[x2][y2] == 0) { //둘 다 숫자가 들어간적 없는지 확인
				pan_frH[x1][y1] = cardset; //x1y1에 숫자넣기
				pan_frH[x2][y2] = cardset; //x2y2에 숫자넣기
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
	gotoxy(0, 20); printf("3초간 정답공개 할게요 ^ㅡ^");
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
	gotoxy(0, 20); printf("3초간 정답공개 할게요 ^ㅡ^");
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
	gotoxy(0, 25); printf("3초간 정답공개 할게요 ^ㅡ^");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else if (card_sangE[x1][y1] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prE();
		}
		else if (card_sangE[x2][y2] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else if (card_sangN[x1][y1] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prN();
		}
		else if (card_sangN[x2][y2] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else if (card_sangH[x1][y1] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
			printf("입력범위를 초과하였습니다.");
			Sleep(1000);
			system("cls");
			pan_prH();
		}
		else if (card_sangH[x2][y2] != 0) {
			printf("뒷면인 카드를 선택해주세요.");
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
	printf("게임종료!! 우와앙");
	gotoxy(29, 10);
	printf("카드뒤집은 횟수 : %d",count);
	gotoxy(0, 20);
}
void endN() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	pan();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(30, 5);
	printf("게임종료!! 우와앙");
	gotoxy(29, 10);
	printf("카드뒤집은 횟수 : %d", count);
	gotoxy(0, 20);
}
void endH() {
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	pan();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoxy(30, 5);
	printf("게임종료!! 우와앙");
	gotoxy(29, 10);
	printf("카드뒤집은 횟수 : %d", count);
	gotoxy(0, 20);
}