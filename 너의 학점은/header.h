#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

typedef struct _user
{
	char id[10];
	char password[30];
	char name[15];
	char phone[15];
	
	struct _user *next;
	struct _user *pre;
}user;

typedef struct _class
{
	char id[10];
	char name[50];
	int day[7];
	int credit;
	int year;
	int semester;
	float grade;
	
	struct _class *next;
	struct _class *pre;
}clas;

typedef struct _note
{
	char id[10];
	char class_name[50];
	int yyyy, mm, dd;
	char writing[10000];
	
	struct _note *next;
	struct _note *pre;
}note;

void load_file();
void save_file();
void initial_menu();
void asterisk(char password[]);
int check_phone(char phone[]);
void join_mem();
void login();
void find_id();
void find_password();
void main_menu(user *login_user);
void apply_class(user *login_user);
void change_and_del(user *login_user);
void change_class(clas *select_class);
void change_class_name(clas *select_class);
void change_class_credit(clas *select_class);
void change_class_day(clas *select_class);
void del_class(clas *select_class);
void my_class(user *login_user);
void my_grade(user *login_user);
void my_info(user *login_user);
