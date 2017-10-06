#include "define.h"

void manage_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Info {edit_UserName = 1, edit_UserPassword, edit_UserPhoneNumber, Del_User, back, exit};
	int select;

	while(1)
	{	
		system("cls");
		
		printf("========================================\n");
		printf("\t   [ �� ��  �� �� ]\n");
		printf("========================================\n\n");
		printf(" \t1. �� �� �� ��\n\n");
		printf(" \t2. �� �� �� ȣ  �� ��\n\n");
		printf(" \t3. �� ȭ �� ȣ  �� ��\n\n");
		printf(" \t4. ȸ �� Ż ��\n\n");
		printf(" \t5. �� �� ȭ �� �� ��\n\n"); 
		printf(" \t6. �� �� �� ��  �� ��\n\n");
		printf("========================================\n");
		printf("\n\t�� ȣ �� �� �� �� �� ��\n");
		printf("\n\t>> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{ 
			case edit_UserName:
				edit_Name(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case edit_UserPassword:
				edit_Password(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case edit_UserPhoneNumber:
				edit_Phone(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
				break;
				
			case Del_User:
				del_User(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
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

void edit_Name(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ �� ��  �� �� ]\n");
	printf("========================================\n\n");
	printf(" \t�� �� : ");
	scanf("%s", login_User->name);
	if(strcmp(login_User->name, "-1") == 0)
	{
		return;
	}
	printf("\n========================================\n");
	printf("\n  �� ��  �� �� ��  �� �� �� �� �� �� ��.");
	getch();
	
	manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void edit_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ �� �� �� ȣ  �� �� ]\n");
	printf("========================================\n\n");
	printf(" \tP A S S W O R D : ");
	asterisk(login_User->password);
	if(strcmp(login_User->password, "-1") == 0)
	{
		return;
	}
	printf("\n\n========================================\n");
	printf("\n  �� �� �� ȣ  �� �� ��  �� �� �� �� �� �� ��.");
	getch();
	
	manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void edit_Phone(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ �� ȭ �� ȣ  �� �� ]\n");
	printf("========================================\n\n");
	printf(" \t�� ȭ �� ȣ (�� �� ��  �� ��)\n");
	printf("\n\t");
	scanf("%s", login_User->phone);
	
	//���� ���� �ٸ� ���� �Է��ߴ��� �˻��ؼ� �ùٸ� ���� ���� ������ �ݺ��ؼ� �Է� ���� 
	while(check_Num(login_User->phone) == 1)
	{
		printf("\n\t�� �� ��  �� �� �� �� �� ��!\n");
		printf("\n\t");
		scanf("%s", login_User->phone);
	}
	
	printf("\n");
	printf("\n========================================\n");
	printf("\n  �� ȭ �� ȣ  �� �� ��  �� �� �� �� �� �� ��.");
	getch();
	
	manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void del_User(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	char select;
	USER *u_tmp;
	GROUP *g_tmp;
	INFO *i_tmp;
	AUTO *a_tmp;
	
	while(1)
	{
		system("cls");
		
		printf("========================================\n");
		printf("\t    [ ȸ �� Ż �� ]\n");
		printf("========================================\n\n");
		printf(" �� ��  �� �� �� �� �� �� �� ��.\n");
		printf(" �� ��  ȸ �� Ż �� �� �� �� �� �� ��? [ y / n]\n");
		printf("\n>> ");
		fflush(stdin);
		scanf("%c", &select);
		
		if(select == 'y' || select == 'Y')
		{
			for(u_tmp = u_head->next; u_tmp->next != NULL; u_tmp = u_tmp->next)
			{
				if(strcmp(u_tmp->id, login_User->id) == 0)
				{
					u_tmp->pre->next = u_tmp->next;
					u_tmp->next->pre = u_tmp->pre;
					free(u_tmp);
				}
			}
			
			for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
			{
				if(strcmp(g_tmp->id, login_User->id) == 0)
				{
					g_tmp->pre->next = g_tmp->next;
					g_tmp->next->pre = g_tmp->pre;
					free(g_tmp);
				}
			}
			
			for(i_tmp = i_head->next; i_tmp->next != NULL; i_tmp = i_tmp->next)
			{
				if(strcmp(i_tmp->id, login_User->id) == 0)
				{
					i_tmp->pre->next = i_tmp->next;
					i_tmp->next->pre = i_tmp->pre;
					free(i_tmp);
				}
			}
			
			for(a_tmp = a_head->next; a_tmp->next != NULL; a_tmp = a_tmp->next)
			{
				if(strcmp(a_tmp->id, login_User->id) == 0)
				{
					a_tmp->pre->next = a_tmp->next;
					a_tmp->next->pre = a_tmp->pre;
					free(a_tmp);
				}
			}
			
			printf("\nȸ �� Ż �� ��  �� �� �� �� �� �� ��.\n");
			getch();
			
			save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			break;
		}
		else if(select == 'n' || select == 'N')
		{
			printf("\n�� �� �� �� �� �� ��.\n");
			getch();
			
			manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
			break;
		}
		else
		{
			printf("\n�� �� ��  �� �� �� �� ��\n");
			getch(); 
		}
	}
}
