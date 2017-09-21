#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//ȸ�� ����ü ���� 
typedef struct _user
{
	char name[20];
	char id[20];
	char password[30];
	char phone[15];
	int total; //�Ѿ� 
	//int yyyy, dd, mm; //������ ���� ��¥ 
	
	struct _user *next;
	struct _user *pre;
}USER;

//ī�װ� ����ü ����
typedef struct _group
{
	char id[20];
	char name[50];
	float daysum;
	float monthsum;
	//float allsum = 0;
	
	struct _group *next;
	struct _group *pre;
}GROUP;

//�������� ���� ����ü ����
typedef struct information
{
	char id[20];
	int key;
	int index;
	char group[50];
	int yyyy, mm, dd;
	int sum;
	char content[100];
	
	struct information *next;
	struct information *pre;
}INFO;

//�ڵ���� ����ü ����
typedef struct autodebit
{
	char id[20];
	int syyyy, smm;
	int eyyyy, emm;
	int dd;
	char group[50];
	int sum;
	char content[100];
	
	struct autodebit *next;
	struct autodebit *pre;
}AUTO;

//���ΰ� �ڱݰ����޴� �Լ� 
void load_List(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void save(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void initial_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void asterisk(char password[]);
void login(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
int check_Num(char str[]);
void join_User(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void find_ID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void find_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
int daysum(int yyyy, int mm, int dd);
void main_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

void manage_Money(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void manage_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void add_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void group_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, GROUP *g_node);
void del_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

void info_form(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key, char _group[]);
void sort_History(INFO *i_head, INFO *i_tail, USER *login_User);
void add_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key);

void manage_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void auto_addform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, char _group[]);
void add_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void auto_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, AUTO *a_node);
void edit_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void del_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void calculate_Total(INFO *i_head, INFO *i_tail, USER *login_User);

//���� ���� �޴� �Լ�
void view_History(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void find_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node);
void del_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node);
void calculate_Percent(GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, USER *login_User);
void view_today(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void view_month(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void view_all(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

//���� ���� �޴� �Լ� 

#include "define.h"

int main()
{
	//����ü ������ ���� ���� 
	USER *u_head, *u_tail;
	GROUP *g_head, *g_tail;
	INFO *i_head, *i_tail;
	AUTO *a_head, *a_tail;
	
	//����ü ������ ���� �޸� �Ҵ� 
	u_head = (USER *)malloc(sizeof(USER));
	u_tail = (USER *)malloc(sizeof(USER));
	
	//��� ���� 
	u_head->next = u_tail;
	u_tail->pre = u_head;
	u_tail->next = NULL;
	u_head->pre = NULL;
	 
	g_head = (GROUP *)malloc(sizeof(GROUP));
	g_tail = (GROUP *)malloc(sizeof(GROUP));
	
	g_head->next = g_tail;
	g_tail->pre = g_head;
	g_tail->next = NULL;
	g_head->pre = NULL;
	
	i_head = (INFO *)malloc(sizeof(INFO));
	i_tail = (INFO *)malloc(sizeof(INFO));
	
	i_head->next = i_tail;
	i_tail->pre = i_head;
	i_tail->next = NULL;
	i_head->pre = NULL;
	
	a_head = (AUTO *)malloc(sizeof(AUTO));
	a_tail = (AUTO *)malloc(sizeof(AUTO));
	
	a_head->next = a_tail;
	a_tail->pre = a_head;
	a_tail->next = NULL;
	a_head->pre = NULL;
	
	//ȸ��, ī�װ�, ����, �ڵ���� ���� �ҷ��ͼ� ����Ʈ ���� 
	load_List(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
	//�ʱ�ȭ�� �޴� 
	initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);

	return 0;
}

void load_List(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	//ȸ������ �Է� 
	FILE *up = fopen("USER.txt", "r");
	 
	if(up == NULL) // ������ ���� ��� ���� ���� 
	{
		up = fopen("USER.txt", "w");
		fclose(up);	
	}
	else{
		while(!feof(up))
		{
			//���ο� �����ͺ��� �����ϰ� �޸� �Ҵ� �� �ʱ�ȭ 
			USER *u_node;
			u_node = (USER *)malloc(sizeof(USER));
			memset(u_node, 0, sizeof(USER));
			
			fscanf(up, "%s\n%s\n%s\n%s\n%d\n", u_node->name, u_node->id, u_node->password, u_node->phone, &u_node->total);
			
			if(strcmp(u_node->id, "") != 0) //���� �ȿ� �����Ͱ� �����Ѵٸ� 
			{
				//��� ���� 
				u_tail->pre->next = u_node;
				u_node->pre = u_tail->pre;
				u_tail->pre = u_node;
				u_node->next = u_tail;
			}
			else{
				free(u_node);
			}
		}
	}
	
	fclose(up);
	
	//ī�װ����� �Է� 
	FILE *gp = fopen("GROUP.txt", "r");
	 
	if(gp == NULL) // ������ ���� ��� ���� ���� 
	{
		gp = fopen("GROUP.txt", "w");
		fclose(gp);	
	}
	else{
		while(!feof(gp))
		{
			//���ο� �����ͺ��� �����ϰ� �޸� �Ҵ� �� �ʱ�ȭ 
			GROUP *g_node;
			g_node = (GROUP *)malloc(sizeof(GROUP));
			memset(g_node, 0, sizeof(GROUP));
			
			fscanf(gp, "%s %s\n", g_node->id, g_node->name);
			
			if(strcmp(g_node->id, "") != 0) //���� �ȿ� �����Ͱ� �����Ѵٸ� 
			{
				//��� ���� 
				g_tail->pre->next = g_node;
				g_node->pre = g_tail->pre;
				g_tail->pre = g_node;
				g_node->next = g_tail;
			}
			else{
				free(g_node);
			}
		}
	}
	
	fclose(gp);
	
	//�������� �Է� 
	FILE *ip = fopen("HISTORY.txt", "r");
	 
	if(ip == NULL) // ������ ���� ��� ���� ���� 
	{
		ip = fopen("HISTORY.txt", "w");
		fclose(ip);	
	}
	else{
		while(!feof(ip))
		{
			//���ο� �����ͺ��� �����ϰ� �޸� �Ҵ� �� �ʱ�ȭ 
			INFO *i_node;
			i_node = (INFO *)malloc(sizeof(INFO));
			memset(i_node, 0, sizeof(INFO));
			
			fscanf(ip, "%s\n%d\n%d\n%s\n%d %d %d\n%d\n", i_node->id, &i_node->key, &i_node->index, i_node->group, &i_node->yyyy, &i_node->mm, &i_node->dd, &i_node->sum);
			fgets(i_node->content, sizeof(i_node->content), ip);
			
			if(strcmp(i_node->id, "") != 0) //���� �ȿ� �����Ͱ� �����Ѵٸ� 
			{
				//��� ���� 
				i_tail->pre->next = i_node;
				i_node->pre = i_tail->pre;
				i_tail->pre = i_node;
				i_node->next = i_tail;
			}
			else{
				free(i_node);
			}
		}
	}
	
	fclose(ip);
	
	//�ڵ�������� �Է� 
	FILE *ap = fopen("AUTODEBIT.txt", "r");
	
	if(ap == NULL) // ������ ���� ��� ���� ���� 
	{
		ap = fopen("AUTODEBIT.txt", "w");
		fclose(ap);
	}
	else{
		while(!feof(ap))
		{
			//���ο� �����ͺ��� �����ϰ� �޸� �Ҵ� �� �ʱ�ȭ 
			AUTO *a_node;
			a_node = (AUTO *)malloc(sizeof(AUTO));
			memset(a_node, 0, sizeof(AUTO));
			
			fscanf(ap, "%s\n%d %d\n%d %d\n%d\n%s\n%d\n", a_node->id, &a_node->syyyy, &a_node->smm, &a_node->eyyyy, &a_node->emm, &a_node->dd, a_node->group, &a_node->sum);
			fgets(a_node->content, sizeof(a_node->content), ap);
			
			if(strcmp(a_node->id, "") != 0) //���� �ȿ� �����Ͱ� �����Ѵٸ� 
			{
				//��� ���� 
				a_tail->pre->next = a_node;
				a_node->pre = a_tail->pre;
				a_tail->pre = a_node;
				a_node->next = a_tail;
			}
			else{
				free(a_node);
			}
		}
	}
	
	fclose(ap);
}

void save(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	USER *u_tmp;
	GROUP *g_tmp;
	INFO *i_tmp;
	AUTO *a_tmp;
	
	//���Ḯ��Ʈ ���� ��� 
	 
	FILE *up = fopen("USER.txt", "w");
	
	for(u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
	{
		fprintf(up, "%s\n%s\n%s\n%s\n%d\n", u_tmp->name, u_tmp->id, u_tmp->password, u_tmp->phone, u_tmp->total);
	}
	
	fclose(up);
	
	
	FILE *gp = fopen("GROUP.txt", "w");
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		fprintf(gp, "%s %s\n", g_tmp->id, g_tmp->name);
	}
	
	fclose(gp);
	
	
	FILE *ip = fopen("HISTORY.txt", "w");
	
	for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next)
	{
		fprintf(ip, "%s\n%d\n%d\n%s\n%d %d %d\n%d\n%s\n", i_tmp->id, i_tmp->key, i_tmp->index, i_tmp->group, i_tmp->yyyy, i_tmp->mm, i_tmp->dd, i_tmp->sum, i_tmp->content);
	}
	
	fclose(ip);
	
	FILE *ap = fopen("AUTODEBIT.txt", "w");
	
	for(a_tmp = a_head->next; a_tmp->next != NULL; a_tmp = a_tmp->next)
	{
		fprintf(ap, "%s\n%d %d\n%d %d\n%d\n%s\n%d\n%s\n", a_tmp->id, a_tmp->syyyy, a_tmp->smm, a_tmp->eyyyy, a_tmp->emm, a_tmp->dd, a_tmp->group, a_tmp->sum, a_tmp->content);
		
	}
	
	fclose(ap);
	
	system("cls");
	printf("========================================\n");
	printf("\t[ �� �� �� �� �� �� �� ]\n");
	printf("========================================\n\n");
	printf("\t�� �� �� �� ��  �� �� �� �� ��.\n"); 
	getch();
	
	exit(1);
}
	
void initial_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	enum initial_menu {userlogin = 1, join, find_userID, find_userPassword, exit};
	int select;
	
	while(1)
	{
		system("cls");
	
		printf("========================================\n");
		printf("\t[ �� �� �� �� �� �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. �� �� ��\n\n");
		printf(" \t2. ȸ �� �� ��\n\n");
		printf(" \t3. �� �� ��  ã ��\n\n");
		printf(" \t4. �� �� �� ȣ  ã ��\n\n");
		printf(" \t5. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case userlogin:
				login(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			case join:
				join_User(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			case find_userID:
				find_ID(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			case find_userPassword:
				find_Password(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			default: //����ó�� 
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void asterisk(char password[])
{
	int i = 0;
	
	while(1)
	{
		password[i] = getch();
		
		if(password[i] == 13)
		{
			password[i] = NULL; // ���๮�� �����ֱ� 
			break;
		}
		
		if(password[i] == 8)
		{	
			if(i > 0)
			{
				printf("\b");
				printf(" ");
				printf("\b");
				i--;
			}
		}
		else{
			printf("*");
			i++;
		}
	}
}

void login(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	char id[20], password[30];
	int flag = 0;
	USER *tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ �� �� �� ]\n");
	printf("========================================\n\n");
	printf(" \tID : ");
	scanf("%s", id);
	printf("\n \tPASSWORD : ");
	asterisk(password);
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(id, tmp->id) == 0)
		{
			if(strcmp(password, tmp->password) == 0)
			{
				main_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, tmp);
				
				flag = 1;
				break;
			}
			else{
				printf("\n\n========================================\n\n");
				printf("\n   �� �� �� ȣ ��  Ȯ �� �� �� �� ��.\n"); 
				getch();
				
				initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			}
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n========================================\n\n");
		printf("\n  �� �� �� �� �� ��  �� �� �� �� �� ��.\n"); 
		getch();
		
		initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
	}
}

int check_Num(char str[]) //���� ���� �ٸ� ���ڸ� �Է��ߴ��� �˻��� 
{
	int i = 0, flag = 0;

	while(str[i] != '\0')
	{
		if(str[i] < '0' || str[i] > '9')
		{
			flag = 1;
			break;
		}
		else{
			i++;
		}
	}
	
	return flag;
} 

void join_User(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	char id[20];
	USER *tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ ȸ �� �� �� ]\n");
	printf("========================================\n\n");
	printf(" \tI D : ");
	scanf("%s", id);
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, id) == 0)
		{
			printf("\n\n\t�� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
			printf("\t�� ��  �� �� �� �� �� ��.\n");
			printf(" \t");
			scanf("%s", id);
			
			tmp = u_head->next; // �̹� �������� �ʴ� ���̵� ���� ������ ��� �ݺ� 
		}
	}
	
	//���ο� ȸ�� ��� �߰� 
	USER *u_node;
	u_node = (USER *)malloc(sizeof(USER));
	memset(u_node, 0, sizeof(USER));
	
	strcpy(u_node->id, id); //���̵� ��� 

	printf("\n \tP A S S W O R D : ");
	asterisk(u_node->password);
	printf("\n");
	
	printf("\n \t�� �� : ");
	scanf("%s", u_node->name);
	printf("\n");
	
	printf(" \t�� ȭ �� ȣ (�� �� ��  �� ��)\n");
	printf("\n\t");
	scanf("%s", u_node->phone);
	
	//���� ���� �ٸ� ���� �Է��ߴ��� �˻��ؼ� �ùٸ� ���� ���� ������ �ݺ��ؼ� �Է� ���� 
	while(check_Num(u_node->phone) == 1)
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��!\n");
		printf("\n\t");
		scanf("%s", u_node->phone);
	}
	
	printf("\n");
	
	//���ο� ȸ����� ���� 
	u_tail->pre->next = u_node;
	u_node->pre = u_tail->pre;
	u_tail->pre = u_node;
	u_node->next = u_tail;

	printf("\n========================================\n");
	printf("\n  ȸ �� �� �� ��  �� �� �� �� �� �� ��.");
	getch();
	
	initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail); //�ٽ� �ʱ�ȭ������ 
}

void find_ID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	char name[20], phone[15];
	int flag = 0;
	USER *tmp;
	
	system("cls");
	printf("========================================\n");
	printf("\t    [ I D  ã �� ]\n");
	printf("========================================\n\n");
	printf(" \t�� �� : ");
	scanf("%s", name);
	printf("\n\t�� ȭ �� ȣ (�� �� ��  �� ��)\n");
	printf("\n\t");
	scanf("%s", phone);
	
	//���� ���� �ٸ� ���� �Է��ߴ��� �˻��ؼ� �ùٸ� ���� ���� ������ �ݺ��ؼ� �Է� ���� 
	while(check_Num(phone) == 1)
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��!\n");
		printf("\n\t");
		scanf("%s", phone);
	}
	
	printf("\n");
	printf("========================================\n\n");
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->name, name) == 0 && strcmp(tmp->phone, phone) == 0)
		{
			printf("\t�� �� �� ��  %s �� �� ��.\n", tmp->id);
			
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
	{
		printf("   �� �� �� ��  �� �� �� ��  �� �� �� ��.\n");
	}
	
	getch();
	
	initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail); //�ٽ� �ʱ�ȭ������ 
}

void find_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	char name[20], id[20], phone[15], newpassword[30];
	int flag = 0;
	
	USER *tmp;
	
	system("cls");
	printf("========================================\n");
	printf("\t[ �� �� �� ȣ   ã �� ]\n");
	printf("========================================\n\n");
	printf(" \t�� �� : ");
	scanf("%s", name);
	printf("\n \tID : ");
	scanf("%s", id); 
	printf("\n\t�� ȭ �� ȣ (�� �� ��  �� ��)\n");
	printf("\n\t");
	scanf("%s", phone);
	
	//���� ���� �ٸ� ���� �Է��ߴ��� �˻��ؼ� �ùٸ� ���� ���� ������ �ݺ��ؼ� �Է� ���� 
	while(check_Num(phone) == 1)
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��!\n");
		printf("\n\t");
		scanf("%s", phone);
	}
	
	printf("\n");
	printf("========================================\n\n");
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next) //�Է��� ������ ��ġ�ϴ� �����Ͱ� �����ϴ��� �˻� 
	{
		if(strcmp(tmp->name, name) == 0 && strcmp(tmp->id, id) == 0 && strcmp(tmp->phone, phone) == 0)
		{
			printf("�� �� �� �� �� �� ȣ ��  �� �� �� �� �� ��.\n");
			printf("\n\t>> ");
			asterisk(tmp->password);
			
			printf("\n �� �� �� �� ��  �� �� �� �� �� �� ��.\n");
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
	{
		printf("   �� �� �� �� �� ��  �� �� �� �� ��.\n");
	}
	
	getch();
	
	initial_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail); //�ٽ� �ʱ�ȭ������ 
}

int daysum(int yyyy, int mm, int dd)
{
	int i, sum;
	int leapyear = 0;
	int month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	for(i = 0; i < yyyy-1; i++)
	{
		if((i%4 == 0 && i%100 != 0) || (i%100 == 0 && i%400 == 0))
		{
			leapyear++;
		}
	}
	
	if((yyyy%4 == 0 && yyyy%100 != 0) || (yyyy%100 == 0 && yyyy%400 == 0))
	{
		month[1] = 29;
	}
	
	sum = (366 * leapyear) + (365 * (yyyy-1)-leapyear);
	
	for(i = 0; i < mm-1; i++)
	{
		sum = sum + month[i];
	}
	
	sum = sum + dd;
	
	return sum;
}

void main_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum main_menu {manage_userMoney = 1, view_userHistory, manage_userInfo, exit};
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("========================================\n");
		printf("     [ %s �� ��  �� �� �� ]\n", login_User->name);
		printf("========================================\n\n");
		printf(" \t1. �� �� �� ��\n\n");
		printf(" \t2. �� �� �� ��\n\n");
		printf(" \t3. �� �� �� ��\n\n");
		printf(" \t4. �� �� �� ��  �� ��\n\n"); 
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case manage_userMoney:
				manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case view_userHistory:
				view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case manage_userInfo:
				//���� ���� 
				printf("3\n"); 
				break;
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				break;
			default: //����ó�� 
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void manage_Money(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Money {manage_moneyGroup = 1, income, spending, manage_Autodebit, back, exit};
	int select;

	while(1)
	{
		system("cls");
		
		printf("========================================\n");
		printf("\t   [ �� �� �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. ī �� �� ��  �� ��\n\n");
		printf(" \t2. �� ��\n\n");
		printf(" \t3. �� ��\n\n");
		printf(" \t4. �� �� �� ��  �� ��\n\n");
		printf(" \t5. �� ��  ȭ �� �� ��\n\n"); 
		printf(" \t6. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{ 
			case manage_moneyGroup:
				manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case income:
				add_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, 1);
				manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case spending:
				add_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, 2);
				manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case manage_Autodebit:
				manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case back:
				main_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			default:
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void manage_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Group {add_moneyGroup = 1, edit_moneyGroup, del_moneyGroup, back, exit};
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("========================================\n");
		printf("\t[ ī �� �� ��  �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. ī �� �� ��  �� ��\n\n");
		printf(" \t2. ī �� �� ��  �� ��\n\n");
		printf(" \t3. ī �� �� ��  �� ��\n\n");
		printf(" \t4. �� ��  ȭ �� �� ��\n\n");
		printf(" \t5. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{
			case add_moneyGroup:
				add_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case edit_moneyGroup:
				edit_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case del_moneyGroup:
				del_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case back:
				manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			default:
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void add_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char name[30];
	GROUP *tmp;

	system("cls");
	
	printf("========================================\n");
	printf(" \t[ ī �� �� ��  �� �� ]\n");
	printf("========================================\n\n");
	printf("\n\t�� �� ��  �� �� �� �� ��\n");
	printf("\n\t>> ");
	scanf("%s", name);
	
	for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->name, name) == 0)
		{
			printf("\n\n\t�� ��  �� �� �� ��  �� �� �� �� ��.\n");
			printf("\t�� ��  �� �� �� �� �� ��. [ �� �� �� �� : -1 ]\n");
			printf("\n\t>> ");
			scanf("%s", name);
			
			if(strcmp(name, "-1") == 0)
			{
				manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				return;
			}
			else{	
				tmp = g_head->next; // �̹� �������� �ʴ� �̸��� ���� ������ ��� �ݺ� 
			}
		}
	}
	
	//���ο� ��� �߰� 
	GROUP *g_node;
	g_node = (GROUP *)malloc(sizeof(GROUP));
	
	//���ο� ��� ���� 
	g_tail->pre->next = g_node;
	g_node->pre = g_tail->pre;
	g_tail->pre = g_node;
	g_node->next = g_tail;
	
	strcpy(g_node->id, login_User->id);
	strcpy(g_node->name, name);
	
	printf("\n========================================\n");
	printf("\n �� �� �� �� ��  �� �� �� �� �� �� ��.\n");
	getch();
	
	manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void group_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, GROUP *g_node)
{
	char _name[30];
	GROUP *g_tmp;
	INFO *i_tmp;
	
	printf("\n�� �� �� �� �� ��  �� �� �� �� �� ��.\n");
	printf("\n>> ");
	scanf("%s", _name);
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		if(strcmp(g_tmp->id, login_User->id) == 0 && strcmp(g_tmp->name, _name) == 0)
		{
			printf("\n�� ��  �� �� ��  �� �� �� �� ��.\n");
			printf("\n�� ��  �� �� �� �� �� ��.\n");
			printf("\n>> ");
			scanf("%s", _name);
			printf("\n");
			
			g_tmp = g_head->next; 
		}
	}
	
	if(strcmp(_name, "-1") == 0)
	{
		return;
	}
	else{
		for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next)
		{
			if(strcmp(i_tmp->id, login_User->id) == 0 && strcmp(i_tmp->group, g_node->name) == 0)
			{
				strcpy(i_tmp->group, _name);
			}
		}
		
		strcpy(g_node->name, _name); 
	
		printf("\n �� �� �� �� ��  �� �� �� �� �� �� ��.\n");
		getch();
	}
	
}

void edit_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char name[30];
	int num = 0, flag = 0;
	GROUP *tmp;
	INFO *i_tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf(" \t[ ī �� �� ��  �� �� ]\n");
	printf("========================================\n\n");
	
	for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next) //ī�װ� ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->name);
			num ++; //ī�װ� ���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("ī �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\nī �� �� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  ī �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			scanf("%s", name);
			
			if(strcmp(name, "-1") == 0)
			{
				break;
			}
			else
			{
				for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->name, name) == 0)
					{
						group_editform(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp);
						
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
	manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User); //���� ȭ������ ���ư���
}

void del_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char name[30];
	int num = 0, flag = 0, check = 0;
	GROUP *tmp;
	INFO *i_tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf(" \t[ ī �� �� ��  �� �� ]\n");
	printf("========================================\n\n");
	
	for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next) //ī�װ� ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->name);
			num ++; //ī�װ� ���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("ī �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\nī �� �� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  ī �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			scanf("%s", name);
			
			if(strcmp(name, "-1") == 0)
			{
				manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				return;
			}
			else
			{
				for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->name, name) == 0)
					{
						for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next) // ī�װ��� ���� ������ �ִ��� ���� 
						{
							if(strcmp(i_tmp->id, login_User->id) == 0 && strcmp(tmp->name, i_tmp->group) == 0)
							{
								check = 1; //ī�װ� �ȿ� ������ ������ 
							}
						}
						
						if(check == 0)
						{
							tmp->pre->next = tmp->next; //��� ���� ���� 
							tmp->next->pre = tmp->pre;
							free(tmp);
							
							printf("\n�� �� �� �� ��  �� �� �� �� �� �� ��.\n");
							getch();
	
							flag = 1;
							break;
						}
						else{
							printf("\n��  ī �� �� �� ��  �� �� �� ��  �� �� ��  �� �� �� ��.\n");
							printf("\n�� �� ��  �� �� �� �� �� ��.\n");
							getch(); 
							
							flag = 1;
							break;
						}
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
	manage_Group(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User); //���� ȭ������ ���ư���
}

void info_form(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key, char _group[])
{
	int _index = 1;
	INFO *tmp1, *tmp2;
	
	INFO *i_node;
	i_node = (INFO *)malloc(sizeof(INFO));

	i_tail->pre->next = i_node;
	i_node->pre = i_tail->pre;
	i_tail->pre = i_node;
	i_node->next = i_tail;
	
	system("cls");
	
	printf("\n\t Ҵ : ");
	scanf("%d", &i_node->yyyy);
	
	printf("\n\n\t �� : ");
	scanf("%d", &i_node->mm);
	
	printf("\n\n\t �� : ");
	scanf("%d", &i_node->dd);
	
	printf("\n\n\t �� �� : ");
	scanf("%d", &i_node->sum);
	
	printf("\n\n\t �� �� : ");
	fflush(stdin);
	gets(i_node->content);
	
	strcpy(i_node->id, login_User->id);
	strcpy(i_node->group, _group);
	i_node->key = _key;
	
	if(_key == 1) //�ڱ� �Ѿ׿� �ݿ� 
	{
		login_User->total = login_User->total + i_node->sum;
	}
	else{
		login_User->total = login_User->total - i_node->sum;
	}
	
	sort_History(i_head, i_tail, login_User);
		
	printf("\n\n �� �� �� �� ��  �� �� �� �� �� �� ��.\n");
	getch();
	
	manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void sort_History(INFO *i_head, INFO *i_tail, USER *login_User)
{
	INFO *tmp1, *tmp2;
	int _index = 1;
	
	for(tmp1 = i_head->next; tmp1->next != NULL; tmp1 = tmp1->next) // ��¥������ ���� ���Ḯ��Ʈ ���� �����ϱ� 
	{
		for(tmp2 = tmp1; tmp2->next != NULL; tmp2 = tmp2->next)
		{
			if(daysum(tmp2->yyyy, tmp2->mm, tmp2->dd) < daysum(tmp1->yyyy, tmp1->mm, tmp1->dd))
			{
				tmp1->pre->next = tmp2;
				tmp2->next->pre = tmp1;
				tmp1->next = tmp2->next;
				tmp2->pre = tmp1->pre;
				tmp2->next = tmp2->next->pre;
				tmp1->pre = tmp1->pre->next;
			}
		}
	}
	
	for(tmp1 = i_head->next; tmp1->next != NULL; tmp1 = tmp1->next) // �ε��� �ű�� 
	{
		if(strcmp(tmp1->id, login_User->id) == 0)
		{
			tmp1->index = _index;
			_index ++;
		}
	}
}

void add_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key)
{
	int num = 0, flag = 0;
	char name[30];
	GROUP *tmp;

	system("cls");
	
	printf("========================================\n");
	printf("\t  [ �� �� / �� �� ]\n");
	printf("========================================\n\n");
	
	for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next) //ī�װ� ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->name);
			num ++; //ī�װ� ���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("ī �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\nī �� �� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  ī �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			scanf("%s", name);
			
			if(strcmp(name, "-1") == 0)
			{
				return;
			}
			else
			{
				for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->name, name) == 0)
					{
						info_form(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, _key, name);
						
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
}

void manage_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Group {add_AutoDebit = 1, edit_AutoDebit, del_AutoDebit, back, exit};
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("========================================\n");
		printf("\t[ �� �� �� ��  �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. �� �� �� ��  �� ��\n\n");
		printf(" \t2. �� �� �� ��  �� ��\n\n");
		printf(" \t3. �� �� �� ��  �� ��\n\n");
		printf(" \t4. �� ��  ȭ �� �� ��\n\n"); 
		printf(" \t5. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{
			case add_AutoDebit:
				add_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case edit_AutoDebit:
				edit_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case del_AutoDebit:
				del_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case back:
				manage_Money(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			default:
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void auto_addform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, char _group[])
{	
	int tmpyy, tmpmm, flag = 0, i, sum;
	char _content[100];
	AUTO *tmp, *a_node;
	a_node = (AUTO *)malloc(sizeof(AUTO));
				
	//���ο� ��� ���� 
	a_tail->pre->next = a_node;
	a_node->pre = a_tail->pre;
	a_tail->pre = a_node;
	a_node->next = a_tail;
	
	system("cls");
	
	printf("========================================\n");
	printf("    [ �� �� �� ��  �� �� �� �� ]\n");
	printf("========================================\n\n");
	printf("�� �� �� ��  �� �� ��  �� ��  �� ��  �� �� �� �� ��.\n\n");
	
	printf("\n\t �� ��  Ҵ : ");
	scanf("%d", &a_node->syyyy);
	
	printf("\n\n\t �� ��  �� : ");
	scanf("%d", &a_node->smm);
	
	printf("\n\n\t �� ��  Ҵ : ");
	scanf("%d", &a_node->eyyyy);
	
	printf("\n\n\t �� ��  �� : ");
	scanf("%d", &a_node->emm);
	
	printf("\n\n\t �� ��  �� : ");
	scanf("%d", &a_node->dd);
	
	printf("\n\n\t �� �� : ");
	scanf("%d", &a_node->sum);

	printf("\n\n\t �� �� : ");
	fflush(stdin);
	gets(_content);
	
	for(tmp = a_head->next; tmp->next != NULL; tmp = tmp->next) // �ڵ���� ���� �ߺ� üũ 
	{
		if(strcmp(tmp->content, _content) == 0)
		{
			printf("\n\t�� ��  �� �� �� �� ��.\n");
			printf("\n\t�� ��  �� �� �� �� ��.\n");
			printf("\n\n\t �� �� : ");
			fflush(stdin);
			gets(_content);
			
			tmp = a_head->next;
		}
	}
	strcpy(a_node->content, _content);
	
	strcpy(a_node->id, login_User->id);
	strcpy(a_node->group, _group);
	strcpy(_content, "�ڵ���� - "); 
	strcat(_content, a_node->content);
	
	tmpyy = a_node->syyyy;
	tmpmm = a_node->smm;
	sum = (((a_node->eyyyy - a_node->syyyy) * 12 + a_node->emm) - a_node->smm) + 1;
	
	for(i = 0; i < sum; i++) //�ڵ���� ���� �Ⱓ�� �ش��ϴ� ���ο� ���� ����� 
	{
		//���ο� ��� �߰� 
		INFO *i_node;
		i_node = (INFO *)malloc(sizeof(INFO));
		
		//���ο� ��� ���� 
		i_tail->pre->next = i_node;
		i_node->pre = i_tail->pre;
		i_tail->pre = i_node;
		i_node->next = i_tail;
		
		strcpy(i_node->id, login_User->id);
		i_node->key = 2;
		strcpy(i_node->group, _group);
		i_node->yyyy = tmpyy;
		i_node->mm = tmpmm;
		i_node->dd = a_node->dd;
		i_node->sum = a_node->sum;
		strcpy(i_node->content, _content);
		
		tmpmm ++;
		
		if(tmpmm > 12)
		{
			tmpyy ++;
			tmpmm = 1;
		}
	}
		
	sort_History(i_head, i_tail, login_User);
	
	printf("\n\n �� �� �� �� ��  �� �� �� �� �� �� ��.\n");
	getch();
}

void add_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	int num = 0, flag = 0;
	char name[30];
	GROUP *tmp;

	system("cls");
	
	printf("========================================\n");
	printf("\t[ �� �� �� ��  �� ��]\n");
	printf("========================================\n\n");
	
	for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next) //ī�װ� ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->name);
			num ++; //ī�װ� ���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("ī �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\nī �� �� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  ī �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			scanf("%s", name);
			
			if(strcmp(name, "-1") == 0)
			{
				manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				return;
			}
			else
			{
				for(tmp = g_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->name, name) == 0)
					{
						auto_addform(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp->name);
						
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
	manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User); //���� ȭ������ ���ư���
}

void auto_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, AUTO *a_node)
{
	char check[100];
	INFO *i_tmp;
	
	strcpy(check, "�ڵ���� - ");
	strcat(check, a_node->content);
	
	for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next)
	{
		if(strcmp(i_tmp->id, login_User->id) == 0 && strcmp(i_tmp->content, check) == 0)
		{
			i_tmp->pre->next = i_tmp->next; //��� ���� ���� 
			i_tmp->next->pre = i_tmp->pre;
			free(i_tmp);
		}
	}
	
	a_node->pre->next = a_node->next; //��� ���� ���� 
	a_node->next->pre = a_node->pre;
	free(a_node);
	
	auto_addform(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, a_node->group);
}

void edit_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char _content[100];
	int num = 0, flag = 0;
	AUTO *tmp;
	INFO *i_tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf(" \t[ �� �� �� ��  �� �� ]\n");
	printf("========================================\n\n");
	
	for(tmp = a_head->next; tmp->next != NULL; tmp = tmp->next) // ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->content);
			num ++; //���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("�� �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\n�� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  �� �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			fflush(stdin);
			gets(_content);
			
			if(strcmp(_content, "-1") == 0)
			{
				manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				return;
			}
			else
			{
				for(tmp = a_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->content, _content) == 0)
					{	
						auto_editform(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp);
						
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
	manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User); //���� ȭ������ ���ư���
}

void auto_delform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, AUTO *a_node)
{
	char check[100];
	INFO *i_tmp;
	
	strcpy(check, "�ڵ���� - ");
	strcat(check, a_node->content);
	
	for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next)
	{
		if(strcmp(i_tmp->id, login_User->id) == 0 && strcmp(i_tmp->content, check) == 0)
		{
			i_tmp->pre->next = i_tmp->next; //��� ���� ���� 
			i_tmp->next->pre = i_tmp->pre;
			free(i_tmp);
		}
	}
	
	a_node->pre->next = a_node->next; //��� ���� ���� 
	a_node->next->pre = a_node->pre;
	free(a_node);
	
	sort_History(i_head, i_tail, login_User);
	
	printf("\n�� �� ��  �� �� �� �� �� �� ��.\n");
	getch(); 
}

void del_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char _content[100];
	int num = 0, flag = 0;
	AUTO *tmp;
	INFO *i_tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf(" \t[ �� �� �� ��  �� �� ]\n");
	printf("\n    �� ��  �� �� ��  �� �� �� �� ��.\n\n"); 
	printf("========================================\n\n");
	
	for(tmp = a_head->next; tmp->next != NULL; tmp = tmp->next) // ��� ��� 
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n\t%s\n", tmp->content);
			num ++; //���� ���� 
		}
	}
	
	if(num == 0)
	{
		printf("�� �� �� �� ��  �� �� �� �� �� �� �� ��.\n");
		printf("\n�� �� ��  �� ��  �� �� �� ��  �� �� �� �� �� ��.\n");
		getch();
		
		manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else{
		printf("\n========================================\n");
		printf("\n�� �� ��  �� �� �� �� ��  �� �� �� �� ��\n");
		
		while(1)
		{
			printf("\n>> ");
			fflush(stdin);
			gets(_content);
			
			if(strcmp(_content, "-1") == 0)
			{
				manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				return;
			}
			else
			{
				for(tmp = a_head->next; tmp->next != NULL; tmp = tmp->next)
				{
					if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->content, _content) == 0)
					{	
						auto_delform(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp);
						
						flag = 1;
						break;
					}
				}
				
				if(flag == 0)
				{
					printf("\n\n�� �� �� �� �� ��  �� �� �� �� ��.\n");
					printf("\n�� ��  �� �� �� �� ��. [��� : -1]\n");
				}
				else{
					break;
				}
			}
		}
	}
	manage_Auto(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User); //���� ȭ������ ���ư���
}

void calculate_Total(INFO *i_head, INFO *i_tail, USER *login_User)
{
	INFO *tmp;
	int sum = 0;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
		{
			if(tmp->key == 1)
			{
				sum = sum + tmp->sum;
			}
			else if(tmp->key == 2)
			{
				sum = sum - tmp->sum;
			}
		}
	}
	
	login_User->total = sum;
}

#include "define.h"

void view_History(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Money {search_userHistory = 1, view_TodayHistory, view_ThismonthHistory, view_AllHistory, back, exit};
	int select;

	while(1)
	{
		calculate_Total(i_head, i_tail, login_User);
		
		system("cls");
		
		printf("========================================\n");
		printf("\t   [ �� �� �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. �� �� �� �� (�� �� / �� ��)\n\n");
		printf(" \t2. �� �� �� �� �� ��\n\n");
		printf(" \t3. �� ��  ��  �� �� �� ��\n\n");
		printf(" \t4. �� �� �� �� �� ��\n\n");
		printf(" \t5. �� �� ȭ �� �� ��\n\n"); 
		printf(" \t6. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{ 
			case search_userHistory:
				find_info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case view_TodayHistory:
				view_today(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case view_ThismonthHistory:
				view_month(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case view_AllHistory:
				view_all(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case back:
				main_menu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case exit:
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			default:
				
				printf("\n\t�� �� ��  �� �� �� �� ��\n");
				getch();
		}
	}
}

void find_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	int num = 0, _index, select, flag = 0;
	char search[100];
	INFO *tmp;
	
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ �� �� �� �� ]\n");
	printf("========================================\n\n");
	printf("\t�� �� �� ��  �� �� �� �� ��.\n");
	printf("\n\t>> ");
	fflush(stdin);
	gets(search);
	
	printf("\n========================================\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if((strcmp(tmp->id, login_User->id) == 0) && (strcmp(tmp->content, search) == 0 || strcmp(tmp->group, search) == 0))
		{
			printf("\n%2d | %4d - %2d - %2d | %d | %8d | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, tmp->sum, tmp->content);
			num ++;
		}
	}
	
	if(num == 0)
	{
		printf("\n�� �� ��  �� �� �� ��.\n\n");
		getch();
		
		view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else
	{
		printf("\n========================================\n\n");
		printf("�� �� �� �� ��  �� �� ��  �� �� �� ��\n    �� �� �� ��  �� �� �� �� ��\n"); 
		printf("\n>> ");
		fflush(stdin);
		scanf("%d", &_index);
		
		for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(strcmp(tmp->id, login_User->id) == 0 && tmp->index == _index)
			{
				while(1)
				{
					printf("\n1. ��  ��\n");
					printf("\n2. ��  ��\n");
					printf("\n>> ");
					scanf("%d", &select);
					
					if(select == 1)
					{
						edit_info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp);
					}
					else if(select == 2)
					{
						del_info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, tmp);
					}
					else{
						printf("\n�� �� ��  �� �� �� �� ��\n"); 
						getch();
						
						continue;
					}
				}
				flag = 1;
				break;
			}
		}
		
		if(flag == 0)
		{
			printf("\n�� �� ��  �� �� �� �� ��\n");
			getch();
			
			find_info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
			
			return;
		}
	}
}

void edit_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node)
{
	int _key = i_node->key;
	
	i_node->pre->next = i_node->next; //��� ���� ���� 
	i_node->next->pre = i_node->pre;
	free(i_node);
	
	add_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, i_node->key);
	
	sort_History(i_head, i_tail, login_User);
	view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void del_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node)
{
	i_node->pre->next = i_node->next; //��� ���� ���� 
	i_node->next->pre = i_node->pre;
	free(i_node);
	
	sort_History(i_head, i_tail, login_User);
	view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void calculate_Percent(GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	float _daysum = 0, _monthsum = 0;//, _allsum = 0;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	//ī�װ� �� �Ϸ� ���, �� �� ���
	printf("������ �����.\n");
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("������ �����.\n");
		g_tmp->daysum = 0;
		g_tmp->monthsum = 0;
		//g_tmp->allsum = 0;
		//printf("������ �����.\n");
		
		for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->group, g_tmp->name) == 0 && tmp->key == 2)
			{
				//g_tmp->allsum = g_tmp->allsum + tmp->sum;
				
				if(daysum(tmp->yyyy, tmp->mm, tmp->dd) == daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
				{
					g_tmp->daysum = g_tmp->daysum + tmp->sum;
				}
				
				if(daysum(t->tm_year + 1900, t->tm_mon + 1, 1) <= daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
				{
					g_tmp->monthsum = g_tmp->monthsum + tmp->sum;
				}
			}
		}
	}
	
	//�Ϸ�, �� �� ���� �� ����� ��� 
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && tmp->key == 2)
		{
			//_allsum = _allsum + tmp->sum;
			
			if(daysum(tmp->yyyy, tmp->mm, tmp->dd) == daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{
				_daysum = _daysum + tmp->sum;
			}
			
			if(daysum(t->tm_year + 1900, t->tm_mon + 1, 1) <= daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{
				_monthsum = _monthsum + tmp->sum;
			}
		}
	}
	
	//�Ϸ�, �� �� ���� ī�װ� �� ����� ������ �� ����� ���ϱ� ���� �Ͽ� �ۼ��������� ����� 
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		/*if(_allsum > 0)
		{
			g_tmp->allsum = (g_tmp->allsum / _allsum) * 100;
		}*/
		
		if(_daysum > 0)
		{
			g_tmp->daysum = (g_tmp->daysum / _daysum) * 100;
		}
		
		if(_monthsum > 0)
		{
			g_tmp->monthsum = (g_tmp->monthsum / _monthsum) * 100;
		}
	}
}

void view_today(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("=====================================================\n");
	printf("\t\t[ �� �� �� �� ]\n");
	printf("=====================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			if(daysum(tmp->yyyy, tmp->mm, tmp->dd) == daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{
				printf("\n%2d | %4d - %2d - %2d | %d | %8d | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, tmp->sum, tmp->content);
			}
		}
	}
	
	printf("=====================================================\n\n");
	printf("\t\t[ �� �� �� �� ]\n\n"); 
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->daysum); 
	}
	
	printf("=====================================================\n\n");
	printf("total : %d", login_User->total);
	
	getch();
}

void view_month(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("========================================================\n");
	printf("\t\t[ �� ��  ��  �� �� ]\n");
	printf("========================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			if(daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday) <= daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{
				printf("\n%2d | %4d - %2d - %2d | %d | %8d | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, tmp->sum, tmp->content);
			}
		}
	}
	
	printf("\n========================================================\n\n");
	printf("\t\t[ �� �� �� �� ]\n\n");
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->monthsum);
	}
	
	printf("========================================================\n\n");
	printf("total : %d", login_User->total);
	
	getch();
}

void view_all(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("========================================================\n");
	printf("\t\t[ �� ��  �� �� ]\n");
	printf("========================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			printf("\n%2d | %4d - %2d - %2d | %d | %8d | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, tmp->sum, tmp->content);
		}
	}
	
	printf("\n========================================================\n\n");
	printf("\t\t[ �� �� �� �� ]\n\n");
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->daysum);
	}
	
	printf("========================================================\n\n");
	printf("total : %d", login_User->total);
	
	getch();
}
