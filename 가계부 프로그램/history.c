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
		printf("\t   [ 내 역 보 기 ]\n");
		printf("========================================\n\n");
		printf(" \t1. 내 역 검 색 (수 정 / 삭 제)\n\n");
		printf(" \t2. 오 늘 내 역 보 기\n\n");
		printf(" \t3. 이 번  달  내 역 보 기\n\n");
		printf(" \t4. 이 전 내 역 보 기\n\n");
		printf(" \t5. 이 전 화 면 으 로\n\n"); 
		printf(" \t6. 프 로 그 램  종 료\n\n");
		printf("========================================\n");
		printf("\n\t번 호 를 입 력 하 세 요\n");
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
				printf("\n\t바 르 게  입 력 하 세 요\n");
				getch();
		}
	}
}

void find_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	int num = 0, _index, select, flag = 0;
	char search[100];
	char str[15];
	INFO *tmp;
	
	struct tm *t;
   	time_t timer;
   
   	timer = time(NULL);
   	t = localtime(&timer);
	
	system("cls");
	
	printf("========================================\n");
	printf("\t    [ 내 역 검 색 ]\n");
	printf("========================================\n\n");
	printf("\t검 색 어 를  입 력 하 세 요.\n");
	printf("\n\t>> ");
	fflush(stdin);
	gets(search);
	
	printf("\n========================================\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if((strcmp(tmp->id, login_User->id) == 0) && (strcmp(tmp->content, search) == 0 || strcmp(tmp->group, search) == 0))
		{
			if(daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{	
				itoa(tmp->sum, str, 10);
				money(str);
				printf("\n%2d | %4d - %2d - %2d | %d | %8s | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, str, tmp->content);
				num ++;
			}
			
		}
	}
	
	if(num == 0)
	{
		printf("\n내 역 이  없 습 니 다.\n\n");
		getch();
		
		view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	}
	else
	{
		printf("\n========================================\n\n");
		printf("수 정 하 거 나  삭 제 할  데 이 터 의\n    인 덱 스 를  입 력 하 세 요\n"); 
		printf("\n>> ");
		fflush(stdin);
		scanf("%d", &_index);
		
		for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(strcmp(tmp->id, login_User->id) == 0 && tmp->index == _index)
			{
				while(1)
				{
					printf("\n1. 수  정\n");
					printf("\n2. 삭  제\n");
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
						printf("\n바 르 게  입 력 하 세 요\n"); 
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
			printf("\n바 르 게  입 력 하 세 요\n");
			getch();
			
			find_info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
			
			return;
		}
	}
}

void edit_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node)
{
	int _key = i_node->key;
	
	i_node->pre->next = i_node->next; //노드 연결 끊기 
	i_node->next->pre = i_node->pre;
	free(i_node);
	
	add_Info(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User, i_node->key);
	
	sort_History(i_head, i_tail, login_User);
	view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
	
	printf("\n 수 정 이  완 료 되 었 습 니 다.\n");
	getch();
	
	view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void del_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node)
{
	i_node->pre->next = i_node->next; //노드 연결 끊기 
	i_node->next->pre = i_node->pre;
	free(i_node);
	
	sort_History(i_head, i_tail, login_User);
	
	printf("\n 삭 제 가  완 료 되 었 습 니 다.\n");
	getch();
	
	view_History(u_head, u_tail, g_head, g_tail, i_head, i_tail, a_head, a_tail, login_User);
}

void calculate_Percent(GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	float _daysum = 0, _monthsum = 0, _allsum = 0;
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	//카테고리 별 하루 계산, 한 달 계산
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		g_tmp->daysum = 0;
		g_tmp->monthsum = 0;
		g_tmp->allsum = 0;
		
		for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(strcmp(tmp->id, login_User->id) == 0 && strcmp(tmp->group, g_tmp->name) == 0 && tmp->key == 2)
			{
				g_tmp->allsum = g_tmp->allsum + tmp->sum;
				
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
	
	//하루, 한 달 별로 총 지출액 계산 
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && tmp->key == 2)
		{
			_allsum = _allsum + tmp->sum;
			
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
	
	//하루, 한 달 별로 카테고리 별 지출액 나누기 총 지출액 곱하기 백을 하여 퍼센테이지를 계산함 
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		if(_allsum > 0)
		{
			g_tmp->allsum = (g_tmp->allsum / _allsum) * 100;
		}
		
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
	char str[15];
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("==========================================================\n");
	printf("\t\t[ 오 늘 내 역 ]\n");
	printf("==========================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && daysum(tmp->yyyy, tmp->mm, tmp->dd) == daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
		{
			itoa(tmp->sum, str, 10);
			money(str);
			printf("\n%2d | %4d - %2d - %2d | %d | %8s | %7s | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, str, tmp->group, tmp->content);
		}
	}
	
	printf("\n==========================================================\n\n");
	printf("\t\t[ 지 출 추 이 ]\n\n"); 
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->daysum); 
	}
	
	printf("==========================================================\n\n");
	itoa(login_User->total, str, 10);
	money(str);
	printf("total : %8s", str);
	
	getch();
}

void view_month(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	char str[15];
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);

	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("=============================================================\n");
	printf("\t\t[ 이 번  달  내 역 ]\n");
	printf("=============================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0)
		{
			if(daysum(t->tm_year + 1900, t->tm_mon + 1, 1) <= daysum(tmp->yyyy, tmp->mm, tmp->dd) && daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
			{
				itoa(tmp->sum, str, 10);
				money(str);
				printf("\n%2d | %4d - %2d - %2d | %d | %8s | %7s | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, str, tmp->group, tmp->content);
			}
		}
	}
	
	printf("\n=============================================================\n\n");
	printf("\t\t[ 지 출 추 이 ]\n\n");
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->monthsum);
	}
	
	printf("=============================================================\n\n");
	itoa(login_User->total, str, 10);
	money(str);
	printf("total : %8s", str);
	
	getch();
}

void view_all(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User)
{
	INFO *tmp;
	GROUP *g_tmp;
	char str[15];
	
	struct tm *t;
	time_t timer;
	
	timer = time(NULL);
	t = localtime(&timer);
	
	calculate_Percent(g_head, g_tail, i_head, i_tail, login_User);
	
	system("cls");
	
	printf("=============================================================\n");
	printf("\t\t[ 이 전  내 역 ]\n");
	printf("=============================================================\n\n");
	
	for(tmp = i_head->next; tmp->next != NULL; tmp = tmp->next)
	{
		if(strcmp(tmp->id, login_User->id) == 0 && daysum(tmp->yyyy, tmp->mm, tmp->dd) <= daysum(t->tm_year + 1900, t->tm_mon + 1, t->tm_mday))
		{
			itoa(tmp->sum, str, 10);
			money(str);
			printf("\n%2d | %4d - %2d - %2d | %d | %8s | %7s | %s \n", tmp->index, tmp->yyyy, tmp->mm, tmp->dd, tmp->key, str, tmp->group, tmp->content);
		}
	}
	
	printf("\n=============================================================\n\n");
	printf("\t\t[ 지 출 추 이 ]\n\n");
	
	for(g_tmp = g_head->next; g_tmp->next != NULL; g_tmp = g_tmp->next)
	{
		printf("\t   %10s : %.2f%%\n\n", g_tmp->name, g_tmp->allsum);
	}
	
	printf("=============================================================\n\n");
	itoa(login_User->total, str, 10);
	money(str);
	printf("total : %8s", str);
	
	getch();
}
