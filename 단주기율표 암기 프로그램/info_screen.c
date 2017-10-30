#include "define.h"

extern learn learning_data[20];
extern mem member_data[101];
extern result result_data[1001];
extern int mem_count;
extern int result_count;

void print_info(int login_user)
{
	enum info_screen_menu {EDIT_USER_NAME = 1, EDIT_USER_PASSWORD, EDIT_USER_PHONE, DEL_MEMBER, PREVIOUS_SCREEN, EXIT_PROGRAM};
	
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("\n\t�� ��  �� ��  �� ��\n\n");
		printf("==========================================\n\n");
		printf("\t1. ��  �� ��  �� ��\n\n");
		printf("\t2. �� �� �� ȣ  �� ��\n\n");
		printf("\t3. �� ȭ �� ȣ  �� ��\n\n");
		printf("\t4. ȸ �� Ż ��\n\n"); 
		printf("\t5. �� ��  ȭ �� �� ��\n\n");
		printf("\t6. �� �� �� ��  �� ��\n\n");
		printf("==========================================\n\n >> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{
			case EDIT_USER_NAME:
				change_name(login_user);
				continue;
			case EDIT_USER_PASSWORD:
				change_password(login_user);
				continue;
			case EDIT_USER_PHONE:
				change_phone(login_user);
				continue;
			case DEL_MEMBER:
				//del_mem(login_user);
				continue;
			case PREVIOUS_SCREEN:
				return;
			case EXIT_PROGRAM:
				save_file();
			default:
				printf("\n�� �� �� ��  �� �� �� �� �� ��\n");
				getch();
				continue;
		}
	}
}

void change_name(int login_user)
{
	system("cls");
	printf("\n\t       �� �� �� ��\n\n");
	printf("==========================================\n\n");
	printf("  �� �� ��  �� �� ��  �� �� �� �� �� ��\n\n\t>> ");
	scanf("%s", member_data[login_user].name);
	printf("\n==========================================\n\n");
	printf("  %s (��) ��  �� �� ��  �� �� �� �� �� �� �� !", member_data[login_user].name); 
	getch();
}

void change_password(int login_user)
{
	system("cls");
	printf("\n\t    �� �� �� ȣ  �� ��\n\n");
	printf("==========================================\n\n");
	printf(" �� �� ��  �� �� �� ȣ ��  �� �� �� �� �� ��\n\n\t>> ");
	asterisk(member_data[login_user].password);
	printf("\n==========================================\n\n");
	printf("  �� �� �� �� ��  �� �� �� �� �� �� �� !");
	getch();
}

void change_phone(int login_user)
{
	system("cls");
	printf("\n\t    �� ȭ �� ȣ  �� ��\n\n");
	printf("==========================================\n\n");
	printf(" �� �� ��  �� ȭ �� ȣ ��  �� �� �� �� �� ��\n\n\t( �� �� ��  �� �� �� �� �� �� )\n\n\t>> ");
	scanf("%s", member_data[login_user].phone);
	
	while(check_phone(member_data[login_user].phone) == 1) // ��ȭ��ȣ ����ó�� 
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��"); 
		getch();
		system("cls");
		printf("\n\t    �� ȭ �� ȣ  �� ��\n\n");
		printf("==========================================\n\n");
		printf(" �� �� ��  �� ȭ �� ȣ ��  �� �� �� �� �� ��\n\n\t( �� �� ��  �� �� �� �� �� �� )\n\n\t>> ");
		scanf("%s", member_data[login_user].phone);
	}
	
	printf("\n==========================================\n\n");
	printf("  �� �� �� �� ��  �� �� �� �� �� �� �� !");
	getch();
}
/*
void del_mem(int login_user)
{
	char respones[5];
	int i;
	
	system("cls");
	printf("\n\t       ȸ �� Ż ��\n\n");
	printf("==========================================\n\n");
	printf("\t�� �� �� �� ��  �� �� ��\n\n   �� ��  �� �� �� ��  �� �� �� �� ��.\n\n   �� �� ��  �� �� �� �� �� �� �� �� ?\n\n\t\t ( Y e s  /  N o )\n\n\t>> ");
	scanf("%s", respones);
	
	if(!strcmp(respones, "YES") || !strcmp(respones, "Yes") || !strcmp(respones, "Y") || !strcmp(respones, "y"))
	{
		for(i = 1; i <= result_count; i++) // �׽�Ʈ ��� �����Ϳ��� �ش� ���̵� ������ ���� 
		{
			if(!strcmp(result_data[i].id, member_data[login_user].id))
			{
				result_data[i].type = result_data[i + 1].type;
				strcpy(result_data[i].id, result_data[i + 1].id);
				result_data[i].yyyy = result_data[i + 1].yyyy;
				result_data[i].mm = result_data[i + 1].mm;
				result_data[i].dd = result_data[i + 1].dd;
				result_data[i].correct = result_data[i + 1].correct;
				
				result_count--; // ��� ī��Ʈ ���� 1 ���� 
			}
		}

		for(i = login_user; i <= mem_count; i++) // ��� �����Ϳ��� �ش� ���̵� ������ ���� 
		{
			strcpy(member_data[i].id, member_data[i + 1].id);
			strcpy(member_data[i].password, member_data[i + 1].password);
			strcpy(member_data[i].name, member_data[i + 1].name);
			strcpy(member_data[i].phone, member_data[i + 1].phone);
			
			mem_count--; // ��� ī��Ʈ ���� 1 ���� 
		}
		printf("\n==========================================\n\n");
		printf("  ȸ �� Ż �� ��  �� �� �� �� �� �� ��\n");
		getch();
		save_file();
	}
	else {
		printf("\n==========================================\n\n");
		printf("  ȸ �� Ż �� ��  �� �� �� �� �� �� �� !\n");
		getch();
	}
}*/
