#include "define.h"

learn learning_data[20];
mem member_data[101];
result result_data[1001];
int mem_count = 0;
int result_count = 0;

int main()
{
	load_file();
	print_initial_screen();
	
	return 0;
}

void load_file() //���� �ҷ����� �Լ� 
{	
	int i;
	
	FILE *fp = fopen("learn_data.txt", "r");
	
	if(fp == NULL) //������ �������� ���� ��� ���� ����
	{
		fp = fopen("learn_data.txt", "w");
	}
	else {
		for(i = 0; i < 20; i++)
		{
			fscanf(fp, "%d %s %s", &learning_data[i].index, learning_data[i].symbol, learning_data[i].name);
		}
	}
	
	fclose(fp);
	
	FILE *mp = fopen("member_data.txt", "r");
	
	if(mp == NULL) //������ �������� ���� ��� ���� ����
	{
		mp = fopen("member_data.txt", "w");
	}
	else {
		while(!feof(mp))
		{
			mem_count++;
			fscanf(mp, "%s %s %s %s", member_data[mem_count].id, member_data[mem_count].password, member_data[mem_count].name, member_data[mem_count].phone);
			
			if(!strcmp(member_data[mem_count].id, "")) //���̵� ���� �������� ���� ��� ȸ�� ī��Ʈ �� ���� 
			{
				mem_count--;
			}
		}
	}
	
	fclose(mp);
	
	FILE *rp = fopen("result_data.txt", "r");
	
	if(rp == NULL) //������ �������� ���� ��� ���� ����
	{
		rp = fopen("result_data.txt", "w");
	}
	else {
		while(!feof(rp))
		{
			result_count++;
			fscanf(rp, "%s %d %d %d %d %d", result_data[result_count].id, &result_data[result_count].type, &result_data[result_count].yyyy, &result_data[result_count].mm, &result_data[result_count].dd, &result_data[result_count].correct);
			
			if(!strcmp(result_data[result_count].id, "")) //���̵� ���� �������� ���� ��� ��� ī��Ʈ �� ���� 
			{
				result_count--;
			}
		}
	}
	
	fclose(rp);
}

void save_file() //����ü �迭 �� ���Ͽ� �����ϰ� ���α׷� ���� 
{
	int i;
	
	FILE *fp = fopen("learn_data.txt", "w");
	
	for(i = 0; i < 20; i++)
	{
		fprintf(fp, "%d %s %s\n", learning_data[i].index, learning_data[i].symbol, learning_data[i].name);
	}
	
	fclose(fp);
	
	FILE *mp = fopen("member_data.txt", "w");
	
	for(i = 1; i <= mem_count; i++)
	{
		fprintf(mp, "%s %s %s %s\n", member_data[i].id, member_data[i].password, member_data[i].name, member_data[i].phone);
	}
	
	fclose(mp);
	
	FILE *rp = fopen("result_data.txt", "w");
	
	for(i = 1; i <= result_count; i++)
	{
		fprintf(rp, "%s %d %d %d %d %d\n", result_data[i].id, result_data[i].type, result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
	}
	
	fclose(rp);
	
	system("cls");
	printf("\n\t==========================================\n\n");
	printf("\t      �� �� �� �� ��  �� �� �� �� ��.\n");
	printf("\n\t==========================================\n\n");
	getch();
	
	exit(0); // ���α׷� ���� ���� 
}

void print_initial_screen()
{
	enum initial_screen_menu {MEMBER_LOGIN = 1, JOIN_MEMBER, SEARCH_MEM_ID, SEARCH_MEM_PASSWORD, EXIT_PROGRAM};
	
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("\n �� �� �� �� ǥ  �� �� �� ��  �� �� �� ��\n\n");
		printf("==========================================\n\n");
		printf("\t1. �� �� ��\n\n");
		printf("\t2. ȸ �� �� ��\n\n");
		printf("\t3. �� �� ��  ã ��\n\n");
		printf("\t4. �� �� �� ȣ  ã ��\n\n");
		printf("\t5. �� �� �� ��  �� ��\n\n");
		printf("==========================================\n\n >> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{
			case MEMBER_LOGIN:
				login();
				continue;
			case JOIN_MEMBER:
				join_mem();
				continue;
			case SEARCH_MEM_ID:
				search_id();
				continue;
			case SEARCH_MEM_PASSWORD:
				search_password();
				continue;
			case EXIT_PROGRAM:
				save_file();
			default:
				printf("\n�� �� �� ��  �� �� �� �� �� ��\n");
				getch();
				continue;
		}
	}
}

void asterisk(char password[]) //��й�ȣ ��ǥ ȭ �Լ� 
{
	int i = 0;
	
	while(1)
	{
		password[i] = getch();
		
		if(password[i] == 13) // ���� �Է� ���� ��� 
		{
			password[i] = '\0'; // ���๮�� ���ְ� ���� 
			break; // �Լ� ���� 
		}
		
		if(password[i] == 8) // �齺���̽� �Է� ���� ��� 
		{	
			if(i > 0)
			{
				printf("\b"); // Ŀ�� �� ĭ �ڷ� �ű�� 
				printf(" "); // ���� ��� 
				printf("\b"); // Ŀ�� �ٽ� �� ĭ �ڷ� �ű�� 
				i--; // ��й�ȣ �����ϴ� �ε��� �� �ϳ� ���� 
			}
		}
		else {
			printf("*"); //��ǥ ��� 
			i++; // ��й�ȣ ���� �ε��� �� �ϳ� ���� 
		}
	}
}

int check_phone(char phone[]) //��ȭ��ȣ ����ó�� �Լ� (���ڸ� �����ϴ��� �˻�) 
{
	int i, flag = 0;
	
	for(i = 0; i < strlen(phone); i++)
	{
		if(phone[i] < '0' || phone[i] > '9') //���ڰ� �ƴ� ���ڰ� ���� ��� 
		{
			flag = 1;
			return 1;
		}
	}
	
	if(flag == 0)
	{
		return 0;
	}
}

void join_mem()
{
	int i, flag = 0;
	char id[15], phone[13];
	
	while(1)
	{
		flag = 0; // ���̵� �˻� �ʱ�ȭ 
		system("cls");
		
		printf("\n\t       ȸ �� �� ��\n\n");
		printf("==========================================\n\n");
		printf("\t�� �� �� : ");
		scanf("%s", id);
		
		for(i = 1; i <= mem_count; i++) // �����ϴ� ���̵����� �˻� 
		{
			if(!strcmp(member_data[i].id, id))
			{
				flag = 1;
				printf("\n\t�� �� �� ��  �� �� �� �� �� ��");
				getch();
			}
		}

		if(flag == 1) // �����ϴ� ���̵��� ��� �ٽ� �Է� �ޱ� 
		{
			continue;
		}
		
		mem_count++; // ���ο� ȸ�� �߰�, ȸ�� �� �ϳ� ���� 
		strcpy(member_data[mem_count].id, id);
		
		printf("\n\t�� �� �� ȣ : ");
		asterisk(member_data[mem_count].password);
		
		printf("\n\n\t�� �� : ");
		scanf("%s", member_data[mem_count].name);
		
		printf("\n\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
		scanf("%s", phone);
		
		while(check_phone(phone) == 1) // ��ȭ��ȣ ����ó�� 
		{
			printf("\n\t�� �� ��  �� �� �� �� �� ��"); 
			getch();
			//�ٽ� �Է� �ޱ� 
			system("cls");
			printf("\n\t       ȸ �� �� ��\n\n");
			printf("==========================================\n\n");
			printf("\t�� �� �� : %s\n\n", member_data[mem_count].id);
			printf("\t�� �� �� ȣ : "); 
			for(i = 0; i < strlen(member_data[mem_count].password); i++) // ����� ��й�ȣ ���̸�ŭ ��ǥ ��� 
			{
				printf("*");
			}
			printf("\n\n\t�� �� : %s\n\n", member_data[mem_count].name);
			printf("\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
			scanf("%s", phone);
			
			continue;	
		}
		
		strcpy(member_data[mem_count].phone, phone);

		printf("\n==========================================\n\n");
		printf("   ȸ �� �� �� ��  �� �� �� �� �� �� ��\n");
		getch();
		
		break;
	}
}

void login()
{
	char id[15];
	char password[40];
	int i, flag = 0;
	
	system("cls");
		
	printf("\n\t        �� �� ��\n\n");
	printf("==========================================\n\n");
	printf("\t�� �� �� : ");
	scanf("%s", id);
	printf("\n\t�� �� �� ȣ : ");
	asterisk(password);
	 
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].id, id))
		{
			flag = 1; // �����ϴ� ���̵��� ���� ǥ���� 
			if(!strcmp(member_data[i].password, password))
			{
				print_main_screen(i);
			}
			else {
				printf("\n\n==========================================\n\n");
				printf(" �� �� �� ȣ ��  �� ��  Ȯ �� �� �� �� ��\n");
				getch();
				
				return;
			}
		}
	}

	if(flag == 0) // �������� �ʴ� ���̵� �Է����� ��� 
	{
		printf("\n\n==========================================\n\n");
		printf("   �� �� �� �� �� ��  �� �� �� �� �� ��\n");
		getch();
	}
}

void search_id()
{
	char name[10];
	char phone[13];
	int i, flag = 0;
	
	system("cls");
		
	printf("\n\t      �� �� ��  ã ��\n\n");
	printf("==========================================\n\n");
	printf("\t�� �� : ");
	scanf("%s", name);
	printf("\n\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
	scanf("%s", phone);
	
	while(check_phone(phone) == 1) // ��ȭ��ȣ ����ó�� 
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��"); 
		getch();
		//�ٽ� �Է� �ޱ� 
		system("cls");
		printf("\n\t      �� �� ��  ã ��\n\n");
		printf("==========================================\n\n");
		printf("\t�� �� : %s\n", name);
		printf("\n\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
		scanf("%s", phone);
	}
	
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].name, name) && !strcmp(member_data[i].phone, phone))
		{
			flag = 1; // �����ϴ� ���������� ǥ�� 
			printf("\n==========================================\n\n");
			printf("\t�� �� �� ��  %s �� �� ��\n", member_data[i].id);
			getch();
			return;
		}
	}
	
	if(flag == 0) // �ش� �����Ͱ� �������� ���� ��� 
	{
		printf("\n==========================================\n\n");
		printf("   �� �� �� �� �� ��  �� �� �� �� �� ��\n");
		getch();
	}
}

void search_password()
{
	char id[15];
	char name[10];
	char phone[13];
	int i, flag = 0;
	
	system("cls");
	
	printf("\n\t     �� �� �� ȣ  ã ��\n\n");
	printf("==========================================\n\n");
	printf("\t�� �� �� : ");
	scanf("%s", id); 
	printf("\n\t�� �� : ");
	scanf("%s", name);
	printf("\n\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
	scanf("%s", phone);
	
	while(check_phone(phone) == 1) // ��ȭ��ȣ ����ó�� 
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��"); 
		getch();
		//�ٽ� �Է� �ޱ� 
		system("cls");
		printf("\n\t     �� �� �� ȣ  ã ��\n\n");
		printf("==========================================\n\n");
		printf("\t�� �� �� : %s\n", id);
		printf("\n\t�� �� : %s\n", name); 
		printf("\n\t�� ȭ �� ȣ ( �� �� ��  �� �� )\n\n\t");
		scanf("%s", phone);
	}
	
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].id, id) && !strcmp(member_data[i].name, name) && !strcmp(member_data[i].phone, phone))
		{
			flag = 1; // �����ϴ� ���������� ǥ�� 
			printf("\n==========================================\n\n");
			printf(" �� �� ��  �� �� �� ȣ ��  �� �� �� �� ��\n\n ");
			printf(">> ");
			asterisk(member_data[i].password);
			printf("\n\n �� �� �� �� ��  �� �� �� �� �� �� �� !");
			getch();
		}
	}
	
	if(flag == 0)
	{
		printf("\n==========================================\n\n");
		printf("   �� �� �� �� �� ��  �� �� �� �� �� ��\n");
		getch();
	}
}
