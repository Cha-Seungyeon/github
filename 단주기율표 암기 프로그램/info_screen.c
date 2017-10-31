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
				del_mem(login_user);
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
	char new_name[10];
	
	while(1)
	{
		system("cls");
		printf("\n\t       �� �� �� ��\n\n");
		printf("==========================================\n\n");
		printf("\t�� ��  �� �� : %s\n\n", member_data[login_user].name);
		printf(" �� �� ��  �� �� ��  �� �� �� �� �� ��\n\n\t\t\t( �� �� : - 1)\n\n\t>> ");
		scanf("%s", new_name);
		
		if(!strcmp(member_data[login_user].name, new_name))
		{
			printf("\n\n\t�� �� ��  �� �� �� �� ��.\n\n\t�� ��  �� �� �� �� �� ��.");
			getch();
			
			continue; 
		}
		
		strcpy(member_data[login_user].name, new_name);
		printf("\n==========================================\n\n");
		printf("  %s (��) ��  �� �� ��  �� �� �� �� �� �� �� !", member_data[login_user].name); 
		getch();
		break;
	}
}

void change_password(int login_user)
{
	char new_password[40];
	
	while(1)
	{
		system("cls");
		printf("\n\t    �� �� �� ȣ  �� ��\n\n");
		printf("==========================================\n\n");
		printf(" �� �� ��  �� �� �� ȣ ��  �� �� �� �� �� ��\n\n\t\t\t( �� �� : - 1)\n\n\t>> ");
		asterisk(new_password);
		
		if(!strcmp(member_data[login_user].password, new_password))
		{
			printf("\n\n\t�� �� ��  �� �� �� ȣ �� �� ��.\n\n\t�� ��  �� �� �� �� �� ��.");
			getch();
			
			continue; 
		}
		
		strcpy(member_data[login_user].password, new_password);
		printf("\n==========================================\n\n");
		printf("  �� �� �� �� ��  �� �� �� �� �� �� �� !");
		getch();
		break;
	}
}

void change_phone(int login_user)
{
	char new_phone[13];
	
	while(1)
	{
		system("cls");
		printf("\n\t    �� ȭ �� ȣ  �� ��\n\n");
		printf("==========================================\n\n");
		printf(" �� ��  �� ȭ �� ȣ : %s\n\n", member_data[login_user].phone); 
		printf(" �� �� ��  �� ȭ �� ȣ ��  �� �� �� �� �� ��\n\n\t( �� �� ��  �� �� �� �� �� �� )\n\n\t\t( �� �� : - 1)\n\n\t>> ");
		scanf("%s", new_phone);
		
		while(check_phone(member_data[login_user].phone) == 1) // ��ȭ��ȣ ����ó�� 
		{
			printf("\n\t�� �� ��  �� �� �� �� �� ��"); 
			getch();
			system("cls");
			printf("\n\t    �� ȭ �� ȣ  �� ��\n\n");
			printf("==========================================\n\n");
			printf(" �� �� ��  �� ȭ �� ȣ ��  �� �� �� �� �� ��\n\n\t( �� �� ��  �� �� �� �� �� �� )\n\n\t>> ");
			scanf("%s", new_phone);
		}
		
		if(!strcmp(member_data[login_user].phone, new_phone))
		{
			printf("\n\n\t�� �� ��  �� ȭ �� ȣ �� �� ��.\n\n\t�� ��  �� �� �� �� �� ��.");
			getch();
			
			continue; 
		}
		
		printf("\n==========================================\n\n");
		printf("  �� �� �� �� ��  �� �� �� �� �� �� �� !");
		getch();
		break;
	}
}

void del_mem(int login_user)
{
	char respones[5];
	int i, j, t, flag = 1;
	
	system("cls");
	printf("\n\t       ȸ �� Ż ��\n\n");
	printf("==========================================\n\n");
	printf("\t�� �� �� �� ��  �� �� ��\n\n   �� ��  �� �� �� ��  �� �� �� �� ��.\n\n   �� �� ��  �� �� �� �� �� �� �� �� ?\n\n\t\t ( Y e s  /  N o )\n\n\t>> ");
	scanf("%s", respones);
	
	if(!strcmp(respones, "YES") || !strcmp(respones, "Yes") || !strcmp(respones, "Y") || !strcmp(respones, "y"))
	{
		while(flag == 1)
		{
			flag = 0; // �ش� ���̵��� �����Ͱ� �����ϴ����� ���� ���� �ʱ�ȭ 

			for(i = 1; i <= result_count; i++)
			{
				if(!strcmp(result_data[i].id, member_data[login_user].id)) // �α����� ���̵��� ����� �ִ��� Ȯ�� 
				{
					for(j = i + 1; j <= result_count; j++) // ���� �ε��� + 1 ���� ������������ ������ �� ĭ ������ �̷�� 
					{
						strcpy(result_data[j - 1].id, result_data[j].id);
						result_data[j - 1].type = result_data[j].type;
						result_data[j - 1].yyyy = result_data[j].yyyy;
						result_data[j - 1].mm = result_data[j].mm;
						result_data[j - 1].dd = result_data[j].dd;
						result_data[j - 1].correct = result_data[j].correct;
					}
					
					result_count--; // ��� ������ ī��Ʈ ���� 1 ���� 
					flag = 1; // �ش� ���̵��� �����Ͱ� �������� ǥ�� 
					break; // �迭�� ���̵� �ִ��� ó������ �˻� (�����͸� �ϳ� ������ �̷�� ����) 
				}
			}
		}

		for(i = login_user; i <= mem_count; i++) // ��� �����Ϳ��� �ش� ���̵� ������ ���� 
		{
			strcpy(member_data[i].id, member_data[i + 1].id);
			strcpy(member_data[i].password, member_data[i + 1].password);
			strcpy(member_data[i].name, member_data[i + 1].name);
			strcpy(member_data[i].phone, member_data[i + 1].phone);
		}
		mem_count--; // ��� ī��Ʈ ���� 1 ���� 
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
}
