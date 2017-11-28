#include "header.h"

user *u_head, *u_tail;
clas *c_head, *c_tail;
note *n_head, *n_tail;

int main()
{	
	// 구조체 포인터 변수 메모리 할당하고 노드 연결 
	u_head = (user *)malloc(sizeof(user));
	u_tail = (user *)malloc(sizeof(user));
	
	u_head->next = u_tail;
	u_tail->pre = u_head;
	u_head->pre = NULL;
	u_tail->next = NULL;
	
	c_head = (clas *)malloc(sizeof(clas));
	c_tail = (clas *)malloc(sizeof(clas));
	
	c_head->next = c_tail;
	c_tail->pre = c_head;
	c_head->pre = NULL;
	c_tail->next = NULL;
	
	n_head = (note *)malloc(sizeof(note));
	n_tail = (note *)malloc(sizeof(note));
	
	n_head->next = n_tail;
	n_tail->pre = n_head;
	n_head->pre = NULL;
	n_tail->next = NULL;
	
	load_file();
	initial_menu();
	
	return 0;
}

void load_file()
{
	FILE *up = fopen("user.txt", "r");
	
	if(up == NULL)
	{
		up = fopen("user.txt", "w");
	}
	else {
		while(!feof(up))
		{
			user *u_node;
			u_node = (user *)malloc(sizeof(user));
			memset(u_node, 0, sizeof(u_node));
			
			fscanf(up, "%s %s %s %s", u_node->id, u_node->password, u_node->name, u_node->phone);
			
			if(!strcmp(u_node->id, ""))
			{
				free(u_node);
			}
			else {
				u_tail->pre->next = u_node;
				u_node->pre = u_tail->pre;
				u_tail->pre = u_node;
				u_node->next = u_tail;
			}
		}
	}
	
	fclose(up);
	
	FILE *cp = fopen("class.txt", "r");
	
	if(cp == NULL)
	{
		cp = fopen("class.txt", "w");
	}
	else {
		while(!feof(cp))
		{
			clas *c_node;
			c_node = (clas *)malloc(sizeof(clas));
			memset(c_node, 0, sizeof(clas));
			
			fscanf(cp, "%s\n", c_node->id);
			fgets(c_node->name, sizeof(c_node->name), cp);
			c_node->name[strlen(c_node->name) - 1] = '\0';
			fscanf(cp, "%d %d %d %d %d %d %d\n", &c_node->day[0], &c_node->day[1], &c_node->day[2], &c_node->day[3], &c_node->day[4], &c_node->day[5], &c_node->day[6]);
			fscanf(cp, "%d %d %d %f\n", &c_node->credit, &c_node->year, &c_node->semester, &c_node->grade);
			
			if(!strcmp(c_node->id, "0"))
			{
				free(c_node);
			}
			else {
				c_tail->pre->next = c_node;
				c_node->pre = c_tail->pre;
				c_tail->pre = c_node;
				c_node->next = c_tail;
			}
		}
	}
	
	fclose(cp);
	
	FILE *np = fopen("note.txt", "r");
	
	if(np == NULL)
	{
		np = fopen("note.txt", "w");
	}
	else {
		while(!feof(np))
		{
			note *n_node;
			n_node = (note *)malloc(sizeof(note));
			memset(n_node, NULL, sizeof(note));
			
			fscanf(np, "%s %s %d %d %d\n", n_node->id, n_node->class_name, &n_node->yyyy, &n_node->mm, &n_node->dd);
			scanf("%[^\]s", n_node->writing);
			//fgets(n_node->writing, sizeof(n_node->writing), np);
			//n_node->writing[strlen(n_node->writing) - 1] = '\0';
			
			if(!strcmp(n_node->id, ""))
			{
				free(n_node);
			}
			else {
				n_tail->pre->next = n_node;
				n_node->pre = n_tail->pre;
				n_tail->pre = n_node;
				n_node->next = n_tail;
			}
		}
	}
	
	fclose(np);
}

void save_file()
{
	int i;
	
	user *u_tmp;
	clas *c_tmp;
	note *n_tmp;
	
	FILE *up = fopen("user.txt", "w");
	
	for(u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
	{
		fprintf(up, "%s %s %s %s\n", u_tmp->id, u_tmp->password, u_tmp->name, u_tmp->phone);
	}
	fclose(up);
	
	FILE *cp = fopen("class.txt", "w");
	
	for(c_tmp = c_head->next; c_tmp->next != NULL; c_tmp = c_tmp->next)
	{
		fprintf(cp, "%s\n%s\n", c_tmp->id, c_tmp->name);
		for(i = 0; i < 7; i++)
		{
			fprintf(cp, "%d ", c_tmp->day[i]);
		}
		fprintf(cp, "\n%d %d %d %.2f\n", c_tmp->credit, c_tmp->year, c_tmp->semester, c_tmp->grade);
	}
	fclose(cp);
	
	FILE *np = fopen("note.txt", "w");

	for(n_tmp = n_head->next; n_tmp->next != NULL; n_tmp = n_tmp->next)
	{
		fprintf(np, "%s %s\n%s\n", n_tmp->id, n_tmp->class_name, n_tmp->writing);
	}
	fclose(np);
	
	system("cls");
	printf("\n\n\t\t-------------------------------");	
	printf("\n\n\t\t프 로 그 램 을  종 료 합 니 다.\n");
	printf("\n\t\t-------------------------------\n");
	getch();
	
	exit(0); 
}

void initial_menu()
{
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t       너 의  학 점 은 ?\n");
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t1. 로 그 인");
		printf("\n\n\t\t2. 회 원 가 입");
		printf("\n\n\t\t3. 아 이 디  찾 기");
		printf("\n\n\t\t4. 비 밀 번 호  찾 기");
		printf("\n\n\t\t5. 프 로 그 램  종 료\n"); 
		printf("\n\n\t\t-------------------------------\n\n\t\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case 1:
				login();
				continue;
			case 2:
				join_mem();
				continue;
			case 3:
				find_id();
				continue;
			case 4:
				find_password();
				continue;
			case 5:
				save_file();
			default:
				printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
				getch(); 
				continue;
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
			password[i] = '\0';
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
		else {
			printf("*");
			i++;
		}
	}
}

int check_phone(char phone[])
{
	int i;
	
	for(i = 0; i < strlen(phone); i++)
	{
		if(phone[i] < '0' || phone[i] > '9')
		{
			return 1;
		}
	}
	
	return 0;
}

void join_mem()
{
	int flag = 0, i;
	
	user *u_node, *tmp;
	u_node = (user *)malloc(sizeof(user));
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t        회 원 가 입\n");
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t아 이 디 : ");
		scanf("%s", u_node->id);
		
		for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(!strcmp(tmp->id, u_node->id))
			{
				flag = 1;
			}
		}
		
		if(flag == 1)
		{
			printf("\n\n\t\t이 미  존 재 하 는  아 이 디 입 니 다.\n");
			getch();
			
			continue;
		}
		else {
			break;
		}
	}
	
	printf("\n\n\t\t비 밀 번 호 : ");
	asterisk(u_node->password);
	printf("\n\n\n\t\t이 름 : ");
	scanf("%s", u_node->name);
	printf("\n\n\t\t전 화 번 호 ( 번 호 만 )\n\n\t\t");
	scanf("%s", u_node->phone);
	
	while(1)
	{
		if(check_phone(u_node->phone) == 1)
		{
			printf("\n\n\t\t올 바 르 게  입 력 해 주 세 요");
			getch();
			
			system("cls");
			printf("\n\t\t-------------------------------\n");
			printf("\n\t\t        회 원 가 입\n");
			printf("\n\t\t-------------------------------\n");
			printf("\n\n\t\t아 이 디 : %s", u_node->id);
			printf("\n\n\n\t\t비 밀 번 호 : ");
			for(i = 0; i < strlen(u_node->password); i++)
			{
				printf("*");
			}
			printf("\n\n\n\t\t이 름 : %s", u_node->name);
			printf("\n\n\n\t\t전 화 번 호 ( 번 호 만 )\n\n\t\t");
			scanf("%s", u_node->phone);
		}
		else {
			break;
		}
	}
	
	u_tail->pre->next = u_node;
	u_node->pre = u_tail->pre;
	u_tail->pre = u_node;
	u_node->next = u_tail;
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t회 원 가 입 이  완 료 되 었 습 니 다");
	getch(); 
}

void login()
{
	int flag = 0;
	char id[15],
		 password[30];
		 
	user *tmp;
	
	system("cls");
	printf("\n\t\t-------------------------------\n");
	printf("\n\t\t         로 그 인\n");
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t아 이 디 : ");
	fflush(stdin);
	gets(id);
	printf("\n\n\t\t비 밀 번 호 : ");
	fflush(stdin);
	asterisk(password);
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->id, id))
		{
			flag = 1;
			if(!strcmp(tmp->password, password))
			{
				main_menu(tmp);
			}
			else {
				printf("\n\n\t\t-------------------------------\n");
				printf("\n\n\t\t비 밀 번 호 를  확 인 해 주 세 요");
				getch();
			}
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n\t\t-------------------------------\n");
		printf("\n\n\t\t존 재 하 지 않 는  아 이 디 입 니 다");
		getch();
	}
}

void find_id()
{
	char name[15],
		 phone[13];
		 
	int flag = 0;

	user *tmp;
	
	system("cls");
	printf("\n\t\t-------------------------------\n");
	printf("\n\t\t      아 이 디  찾 기\n");
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t이 름 : ");
	fflush(stdin);
	gets(name);
	printf("\n\n\t\t전 화 번 호 ( 번 호 만)\n\n\t\t");
	fflush(stdin);
	gets(phone);
	
	while(1)
	{
		if(check_phone(phone) == 1)
		{
			printf("\n\n\t\t올 바 르 게  입 력 해 주 세 요");
			getch();
			
			system("cls");
			printf("\n\t\t-------------------------------\n");
			printf("\n\t\t      아 이 디  찾 기\n");
			printf("\n\t\t-------------------------------\n");
			printf("\n\n\t\t이 름 : %s", name);
			printf("\n\n\n\t\t전 화 번 호 ( 번 호 만)\n\n\t\t");
			fflush(stdin);
			gets(phone);
		}
		else {
			break;
		}
	}
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->name, name) && !strcmp(tmp->phone, phone))
		{
			flag = 1;
			
			printf("\n\n\t\t-------------------------------\n");
			printf("\n\n\t\t아 이 디 는  %s 입 니 다.", tmp->id);
			getch();
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n\t\t-------------------------------\n");
		printf("\n\n\t\t존 재 하 지 않 는  정 보 입 니 다");
		getch();
	}
}

void find_password()
{
	char name[15],
		 phone[13],
		 id[15];
		 
	int flag = 0;

	user *tmp;
	system("cls");
	printf("\n\t\t-------------------------------\n");
	printf("\n\t\t     비 밀 번 호  찾 기\n");
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t아 이 디 : ");
	fflush(stdin);
	gets(id);
	printf("\n\n\t\t이 름 : ");
	fflush(stdin);
	gets(name);
	printf("\n\n\t\t전 화 번 호 ( 번 호 만)\n\n\t\t");
	fflush(stdin);
	gets(phone);
	
	while(1)
	{
		if(check_phone(phone) == 1)
		{
			printf("\n\n\t\t올 바 르 게  입 력 해 주 세 요");
			getch();
			
			system("cls");
			printf("\n\t\t-------------------------------\n");
			printf("\n\t\t     비 밀 번 호  찾 기\n");
			printf("\n\t\t-------------------------------\n");
			printf("\n\n\t\t아 이 디 : %s\n", id); 
			printf("\n\n\t\t이 름 : %s", name);
			printf("\n\n\n\t\t전 화 번 호 ( 번 호 만)\n\n\t\t");
			fflush(stdin);
			gets(phone);
		}
		else {
			break;
		}
	}
	
	for(tmp = u_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(!strcmp(tmp->id, id) && !strcmp(tmp->name, name) && !strcmp(tmp->phone, phone))
		{
			flag = 1;
			
			printf("\n\n\t\t-------------------------------\n");
			printf("\n\n\t\t새 로 운  비 밀 번 호 를  입 력 하 세 요\n\n\t\t");
			asterisk(tmp->password);
			
			printf("\n\n\t\t변 경 되 었 습 니 다");
			getch();
		}
	}
	
	if(flag == 0)
	{
		printf("\n\n\t\t-------------------------------\n");
		printf("\n\n\t\t존 재 하 지 않 는  정 보 입 니 다");
		getch();
	}
}
