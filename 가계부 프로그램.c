#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

//회원 구조체 정의 
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

//카테고리 구조체 정의
typedef struct GROUP
{
	char id[20];
	char name[50];
	
	struct GROUP *next;
	struct GROUP *pre;
}GROUP;

//수입지출 내역 구조체 정의
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

//자동출금 구조체 정의
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

//함수 선언 
void loadList(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void save(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void initialmenu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void login(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void joinUser(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void findID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);

int main()
{
	//구조체 포인터 변수 선언 
	USER *u_head, *u_tail;
	GROUP *g_head, *g_tail;
	INFO *i_head, *i_tail;
	AUTO *a_head, *a_tail;
	
	//구조체 포인터 변수 메모리 할당 
	u_head = (USER *)malloc(sizeof(USER));
	u_tail = (USER *)malloc(sizeof(USER));
	
	//노드 연결 
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
	
	//회원, 카테고리, 내역, 자동출금 정보 불러와서 리스트 연결 
	loadList(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
	//초기화면 메뉴 
	initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);

	return 0;
}

void loadList(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	//회원파일 입력 
	FILE *up = fopen("USER.txt", "r");
	 
	if(up == NULL) // 파일이 없을 경우 새로 만듦 
	{
		up = fopen("USER.txt", "w");
		fclose(up);	
	}
	else{
		while(!feof(up))
		{
			//새로운 포인터변수 선언하고 메모리 할당 후 초기화 
			USER *u_node;
			u_node = (USER *)malloc(sizeof(USER));
			memset(u_node, 0, sizeof(USER));
			
			fscanf(up, "%s\n%s\n%s\n%s\n%d\n%d %d %d\n", u_node->name, u_node->id, u_node->password, u_node->phone, &u_node->total, &u_node->yyyy, &u_node->mm, &u_node->dd);
			
			if(strcmp(u_node->id, "") != 0) //파일 안에 데이터가 존재한다면 
			{
				//노드 연결 
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
	
	//카테고리파일 입력 
	FILE *gp = fopen("GROUP.txt", "r");
	 
	if(gp == NULL) // 파일이 없을 경우 새로 만듦 
	{
		gp = fopen("GROUP.txt", "w");
		fclose(gp);	
	}
	else{
		while(!feof(gp))
		{
			//새로운 포인터변수 선언하고 메모리 할당 후 초기화 
			GROUP *g_node;
			g_node = (GROUP *)malloc(sizeof(GROUP));
			memset(g_node, 0, sizeof(GROUP));
			
			fscanf(gp, "%s %s\n", g_node->id, g_node->name);
			
			if(strcmp(g_node->id, "") != 0) //파일 안에 데이터가 존재한다면 
			{
				//노드 연결 
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
	
	//내역파일 입력 
	FILE *ip = fopen("HISTORY.txt", "r");
	 
	if(ip == NULL) // 파일이 없을 경우 새로 만듦 
	{
		ip = fopen("HISTORY.txt", "w");
		fclose(ip);	
	}
	else{
		while(!feof(ip))
		{
			//새로운 포인터변수 선언하고 메모리 할당 후 초기화 
			INFO *i_node;
			i_node = (INFO *)malloc(sizeof(INFO));
			memset(i_node, 0, sizeof(INFO));
			
			fscanf(ip, "%s\n%d\n%d\n%d %d %d\n%d\n%s\n", i_node->id, &i_node->key, &i_node->index, &i_node->yyyy, &i_node->dd, &i_node->mm, &i_node->sum, i_node->content);
			
			if(strcmp(i_node->id, "") != 0) //파일 안에 데이터가 존재한다면 
			{
				//노드 연결 
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
	
	//자동출금파일 입력 
	FILE *ap = fopen("AUTODEBIT.txt", "r");
	
	if(ap == NULL) // 파일이 없을 경우 새로 만듦 
	{
		ap = fopen("AUTODEBIT.txt", "w");
		fclose(ap);
	}
	else{
		while(!feof(ap))
		{
			//새로운 포인터변수 선언하고 메모리 할당 후 초기화 
			AUTO *a_node;
			a_node = (AUTO *)malloc(sizeof(AUTO));
			memset(a_node, 0, sizeof(AUTO));
			
			fscanf(ap, "%s\n%d %d %d\n%d %d %d\n%d\n%s\n", a_node->id, &a_node->syyyy, &a_node->smm, &a_node->sdd, &a_node->eyyyy, &a_node->emm, &a_node->edd, &a_node->sum, a_node->content);
			
			if(strcmp(a_node->id, "") != 0) //파일 안에 데이터가 존재한다면 
			{
				//노드 연결 
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
	
	//연결리스트 파일 출력 
	 
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
	printf("\t[ 가 계 부 프 로 그 램 ]\n");
	printf("========================================\n\n");
	printf("\t프 로 그 램 을  종 료 합 니 다.\n"); 
	getch();
	
	exit(1);
}
	
void initialmenu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail)
{
	int select;
	
	system("cls");
	
	printf("========================================\n");
	printf("\t[ 가 계 부 프 로 그 램 ]\n");
	printf("========================================\n\n");
	printf(" \t1. 로 그 인\n\n");
	printf(" \t2. 회 원 가 입\n\n");
	printf(" \t3. 아 이 디  찾 기\n\n");
	printf(" \t4. 비 밀 번 호  찾 기\n\n");
	printf(" \t5. 프 로 그 램  종 료\n\n"); 
	printf("========================================\n");
	printf("\n\t번 호 를 입 력 하 세 요\n");
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
			//비밀번호 찾기
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
	printf("\t    [ 로 그 인 ]\n");
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
				//마지막 접속 날짜 업데이트 할 것 
				flag = 1;
				break;
			}
			else{
				printf("\n\n========================================\n\n");
				printf("\n   비 밀 번 호 를  확 인 해 주 세 요.\n"); 
				getch();
				
				initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			}
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n========================================\n\n");
		printf("\n  존 재 하 지 않 는  아 이 디 입 니 다.\n"); 
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
	printf("\t    [ 회 원 가 입 ]\n");
	printf("========================================\n\n");
	printf(" \tI D : ");
	scanf("%s", id);
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, id) == 0)
		{
			printf("\n\n\t이 미  존 재 하 는  아 이 디 입 니 다.\n");
			printf("\t다 시  입 력 해 주 세 요.\n");
			scanf("%s", id);
			
			tmp = u_head->next; // 이미 존재하지 않는 아이디가 나올 때까지 계속 반복 
		}
	}
	
	//새로운 회원 노드 추가 
	USER *u_node;
	u_node = (USER *)malloc(sizeof(USER));
	memset(u_node, 0, sizeof(USER));
	
	strcpy(u_node->id, id); //아이디 등록 

	printf("\n");
	printf(" \tP A S S W O R D : ");
	scanf("%s", u_node->password);
	printf("\n");
	
	printf(" \t이 름 : ");
	scanf("%s", u_node->name);
	printf("\n"); 
	
	printf("\t전 화 번 호 (숫 자 만  입 력)\n");
	printf("\n\t");
	scanf("%s", u_node->phone);
	printf("\n");
	
	//새로운 회원노드 연결 
	u_tail->pre->next = u_node;
	u_node->pre = u_tail->pre;
	u_tail->pre = u_node;
	u_node->next = u_tail;

	printf("\n========================================\n");
	printf("\n  회 원 가 입 이  완 료 되 었 습 니 다.");
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
	printf("\t    [ I D  찾 기 ]\n");
	printf("========================================\n\n");
	printf(" \t이 름 : ");
	scanf("%s", name); 
	printf("\n\t전 화 번 호 (숫 자 만  입 력)\n");
	printf("\n\t");
	scanf("%s", phone);
	printf("\n");
	printf("========================================\n\n");
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->name, name) == 0 && strcmp(tmp->phone, phone) == 0)
		{
			printf("\t아 이 디 는  %s 입 니 다.\n", tmp->id);
			
			flag = 1;
			break;
		}
	}
	
	if(flag == 0)
	{
		printf("존 재 하 는  아 이 디 가  없 습 니 다.\n");
	}
	
	getch();
	
	initialmenu(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
}
