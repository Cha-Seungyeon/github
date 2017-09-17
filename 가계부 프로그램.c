#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//ȸ�� ����ü ���� 
typedef struct USER
{
	char name[20];
	char id[20];
	char password[30];
	char phone[15];
	int total;
	int yyyy, dd, mm;
	
	struct USER *next;
	struct USER *pre;
}USER;

//ī�װ� ����ü ����
typedef struct GROUP
{
	char id[20];
	char name[50];
	
	struct GROUP *next;
	struct GROUP *pre;
}GROUP;

//�������� ���� ����ü ����
typedef struct INFORMATION
{
	char id[20];
	int key;
	int index;
	char group[50];
	int yyyy, mm, dd;
	int sum;
	char content[100];
	
	struct INFORMATION *next;
	struct INFORMATION *pre;
}INFO;

//�ڵ���� ����ü ����
typedef struct AUTODEBIT
{
	char id[20];
	int syyyy, smm, sdd;
	int eyyyy, emm, edd;
	int sum;
	char content[100];
	
	struct AUTODEBIT *next;
	struct AUTODEBIT *pre;
}AUTO;

//�Լ� ���� 
void loadList(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void save(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void initialmenu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void login(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void joinUser(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void findID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);

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
	loadList(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
	//�ʱ�ȭ�� �޴� 
	initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);

	return 0;
}

void loadList(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
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
			
			fscanf(up, "%s\n%s\n%s\n%s\n%d\n%d %d %d\n", u_node->name, u_node->id, u_node->password, u_node->phone, &u_node->total, &u_node->yyyy, &u_node->mm, &u_node->dd);
			
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
			
			fscanf(ip, "%s\n%d\n%d\n%d %d %d\n%d\n%s\n", i_node->id, &i_node->key, &i_node->index, &i_node->yyyy, &i_node->dd, &i_node->mm, &i_node->sum, i_node->content);
			
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
			
			fscanf(ap, "%s\n%d %d %d\n%d %d %d\n%d\n%s\n", a_node->id, &a_node->syyyy, &a_node->smm, &a_node->sdd, &a_node->eyyyy, &a_node->emm, &a_node->edd, &a_node->sum, a_node->content);
			
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
		fprintf(up, "%s\n%s\n%s\n%s\n%d\n%d %d %d\n", u_tmp->name, u_tmp->id, u_tmp->password, u_tmp->phone, u_tmp->total, u_tmp->yyyy, u_tmp->mm, u_tmp->dd);
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
		fprintf(ip, "%s\n%d\n%d\n%d %d %d\n%d\n%s\n", i_tmp->id, i_tmp->key, i_tmp->index, i_tmp->yyyy, i_tmp->dd, i_tmp->mm, i_tmp->sum, i_tmp->content);
	}
	
	fclose(ip);
	
	FILE *ap = fopen("AUTODEBIT.txt", "w");
	
	for(a_tmp = a_head->next; a_tmp->next != NULL; a_tmp = a_tmp->next)
	{
		fprintf(ap, "%s\n%d %d %d\n%d %d %d\n%d\n%s\n", a_tmp->id, a_tmp->syyyy, a_tmp->smm, a_tmp->sdd, a_tmp->eyyyy, a_tmp->emm, a_tmp->edd, a_tmp->sum, a_tmp->content);
		
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
	
void initialmenu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	int select;
	
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
		case 1:
			login(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			break;
		case 2:
			joinUser(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			break;
		case 3:
			findID(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			break;
		case 4:
			//��й�ȣ ã��
			break;
		case 5:
			save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
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
	printf(" \tPASSWORD : ");
	scanf("%s", password);
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, id) == 0)
		{
			if(strcmp(tmp->password, password) == 0)
			{
				save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
				//mainmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, id);
				//������ ���� ��¥ ������Ʈ �� �� 
				flag = 1;
				break;
			}
			else{
				printf("\n\n========================================\n\n");
				printf("\n   �� �� �� ȣ ��  Ȯ �� �� �� �� ��.\n"); 
				getch();
				
				initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			}
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n========================================\n\n");
		printf("\n  �� �� �� �� �� ��  �� �� �� �� �� ��.\n"); 
		getch();
		
		initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
	}
}

void joinUser(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
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
			scanf("%s", id);
			
			tmp = u_head->next; // �̹� �������� �ʴ� ���̵� ���� ������ ��� �ݺ� 
		}
	}
	
	//���ο� ȸ�� ��� �߰� 
	USER *u_node;
	u_node = (USER *)malloc(sizeof(USER));
	memset(u_node, 0, sizeof(USER));
	
	strcpy(u_node->id, id); //���̵� ��� 

	printf("\n");
	printf(" \tP A S S W O R D : ");
	scanf("%s", u_node->password);
	printf("\n");
	
	printf(" \t�� �� : ");
	scanf("%s", u_node->name);
	printf("\n"); 
	
	printf("\t�� ȭ �� ȣ (�� �� ��  �� ��)\n");
	printf("\n\t");
	scanf("%s", u_node->phone);
	printf("\n");
	
	//���ο� ȸ����� ���� 
	u_tail->pre->next = u_node;
	u_node->pre = u_tail->pre;
	u_tail->pre = u_node;
	u_node->next = u_tail;

	printf("\n========================================\n");
	printf("\n  ȸ �� �� �� ��  �� �� �� �� �� �� ��.");
	getch();
	
	initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
}

void findID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
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
		printf("�� �� �� ��  �� �� �� ��  �� �� �� ��.\n");
	}
	
	getch();
	
	initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
}
