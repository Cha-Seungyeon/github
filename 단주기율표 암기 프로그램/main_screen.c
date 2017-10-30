#include "define.h"

extern learn learning_data[20];
extern mem member_data[101];
extern result result_data[1001];
extern int mem_count;
extern int result_count;

void print_main_screen(int login_user)
{
	enum main_screen_menu {LEARN = 1, INDEX_TEST, SYMBOL_TEST, NAME_TEST, VIEW_TEST_RESULT, EDIT_MEM_INFO, EXIT_PROGRAM};
	
	int i, select;
	
	while(1)
	{
		system("cls");
		
		printf("\n%14s 님, 열 공 하 세 요 !\n\n", member_data[login_user].name);
		printf("==========================================\n\n");
		printf("\t1. 학 습 하 기\n\n");
		printf("\t2. 원 소 번 호 T E S T\n\n");
		printf("\t3. 원 소 기 호 T E S T\n\n");
		printf("\t4. 원 소 이 름 T E S T\n\n");
		printf("\t5. T E S T 결 과  보 기\n\n"); 
		printf("\t6. 내  정 보 관 리\n\n"); 
		printf("\t7. 프 로 그 램  종 료\n\n");
		printf("==========================================\n\n >> ");
		fflush(stdin);
		scanf("%d", &select);
		
		switch(select)
		{
			case LEARN:
				learning();
				continue;
			case INDEX_TEST:
				index_test(login_user);
				continue;
			case SYMBOL_TEST:
				name_test(login_user);
				continue;
			case NAME_TEST:
				symbol_test(login_user);
				continue;
			case VIEW_TEST_RESULT:
				print_result(login_user);
				continue;
			case EDIT_MEM_INFO:
				print_info(login_user);
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

void learning()
{
	int i, count, index;
	char name[6], symbol[5];
	
	for(i = 0; i < 20; i++)
	{
		count = 1; // 진행현황 초기화 
			
		while(count < 4)
		{
			system("cls");
			printf("\n\t진 행 현 황 : %d / 3\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%d   %s   %s\n\n", learning_data[i].index, learning_data[i].name, learning_data[i].symbol); // 샘플 출력해주기 
			printf("==========================================\n\n");
			printf("\n\t원 소 번 호 : ");
			fflush(stdin);
			scanf("%d", &index);
			printf("\n\n\t원 소 이 름 : ");
			fflush(stdin);
			scanf("%s", name);
			printf("\n\n\t원 소 기 호 : ");
			fflush(stdin);
			scanf("%s", symbol);
			
			if(index != learning_data[i].index || strcmp(name, learning_data[i].name) != 0 || strcmp(symbol, learning_data[i].symbol) != 0) // 올바르게 입력했는지 확인 
			{
				printf("\n==========================================\n\n");
				printf("\n    올 바 르 게  입 력 해 주 세 요\n");
				getch();
				
				continue; // 현재 진행현황의 원소 다시 입력하기 
			} 
			
			count++; // 정확하게 입력했으니 진행현황 1 증가 
			
			if(4-count == 0) // 3번 쓰기 완료했을 경우 
			{
				printf("\n==========================================\n\n");
				printf("       다 음 으 로  넘 어 갑 니 다 !", 4-count);
				getch();
			}
			else { // 남은 진행현황 표시해주기 
				printf("\n==========================================\n\n");
				printf("       %d 번  남 았 습 니 다 !", 4-count);
				getch();
			}	
		}
	}
	
	system("cls"); // 학습 정상적으로 마쳤다는 안내문 출력 
	
	printf("\n==========================================\n\n");
	printf("학 습 을  정 상 적 으 로  마 치 셨 습 니 다 !");
	printf("\n==========================================\n\n");
	
	getch();
}

void index_test(int login_user)
{
	int number[20] = {0,};
	int i, random_index, index, correct_count = 0, count = 1;
	
	srand(time(NULL)); // 랜덤 시드 초기화 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() % 20; // 0~19 까지의 수 랜덤으로 
		if(number[random_index] == 1) // 이미 나왔던 수라면 다시 랜덤 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // 다음에 똑같은 숫자가 랜덤되지 않도록 표시
			
			system("cls");
			printf("\n\t진 행 현 황 : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8s%6s\n\n", learning_data[random_index].name, learning_data[random_index].symbol); // 문제 출력 
			printf("\n==========================================\n\n");
			printf("\n\t원 소 번 호 : ");
			fflush(stdin);
			scanf("%d", &index);
			printf("\n\n==========================================\n\n");
			
			if(learning_data[random_index].index == index) // 사용자가 입력한 원소 번호와 정답이 맞는지 비교 
			{
				correct_count++;
				printf("\t정 답 입 니 다 !");
				getch();
			}
			else { // 틀렸을 경우 
				printf("\t오 답 입 니 다 !\n\n");
				printf("\t정 답 :  %d ", learning_data[random_index].index);
				getch();
			}
			
			count++; // 진행현황 카운트 변수 1 증가 
			
			if(count == 21)
			{
				system("cls"); // 테스트 정상적으로 마쳤다는 안내문 출력 
	
				printf("\n\t==========================================\n\n");
				printf("\t시 험 을  정 상 적 으 로  마 치 셨 습 니 다 !\n\n");
				printf("\t    맞 추 신  개 수 는  %d 개  입 니 다 !\n", correct_count);
				printf("\n\t==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // 테스트 카운트 변수 1 증가 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // 현재 시각을 초 단위로 얻기

	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
	
	//새로운 테스트 결과 기록 
	strcpy(result_data[result_count].id, member_data[login_user].id);
	result_data[result_count].type = 1;
	result_data[result_count].yyyy = t->tm_year + 1900;
	result_data[result_count].mm = t->tm_mon + 1;
	result_data[result_count].dd = t->tm_mday;
	result_data[result_count].correct = correct_count;
}

void name_test(int login_user)
{
	int number[20] = {0,};
	int i, random_index, correct_count = 0, count = 1;
	char name[10];
	
	srand(time(NULL)); // 랜덤 시드 초기화 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() %20; // 1~20 까지의 수 랜덤으로 
		if(number[random_index] == 1) // 이미 나왔던 수라면 다시 랜덤 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // 다음에 똑같은 숫자가 랜덤되지 않도록 표시
			
			system("cls");
			printf("\n\t진 행 현 황 : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8d%6s\n\n", learning_data[random_index].index, learning_data[random_index].symbol); // 문제 출력 
			printf("\n==========================================\n\n");
			printf("\n\t원 소 이 름 : ");
			fflush(stdin);
			scanf("%s", name);
			printf("\n\n==========================================\n\n");
			
			if(!strcmp(learning_data[random_index].name, name)) // 사용자가 입력한 원소 이름과 정답이 맞는지 비교 
			{
				correct_count++;
				printf("\t정 답 입 니 다 !");
				getch();
			}
			else { // 틀렸을 경우 
				printf("\t오 답 입 니 다 !\n\n");
				printf("\t정 답 :  %s", learning_data[random_index].name);
				getch();
			}
			
			count++; // 진행현황 카운트 변수 1 증가 
			
			if(count == 21)
			{
				system("cls"); // 테스트 정상적으로 마쳤다는 안내문 출력 
	
				printf("\n\t==========================================\n\n");
				printf("\t시 험 을  정 상 적 으 로  마 치 셨 습 니 다 !\n\n");
				printf("\t    맞 추 신  개 수 는  %d 개  입 니 다 !\n", correct_count);
				printf("\n==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // 테스트 카운트 변수 1 증가 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // 현재 시각을 초 단위로 얻기

	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
	
	//새로운 테스트 결과 기록 
	strcpy(result_data[result_count].id, member_data[login_user].id);
	result_data[result_count].type = 2;
	result_data[result_count].yyyy = t->tm_year + 1900;
	result_data[result_count].mm = t->tm_mon + 1;
	result_data[result_count].dd = t->tm_mday;
	result_data[result_count].correct = correct_count;
}

void symbol_test(int login_user)
{
	int number[20] = {0,};
	int i, random_index, correct_count = 0, count = 1;
	char symbol[6];
	
	srand(time(NULL)); // 랜덤 시드 초기화 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() %20; // 1~20 까지의 수 랜덤으로 
		if(number[random_index] == 1) // 이미 나왔던 수라면 다시 랜덤 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // 다음에 똑같은 숫자가 랜덤되지 않도록 표시
			 
			system("cls");
			printf("\n\t진 행 현 황 : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8d%6s\n\n", learning_data[random_index].index, learning_data[random_index].name); // 문제 출력 
			printf("\n==========================================\n\n");
			printf("\n\t원 소 기 호 : ");
			fflush(stdin);
			scanf("%s", symbol);
			printf("\n\n==========================================\n\n");
			
			if(!strcmp(learning_data[random_index].symbol, symbol)) // 사용자가 입력한 원소 기호와 정답이 맞는지 비교 
			{
				correct_count++;
				printf("\t정 답 입 니 다 !");
				getch();
			}
			else { // 틀렸을 경우 
				printf("\t오 답 입 니 다 !\n\n");
				printf("\t정 답 :  %s", learning_data[random_index].symbol);
				getch();
			}
			
			count++; // 진행현황 카운트 변수 1 증가 
			
			if(count == 21)
			{
				system("cls"); // 테스트 정상적으로 마쳤다는 안내문 출력 
	
				printf("\n\t==========================================\n\n");
				printf("\t시 험 을  정 상 적 으 로  마 치 셨 습 니 다 !\n\n");
				printf("\t    맞 추 신  개 수 는  %d 개  입 니 다 !\n", correct_count);
				printf("\n\t==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // 테스트 카운트 변수 1 증가 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // 현재 시각을 초 단위로 얻기

	t = localtime(&timer); // 초 단위의 시간을 분리하여 구조체에 넣기
	
	//새로운 테스트 결과 기록 
	strcpy(result_data[result_count].id, member_data[login_user].id);
	result_data[result_count].type = 3;
	result_data[result_count].yyyy = t->tm_year + 1900;
	result_data[result_count].mm = t->tm_mon + 1;
	result_data[result_count].dd = t->tm_mday;
	result_data[result_count].correct = correct_count;
}

void print_result(int login_user)
{
	enum main_screen_menu {INDEX_TEST = 1, NAME_TEST, SYMBOL_TEST};
	
	int i, flag = 0;
	
	system("cls");
		
	printf("\n\t\t  T E S T  결 과  확 인\n\n");
	printf("\t==============================================\n\n");
	printf("\t T E S T 이 름 | 시  행  날  짜 | 맞 은 개 수\n\n"); 
	
	for(i = 1; i <= result_count; i++)
	{
		if(!strcmp(result_data[i].id, member_data[login_user].id)) // 현재 로그인 한 아이디와 시험 결과의 아이디가 일치하면 
		{
			flag = 1;
			switch(result_data[i].type)
			{
				case INDEX_TEST:
					printf("\t 번 호 T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
				case NAME_TEST:
					printf("\t 이 름 T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
				case SYMBOL_TEST:
					printf("\t 기 호 T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
			}
		}
	}
	
	if(flag == 0)
	{
		system("cls");
		printf("\n\t\t  T E S T  결 과  확 인\n\n");
		printf("\t==============================================\n\n");
		printf("\t    데 이 터 가  존 재 하 지 않 습 니 다.\n\n");
	}
	
	printf("\t==============================================\n\n");
	getch();
}
