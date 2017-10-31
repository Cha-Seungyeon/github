#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//원소 주기율표 학습 데이터 
typedef struct _learning_data
{
	int index;
	char symbol[5];
	char name[10];
}learn;

//회원 정보 데이터 
typedef struct _member_data
{
	char id[15];
	char password[40];
	char name[10];
	char phone[13];
}mem;

//테스트 결과 데이터
typedef struct _result_data
{
	int type;
	char id[15];
	int yyyy, mm, dd;
	int correct;
}result;

//함수 선언 
void load_file();
void save_file();
void print_initial_screen();
void join_mem();
void asterisk(char password[]);
int check_phone(char phone[]);
void login();
void search_id();
void search_password();
void print_main_screen(int login_user);
void learning();
void index_test(int login_user);
void name_test(int login_user);
void symbol_test(int login_user);
void print_result(int login_user);
void print_info(int login_user);
void change_name(int login_user);
void change_password(int login_user);
void change_phone(int login_user);
void del_mem(int login_user);
