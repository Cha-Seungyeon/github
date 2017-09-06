#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

typedef struct USER {
	char num[20];
	char pw[20];
	char name[20];

	struct USER *next;
	struct USER *pre;
}USER;

typedef struct BOOK {
	int index;
	char name[50];
	char num[20];

	struct BOOK *next;
	struct BOOK *pre;
}BOOK;

int Userload(USER *u_head, USER *u_tail, int u_count);
int Bookload(BOOK *b_head, BOOK *b_tail, int b_count);
void save(USER *u_head, USER *u_tail, BOOK *b_head, BOOK *b_tail);

void login(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
void search_pw(USER *u_head, USER *u_tail, int u_count);
void master(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);

void userlist(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
int add_user(USER *u_head, USER *u_tail, int u_count);
void edit_user(USER *u_head, USER *u_tail, int u_count);
int del_user(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);

void booklist(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
int add_book(BOOK *b_head, BOOK *b_tail, int b_count);
void edit_book(BOOK *b_head, BOOK *b_tail, int b_count);
int del_book(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);

void menu(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
void book_list(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
void rental(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
void returning(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);
void edit_login(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count);


int main()
{
	int u_count = 0, b_count = 0, select; // 회원 수, 도서 수 저장하는 변수 

	USER *u_head, *u_tail;
	u_head = (USER *)malloc(sizeof(USER));
	u_tail = (USER *)malloc(sizeof(USER));

	u_head->next = u_tail;
	u_tail->pre = u_head;
	u_tail->next = NULL;
	u_head->pre = NULL;

	u_count = Userload(u_head, u_tail, u_count); // 현재 회원정보 불러오기 

	BOOK *b_head, *b_tail;
	b_head = (BOOK *)malloc(sizeof(BOOK));
	b_tail = (BOOK *)malloc(sizeof(BOOK));

	b_head->index = 0; // 첫번째 책의 인덱스가 1이 되도록 헤드노드에 0 저장 

	b_head->next = b_tail;
	b_tail->pre = b_head;
	b_tail->next = NULL;
	b_head->pre = NULL;

	b_count = Bookload(b_head, b_tail, b_count); // 현재 도서목록 불러오기 

	system("cls");

	printf("\n메뉴를 선택하세요.\n");
	printf("1. 로그인\n");
	printf("2. 비밀번호 찾기\n");
	printf("3. 프로그램 종료\n");

	fflush(stdin);
	scanf("%d", &select);

	while (select != 1 && select != 2 && select != 3) // 예외처리 
	{
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n");

		fflush(stdin);
		scanf("%d", &select);
	}

	switch (select)
	{
	case 1:
		login(u_head, u_tail, u_count, b_head, b_tail, b_count);
		break;
	case 2:
		search_pw(u_head, u_tail, u_count);
		main();
		break;
	case 3:
		system("cls");

		printf("\n프로그램을 종료합니다.");
		getch();

		save(u_head, u_tail, b_head, b_tail);

		exit(1);
	}

	return 0;
}

int Userload(USER *u_head, USER *u_tail, int u_count)
{
	FILE *fp = fopen("user.txt", "r");

	if (fp == NULL) // user.txt가 없을 경우 새로 만들기 
	{
		fp = fopen("user.txt", "w");
		fclose(fp);
	}
	else {
		while (!feof(fp))
		{
			USER *u_add;
			u_add = (USER *)malloc(sizeof(USER));

			strcpy(u_add->num, "");
			strcpy(u_add->pw, "");
			strcpy(u_add->name, ""); // fscanf하기 전 초기화 

			fscanf(fp, "%s %s %s\n", u_add->num, u_add->pw, u_add->name);

			u_tail->pre->next = u_add;
			u_add->pre = u_tail->pre;
			u_tail->pre = u_add;
			u_add->next = u_tail;

			u_count++;

			if (strcmp(u_add->num, "") == 0) { // 노드의 학번 데이터가 없을경우 노드를 삭제하고 회원 수를 1 감소한다. 

				u_add->pre->next = u_add->next;
				u_add->next->pre = u_add->pre;

				free(u_add);

				u_count--;
			}
		}
	}

	fclose(fp);
	return u_count;
}

int Bookload(BOOK *b_head, BOOK *b_tail, int b_count)
{
	FILE *bp = fopen("book.txt", "r");

	if (bp == NULL) // book.txt가 없을 경우 새로 만든다 
	{
		bp = fopen("book.txt", "w");
		fclose(bp);
	}
	else {
		while (!feof(bp))
		{
			BOOK *b_add;
			b_add = (BOOK *)malloc(sizeof(BOOK));

			b_add->index = 0;
			strcpy(b_add->name, "");
			strcpy(b_add->num, ""); // fscanf 전 초기화 

			fscanf(bp, "%d\n", &b_add->index);
			fgets(b_add->name, sizeof(b_add->name), bp);
			b_add->name[strlen(b_add->name) - 1] = '\0';
			fscanf(bp, "%s\n", b_add->num);

			b_tail->pre->next = b_add;
			b_add->pre = b_tail->pre;
			b_tail->pre = b_add;
			b_add->next = b_tail;

			b_count++;

			if (strcmp(b_add->name, "") == 0) { // 노드에 책이름 데이터가 없다면 노드를 삭제하고 도서 수를 1 감소한다. 
				b_add->pre->next = b_add->next;
				b_add->next->pre = b_add->pre;

				free(b_add);

				b_count--;
			}
		}
	}

	fclose(bp);
	return b_count;
}

void save(USER *u_head, USER *u_tail, BOOK *b_head, BOOK *b_tail)
{
	int i = 1; // 책 인덱스 변수 

	FILE *fp, *bp;

	USER *u_tmp;
	BOOK *b_tmp;

	fp = fopen("user.txt", "w");

	for (u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
	{
		fprintf(fp, "%s %s %s\n", u_tmp->num, u_tmp->pw, u_tmp->name);
	}

	fclose(fp);

	bp = fopen("book.txt", "w");

	for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next)
	{
		b_tmp->index = i; // 처음부터 차례대로 책 인덱스 지정 
		fprintf(bp, "%d\n%s\n%s\n", b_tmp->index, b_tmp->name, b_tmp->num);
		i++; // 책 인덱스 증가 
	}

	fclose(bp);
}

void login(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	char login_num[20];
	char login_pw[20];
	int check = 0;

	USER *tmp; // 반복문 변수 

	system("cls");

	printf("\n아이디[학번] : ");
	fflush(stdin);
	gets(login_num);

	printf("비밀번호 : ");
	fflush(stdin);
	gets(login_pw);

	if (strcmp(login_num, "root") == 0) // 마스터아이디 체크 
	{
		if (strcmp(login_pw, "tmddus") == 0)
		{
			master(u_head, u_tail, u_count, b_head, b_tail, b_count);
			return;
		}
		else {
			printf("비밀번호가 일치하지않습니다.\n");
			getch();

			main();
			return;
		}
	}
	else {
		for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if (strcmp(tmp->num, login_num) == 0) // 아이디 체크 
			{
				if (strcmp(tmp->pw, login_pw) == 0) // 비밀번호 체크 
				{
					menu(tmp, u_head, u_tail, u_count, b_head, b_tail, b_count); // 로그인 성공 시 메인메뉴로 이동 
					break;
				}
				else {
					printf("비밀번호가 일치하지않습니다.\n"); // 아이디는 맞고 비밀번호가 틀릴 때 
					getch();

					main();
					break;
				}
			}
			else {
				check++; // 아이디가 없을 경우 1씩 카운팅 
			}
		}
		if (check == u_count) // 아이디가 없는 경우와 회원 수가 같을 경우
		{
			printf("등록되지 않은 학생입니다. 관리자에게 문의하세요.\n"); 
			getch();

			main();
		}
	}
}

void master(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n--*--* 관리자 모드 *--*--\n");
	printf("메뉴를 선택하세요.\n");
	printf("1. 회원 목록 [회원 등록/ 수정/ 삭제]\n");
	printf("2. 도서 목록 [도서 등록/ 수정/ 삭제]\n");
	printf("3. 프로그램 종료\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		userlist(u_head, u_tail, u_count, b_head, b_tail, b_count);
		master(u_head, u_tail, u_count, b_head, b_tail, b_count);
		break;
	case 2:
		booklist(u_head, u_tail, u_count, b_head, b_tail, b_count);
		master(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 3:
		system("cls");

		printf("\n\n프로그램을 종료합니다.");
		getch();

		save(u_head, u_tail, b_head, b_tail);

		exit(1);
	}
}

void userlist(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	USER *tmp;
	int select;

	system("cls");

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next) // 회원목록 출력 [학번, 이름] 
	{
		printf("%s %s\n", tmp->num, tmp->name);
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. 회원 등록\n");
	printf("2. 회원 정보 수정\n");
	printf("3. 회원 삭제\n");
	printf("4. 이전으로\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		u_count = add_user(u_head, u_tail, u_count);
		userlist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 2:
		edit_user(u_head, u_tail, u_count);
		userlist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 3:
		u_count = del_user(u_head, u_tail, u_count, b_head, b_tail, b_count);
		userlist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 4:
		master(u_head, u_tail, u_count, b_head, b_tail, b_count);
	}
}

int add_user(USER *u_head, USER *u_tail, int u_count)
{
	USER *tmp, *u_add;
	u_add = (USER *)malloc(sizeof(USER));

	char num[20];

	system("cls");
	printf("\n--*--* 회원등록 *--*--\n");

	printf("\n학번 : ");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->num, u_add->num) == 0) // 현재 존재하는 학번과 새로 입력된 학번 비교 
		{
			printf("이미 존재하는 학번입니다. 다시 입력해주세요.\n");
			fflush(stdin);
			gets(num);

			continue;
		}
	}

	strcpy(u_add->num, num);

	printf("비밀번호 : ");
	fflush(stdin);
	gets(u_add->pw);

	printf("이름 : ");
	fflush(stdin);
	gets(u_add->name);

	u_tail->pre->next = u_add;
	u_add->pre = u_tail->pre;
	u_tail->pre = u_add;
	u_add->next = u_tail;

	u_count++; // 회원 수 증가 

	system("cls");

	printf("\n--*--* 회원등록이 완료되었습니다. *--*--\n");
	getch();

	return u_count;
}

void edit_user(USER *u_head, USER *u_tail, int u_count)
{
	USER *tmp;
	int check = 0, select;
	char num[20];

	system("cls");

	printf("\n정보를 수정하고자 하는 학번을 입력해주세요.\n");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(num, tmp->num) == 0) // 정보를 수정하고자 하는 학번과 기존의 학번 비교 
		{
			system("cls");

			printf("\n1. 비밀번호 수정\n");
			printf("2. 이름 수정\n");
			fflush(stdin);
			scanf("%d", &select);

			switch (select)
			{
			case 1:
				system("cls");
				printf("\n새로운 비밀번호를 입력하세요.\n");
				fflush(stdin);
				gets(tmp->pw);

				system("cls");
				printf("\n--*--* 변경이 완료되었습니다. *--*--\n");
				getch();

				break;
			case 2:
				system("cls");
				printf("\n새로운 이름을 입력하세요.\n");
				fflush(stdin);
				gets(tmp->name);

				system("cls");
				printf("\n--*--* 변경이 완료되었습니다. *--*--\n");
				getch();

				break;
			}
		}
		else {
			check++; // 기존에 존재하지 않는 학번일 경우 카운트 
		}
	}

	if (check == u_count) // 카운트한 숫자와 회원 수가 같을 경우 
	{
		printf("\n학번이 존재하지않습니다.\n");
		getch();
	}
}

int del_user(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	USER *u_tmp;
	BOOK *b_tmp;

	char num[20];
	int check1 = 0, check2 = 0;

	system("cls");
	printf("\n삭제하고자 하는 학번을 입력해주세요.\n");

	fflush(stdin);
	gets(num);

	for (u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
	{
		if (strcmp(num, u_tmp->num) == 0) // 삭제하고자하는 학번과 기존 학번 비교 
		{
			for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next) // 학번이 같을 경우 대출한 책 여부를 알아보기 위함 
			{
				if (strcmp(u_tmp->num, b_tmp->num) == 0) // 대출한 학번과 삭제하고자하는 학번 비교 
				{
					printf("대출한 책이 존재하여 회원을 삭제 할 수 없습니다.\n");

					return u_count;
				}
				else {
					check2++; // 대출한 학번이 아닐경우 카운트 
				}
			}

			if (check2 == b_count) // 카운트와 책 개수가 같을 때 [대출한 책이 없음] 
			{
				u_tmp->pre->next = u_tmp->next;
				u_tmp->next->pre = u_tmp->pre;
				free(u_tmp);

				u_count--;

				system("cls");
				printf("\n--*--* 회원 삭제가 완료되었습니다. *--*--\n");
				getch();

				return u_count;
			}
		}
		else {
			check1++; // 기존의 학번이 아닐경우 카운트 
		}
	}

	if (check1 == u_count) // 카운트와 회원 수가 같을 때 
	{
		printf("학번이 존재하지 않습니다.\n");
		getch();
	}

	return u_count; // 삭제되어서 감소하거나 삭제되지 않아서 그대로인 회원 수를 반환함 
}

void booklist(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	int select;

	system("cls");
	printf("\n책 번호, 책 이름, 대출한 학번 순 입니다.\n\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // 인덱스, 책 이름, 대출했다면 대출 한 학번 수 출력 
	{
		printf("%d %s %s\n", tmp->index, tmp->name, tmp->num);
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. 도서 등록\n");
	printf("2. 도서 정보 수정\n");
	printf("3. 도서 삭제\n");
	printf("4. 이전으로\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		b_count = add_book(b_head, b_tail, b_count);
		booklist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 2:
		edit_book(b_head, b_tail, b_count);
		booklist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 3:
		b_count = del_book(u_head, u_tail, u_count, b_head, b_tail, b_count);
		booklist(u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 4:
		master(u_head, u_tail, u_count, b_head, b_tail, b_count);
	}
}

int add_book(BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	char name[50];

	system("cls");
	printf("\n--*--* 도서 등록 *--*--\n");

	printf("도서 이름 : ");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(name, tmp->name) == 0) // 기존의 책 이름과 등록하고자 하는 책 이름 비교 
		{
			printf("이미 존재하는 도서입니다. 다시 입력해주세요.\n");
			fflush(stdin);
			gets(name);

			continue;
		}
	}

	BOOK *b_add;
	b_add = (BOOK *)malloc(sizeof(BOOK));

	b_tail->pre->next = b_add;
	b_add->pre = b_tail->pre;
	b_tail->pre = b_add;
	b_add->next = b_tail;

	b_add->index = b_add->pre->index + 1; // 그 전 노드의 인덱스+1 한 인덱스 저장 
	strcpy(b_add->name, name);
	strcpy(b_add->num, "");

	b_count++;

	printf("\n--*--* 도서등록이 완료되었습니다. *--*--\n");
	getch();

	return b_count; // 새로 늘어나거나 변동되지 않은 카운트 값 반환 
}

void edit_book(BOOK *b_head, BOOK *b_tail, int b_count)
{
	int check = 0, index;
	char newname[50];
	BOOK *tmp1, *tmp2;

	system("cls");
	printf("\n--*--* 도서 정보 수정 *--*--\n");

	for (tmp1 = b_head->next; tmp1->next != NULL; tmp1 = tmp1->next) // 도서 목록 출력 
	{
		printf("%d %s %s\n", tmp1->index, tmp1->name, tmp1->num);
	}

	printf("\n 수정할 도서의 번호를 입력하세요\n");
	fflush(stdin);
	scanf("%d", &index);

	for (tmp1 = b_head->next; tmp1->next != NULL; tmp1 = tmp1->next)
	{
		if (index == tmp1->index) // 입력한 인덱스와 기존의 인덱스 비교 
		{
			printf("새로운 이름을 입력하세요.\n");
			fflush(stdin);
			gets(newname);

			for (tmp2 = b_head->next; tmp2->next != NULL; tmp2 = tmp2->next) // 새로 입력한 이름과 기존의 책 이름이 같은지 비교 
			{
				if (strcmp(tmp2->name, newname) == 0) // 같은 이름이 존재하지 않을 때 까지 반복 
				{
					printf("이미 존재하는 도서입니다. 다시 입력해주세요.\n");
					fflush(stdin);
					gets(newname);

					continue;
				}
			}

			strcpy(tmp1->name, newname); 

			return;
		}
		else {
			check++; // 입력한 인덱스와 기존의 인덱스가 같지 않을 때 카운트 
		}
	}

	if (check == b_count) // 카운트가 책 개수와 같을 경우 
	{
		printf("도서가 존재하지 않습니다.\n");
		getch();

		return;
	}
}

int del_book(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *b_tmp;
	int check = 0, index;
	char name[50];

	system("cls");
	printf("\n--*--* 도서 삭제 *--*--\n\n");

	for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next) // 책 목록 출력 
	{
		printf("%d %s %s\n", b_tmp->index, b_tmp->name, b_tmp->num);
	}
	printf("삭제할 도서의 번호를 입력해주세요.\n");
	fflush(stdin);
	scanf("%d", &index);

	for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next)
	{
		if (index == b_tmp->index) // 입력한 인덱스와 기존의 인덱스 비교 
		{
			if (strcmp(b_tmp->num, "") != 0) // 입력한 도서를 대출한 학생이 있는지 체크 
			{
				printf("대출한 학생이 있어서 삭제가 불가능합니다.\n");
				getch();

				return b_count;
			}
			else {
				b_tmp->next->pre = b_tmp->pre;
				b_tmp->pre->next = b_tmp->next;
				free(b_tmp);

				b_count--;

				save(u_head, u_tail, b_head, b_tail);

				printf("\n--*--* 도서 삭제가 완료되었습니다. *--*--\n");
				getch();

				return b_count;
			}
		}
		else {
			check++; // 기존의 인덱스와 입력받은 책의 인덱스가 같지 않은 경우 카운트 
		}
	}

	if (check == b_count) // 카운트와 책 개수가 같은경우 
	{
		printf("도서가 존재하지않습니다.\n");
		getch();
	}

	return b_count;
}

void menu(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n--*--* 메뉴를 선택하세요. *--*--\n");
	printf("1. 도서 대출/반납\n");
	printf("2. 회원정보 수정\n");
	printf("3. 프로그램 종료\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		book_list(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
		menu(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 2:
		edit_login(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
		menu(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 3:
		system("cls");

		printf("\n\n프로그램을 종료합니다.");
		getch();

		save(u_head, u_tail, b_head, b_tail);

		exit(1);
	}
}

void book_list(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	int select;

	system("cls");
	printf("\n책 이름, 대출한 여부 순 입니다.\n\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->num, "") != 0) // 대출 여부 체크 
		{
			printf("%s 대출 중\n", tmp->name);
		}
		else {
			printf("%s 대출가능\n", tmp->name);
		}
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. 대출\n");
	printf("2. 반납\n");
	printf("3. 이전으로\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		rental(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
		book_list(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 2:
		returning(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
		book_list(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
	case 3:
		menu(login, u_head, u_tail, u_count, b_head, b_tail, b_count);
	}
}

void rental(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	char name[50];
	int check = 0;

	system("cls");

	printf("--*--* 현재 대출 가능한 책 목록 *--*--\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // 대출가능한 책들만의 목록 출력 
	{
		if (strcmp(tmp->num, "") == 0)
		{
			printf("%s\n", tmp->name);
		}
	}

	printf("\n\n--*--* 대출하실 도서명을 입력하세요. *--*--\n");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->name, name) == 0) // 대출할 도서명과 기존의 도서명 비교 
		{
			if (strcmp(tmp->num, "") != 0) // 대출한 학생이 있는지 체크 
			{
				printf("이미 대출 중인 도서입니다.\n");
				return;
			}
			else {
				strcpy(tmp->num, login->num);

				system("cls");
				printf("--*--* 대출이 완료되었습니다. *--*--\n");
				getch();

				return;
			}
		}
		else { // 대출할 도서명과 기존의 도서명이 같지 않은 경우 카운트 
			check++;
		}
	}

	if (check == b_count) // 카운트와 책 개수가 같은경우 
	{
		printf("존재하지 않는 도서입니다.\n");
		return;
	}
}

void returning(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	char name[50];
	int check = 0;

	system("cls");

	printf("--*--* 현재 대출하신 책 목록 *--*--\n");
	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // 현재 로그인 한 학생이 대출한 책 목록만을 출력 
	{
		if (strcmp(tmp->num, login->num) == 0)
		{
			printf("%s\n", tmp->name);
		}
	}

	printf("\n\n--*--* 반납하실 도서명을 입력하세요. *--*--\n");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->name, name) == 0) // 반납할 도서명과 기존의 도서명 비교 
		{
			if (strcmp(tmp->num, login->num) != 0) // 도서를 대출한 학번과 현재 로그인 된 학생의 학번 비교 
			{
				printf("직접 대출하신 도서가 아닙니다.\n");
				return;
			}
			else {
				strcpy(tmp->num, "");

				system("cls");
				printf("--*--* 반납이 완료되었습니다. *--*--\n");
				getch();

				return;
			}
		}
		else { // 기존의 도서명과 반납하고자 하는 도서명이 다를 경우 카운트 
			check++;
		}
	}

	if (check == b_count) // 카운트와 책 개수가 같을 경우 
	{
		printf("존재하지 않는 도서입니다.\n");
		return;
	}
}

void edit_login(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n1. 비밀번호 수정\n");
	printf("2. 이름 수정\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		system("cls");
		printf("\n새로운 비밀번호를 입력하세요.\n");
		fflush(stdin);
		gets(login->pw);

		system("cls");
		printf("\n--*--* 변경이 완료되었습니다. *--*--\n");
		getch();

		break;
	case 2:
		system("cls");
		printf("\n새로운 이름을 입력하세요.\n");
		fflush(stdin);
		gets(login->name);

		system("cls");
		printf("\n--*--* 변경이 완료되었습니다. *--*--\n");
		getch();

		break;
	}
}

void search_pw(USER *u_head, USER *u_tail, int u_count)
{
	USER *tmp;
	int check = 0;
	char num[20];

	system("cls");

	printf("\n정보를 찾고자 하는 학번을 입력해주세요.\n");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(num, tmp->num) == 0) // 입력받은 학번과 기존의 학번들 비교 
		{
			system("cls");

			printf("\n새로운 비밀번호를 입력해주세요.\n");
			fflush(stdin);
			gets(tmp->pw);

			system("cls");
			printf("\n--*--* 변경이 완료되었습니다. *--*--\n");
			getch();

			return;
		}
		else {
			check++; // 기존의 학번과 입력 받은 학번이 같지 않을 경우 카운트 
		}
	}

	if (check == u_count) // 카운트와 회원 수가 같을경우 
	{
		printf("\n학번이 존재하지않습니다.\n");
		getch();
	}
}
