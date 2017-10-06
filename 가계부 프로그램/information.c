#include "define.h"

void manage_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	enum manage_Info {edit_UserName = 1, edit_UserPassword, edit_UserPhoneNumber, Del_User, back, exit};
	int select;

	while(1)
	{	
		system("cls");
		
		printf("========================================\n");
		printf("\t   [ 정 보  관 리 ]\n");
		printf("========================================\n\n");
		printf(" \t1. 이 름 변 경\n\n");
		printf(" \t2. 비 밀 번 호  변 경\n\n");
		printf(" \t3. 전 화 번 호  변 경\n\n");
		printf(" \t4. 회 원 탈 퇴\n\n");
		printf(" \t5. 이 전 화 면 으 로\n\n"); 
		printf(" \t6. 프 로 그 램  종 료\n\n");
		printf("========================================\n");
		printf("\n\t번 호 를 입 력 하 세 요\n");
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
				printf("\n\t바 르 게  입 력 하 세 요\n");
				getch();
		}
	}
}

void edit_Name(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ 이 름  변 경 ]\n");
	printf("========================================\n\n");
	printf(" \t이 름 : ");
	scanf("%s", login_User->name);
	if(strcmp(login_User->name, "-1") == 0)
	{
		return;
	}
	printf("\n========================================\n");
	printf("\n  이 름  변 경 이  완 료 되 었 습 니 다.");
	getch();
	
	manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void edit_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ 비 밀 번 호  변 경 ]\n");
	printf("========================================\n\n");
	printf(" \tP A S S W O R D : ");
	asterisk(login_User->password);
	if(strcmp(login_User->password, "-1") == 0)
	{
		return;
	}
	printf("\n\n========================================\n");
	printf("\n  비 밀 번 호  변 경 이  완 료 되 었 습 니 다.");
	getch();
	
	manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void edit_Phone(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ 전 화 번 호  변 경 ]\n");
	printf("========================================\n\n");
	printf(" \t전 화 번 호 (숫 자 만  입 력)\n");
	printf("\n\t");
	scanf("%s", login_User->phone);
	
	//숫자 말고 다른 문자 입력했는지 검사해서 올바른 값이 나올 때까지 반복해서 입력 받음 
	while(check_Num(login_User->phone) == 1)
	{
		printf("\n\t숫 자 만  입 력 해 주 세 요!\n");
		printf("\n\t");
		scanf("%s", login_User->phone);
	}
	
	printf("\n");
	printf("\n========================================\n");
	printf("\n  전 화 번 호  변 경 이  완 료 되 었 습 니 다.");
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
		printf("\t    [ 회 원 탈 퇴 ]\n");
		printf("========================================\n\n");
		printf(" 모 든  정 보 가 삭 제 됩 니 다.\n");
		printf(" 정 말  회 원 탈 퇴 하 시 겠 습 니 까? [ y / n]\n");
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
			
			printf("\n회 원 탈 퇴 가  완 료 되 었 습 니 다.\n");
			getch();
			
			save(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail);
			break;
		}
		else if(select == 'n' || select == 'N')
		{
			printf("\n취 소 되 었 습 니 다.\n");
			getch();
			
			manage_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
			break;
		}
		else
		{
			printf("\n바 르 게  입 력 하 세 요\n");
			getch(); 
		}
	}
}
