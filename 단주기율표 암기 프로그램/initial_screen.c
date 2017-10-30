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

void load_file() //파일 불러오기 함수 
{	
	int i;
	
	FILE *fp = fopen("learn_data.txt", "r");
	
	if(fp == NULL) //파일이 존재하지 않을 경우 새로 만듦
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
	
	if(mp == NULL) //파일이 존재하지 않을 경우 새로 만듦
	{
		mp = fopen("member_data.txt", "w");
	}
	else {
		while(!feof(mp))
		{
			mem_count++;
			fscanf(mp, "%s %s %s %s", member_data[mem_count].id, member_data[mem_count].password, member_data[mem_count].name, member_data[mem_count].phone);
			
			if(!strcmp(member_data[mem_count].id, "")) //아이디 값이 존재하지 않을 경우 회원 카운트 수 감소 
			{
				mem_count--;
			}
		}
	}
	
	fclose(mp);
	
	FILE *rp = fopen("result_data.txt", "r");
	
	if(rp == NULL) //파일이 존재하지 않을 경우 새로 만듦
	{
		rp = fopen("result_data.txt", "w");
	}
	else {
		while(!feof(rp))
		{
			result_count++;
			fscanf(rp, "%s %d %d %d %d %d", result_data[result_count].id, &result_data[result_count].type, &result_data[result_count].yyyy, &result_data[result_count].mm, &result_data[result_count].dd, &result_data[result_count].correct);
			
			if(!strcmp(result_data[result_count].id, "")) //아이디 값이 존재하지 않을 경우 결과 카운트 수 감소 
			{
				result_count--;
			}
		}
	}
	
	fclose(rp);
}

void save_file() //구조체 배열 값 파일에 저장하고 프로그램 종료 
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
	printf("\t      프 로 그 램 을  종 료 합 니 다.\n");
	printf("\n\t==========================================\n\n");
	getch();
	
	exit(0); // 프로그램 정상 종료 
}

void print_initial_screen()
{
	enum initial_screen_menu {MEMBER_LOGIN = 1, JOIN_MEMBER, SEARCH_MEM_ID, SEARCH_MEM_PASSWORD, EXIT_PROGRAM};
	
	int select;
	
	while(1)
	{
		system("cls");
		
		printf("\n 단 주 기 율 표  암 기 학 습  프 로 그 램\n\n");
		printf("==========================================\n\n");
		printf("\t1. 로 그 인\n\n");
		printf("\t2. 회 원 가 입\n\n");
		printf("\t3. 아 이 디  찾 기\n\n");
		printf("\t4. 비 밀 번 호  찾 기\n\n");
		printf("\t5. 프 로 그 램  종 료\n\n");
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
				printf("\n올 바 르 게  입 력 해 주 세 요\n");
				getch();
				continue;
		}
	}
}

void asterisk(char password[]) //비밀번호 별표 화 함수 
{
	int i = 0;
	
	while(1)
	{
		password[i] = getch();
		
		if(password[i] == 13) // 엔터 입력 받은 경우 
		{
			password[i] = '\0'; // 개행문자 없애고 저장 
			break; // 함수 종료 
		}
		
		if(password[i] == 8) // 백스페이스 입력 받은 경우 
		{	
			if(i > 0)
			{
				printf("\b"); // 커서 한 칸 뒤로 옮기기 
				printf(" "); // 공백 출력 
				printf("\b"); // 커서 다시 한 칸 뒤로 옮기기 
				i--; // 비밀번호 저장하는 인덱스 값 하나 감소 
			}
		}
		else {
			printf("*"); //별표 출력 
			i++; // 비밀번호 저장 인덱스 값 하나 증가 
		}
	}
}

int check_phone(char phone[]) //전화번호 예외처리 함수 (숫자만 존재하는지 검사) 
{
	int i, flag = 0;
	
	for(i = 0; i < strlen(phone); i++)
	{
		if(phone[i] < '0' || phone[i] > '9') //숫자가 아닌 문자가 들어갔을 경우 
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
		flag = 0; // 아이디 검사 초기화 
		system("cls");
		
		printf("\n\t       회 원 가 입\n\n");
		printf("==========================================\n\n");
		printf("\t아 이 디 : ");
		scanf("%s", id);
		
		for(i = 1; i <= mem_count; i++) // 존재하는 아이디인지 검사 
		{
			if(!strcmp(member_data[i].id, id))
			{
				flag = 1;
				printf("\n\t존 재 하 는  아 이 디 입 니 다");
				getch();
			}
		}

		if(flag == 1) // 존재하는 아이디일 경우 다시 입력 받기 
		{
			continue;
		}
		
		mem_count++; // 새로운 회원 추가, 회원 수 하나 증가 
		strcpy(member_data[mem_count].id, id);
		
		printf("\n\t비 밀 번 호 : ");
		asterisk(member_data[mem_count].password);
		
		printf("\n\n\t이 름 : ");
		scanf("%s", member_data[mem_count].name);
		
		printf("\n\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
		scanf("%s", phone);
		
		while(check_phone(phone) == 1) // 전화번호 예외처리 
		{
			printf("\n\t숫 자 만  입 력 해 주 세 요"); 
			getch();
			//다시 입력 받기 
			system("cls");
			printf("\n\t       회 원 가 입\n\n");
			printf("==========================================\n\n");
			printf("\t아 이 디 : %s\n\n", member_data[mem_count].id);
			printf("\t비 밀 번 호 : "); 
			for(i = 0; i < strlen(member_data[mem_count].password); i++) // 저장된 비밀번호 길이만큼 별표 출력 
			{
				printf("*");
			}
			printf("\n\n\t이 름 : %s\n\n", member_data[mem_count].name);
			printf("\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
			scanf("%s", phone);
			
			continue;	
		}
		
		strcpy(member_data[mem_count].phone, phone);

		printf("\n==========================================\n\n");
		printf("   회 원 가 입 이  완 료 되 었 습 니 다\n");
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
		
	printf("\n\t        로 그 인\n\n");
	printf("==========================================\n\n");
	printf("\t아 이 디 : ");
	scanf("%s", id);
	printf("\n\t비 밀 번 호 : ");
	asterisk(password);
	 
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].id, id))
		{
			flag = 1; // 존재하는 아이디라는 것을 표시함 
			if(!strcmp(member_data[i].password, password))
			{
				print_main_screen(i);
			}
			else {
				printf("\n\n==========================================\n\n");
				printf(" 비 밀 번 호 를  다 시  확 인 해 주 세 요\n");
				getch();
				
				return;
			}
		}
	}

	if(flag == 0) // 존재하지 않는 아이디를 입력했을 경우 
	{
		printf("\n\n==========================================\n\n");
		printf("   존 재 하 지 않 는  아 이 디 입 니 다\n");
		getch();
	}
}

void search_id()
{
	char name[10];
	char phone[13];
	int i, flag = 0;
	
	system("cls");
		
	printf("\n\t      아 이 디  찾 기\n\n");
	printf("==========================================\n\n");
	printf("\t이 름 : ");
	scanf("%s", name);
	printf("\n\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
	scanf("%s", phone);
	
	while(check_phone(phone) == 1) // 전화번호 예외처리 
	{
		printf("\n\t숫 자 만  입 력 해 주 세 요"); 
		getch();
		//다시 입력 받기 
		system("cls");
		printf("\n\t      아 이 디  찾 기\n\n");
		printf("==========================================\n\n");
		printf("\t이 름 : %s\n", name);
		printf("\n\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
		scanf("%s", phone);
	}
	
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].name, name) && !strcmp(member_data[i].phone, phone))
		{
			flag = 1; // 존재하는 데이터임을 표시 
			printf("\n==========================================\n\n");
			printf("\t아 이 디 는  %s 입 니 다\n", member_data[i].id);
			getch();
			return;
		}
	}
	
	if(flag == 0) // 해당 데이터가 존재하지 않을 경우 
	{
		printf("\n==========================================\n\n");
		printf("   존 재 하 지 않 는  데 이 터 입 니 다\n");
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
	
	printf("\n\t     비 밀 번 호  찾 기\n\n");
	printf("==========================================\n\n");
	printf("\t아 이 디 : ");
	scanf("%s", id); 
	printf("\n\t이 름 : ");
	scanf("%s", name);
	printf("\n\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
	scanf("%s", phone);
	
	while(check_phone(phone) == 1) // 전화번호 예외처리 
	{
		printf("\n\t숫 자 만  입 력 해 주 세 요"); 
		getch();
		//다시 입력 받기 
		system("cls");
		printf("\n\t     비 밀 번 호  찾 기\n\n");
		printf("==========================================\n\n");
		printf("\t아 이 디 : %s\n", id);
		printf("\n\t이 름 : %s\n", name); 
		printf("\n\t전 화 번 호 ( 숫 자 만  입 력 )\n\n\t");
		scanf("%s", phone);
	}
	
	for(i = 1; i <= mem_count; i++)
	{
		if(!strcmp(member_data[i].id, id) && !strcmp(member_data[i].name, name) && !strcmp(member_data[i].phone, phone))
		{
			flag = 1; // 존재하는 데이터임을 표시 
			printf("\n==========================================\n\n");
			printf(" 새 로 운  비 밀 번 호 를  입 력 하 세 요\n\n ");
			printf(">> ");
			asterisk(member_data[i].password);
			printf("\n\n 성 공 적 으 로  변 경 되 었 습 니 다 !");
			getch();
		}
	}
	
	if(flag == 0)
	{
		printf("\n==========================================\n\n");
		printf("   존 재 하 지 않 는  데 이 터 입 니 다\n");
		getch();
	}
}
