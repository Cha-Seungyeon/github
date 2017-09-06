#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef struct information {
	char name[20];
	char id[20];
	char pw[20];
	char phone[11]; 
	
	struct information *next;
	struct information *pre;
}info;

typedef struct webtoon {
	int index;
	char name[50];
	float story, style, gag;
	
	struct webtoon *next;
	struct webtoon *pre;
}wbtn;

typedef struct mkreview {
	char name[50];
	char id[20];
	char review[200];
	int yy, mm, dd;
	int story, style, gag;
	
	struct mkreview *next;
	struct mkreview *pre;
}view;

typedef struct rollback {
	int level;
	int del_ck;
	int index;
	char name[30];
	char id[20];
	char review[200];
	int yy, mm, dd;
	float story, style, gag;
	
	struct rollback *next;
	struct rollback *pre;
}rlbk;

typedef struct story {
	char name[50];
	float story;
	
	struct story *next;
	struct story *pre;
}story;

typedef struct style {
	char name[50];
	float style;
	
	struct style *next;
	struct style *pre;
}style;

typedef struct gag {
	char name[50];
	float gag;
	
	struct gag *next;
	struct gag *pre;
}gag;

void login(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int add_mem(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
void search_mem(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
void save(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
int M_load(info *M_head, info *M_tail, int M_count);

void primary(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int edit(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int M_del(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int W_load(wbtn *W_head, wbtn *W_tail, int W_count);
int R_load(view *R_head, view *R_tail, int R_count);
void view_webtoon(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int add_review(char login_id[20], char wbtn_name[30], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int del_review(char login_id[20], char wbtn_name[30], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);

void master(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int add_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int del_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int master_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);
int daysum(int year,int month, int day);
int del_memory(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);

void average(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
void rk_story(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
void rk_style(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);
void rk_gag(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count);

int back(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail);

int add_Mnode(info *M_head, info *M_tail, info *M_mem, int M_count);
int add_Wnode(wbtn *W_head, wbtn *W_tail, wbtn *W_add, int W_count);
int add_Rnode(view *R_head, view *R_tail, view *R_add, int R_count);
void add_Bnode(rlbk *B_head, rlbk *B_tail, rlbk *B_add);

int del_Mnode(info *M_head, info *W_tail, info *tmp, int M_count);
int del_Wnode(wbtn *W_head, wbtn *W_tail, wbtn *tmp, int W_count);
int del_Rnode(view *R_head, view *R_tail, view *tmp, int R_count);
void del_Bnode(rlbk *B_head, rlbk *B_tail, rlbk *tmp);

void blank(char string[20]);
void number(char string[20]);
void blank_number(char string[20]);
void blank_number0(char string[11]);
