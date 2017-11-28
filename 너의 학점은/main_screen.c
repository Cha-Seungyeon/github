#include "header.h"

extern user *u_head, *u_tail;
extern clas *c_head, *c_tail;
extern note *n_head, *n_tail;

void main_menu(user *login_user)
{
	int select;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t     %s 의  학 점 은 ?\n", login_user->name);
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t1. 수 강 신 청");
		printf("\n\n\t\t2. 수 강 변 경 / 삭 제"); 
		printf("\n\n\t\t3. 내  수 강 내 역");
		printf("\n\n\t\t4. 필 기 하 기");
		printf("\n\n\t\t5. 학 점 관 리");
		printf("\n\n\t\t6. 개 인 정 보  변 경");
		printf("\n\n\t\t7. 프 로 그 램  종 료");
		printf("\n\n\n\t\t-------------------------------\n\t\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case 1:
				apply_class(login_user);
				continue;
			case 2:
				change_and_del(login_user);
				continue;
			case 3:
				my_class(login_user);
				continue;
			case 4:
				//writing_note(login_user);
				continue;
			case 5:
				my_grade(login_user);
				continue;
			case 6:
				my_info(login_user);
				continue;
			case 7: 
				save_file();
			default:
				printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
				getch(); 
				continue;
		}
	}
}

void apply_class(user *login_user)
{
	char day[15];
	int i, flag = 0;
	
	clas *c_node, *tmp;
	c_node = (clas *)malloc(sizeof(clas));
	memset(c_node, 0, sizeof(clas));
	
	strcpy(c_node->id, login_user->id);
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t           강 의 추 가\n");
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t과 목 명 : ");
		fflush(stdin);
		gets(c_node->name);
		
		for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(!strcmp(tmp->id, login_user->id) && !strcmp(tmp->name, c_node->name))
			{
				flag = 1;
				printf("\n\n\t\t이 미  존 재 하 는  강 의 입 니 다");
				getch(); 
			}
		}
		
		if(flag == 0)
		{
			break;
		}
	}
	
	printf("\n\n\t\t이 수 학 점 : ");
	scanf("%d", &c_node->credit);
	
	printf("\n\n\t\t날 짜 ( 쉼 표 없 이  입 력, ex. 월 화-> 1 2 )\n\n\t\t( 월 : 1  화 : 2  수 : 3  목 : 4  금 : 5 )\n\n\t\t");
	fflush(stdin);
	gets(day);
	
	char *str = strtok(day, " ");
	while(str != NULL)
	{
		c_node->day[atoi(str)-1] = 1;
		str = strtok(NULL, " ");
	}
	
	printf("\n\n\t\t학 년 : ");
	scanf("%d", &c_node->year);
	printf("\n\n\t\t학 기 : "); 
	scanf("%d", &c_node->semester); 
	
	c_tail->pre->next = c_node;
	c_node->pre = c_tail->pre;
	c_tail->pre = c_node;
	c_node->next = c_tail;
	
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t추 가  되 었 습 니 다");
	getch();
}

void change_and_del(user *login_user)
{
	char class_name[50];
	int select, flag = 0, class_count;
	
	clas *tmp;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t      강 의 변 경 / 삭 제\n");
		printf("\n\t\t-------------------------------\n");
		
		for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			class_count++;
			printf("\n\n\t\t%s", tmp->name);
		}
		
		if(class_count == 0)
		{
			printf("\n\n\t\t-------------------------------\n");
			printf("\n\n\t\t신 청 한  강 의 가  없 습 니 다");
			getch();
			break;
		}
		
		printf("\n\n\t\t-------------------------------\n");
		printf("\n\n\t\t변 경 / 삭 제 할  강 의 명 을  입 력 하 세 요\n\n\t\t\t( 취 소 : - 1 )\n\n\t\t");
		fflush(stdin);
		gets(class_name);
		
		if(!strcmp(class_name, "-1"))
		{
			break;
		}
		
		for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(!strcmp(tmp->name, class_name))
			{
				flag = 1;
				
				while(1)
				{
					printf("\n\n\t\t1. 변 경  2. 삭 제\n\n\t\t>> "); 
					scanf("%d", &select);
					
					switch(select)
					{
						case 1:
							change_class(tmp);
							return;
						case 2:
							del_class(tmp);
							return;
						default:
							printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
							getch(); 
							continue;
					}
				}
			}
		}
		
		if(flag == 0)
		{
			printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
			getch(); 
			continue;
		}
	}
}

void change_class(clas *select_class)
{
	int select;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t           강 의 변 경\n");
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t1. 과 목 명  변 경");
		printf("\n\n\t\t2. 이 수 학 점  변 경");
		printf("\n\n\t\t3. 날 짜 변 경");
		printf("\n\n\t\t4. 학 년 변 경");
		printf("\n\n\t\t5. 학 기 변 경"); 
		printf("\n\n\t\t6. 이 전 으 로"); 
		printf("\n\n\n\t\t-------------------------------\n\t\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case 1:
				change_class_name(select_class);
				continue;
			case 2:
				change_class_credit(select_class);
				continue;
			case 3:
				change_class_day(select_class);
				continue;
			case 4:
				system("cls");
				printf("\n\n\t\t-------------------------------\n");
				printf("\n\t\t          이 수 학 년  변 경\n");
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t새 로 운  이 수 학 년 을  입 력 하 세 요\n\n\t\t\t    ( 취 소 - 1 )\n\n\t\t");
				scanf("%d", &select_class->year);
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t변 경 되 었 습 니 다"); 
				getch();
				
				continue;
			case 5:
				system("cls");
				printf("\n\n\t\t-------------------------------\n");
				printf("\n\t\t          이 수 학 기  변 경\n");
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t새 로 운  이 수 학 기 를  입 력 하 세 요\n\n\t\t\t    ( 취 소 - 1 )\n\n\t\t");
				scanf("%d", &select_class->semester);
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t변 경 되 었 습 니 다"); 
				getch();
			case 6:
				return;
			default:
				printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
				getch(); 
				continue;
		}
	}
}

void change_class_name(clas *select_class)
{
	clas *tmp;
	
	char new_name[50];
	int flag = 0;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t         강 의 명  변 경\n");
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t새 로 운  강 의 명 을  입 력 해 주 세 요\n\n\t\t\t    (취 소 - 1 )\n\n\t\t");
		fflush(stdin);
		gets(new_name);
		
		if(!strcmp(new_name, "-1"))
		{
			return;
		}
		
		for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(!strcmp(tmp->name, new_name))
			{
				flag = 1;
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t이 미  존 재 합 니 다\n");
				getch();
				
				continue;
			}
		}
		
		if(flag == 0)
		{
			strcpy(select_class->name, new_name);
			printf("\n\t\t-------------------------------\n");
			printf("\n\n\t\t변 경 되 었 습 니 다"); 
			getch();
			break;
		}
	}
	
}

void change_class_credit(clas *select_class)
{
	system("cls");
	printf("\n\n\t\t-------------------------------\n");
	printf("\n\t\t          이 수 학 점  변 경\n");
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t새 로 운  이 수 학 점 을  입 력 하 세 요\n\n\t\t\t    ( 취 소 - 1 )\n\n\t\t");
	scanf("%d", &select_class->credit);
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t변 경 되 었 습 니 다"); 
	getch();
}

void change_class_day(clas *select_class)
{
	char day[15];
	
	system("cls");
	printf("\n\n\t\t-------------------------------\n");
	printf("\n\t\t          강 의 날 짜  변 경\n");
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t새 로 운  날 짜 를  입 력 하 세 요\n\n\t\t(ex. 월 화)\t( 취 소 - 1 )\n\n\t\t");
	fflush(stdin);
	gets(day);
	
	memset(select_class->day, 0, sizeof(select_class->day));
	char *str = strtok(day, " ");
	while(str != NULL)
	{
		select_class->day[atoi(str)-1] = 1;
		str = strtok(NULL, " ");
	}
	
	printf("\n\t\t-------------------------------\n");
	printf("\n\n\t\t변 경 되 었 습 니 다"); 
	getch();
}

void del_class(clas *select_class)
{
	select_class->pre->next = select_class->next;
	select_class->next->pre = select_class->pre;
	
	free(select_class);
	
	system("cls");
	printf("\n\t\t-------------------------------\n");
	printf("\n\t\t     삭 제 되 었 습 니 다\n");
	printf("\n\t\t-------------------------------\n");
	getch();
}

void my_class(user *login_user)
{
	char *week[5] = {"월", "화", "수", "목", "금"};
	int i;
	
	clas *tmp;
	
	system("cls");
	printf("\n\n\t\t-------------------------------\n");
	printf("\n\t\t        내  수 강  내 역\n");
	printf("\n\t\t-------------------------------\n");
	
	for(i = 0; i < 5; i++)
	{
		printf("\n\n\t\t%s : ", week[i]);
		
		for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
		{
			if(!strcmp(login_user->id, tmp->id) && tmp->day[i] == 1)
			{
				printf("%s  ", tmp->name);
			}
		}
	}
	
	getch();
}

void my_grade(user *login_user)
{
	char class_name[50];
	int select, flag = 0, class_count, i, j, count_credit, whole_credit = 0;
	float count_grade, whole_grade = 0;
	
	clas *tmp;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t     %s 의  학 점 은 ?\n", login_user->name);
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t1. 학 점  입 력");
		printf("\n\n\t\t2. 학 점  보 기"); 
		printf("\n\n\t\t3. 이 전 으 로\n"); 
		printf("\n\t\t-------------------------------\n\n\t\t>> ");
		scanf("%d", &select);
		
		switch(select)
		{
			case 1:
				while(1)
				{
					system("cls");
					printf("\n\t\t-------------------------------\n");
					printf("\n\t\t            학 점  입 력\n");
					printf("\n\t\t-------------------------------\n");
					
					for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
					{
						class_count++;
						printf("\n\n\t\t%s", tmp->name);
					}
					
					if(class_count == 0)
					{
						printf("\n\n\t\t-------------------------------\n");
						printf("\n\n\t\t신 청 한  강 의 가  없 습 니 다");
						getch();
						break;
					}
					
					printf("\n\n\t\t-------------------------------\n");
					printf("\n\n\t\t강 의 명 을  입 력 하 세 요 ( 취 소 : - 1 )\n\n\t\t");
					fflush(stdin);
					gets(class_name);
					
					if(!strcmp(class_name, "-1"))
					{
						break;
					}
					
					for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
					{
						if(!strcmp(tmp->name, class_name))
						{
							flag = 1;
							system("cls");
							printf("\n\t\t-------------------------------\n");
							printf("\n\t\t     %s 의  학 점 은 ?\n", login_user->name);
							printf("\n\t\t-------------------------------\n");
							printf("\n\n\t\t학 점 을  입 력 해 주 세 요\n\n\t\t"); 
							scanf("%f", &tmp->grade);
							printf("\n\t\t-------------------------------\n");
							printf("\n\n\t\t입 력 되 었 습 니 다"); 
							getch();
						}
					}
					
					if(flag == 0)
					{
						printf("\n\n\t\t올 바 르 게  입 력 하 세 요");
						getch();
						
						continue; 
					}
				}
				continue;
			case 2:
				whole_credit = 0, whole_grade = 0;
				system("cls");
				printf("\n\t\t-------------------------------\n");
				printf("\n\t\t     %s 의  학 점 은 ?\n", login_user->name);
				printf("\n\t\t-------------------------------\n");
				for(i = 1; i < 5; i++)
				{
					for(j = 1; j < 3; j++)
					{
						flag = 0;
						count_credit = 0;
						count_grade = 0;
						printf("\n\n\t\t%d 학 년  %d 학 기", i, j); 
						
						for(tmp = c_head->next; tmp->next != NULL; tmp = tmp->next)
						{
							if(!strcmp(tmp->id, login_user->id) && tmp->year == i && tmp->semester == j && tmp->grade != 0)
							{
								printf("\n\n\t\t과 목 명 : %s  [ %.1f ]", tmp->name, tmp->grade);
								count_credit  = count_credit + tmp->credit;
								count_grade = count_grade + (tmp->grade * tmp->credit);
								whole_credit = whole_credit + tmp->credit;
								whole_grade = whole_grade + (tmp->grade * tmp->credit);
							}
						}
						
						if(count_credit == 0)
						{
							printf("\n\n\t\t존 재 하 지 않 습 니 다");
							printf("\n\n\t\t-------------------------------\n");
						}
						else
						{
							printf("\n\n\n\t\t총  이 수 학 점 : %d", count_credit);
							printf("\n\n\t\t총  학 점 : %.2f", (count_grade / count_credit));
							printf("\n\n\t\t-------------------------------\n");
							
						}
					}
				}
				printf("\n\n\n\t\t-------------------------------\n");
				printf("\n\n\t\t총  이 수 학 점 : %d", whole_credit);
				printf("\n\n\t\t총  학 점 : %.2f", (whole_grade / whole_credit));
				getch();
				continue;
			case 3:
				return;
			default:
				printf("\n\n\t\t올 바 르 게  입 력 하 세 요 ");
				getch();
				
				continue;	
		}
	}
}

void my_info(user *login_user)
{
	int select;
	
	while(1)
	{
		system("cls");
		printf("\n\t\t-------------------------------\n");
		printf("\n\t\t     %s 의  정 보 는 ?\n",login_user->name);
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t아 이 디 : %s", login_user->id);
		printf("\n\n\t\t1. 이 름 : %s", login_user->name);
		printf("\n\n\t\t2. 전 화 번 호 : %s\n", login_user->phone); 
		printf("\n\t\t-------------------------------\n");
		printf("\n\n\t\t변 경 할  정 보 의  번 호 를  입 력 하 세 요 (취 소 : -1 ) ");
		scanf("%d", &select);
		
		switch(select)
		{
			case 1:
				system("cls");
				printf("\n\t\t-------------------------------\n");
				printf("\n\t\t     이 름  변 경");
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t새 로 운  이 름 을  입 력 하 세 요\n\n\t\t");
				gets(login_user->name);
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t변 경 되 었 습 니 다");
				getch();
				
				continue;
			case 2:
				system("cls");
				printf("\n\t\t-------------------------------\n");
				printf("\n\t\t   전 화 번 호  변 경");
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t새 로 운  번 호 를  입 력 하 세 요\n\n\t\t");
				fflush(stdin);
				gets(login_user->phone);
	
				while(1)
				{
					if(check_phone(login_user->phone) == 1)
					{
						printf("\n\n\t\t올 바 르 게  입 력 해 주 세 요");
						getch();
						
						system("cls");
						printf("\n\t\t-------------------------------\n");
						printf("\n\t\t   전 화 번 호  변 경");
						printf("\n\t\t-------------------------------\n");
						printf("\n\n\t\t새 로 운  번 호 를  입 력 하 세 요\n\n\t\t");
						fflush(stdin);
						gets(login_user->phone);
					}
					else {
						break;
					}
				}
				
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t변 경 되 었 습 니 다");
				getch();
			case -1:
				return;
			default:
				printf("\n\t\t-------------------------------\n");
				printf("\n\n\t\t올 바 르 게 입 력 하 세 요");
				getch();
		}
	}
}
