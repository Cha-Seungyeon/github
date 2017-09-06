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
	int u_count = 0, b_count = 0, select; // ȸ�� ��, ���� �� �����ϴ� ���� 

	USER *u_head, *u_tail;
	u_head = (USER *)malloc(sizeof(USER));
	u_tail = (USER *)malloc(sizeof(USER));

	u_head->next = u_tail;
	u_tail->pre = u_head;
	u_tail->next = NULL;
	u_head->pre = NULL;

	u_count = Userload(u_head, u_tail, u_count); // ���� ȸ������ �ҷ����� 

	BOOK *b_head, *b_tail;
	b_head = (BOOK *)malloc(sizeof(BOOK));
	b_tail = (BOOK *)malloc(sizeof(BOOK));

	b_head->index = 0; // ù��° å�� �ε����� 1�� �ǵ��� ����忡 0 ���� 

	b_head->next = b_tail;
	b_tail->pre = b_head;
	b_tail->next = NULL;
	b_head->pre = NULL;

	b_count = Bookload(b_head, b_tail, b_count); // ���� ������� �ҷ����� 

	system("cls");

	printf("\n�޴��� �����ϼ���.\n");
	printf("1. �α���\n");
	printf("2. ��й�ȣ ã��\n");
	printf("3. ���α׷� ����\n");

	fflush(stdin);
	scanf("%d", &select);

	while (select != 1 && select != 2 && select != 3) // ����ó�� 
	{
		printf("�޴��� ���� ���ڸ� �Է��ϼ���.\n");
		printf("�ٽ� �Է��ϼ���.\n");

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

		printf("\n���α׷��� �����մϴ�.");
		getch();

		save(u_head, u_tail, b_head, b_tail);

		exit(1);
	}

	return 0;
}

int Userload(USER *u_head, USER *u_tail, int u_count)
{
	FILE *fp = fopen("user.txt", "r");

	if (fp == NULL) // user.txt�� ���� ��� ���� ����� 
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
			strcpy(u_add->name, ""); // fscanf�ϱ� �� �ʱ�ȭ 

			fscanf(fp, "%s %s %s\n", u_add->num, u_add->pw, u_add->name);

			u_tail->pre->next = u_add;
			u_add->pre = u_tail->pre;
			u_tail->pre = u_add;
			u_add->next = u_tail;

			u_count++;

			if (strcmp(u_add->num, "") == 0) { // ����� �й� �����Ͱ� ������� ��带 �����ϰ� ȸ�� ���� 1 �����Ѵ�. 

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

	if (bp == NULL) // book.txt�� ���� ��� ���� ����� 
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
			strcpy(b_add->num, ""); // fscanf �� �ʱ�ȭ 

			fscanf(bp, "%d\n", &b_add->index);
			fgets(b_add->name, sizeof(b_add->name), bp);
			b_add->name[strlen(b_add->name) - 1] = '\0';
			fscanf(bp, "%s\n", b_add->num);

			b_tail->pre->next = b_add;
			b_add->pre = b_tail->pre;
			b_tail->pre = b_add;
			b_add->next = b_tail;

			b_count++;

			if (strcmp(b_add->name, "") == 0) { // ��忡 å�̸� �����Ͱ� ���ٸ� ��带 �����ϰ� ���� ���� 1 �����Ѵ�. 
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
	int i = 1; // å �ε��� ���� 

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
		b_tmp->index = i; // ó������ ���ʴ�� å �ε��� ���� 
		fprintf(bp, "%d\n%s\n%s\n", b_tmp->index, b_tmp->name, b_tmp->num);
		i++; // å �ε��� ���� 
	}

	fclose(bp);
}

void login(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	char login_num[20];
	char login_pw[20];
	int check = 0;

	USER *tmp; // �ݺ��� ���� 

	system("cls");

	printf("\n���̵�[�й�] : ");
	fflush(stdin);
	gets(login_num);

	printf("��й�ȣ : ");
	fflush(stdin);
	gets(login_pw);

	if (strcmp(login_num, "root") == 0) // �����;��̵� üũ 
	{
		if (strcmp(login_pw, "tmddus") == 0)
		{
			master(u_head, u_tail, u_count, b_head, b_tail, b_count);
			return;
		}
		else {
			printf("��й�ȣ�� ��ġ�����ʽ��ϴ�.\n");
			getch();

			main();
			return;
		}
	}
	else {
		for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if (strcmp(tmp->num, login_num) == 0) // ���̵� üũ 
			{
				if (strcmp(tmp->pw, login_pw) == 0) // ��й�ȣ üũ 
				{
					menu(tmp, u_head, u_tail, u_count, b_head, b_tail, b_count); // �α��� ���� �� ���θ޴��� �̵� 
					break;
				}
				else {
					printf("��й�ȣ�� ��ġ�����ʽ��ϴ�.\n"); // ���̵�� �°� ��й�ȣ�� Ʋ�� �� 
					getch();

					main();
					break;
				}
			}
			else {
				check++; // ���̵� ���� ��� 1�� ī���� 
			}
		}
		if (check == u_count) // ���̵� ���� ���� ȸ�� ���� ���� ���
		{
			printf("��ϵ��� ���� �л��Դϴ�. �����ڿ��� �����ϼ���.\n"); 
			getch();

			main();
		}
	}
}

void master(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n--*--* ������ ��� *--*--\n");
	printf("�޴��� �����ϼ���.\n");
	printf("1. ȸ�� ��� [ȸ�� ���/ ����/ ����]\n");
	printf("2. ���� ��� [���� ���/ ����/ ����]\n");
	printf("3. ���α׷� ����\n");

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

		printf("\n\n���α׷��� �����մϴ�.");
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

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next) // ȸ����� ��� [�й�, �̸�] 
	{
		printf("%s %s\n", tmp->num, tmp->name);
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. ȸ�� ���\n");
	printf("2. ȸ�� ���� ����\n");
	printf("3. ȸ�� ����\n");
	printf("4. ��������\n");

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
	printf("\n--*--* ȸ����� *--*--\n");

	printf("\n�й� : ");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->num, u_add->num) == 0) // ���� �����ϴ� �й��� ���� �Էµ� �й� �� 
		{
			printf("�̹� �����ϴ� �й��Դϴ�. �ٽ� �Է����ּ���.\n");
			fflush(stdin);
			gets(num);

			continue;
		}
	}

	strcpy(u_add->num, num);

	printf("��й�ȣ : ");
	fflush(stdin);
	gets(u_add->pw);

	printf("�̸� : ");
	fflush(stdin);
	gets(u_add->name);

	u_tail->pre->next = u_add;
	u_add->pre = u_tail->pre;
	u_tail->pre = u_add;
	u_add->next = u_tail;

	u_count++; // ȸ�� �� ���� 

	system("cls");

	printf("\n--*--* ȸ������� �Ϸ�Ǿ����ϴ�. *--*--\n");
	getch();

	return u_count;
}

void edit_user(USER *u_head, USER *u_tail, int u_count)
{
	USER *tmp;
	int check = 0, select;
	char num[20];

	system("cls");

	printf("\n������ �����ϰ��� �ϴ� �й��� �Է����ּ���.\n");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(num, tmp->num) == 0) // ������ �����ϰ��� �ϴ� �й��� ������ �й� �� 
		{
			system("cls");

			printf("\n1. ��й�ȣ ����\n");
			printf("2. �̸� ����\n");
			fflush(stdin);
			scanf("%d", &select);

			switch (select)
			{
			case 1:
				system("cls");
				printf("\n���ο� ��й�ȣ�� �Է��ϼ���.\n");
				fflush(stdin);
				gets(tmp->pw);

				system("cls");
				printf("\n--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				break;
			case 2:
				system("cls");
				printf("\n���ο� �̸��� �Է��ϼ���.\n");
				fflush(stdin);
				gets(tmp->name);

				system("cls");
				printf("\n--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				break;
			}
		}
		else {
			check++; // ������ �������� �ʴ� �й��� ��� ī��Ʈ 
		}
	}

	if (check == u_count) // ī��Ʈ�� ���ڿ� ȸ�� ���� ���� ��� 
	{
		printf("\n�й��� ���������ʽ��ϴ�.\n");
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
	printf("\n�����ϰ��� �ϴ� �й��� �Է����ּ���.\n");

	fflush(stdin);
	gets(num);

	for (u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
	{
		if (strcmp(num, u_tmp->num) == 0) // �����ϰ����ϴ� �й��� ���� �й� �� 
		{
			for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next) // �й��� ���� ��� ������ å ���θ� �˾ƺ��� ���� 
			{
				if (strcmp(u_tmp->num, b_tmp->num) == 0) // ������ �й��� �����ϰ����ϴ� �й� �� 
				{
					printf("������ å�� �����Ͽ� ȸ���� ���� �� �� �����ϴ�.\n");

					return u_count;
				}
				else {
					check2++; // ������ �й��� �ƴҰ�� ī��Ʈ 
				}
			}

			if (check2 == b_count) // ī��Ʈ�� å ������ ���� �� [������ å�� ����] 
			{
				u_tmp->pre->next = u_tmp->next;
				u_tmp->next->pre = u_tmp->pre;
				free(u_tmp);

				u_count--;

				system("cls");
				printf("\n--*--* ȸ�� ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				return u_count;
			}
		}
		else {
			check1++; // ������ �й��� �ƴҰ�� ī��Ʈ 
		}
	}

	if (check1 == u_count) // ī��Ʈ�� ȸ�� ���� ���� �� 
	{
		printf("�й��� �������� �ʽ��ϴ�.\n");
		getch();
	}

	return u_count; // �����Ǿ �����ϰų� �������� �ʾƼ� �״���� ȸ�� ���� ��ȯ�� 
}

void booklist(USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	int select;

	system("cls");
	printf("\nå ��ȣ, å �̸�, ������ �й� �� �Դϴ�.\n\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // �ε���, å �̸�, �����ߴٸ� ���� �� �й� �� ��� 
	{
		printf("%d %s %s\n", tmp->index, tmp->name, tmp->num);
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. ���� ���\n");
	printf("2. ���� ���� ����\n");
	printf("3. ���� ����\n");
	printf("4. ��������\n");

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
	printf("\n--*--* ���� ��� *--*--\n");

	printf("���� �̸� : ");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(name, tmp->name) == 0) // ������ å �̸��� ����ϰ��� �ϴ� å �̸� �� 
		{
			printf("�̹� �����ϴ� �����Դϴ�. �ٽ� �Է����ּ���.\n");
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

	b_add->index = b_add->pre->index + 1; // �� �� ����� �ε���+1 �� �ε��� ���� 
	strcpy(b_add->name, name);
	strcpy(b_add->num, "");

	b_count++;

	printf("\n--*--* ��������� �Ϸ�Ǿ����ϴ�. *--*--\n");
	getch();

	return b_count; // ���� �þ�ų� �������� ���� ī��Ʈ �� ��ȯ 
}

void edit_book(BOOK *b_head, BOOK *b_tail, int b_count)
{
	int check = 0, index;
	char newname[50];
	BOOK *tmp1, *tmp2;

	system("cls");
	printf("\n--*--* ���� ���� ���� *--*--\n");

	for (tmp1 = b_head->next; tmp1->next != NULL; tmp1 = tmp1->next) // ���� ��� ��� 
	{
		printf("%d %s %s\n", tmp1->index, tmp1->name, tmp1->num);
	}

	printf("\n ������ ������ ��ȣ�� �Է��ϼ���\n");
	fflush(stdin);
	scanf("%d", &index);

	for (tmp1 = b_head->next; tmp1->next != NULL; tmp1 = tmp1->next)
	{
		if (index == tmp1->index) // �Է��� �ε����� ������ �ε��� �� 
		{
			printf("���ο� �̸��� �Է��ϼ���.\n");
			fflush(stdin);
			gets(newname);

			for (tmp2 = b_head->next; tmp2->next != NULL; tmp2 = tmp2->next) // ���� �Է��� �̸��� ������ å �̸��� ������ �� 
			{
				if (strcmp(tmp2->name, newname) == 0) // ���� �̸��� �������� ���� �� ���� �ݺ� 
				{
					printf("�̹� �����ϴ� �����Դϴ�. �ٽ� �Է����ּ���.\n");
					fflush(stdin);
					gets(newname);

					continue;
				}
			}

			strcpy(tmp1->name, newname); 

			return;
		}
		else {
			check++; // �Է��� �ε����� ������ �ε����� ���� ���� �� ī��Ʈ 
		}
	}

	if (check == b_count) // ī��Ʈ�� å ������ ���� ��� 
	{
		printf("������ �������� �ʽ��ϴ�.\n");
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
	printf("\n--*--* ���� ���� *--*--\n\n");

	for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next) // å ��� ��� 
	{
		printf("%d %s %s\n", b_tmp->index, b_tmp->name, b_tmp->num);
	}
	printf("������ ������ ��ȣ�� �Է����ּ���.\n");
	fflush(stdin);
	scanf("%d", &index);

	for (b_tmp = b_head->next; b_tmp->next != NULL; b_tmp = b_tmp->next)
	{
		if (index == b_tmp->index) // �Է��� �ε����� ������ �ε��� �� 
		{
			if (strcmp(b_tmp->num, "") != 0) // �Է��� ������ ������ �л��� �ִ��� üũ 
			{
				printf("������ �л��� �־ ������ �Ұ����մϴ�.\n");
				getch();

				return b_count;
			}
			else {
				b_tmp->next->pre = b_tmp->pre;
				b_tmp->pre->next = b_tmp->next;
				free(b_tmp);

				b_count--;

				save(u_head, u_tail, b_head, b_tail);

				printf("\n--*--* ���� ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				return b_count;
			}
		}
		else {
			check++; // ������ �ε����� �Է¹��� å�� �ε����� ���� ���� ��� ī��Ʈ 
		}
	}

	if (check == b_count) // ī��Ʈ�� å ������ ������� 
	{
		printf("������ ���������ʽ��ϴ�.\n");
		getch();
	}

	return b_count;
}

void menu(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n--*--* �޴��� �����ϼ���. *--*--\n");
	printf("1. ���� ����/�ݳ�\n");
	printf("2. ȸ������ ����\n");
	printf("3. ���α׷� ����\n");

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

		printf("\n\n���α׷��� �����մϴ�.");
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
	printf("\nå �̸�, ������ ���� �� �Դϴ�.\n\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->num, "") != 0) // ���� ���� üũ 
		{
			printf("%s ���� ��\n", tmp->name);
		}
		else {
			printf("%s ���Ⱑ��\n", tmp->name);
		}
	}

	printf("\n--*--*--*--*--*--*--*--*--*--*--*\n");
	printf("1. ����\n");
	printf("2. �ݳ�\n");
	printf("3. ��������\n");

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

	printf("--*--* ���� ���� ������ å ��� *--*--\n");

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // ���Ⱑ���� å�鸸�� ��� ��� 
	{
		if (strcmp(tmp->num, "") == 0)
		{
			printf("%s\n", tmp->name);
		}
	}

	printf("\n\n--*--* �����Ͻ� �������� �Է��ϼ���. *--*--\n");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->name, name) == 0) // ������ ������� ������ ������ �� 
		{
			if (strcmp(tmp->num, "") != 0) // ������ �л��� �ִ��� üũ 
			{
				printf("�̹� ���� ���� �����Դϴ�.\n");
				return;
			}
			else {
				strcpy(tmp->num, login->num);

				system("cls");
				printf("--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				return;
			}
		}
		else { // ������ ������� ������ �������� ���� ���� ��� ī��Ʈ 
			check++;
		}
	}

	if (check == b_count) // ī��Ʈ�� å ������ ������� 
	{
		printf("�������� �ʴ� �����Դϴ�.\n");
		return;
	}
}

void returning(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	BOOK *tmp;
	char name[50];
	int check = 0;

	system("cls");

	printf("--*--* ���� �����Ͻ� å ��� *--*--\n");
	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next) // ���� �α��� �� �л��� ������ å ��ϸ��� ��� 
	{
		if (strcmp(tmp->num, login->num) == 0)
		{
			printf("%s\n", tmp->name);
		}
	}

	printf("\n\n--*--* �ݳ��Ͻ� �������� �Է��ϼ���. *--*--\n");
	fflush(stdin);
	gets(name);

	for (tmp = b_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(tmp->name, name) == 0) // �ݳ��� ������� ������ ������ �� 
		{
			if (strcmp(tmp->num, login->num) != 0) // ������ ������ �й��� ���� �α��� �� �л��� �й� �� 
			{
				printf("���� �����Ͻ� ������ �ƴմϴ�.\n");
				return;
			}
			else {
				strcpy(tmp->num, "");

				system("cls");
				printf("--*--* �ݳ��� �Ϸ�Ǿ����ϴ�. *--*--\n");
				getch();

				return;
			}
		}
		else { // ������ ������� �ݳ��ϰ��� �ϴ� �������� �ٸ� ��� ī��Ʈ 
			check++;
		}
	}

	if (check == b_count) // ī��Ʈ�� å ������ ���� ��� 
	{
		printf("�������� �ʴ� �����Դϴ�.\n");
		return;
	}
}

void edit_login(USER *login, USER *u_head, USER *u_tail, int u_count, BOOK *b_head, BOOK *b_tail, int b_count)
{
	int select;

	system("cls");

	printf("\n1. ��й�ȣ ����\n");
	printf("2. �̸� ����\n");

	fflush(stdin);
	scanf("%d", &select);

	switch (select)
	{
	case 1:
		system("cls");
		printf("\n���ο� ��й�ȣ�� �Է��ϼ���.\n");
		fflush(stdin);
		gets(login->pw);

		system("cls");
		printf("\n--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
		getch();

		break;
	case 2:
		system("cls");
		printf("\n���ο� �̸��� �Է��ϼ���.\n");
		fflush(stdin);
		gets(login->name);

		system("cls");
		printf("\n--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
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

	printf("\n������ ã���� �ϴ� �й��� �Է����ּ���.\n");
	fflush(stdin);
	gets(num);

	for (tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if (strcmp(num, tmp->num) == 0) // �Է¹��� �й��� ������ �й��� �� 
		{
			system("cls");

			printf("\n���ο� ��й�ȣ�� �Է����ּ���.\n");
			fflush(stdin);
			gets(tmp->pw);

			system("cls");
			printf("\n--*--* ������ �Ϸ�Ǿ����ϴ�. *--*--\n");
			getch();

			return;
		}
		else {
			check++; // ������ �й��� �Է� ���� �й��� ���� ���� ��� ī��Ʈ 
		}
	}

	if (check == u_count) // ī��Ʈ�� ȸ�� ���� ������� 
	{
		printf("\n�й��� ���������ʽ��ϴ�.\n");
		getch();
	}
}
