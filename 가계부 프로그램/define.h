#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <time.h>

//회원 구조체 정의 
typedef struct _user
{
	char name[20];
	char id[20];
	char password[30];
	char phone[15];
	int total; //총액
	
	struct _user *next;
	struct _user *pre;
}USER;

//카테고리 구조체 정의
typedef struct _group
{
	char id[20];
	char name[50];
	float daysum;
	float monthsum;
	float allsum;
	
	struct _group *next;
	struct _group *pre;
}GROUP;

//수입지출 내역 구조체 정의
typedef struct information
{
	char id[20];
	int key;
	int index;
	char group[50];
	int yyyy, mm, dd;
	int sum;
	char content[100];
	
	struct information *next;
	struct information *pre;
}INFO;

//자동출금 구조체 정의
typedef struct autodebit
{
	char id[20];
	int syyyy, smm;
	int eyyyy, emm;
	int dd;
	char group[50];
	int sum;
	char content[100];
	
	struct autodebit *next;
	struct autodebit *pre;
}AUTO;

//메인과 자금관리메뉴 함수 
void load_List(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void save(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void initial_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void asterisk(char password[]);
void login(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
int check_Num(char str[]);
void join_User(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void find_ID(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
void find_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail);
int daysum(int yyyy, int mm, int dd);
void money(char str[]);
void main_menu(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

void manage_Money(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void manage_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void add_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void group_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, GROUP *g_node);
void del_Group(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

int check_day(int mm, int dd);
void info_form(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key, char _group[]);
void sort_History(INFO *i_head, INFO *i_tail, USER *login_User);
void add_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, int _key);

void manage_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void auto_addform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, char _group[]);
void add_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void auto_editform(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, AUTO *a_node);
void edit_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void del_Auto(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void calculate_Total(INFO *i_head, INFO *i_tail, USER *login_User);

//내역 보기 메뉴 함수
void view_History(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void find_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node);
void del_info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User, INFO *i_node);
void calculate_Percent(GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, USER *login_User);
void view_today(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void view_month(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void view_all(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);

//정보 관리 메뉴 함수 
void manage_Info(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_Name(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_Password(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void edit_Phone(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
void del_User(USER *u_head, USER *u_tail, GROUP *g_head, GROUP *g_tail, INFO *i_head, INFO *i_tail, AUTO *a_head, AUTO *a_tail, USER *login_User);
