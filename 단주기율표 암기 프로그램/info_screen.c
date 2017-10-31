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
		
		printf("\n\t정 보  관 리  메 뉴\n\n");
		printf("==========================================\n\n");
		printf("\t1. 내  이 름  변 경\n\n");
		printf("\t2. 비 밀 번 호  변 경\n\n");
		printf("\t3. 전 화 번 호  변 경\n\n");
		printf("\t4. 회 원 탈 퇴\n\n"); 
		printf("\t5. 이 전  화 면 으 로\n\n");
		printf("\t6. 프 로 그 램  종 료\n\n");
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
				printf("\n올 바 르 게  입 력 해 주 세 요\n");
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
		printf("\n\t       이 름 변 경\n\n");
		printf("==========================================\n\n");
		printf("\t현 재  이 름 : %s\n\n", member_data[login_user].name);
		printf(" 새 로 운  이 름 을  입 력 해 주 세 요\n\n\t\t\t( 취 소 : - 1)\n\n\t>> ");
		scanf("%s", new_name);
		
		if(!strcmp(member_data[login_user].name, new_name))
		{
			printf("\n\n\t똑 같 은  이 름 입 니 다.\n\n\t다 시  입 력 해 주 세 요.");
			getch();
			
			continue; 
		}
		
		strcpy(member_data[login_user].name, new_name);
		printf("\n==========================================\n\n");
		printf("  %s (으) 로  이 름 이  변 경 되 었 습 니 다 !", member_data[login_user].name); 
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
		printf("\n\t    비 밀 번 호  변 경\n\n");
		printf("==========================================\n\n");
		printf(" 새 로 운  비 밀 번 호 를  입 력 해 주 세 요\n\n\t\t\t( 취 소 : - 1)\n\n\t>> ");
		asterisk(new_password);
		
		if(!strcmp(member_data[login_user].password, new_password))
		{
			printf("\n\n\t똑 같 은  비 밀 번 호 입 니 다.\n\n\t다 시  입 력 해 주 세 요.");
			getch();
			
			continue; 
		}
		
		strcpy(member_data[login_user].password, new_password);
		printf("\n==========================================\n\n");
		printf("  성 공 적 으 로  변 경 되 었 습 니 다 !");
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
		printf("\n\t    전 화 번 호  변 경\n\n");
		printf("==========================================\n\n");
		printf(" 현 재  전 화 번 호 : %s\n\n", member_data[login_user].phone); 
		printf(" 새 로 운  전 화 번 호 를  입 력 해 주 세 요\n\n\t( 숫 자 만  입 력 해 주 세 요 )\n\n\t\t( 취 소 : - 1)\n\n\t>> ");
		scanf("%s", new_phone);
		
		while(check_phone(member_data[login_user].phone) == 1) // 전화번호 예외처리 
		{
			printf("\n\t숫 자 만  입 력 해 주 세 요"); 
			getch();
			system("cls");
			printf("\n\t    전 화 번 호  변 경\n\n");
			printf("==========================================\n\n");
			printf(" 새 로 운  전 화 번 호 를  입 력 해 주 세 요\n\n\t( 숫 자 만  입 력 해 주 세 요 )\n\n\t>> ");
			scanf("%s", new_phone);
		}
		
		if(!strcmp(member_data[login_user].phone, new_phone))
		{
			printf("\n\n\t똑 같 은  전 화 번 호 입 니 다.\n\n\t다 시  입 력 해 주 세 요.");
			getch();
			
			continue; 
		}
		
		printf("\n==========================================\n\n");
		printf("  성 공 적 으 로  변 경 되 었 습 니 다 !");
		getch();
		break;
	}
}

void del_mem(int login_user)
{
	char respones[5];
	int i, j, t, flag = 1;
	
	system("cls");
	printf("\n\t       회 원 탈 퇴\n\n");
	printf("==========================================\n\n");
	printf("\t학 습 정 보 를  비 롯 한\n\n   모 든  데 이 터 가  삭 제 됩 니 다.\n\n   그 래 도  진 행 하 시 겠 습 니 까 ?\n\n\t\t ( Y e s  /  N o )\n\n\t>> ");
	scanf("%s", respones);
	
	if(!strcmp(respones, "YES") || !strcmp(respones, "Yes") || !strcmp(respones, "Y") || !strcmp(respones, "y"))
	{
		while(flag == 1)
		{
			flag = 0; // 해당 아이디의 데이터가 존재하는지에 대한 변수 초기화 

			for(i = 1; i <= result_count; i++)
			{
				if(!strcmp(result_data[i].id, member_data[login_user].id)) // 로그인한 아이디의 기록이 있는지 확인 
				{
					for(j = i + 1; j <= result_count; j++) // 현재 인덱스 + 1 부터 마지막까지의 데이터 한 칸 전으로 미루기 
					{
						strcpy(result_data[j - 1].id, result_data[j].id);
						result_data[j - 1].type = result_data[j].type;
						result_data[j - 1].yyyy = result_data[j].yyyy;
						result_data[j - 1].mm = result_data[j].mm;
						result_data[j - 1].dd = result_data[j].dd;
						result_data[j - 1].correct = result_data[j].correct;
					}
					
					result_count--; // 결과 데이터 카운트 변수 1 감소 
					flag = 1; // 해당 아이디의 데이터가 존재함을 표시 
					break; // 배열에 아이디가 있는지 처음부터 검사 (데이터를 하나 전으로 미뤘기 때문) 
				}
			}
		}

		for(i = login_user; i <= mem_count; i++) // 멤버 데이터에서 해당 아이디 데이터 삭제 
		{
			strcpy(member_data[i].id, member_data[i + 1].id);
			strcpy(member_data[i].password, member_data[i + 1].password);
			strcpy(member_data[i].name, member_data[i + 1].name);
			strcpy(member_data[i].phone, member_data[i + 1].phone);
		}
		mem_count--; // 멤버 카운트 변수 1 감소 
		printf("\n==========================================\n\n");
		printf("  회 원 탈 퇴 가  완 료 되 었 습 니 다\n");
		getch();
		save_file();
	}
	else {
		printf("\n==========================================\n\n");
		printf("  회 원 탈 퇴 가  취 소 되 었 습 니 다 !\n");
		getch();
	}
}
