#include "base.h"

int main() {
	int M_count=0, W_count=0, R_count=0;
	int select;
	
	info *M_head;
	info *M_tail;
	
	M_head = (info *)malloc(sizeof(info));
	M_tail = (info *)malloc(sizeof(info));
	
	M_head->next = M_tail;
	M_tail->pre = M_head;
	M_tail->next = NULL;
	M_head->pre = NULL;
	
	M_count = M_load(M_head, M_tail, M_count);
	
	wbtn *W_head;
	wbtn *W_tail;
	
	W_head = (wbtn *)malloc(sizeof(wbtn));
	W_tail = (wbtn *)malloc(sizeof(wbtn));
	
	W_head->next = W_tail;
	W_tail->pre = W_head;
	W_head->pre = NULL;
	W_tail->next = NULL;
	
	W_head->index = 0;
	
	W_count = W_load(W_head, W_tail, W_count);
	
	view *R_head;
	view *R_tail;
	
	R_head = (view *)malloc(sizeof(view));
	R_tail = (view *)malloc(sizeof(view));
	
	R_head->next = R_tail;
	R_tail->pre = R_head;
	R_head->pre = NULL;
	R_tail->next = NULL;
	
	R_count = R_load(R_head, R_tail, R_count);
	
	rlbk *B_head;
	rlbk *B_tail;
	
	B_head = (rlbk *)malloc(sizeof(rlbk));
	B_tail = (rlbk *)malloc(sizeof(rlbk));
	
	B_head->next = B_tail;
	B_tail->pre = B_head;
	B_head->pre = NULL;
	B_tail->next = NULL;
	
	system("cls");
	
	printf("\n\n메뉴를 선택하세요.\n"); 
	printf("1. 로그인\n");
	printf("2. 회원가입\n");
	printf("3. 아이디/비밀번호 찾기\n");
	printf("4. 프로그램 종료\n"); 
	fflush(stdin);
	scanf("%d", &select);
		
	while(select != 1 && select != 2 && select != 3 && select != 4) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n"); 
		fflush(stdin);
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
			login(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;	
		case 2:
			M_count=add_mem(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			main();
			break;
		case 3:
			search_mem(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			break;
		case 4:
			
			system("cls");
			
			printf("\n\n프로그램을 종료합니다.");
			getch();
			
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			exit(1);
	}
	
	return 0;
}

void login(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	info *tmp;
	char login_id[20];
	char login_pw[20];
	int check=0;
	
	system("cls");
	
	printf("\n\n아이디 : ");
	fflush(stdin);
	gets(login_id);

	printf("비밀번호 : ");
	fflush(stdin);
	gets(login_pw);
	
	if(strcmp(login_id, "imsgyn")==0) {
		if(strcmp(login_pw, "tmddus2886!")==0) {
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			return;
		}else {
			printf("비밀번호가 일치하지않습니다.\n");
			getch();
			
			main();
			return;
		}
	}else {
		for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
			if(strcmp(tmp->id, login_id)==0) {
				if(strcmp(tmp->pw, login_pw)==0) {
					primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
					break;
				}else {
					printf("비밀번호가 일치하지않습니다.\n");
					getch();
					
					main();
					break;
				}
			}else {
				check++;
			}
		}
		if(check==M_count) {
			printf("아이디가 존재하지않습니다.\n");
			getch();
			main();
		}
	}
}

int add_mem(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {

	char id[20];
	
	info *tmp;
	info *M_mem;
	M_mem = (info *)malloc(sizeof(info));
	
	system("cls");
	
	printf("\n\n이름 : ");
	fflush(stdin);
	gets(M_mem->name);
	
	blank_number(M_mem->name);
	
	printf("아이디 : ");
	fflush(stdin);
	gets(id);
	
	blank(id);
	
	if(strcmp(id ,"imsgyn") == 0) {
		printf("같은 아이디가 존재합니다.\n");
		printf("다시 입력해주세요.\n");
		
		fflush(stdin);
		gets(id);
			
		blank(id);
	}
	
	for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
		if(strcmp(tmp->id, id)==0) {
			printf("같은 아이디가 존재합니다.\n");
			printf("다시 입력해주세요.\n");
			
			fflush(stdin);
			gets(id);
			
			blank(id);
			
			continue;	
		}
	}
	
	strcpy(M_mem->id, id);
	
	printf("비밀번호 : ");
	fflush(stdin);
	gets(M_mem->pw);
	
	blank(M_mem->pw);
	
	printf("핸드폰 번호(숫자만) : ");
	fflush(stdin);
	gets(M_mem->phone);
	
	blank_number0(M_mem->phone);
	
	M_count = add_Mnode(M_head, M_tail, M_mem, M_count);
	
	save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
	
	return M_count;
}

void search_mem(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {

	int select;
	int check=0;
	char phone[11];
	char id[20];
	char new_pw[20];
	info *tmp;
	
	system("cls");
	
	printf("\n\n1. 아이디 찾기\n");
	printf("2. 비밀번호 찾기\n");
	fflush(stdin);
	scanf("%d", &select);
	
	while(select != 1 && select != 2) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n");
		fflush(stdin);
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
			check=0;
			printf("\n\n핸드폰 번호를 입력하세요 : ");
			fflush(stdin);
			gets(phone);
			
			for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
				if(strcmp(tmp->phone, phone)==0) {
					printf("아이디 : %s", tmp->id);
					getch();
					
					main();
					break;
				}else {
					check++;
				}
			}
			if(check==M_count) {
				printf("아이디가 존재하지않습니다.\n");
				getch();
				main();
			}
			break;
		case 2:
			check=0;
			printf("\n\n아이디를 입력하세요 : ");
			fflush(stdin);
			gets(id);
			
			for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
				if(strcmp(tmp->id, id)==0) {
					printf("핸드폰번호를 입력하세요 : ");
					fflush(stdin);
					gets(phone);
					
					if(strcmp(tmp->phone, phone)==0) {
						printf("새로운 비밀번호를 입력하세요 : ");
						
						fflush(stdin);
			            gets(new_pw);
			            
			            blank(new_pw);
						strcpy(tmp->pw, new_pw);
						
						save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
						main();
					}else {
						printf("핸드폰번호가 일치하지않습니다.\n");
						getch();
						
						main();
					}
				}else {
					check++; 
				}
			}
			
			if(check == M_count) {
				printf("아이디가 존재하지않습니다.\n");
				getch();
				
				main(); 
			}
			break;
	}
}

void save(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {
	
	int i=1;

	FILE *fp;
	FILE *wp;
	FILE *rp;
	
	info *M_tmp;
	wbtn *W_tmp;
	view *R_tmp;
	
	if(M_count>0) {
		fp=fopen("member.txt","w");
		for(M_tmp=M_head->next; M_tmp->next!=NULL; M_tmp=M_tmp->next) {
			fprintf(fp,"%s %s %s %s\n",M_tmp->name, M_tmp->id, M_tmp->pw, M_tmp->phone);
		}
		fclose(fp);
	}else {
		fp=fopen("member.txt","w");
		fclose(fp);
	}
	
	if(W_count>0) {
		wp=fopen("webtoon.txt", "w");
		for(W_tmp=W_head->next; W_tmp->next!=NULL; W_tmp=W_tmp->next) {
			W_tmp->index = i;
			fprintf(wp, "%d\n", W_tmp->index);
			fprintf(wp, "%s\n%f %f %f\n", W_tmp->name, W_tmp->story, W_tmp->style, W_tmp->gag);
			i++;
		}
		fclose(wp);
	}else {
		wp=fopen("webtoon.txt", "w");
		fclose(wp);
	}
	
	if(R_count>0) {
		rp = fopen("review.txt", "w");
			for(R_tmp=R_head->next; R_tmp->next!=NULL; R_tmp=R_tmp->next) {
				fprintf(rp, "%s\n%s\n%s\n%d %d %d\n%d %d %d\n", R_tmp->name, R_tmp->id, R_tmp->review, R_tmp->yy, R_tmp->mm, R_tmp->dd, R_tmp->story, R_tmp->style, R_tmp->gag);
			}
		fclose(rp);
	}else {
		rp = fopen("review.txt", "w");
		fclose(rp);
	}
}

int M_load(info *M_head, info *M_tail, int M_count) {

	FILE *fp = fopen("member.txt", "r");
	
	while(!feof(fp)) {
		info *M_mem;
		M_mem = (info *)malloc(sizeof(info));
		strcpy(M_mem->name, "");
		strcpy(M_mem->id, "");
		strcpy(M_mem->pw, "");
		strcpy(M_mem->phone, "");
		fscanf(fp, "%s %s %s %s\n", M_mem->name, M_mem->id, M_mem->pw, M_mem->phone);
		
		M_count = add_Mnode(M_head, M_tail, M_mem, M_count);

		if(strcmp(M_mem->name, "") == 0) {
			M_mem->pre->next = M_mem->next;
			M_mem->next->pre = M_mem->pre;
			
			M_count--;
		}
	}
	fclose(fp);
	return M_count;
}

void primary(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail)
{
	int select;
	int back;
	
	wbtn *W_tmp;
	
	system("cls");
	
	printf("\n\n메뉴를 선택하세요.\n");
	printf("1. 웹툰 리뷰 보기/남기기\n");
	printf("2. 랭킹 보기 (스토리)\n");
	printf("3. 랭킹 보기 (그림체)\n");
	printf("4. 랭킹 보기 (개그)\n");
	printf("5. 내 정보 관리\n");
	printf("6. 프로그램 종료\n"); 
	fflush(stdin);
	scanf("%d", &select);
	
	while(select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n");
		fflush(stdin);
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
			view_webtoon(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 2:
			average(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			rk_story(W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			printf("\n1. 돌아가기\n");
			fflush(stdin);
			scanf("%d", &back);
			
			while(back!=1) {
				printf("이전으로 돌아가려면 1번을 입력해주세요.\n");
				printf("다시 입력하세요.\n");
				fflush(stdin);
				scanf("%d", &back);
			}
			
			primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 3:
			average(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			rk_style(W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			printf("\n1. 돌아가기\n");
			fflush(stdin);
			scanf("%d", &back);
			
			while(back!=1) {
				printf("이전으로 돌아가려면 1번을 입력해주세요.\n");
				printf("다시 입력하세요.\n");
				fflush(stdin);
				scanf("%d", &back);
			}
			
			primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 4:
			average(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			rk_gag(W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			printf("\n1. 돌아가기\n");
			fflush(stdin);
			scanf("%d", &back);
			
			while(back!=1) {
				printf("이전으로 돌아가려면 1번을 입력해주세요.\n");
				printf("다시 입력하세요.\n");
				fflush(stdin);
				scanf("%d", &back);
			}
			
			primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 5:
			W_count = edit(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 6:
			
			system("cls");
			
			printf("\n\n프로그램을 종료합니다.");
			getch();
			 
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			exit(1); 
	}
}

int edit(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	int select;
	char new_pw[20];
	char new_phone[20];
	info *tmp;
	
	system("cls");
	
	printf("\n\n<내 정보>\n");
	for(tmp = M_head->next; tmp->next != NULL; tmp = tmp->next) {
		if(strcmp(login_id, tmp->id)==0) {
			printf("이름 : %s\n", tmp->name);
			printf("ID : %s\n", tmp->id);
			printf("핸드폰 번호 : %s\n", tmp->phone);
			
			break; 
		}
	}
	
	printf("\n메뉴를 선택하세요.\n");
	printf("1. 비밀번호 수정\n");
	printf("2. 개인정보 수정\n");
	printf("3. 회원탈퇴\n");
	printf("4. 메인화면으로\n"); 
	fflush(stdin);
	scanf("%d", &select);
	
	while(select != 1 && select != 2 && select != 3 && select != 4) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n");
		fflush(stdin); 
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
		    printf("\n\n 수정할 비밀번호를 입력하세요.\n");
	        fflush(stdin);
	        gets(new_pw);
	        
	        blank(new_pw);
	        
			for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
				if(strcmp(tmp->id, login_id)==0) {
					strcpy(tmp->pw, new_pw);
					save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
					
					primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
					
					return M_count;
					
					break;
				}
			}
			
			break;
		case 2:
			printf("\n\n수정할 핸드폰번호를 입력하세요.\n");
	        fflush(stdin);
	        gets(new_phone);
	        
	        blank_number0(new_phone);

			for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
				if(strcmp(tmp->id, login_id)==0) {
					strcpy(tmp->phone, new_phone);
					save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
					primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
					return M_count;
					break;
				}
			}
			break;
		case 3:
			M_count=M_del(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			return M_count;
			break;
		case 4:
			primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			return M_count;
			break;
	}
}

int M_del(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	int select;
	info *tmp;
	
	system("cls");
	
	printf("\n\n회원탈퇴 하시겠습니까?\n");
	printf("1. Yes 2. No\n");
	fflush(stdin);
	scanf("%d", &select);
	
	while(select != 1 && select != 2) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n");
		fflush(stdin); 
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
			for(tmp=M_head->next; tmp->next!=NULL; tmp=tmp->next) {
				if(strcmp(tmp->id, login_id)==0) {
					M_count = del_Mnode(M_head, M_tail, tmp, M_count);
				}
			}
			
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			printf("회원탈퇴 되었습니다.\n");
			getch();
			
			main();
			return M_count;
			
			break;
		case 2:
			primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			
			return M_count;
			break;
	}
}

int W_load(wbtn *W_head, wbtn *W_tail, int W_count) {

	FILE *wp = fopen("webtoon.txt", "r");
	
	while(!feof(wp)) {
		wbtn *W_add;
		W_add = (wbtn *)malloc(sizeof(wbtn));
		W_add->index = 0;
		strcpy(W_add->name, "");
		
		fscanf(wp, "%d\n", &W_add->index);
		fgets(W_add->name, sizeof(W_add->name), wp);
		W_add->name[strlen(W_add->name) - 1] = '\0';
		fscanf(wp, "%f %f %f\n", &W_add->story, &W_add->style, &W_add->gag);
		
		
		W_count = add_Wnode(W_head, W_tail, W_add, W_count);
		
		W_add->story = 0;
		W_add->style = 0;
		W_add->gag = 0;

		if(strcmp(W_add->name, "")==0) {
			W_add->pre->next = W_add->next;
			W_add->next->pre = W_add->pre;
			W_count--;
			break;
		}
	}

	fclose(wp);
	
	return W_count;
}

int R_load(view *R_head, view *R_tail, int R_count) {
	FILE *rp = fopen("review.txt", "r");
	
	while(!feof(rp)) {
		view *R_add;
		
		R_add = (view *)malloc(sizeof(view));
		
		strcpy(R_add->name, "");
		strcpy(R_add->id, "");
		strcpy(R_add->review, "");
		R_add->yy = 0;
		R_add->mm = 0;
		R_add->dd = 0;
		R_add->story = 0;
		R_add->style = 0;
		R_add->gag = 0;
		
		fgets(R_add->name, sizeof(R_add->name), rp);
		R_add->name[strlen(R_add->name) - 1] = '\0';
		fscanf(rp, "%s\n", R_add->id);
		fgets(R_add->review, sizeof(R_add->review), rp);
		R_add->review[strlen(R_add->review) - 1] = '\0';
		fscanf(rp, "%d %d %d\n%d %d %d\n", &R_add->yy, &R_add->mm, &R_add->dd, &R_add->story, &R_add->style, &R_add->gag);
		
		R_count = add_Rnode(R_head, R_tail, R_add, R_count);
		
		if(strcmp(R_add->name, "")==0) {
			R_add->pre->next = R_add->next;
			R_add->next->pre = R_add->pre;
			R_count--;
			break;
		}
	}
	
	fclose(rp);
	
	return R_count;
}

void view_webtoon(char login_id[20], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	wbtn *W_tmp;
	view *R_tmp;
	
	int now_wbtn, select, ck, i;
	char wbtn_name[30];
	
	system("cls");
	
	if(W_count > 0) {
		
		printf("\n\n");
		
		for(W_tmp=W_head->next; W_tmp->next!=NULL; W_tmp=W_tmp->next) {
			printf("%d %s\n", W_tmp->index, W_tmp->name);
		}
		
		ck = 0;
		
		printf("\n\n");
		printf("--------------------------------------------------------\n리뷰를 보거나 남길 웹툰 번호를 입력하세요.\n");
		fflush(stdin);
		scanf("%d", &now_wbtn);
		
		for(i=1; i<=W_count; i++) {
	        if(now_wbtn == i) {
	            ck=1;
				break;
		    }
	    }
		
	    while(ck != 1) {
	    	printf("올바른 숫자를 입력해주세요.\n");
			printf("다시 입력하세요.\n"); 
	        fflush(stdin);
	        scanf("%d", &now_wbtn);
	    
	    	for(i=1; i<=W_count; i++) {
	            if(now_wbtn == i) {
	                ck=1;
			        break;
		        }
	        }
	    }
		
		for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) { //index값 비교해서 웹툰 이름 가지고오기 
			if(W_tmp->index == now_wbtn) {
				strcpy(wbtn_name, W_tmp->name);
				break;
			}
		}
		
		system("cls");
		
		printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
		for(R_tmp=R_head->next; R_tmp->next!=NULL; R_tmp=R_tmp->next) {
			if(strcmp(wbtn_name, R_tmp->name)==0) {
				printf("\n\nID : %s\n", R_tmp->id);
				printf("%s\n", R_tmp->review);
				printf("날짜 : %d %d %d\n",R_tmp->yy, R_tmp->mm, R_tmp->dd);
			}
		}
		printf( "\n\n-------------------------------------------------------------------------------------------------------------------\n");
		
		printf("\n메뉴를 선택하세요.\n");
		printf("1. 메인화면으로\n");
		printf("2. 리뷰 쓰기\n");
		printf("3. 내 리뷰 삭제하기\n");
		fflush(stdin);
		scanf("%d", &select);
		
		while(select != 1 && select != 2 && select != 3) {
			printf("메뉴에 나온 숫자만 입력하세요.\n");
			printf("다시 입력하세요.\n");
			fflush(stdin);
			scanf("%d", &select);
		}
		
		switch(select) {
			case 1:
				primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				break;
			case 2:
				R_count = add_review(login_id, wbtn_name, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				break;
			case 3:
				R_count = del_review(login_id, wbtn_name, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				break;
		}
	}else {
		printf("등록된 웹툰이 없습니다.\n");
		
		getch();
		
		primary(login_id, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail); 
	}	
}

int add_review(char login_id[20], char wbtn_name[30], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	int check=0;
	
	view *tmp;
	
	system("cls");
	
	for(tmp=R_head->next; tmp->next!=NULL; tmp=tmp->next) {
		if(strcmp(wbtn_name, tmp->name)==0 && strcmp(login_id, tmp->id)==0) {
			printf("\n이미 작성한 리뷰가 있습니다. 삭제하고 다시 작성해주세요.\n");
			getch();
			return R_count;
		}else {
			check++;
		}
	}
	
	if(check == R_count) {
		view *R_add;
		
		R_add = (view *)malloc(sizeof(view));
		
		strcpy(R_add->name, wbtn_name);
		strcpy(R_add->id, login_id);
		
		system("cls");
		
		printf("\n리뷰를 작성해주세요.\n");
		fflush(stdin);
	    gets(R_add->review);
		
		time_t t;
		struct tm *pt;
		
		time(&t);
		pt = localtime(&t);
		
		R_add->yy = pt->tm_year+1900;
		R_add->mm = pt->tm_mon+1;
		R_add->dd = pt->tm_mday;
		
		printf("스토리 평점을 입력해주세요.(1~5, 정수)\n");
		fflush(stdin);
		scanf("%d", &R_add->story);
		
		while(R_add->story != 1 && R_add->story != 2 && R_add->story != 3 && R_add->story != 4 && R_add->story != 5) {
			printf("정해진 숫자만 입력하세요. [1~5 정수] \n"); 
			printf("다시 입력하세요.\n");
			fflush(stdin);
			scanf("%d", &R_add->story);
		}
		
		printf("그림체 평점을 입력해주세요.(1~5, 정수)\n");
		fflush(stdin);
		scanf("%d", &R_add->style);
		
		while(R_add->style != 1 && R_add->style != 2 && R_add->style != 3 && R_add->style != 4 && R_add->style != 5) {
			printf("정해진 숫자만 입력하세요. [1~5 정수] \n"); 
			printf("다시 입력하세요.\n");
			fflush(stdin);
			scanf("%d", &R_add->style);
		}
		
		printf("개그 평점을 입력해주세요.(1~5, 정수)\n");
		fflush(stdin);
		scanf("%d", &R_add->gag);
		
		while(R_add->gag != 1 && R_add->gag != 2 && R_add->gag != 3 && R_add->gag != 4 && R_add->gag != 5) {
			printf("정해진 숫자만 입력하세요. [1~5 정수] \n"); 
			printf("다시 입력하세요.\n");
			fflush(stdin);
			scanf("%d", &R_add->gag);
		}
		
		R_count = add_Rnode(R_head, R_tail, R_add, R_count);
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		return R_count;
	}
}

int del_review(char login_id[20], char wbtn_name[30], info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {
	view *tmp;
	int check=0;
	
	for(tmp=R_head->next; tmp->next!=NULL; tmp=tmp->next) {
		if(strcmp(tmp->name, wbtn_name)==0 && strcmp(tmp->id, login_id)==0) {
			
			rlbk *B_add;
	
			B_add = (rlbk *)malloc(sizeof(rlbk));
	
			B_add->level = 3;
			B_add->del_ck = 0;
			B_add->index = 0;
			strcpy(B_add->name, tmp->name);
			strcpy(B_add->id, tmp->id);
			strcpy(B_add->review, tmp->review);
			B_add->yy = tmp->yy;
			B_add->mm = tmp->mm;
			B_add->dd = tmp->dd;
			B_add->story = tmp->story;
			B_add->style = tmp->style;
			B_add->gag = tmp->gag;
		
			add_Bnode(B_head, B_tail, B_add);
			
			R_count = del_Rnode(R_head, R_tail, tmp, R_count);
			
			printf("삭제되었습니다.\n");
			getch();
			
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);

			return R_count;
		}else {
			check++;
		}
	}
	
	if(check == R_count) {
		printf("삭제할 리뷰가 없습니다.\n");
		
		getch();
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		return R_count;
	}
}

void average(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {
	wbtn *W_tmp;
	view *R_tmp;
	
	int count;
	
	
	for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
		count = 0;
		
		W_tmp->story = 0;
		W_tmp->style = 0;
		W_tmp->gag = 0;
		
		for(R_tmp = R_head->next; R_tmp->next != NULL; R_tmp = R_tmp->next) {
			
			if(strcmp(W_tmp->name, R_tmp->name) == 0) {
				W_tmp->story = W_tmp->story + R_tmp->story;
				W_tmp->style = W_tmp->style + R_tmp->style;
				W_tmp->gag = W_tmp->gag + R_tmp->gag;
				count ++;
			}
		}
		
		if(count > 0) {
			W_tmp->story = W_tmp->story/(float)count;
			W_tmp->style = W_tmp->style/(float)count;
			W_tmp->gag = W_tmp->gag/(float)count;
		}
	}
	
	save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
}

void rk_story(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {
	wbtn *W_tmp;
	story *K_tmp;
	story *K_tmp1;
	
	int i;
	
	story *K_head;
	story *K_tail;
	
	K_head = (story *)malloc(sizeof(story));
	K_tail = (story *)malloc(sizeof(story));
	
	K_head->next = K_tail;
	K_tail->pre = K_head;
	K_tail->next = NULL;
	K_head->pre = NULL;
	
	for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
		if(W_tmp->story > 0) {
			story *K_add;
			
			K_add = (story *)malloc(sizeof(story));
			
			K_tail->pre->next = K_add;
			K_add->pre = K_tail->pre;
			K_tail->pre=K_add;
			K_add->next=K_tail;
			
			K_add->story = W_tmp->story;
			strcpy(K_add->name, W_tmp->name);
		}
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		for(K_tmp1 = K_tmp; K_tmp1->next != NULL; K_tmp1 = K_tmp1->next) {
			if(K_tmp1->story > K_tmp->story) {
				K_tmp->pre->next = K_tmp1;
				K_tmp1->next->pre = K_tmp;
				K_tmp->next = K_tmp1->next;
				K_tmp1->pre = K_tmp->pre;
				K_tmp1->next = K_tmp1->next->pre;
				K_tmp->pre = K_tmp->pre->next;
			}
		}
	}
	system("cls");
	
	printf("\n\n스토리 랭킹-------------------------------\n\n"); 
	
	i=1;
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		printf("%d위 : %s [%.2f 점]\n",  i, K_tmp->name, K_tmp->story);
		i++;
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		free(K_tmp);
	}
	
	printf("\n\n------------------------------------------\n");
}

void rk_style(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {
	wbtn *W_tmp;
	style *K_tmp;
	style *K_tmp1;
	
	int i;
	
	style *K_head;
	style *K_tail;
	
	K_head = (style *)malloc(sizeof(style));
	K_tail = (style *)malloc(sizeof(style));
	
	K_head->next = K_tail;
	K_tail->pre = K_head;
	K_tail->next = NULL;
	K_head->pre = NULL;
	
	for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
		if(W_tmp->style > 0) {
			style *K_add;
			
			K_add = (style *)malloc(sizeof(style));
			
			K_tail->pre->next = K_add;
			K_add->pre = K_tail->pre;
			K_tail->pre=K_add;
			K_add->next=K_tail;
			
			K_add->style = W_tmp->style;
			strcpy(K_add->name, W_tmp->name);
		}
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		for(K_tmp1 = K_tmp; K_tmp1->next != NULL; K_tmp1 = K_tmp1->next) {
			if(K_tmp1->style > K_tmp->style) {
				K_tmp->pre->next = K_tmp1;
				K_tmp1->next->pre = K_tmp;
				K_tmp->next = K_tmp1->next;
				K_tmp1->pre = K_tmp->pre;
				K_tmp1->next = K_tmp1->next->pre;
				K_tmp->pre = K_tmp->pre->next;
			}
		}
	}
	
	system("cls");
	
	printf("\n\n그림체 랭킹-------------------------------\n\n"); 
	
	i=1;
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		printf("%d위 : %s [%.2f 점]\n",  i, K_tmp->name, K_tmp->style);
		i++;
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		free(K_tmp);
	}
	
	printf("\n\n------------------------------------------\n");
}

void rk_gag(wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count) {
	wbtn *W_tmp;
	gag *K_tmp;
	gag *K_tmp1;
	
	int i;
	
	gag *K_head;
	gag *K_tail;
	
	K_head = (gag *)malloc(sizeof(gag));
	K_tail = (gag *)malloc(sizeof(gag));
	
	K_head->next = K_tail;
	K_tail->pre = K_head;
	K_tail->next = NULL;
	K_head->pre = NULL;
	
	for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
		if(W_tmp->gag > 0) {
			gag *K_add;
			
			K_add = (gag *)malloc(sizeof(gag));
			
			K_tail->pre->next = K_add;
			K_add->pre = K_tail->pre;
			K_tail->pre=K_add;
			K_add->next=K_tail;
			
			K_add->gag = W_tmp->gag;
			strcpy(K_add->name, W_tmp->name);
		}
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		for(K_tmp1 = K_tmp; K_tmp1->next != NULL; K_tmp1 = K_tmp1->next) {
			if(K_tmp1->gag > K_tmp->gag) {
				K_tmp->pre->next = K_tmp1;
				K_tmp1->next->pre = K_tmp;
				K_tmp->next = K_tmp1->next;
				K_tmp1->pre = K_tmp->pre;
				K_tmp1->next = K_tmp1->next->pre;
				K_tmp->pre = K_tmp->pre->next;
			}
		}
	}
	
	system("cls");
	
	printf("\n\n개그 랭킹-------------------------------\n\n"); 
	
	i=1;
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		printf("%d위 : %s [%.2f 점]\n",  i, K_tmp->name, K_tmp->gag);
		i++;
	}
	
	for(K_tmp = K_head->next; K_tmp->next != NULL; K_tmp = K_tmp->next) {
		free(K_tmp);
	}
	
	printf("\n\n------------------------------------------\n");
}

int back(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {
	rlbk *work = B_tail->pre;
	int count=0;

	wbtn *W_tmp;
	rlbk *B_tmp;
	
	system("cls");
	
	if(work->level == 1) { //웹툰추가에 대한 롤백 
	
		printf("새로 추가된 웹툰을 삭제합니다.\n"); 
	
		for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
			if(strcmp(work->name, W_tmp->name) == 0) {
				del_Wnode(W_head, W_tail, W_tmp, W_count);
			}
		}
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		del_Bnode(B_head, B_tail, B_tail->pre);
		
		printf("\n\n롤백 완료\n");
		getch(); 
		
		return 1;
		
	}else if(work->level == 2) { //웹툰삭제에 대한 롤백 
		
		printf("삭제된 웹툰을 다시 추가합니다.\n"); 
		
		wbtn *W_add;
		
		W_add = (wbtn *)malloc(sizeof(wbtn));
		
		W_count = add_Wnode(W_head, W_tail, W_add, W_count);
		
		W_add->index = work->index;
		strcpy(W_add->name, work->name);
		W_add->story = work->story;
		W_add->style = work->style;
		W_add->gag = work->gag;
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		del_Bnode(B_head, B_tail, B_tail->pre);
		
		printf("\n\n롤백 완료\n");
		getch(); 
		
		return 2;
		
	}else if(work->level == 3) { //리뷰 삭제에 대한 롤백 
	
		printf("삭제된 리뷰를 다시 추가합니다.\n"); 
	
		view *R_add;
		
		R_add = (view *)malloc(sizeof(view));
		
		R_count = add_Rnode(R_head, R_tail, R_add, R_count);
		
		strcpy(R_add->name, work->name);
		strcpy(R_add->id, work->id);
		strcpy(R_add->review, work->review);
		R_add->yy = work->yy;
		R_add->mm = work->mm;
		R_add->dd = work->dd;
		R_add->story = work->story;
		R_add->style = work->style;
		R_add->gag = work->gag;
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		del_Bnode(B_head, B_tail, B_tail->pre);
		
		printf("\n\n롤백 완료\n");
		getch(); 
		
		return 3;
	
	}else if(work->level == 4) { //메모리 삭제에 대한 롤백 
		
		printf("삭제된 리뷰들을 추가합니다.\n"); 
		
		view *R_add;
		
		for(B_tmp = B_tail->pre; B_tmp->del_ck != 0; B_tmp = B_tmp->pre) {
		
			view *R_add;
			
			R_add = (view *)malloc(sizeof(view));
		
			R_count = add_Rnode(R_head, R_tail, R_add, R_count);
			
			strcpy(R_add->name, B_tmp->name);
			strcpy(R_add->id, B_tmp->id);
			strcpy(R_add->review, B_tmp->review);
			R_add->yy = B_tmp->yy;
			R_add->mm = B_tmp->mm;
			R_add->dd = B_tmp->dd;
			R_add->story = B_tmp->story;
			R_add->style = B_tmp->style;
			R_add->gag = B_tmp->gag;
			
			count++;
		}
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		for(B_tmp = B_tail->pre; B_tmp->pre->del_ck != 0; B_tmp = B_tmp->pre) {
			del_Bnode(B_head, B_tail, B_tail->pre);
		}
		
		printf("\n\n롤백완료");
		getch(); 
		
		return count;
	}
}

int add_Mnode(info *M_head, info *M_tail, info *M_mem, int M_count)
{
	M_tail->pre->next = M_mem;
	M_mem->pre = M_tail->pre;
	M_tail->pre = M_mem;
	M_mem->next = M_tail;
	
	return ++M_count;
}

int add_Wnode(wbtn *W_head, wbtn *W_tail, wbtn *W_add, int W_count)
{
	W_tail->pre->next = W_add;
	W_add->pre = W_tail->pre;
	W_tail->pre = W_add;
	W_add->next = W_tail;
	
	return ++W_count;
}

int add_Rnode(view *R_head, view *R_tail, view *R_add, int R_count)
{
	R_tail->pre->next = R_add;
	R_add->pre = R_tail->pre;
	R_tail->pre = R_add;
	R_add->next = R_tail;
	
	return ++R_count;
}

void add_Bnode(rlbk *B_head, rlbk *B_tail, rlbk *B_add)
{
	B_tail->pre->next = B_add;
	B_add->pre = B_tail->pre;
	B_tail->pre = B_add;
	B_add->next = B_tail;
}

int del_Mnode(info *M_head, info *M_tail, info *tmp, int M_count)
{
	tmp->pre->next = tmp->next;
	tmp->next->pre = tmp->pre;
	free(tmp);
	
	return --M_count;
}

int del_Wnode(wbtn *W_head, wbtn *W_tail, wbtn *tmp, int W_count)
{
	tmp->pre->next = tmp->next;
	tmp->next->pre = tmp->pre;
	free(tmp);
	
	return --W_count;
}

int del_Rnode(view *R_head, view *R_tail, view *tmp, int R_count)
{
	tmp->pre->next = tmp->next;
	tmp->next->pre = tmp->pre;
	free(tmp);
	
	return --R_count;
}

void del_Bnode(rlbk *B_head, rlbk *B_tail, rlbk *tmp)
{
	tmp->pre->next = tmp->next;
	tmp->next->pre = tmp->pre;
	free(tmp);
}

void blank(char string[20])
{
	int i=0;
	int ck=0;
	
	while(ck != 1)
	{
		if(string[i] == '\0')
		{
			printf("값을 입력하세요.\n");
			
			ck=0;
			fflush(stdin);
			gets(string);
		}else {
			ck = 1;
		}
	}
	
	while(string[i] != '\0') {
	
    	if(string[i] == ' ')
    	{
			printf("공백 없이 입력해주세요.\n");
            printf("다시 입력하세요.\n");
            
            i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue;
        }
		
        i++;
	}
}

void number(char string[20])
{
	int i=0;
	int ck=0;
	
	while(ck != 1)
	{
		if(string[i] == '\0')
		{
			printf("값을 입력하세요.\n");
			ck=0;
			fflush(stdin);
			gets(string);
		}else {
			ck = 1;
		}
	}
	
	while(string[i] != '\0') {
		
		if('0' <= string[i] && '9' >= string[i])
		{
			printf("숫자 없이 입력해주세요.\n");
			printf("다시 입력하세요.\n");
			
			i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue; 
		}
		
		i++;
	}
}

void blank_number(char string[20])
{
	int i=0;
	int ck=0;
	
	while(ck != 1)
	{
		if(string[i] == '\0')
		{
			printf("값을 입력하세요.\n");
			ck=0;
			fflush(stdin);
			gets(string);
		}else {
			ck = 1;
		}
	}
	
	while(string[i] != '\0')
	{
		if(string[i] == ' ')
    	{
			printf("공백 없이 입력해주세요.\n");
            printf("다시 입력하세요.\n");
            
            i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue;
        }else if('0' <= string[i] && '9' >= string[i]) {
			printf("숫자 없이 입력해주세요.\n");
			printf("다시 입력하세요.\n");
			
			i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue; 
		}
		
		i++;
	}
}

void blank_number0(char string[11])
{
	int i=0;
	int ck=0;
	
	while(ck != 1)
	{
		if(string[i] == '\0')
		{
			printf("값을 입력하세요.\n");
			ck=0;
			fflush(stdin);
			gets(string);
		}else {
			ck = 1;
		}
	}
	
	while(string[i] != '\0')
	{
		if(string[i] == ' ')
		{
			printf("공백 없이 입력해주세요.\n");
            printf("다시 입력하세요.\n");
            
			i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue;
        }else if(string[i] >= '0' && string[i] <= '9') {

		}else {
			printf("숫자만 입력해주세요.\n");
			printf("다시 입력하세요.\n");
			
			i=0;
			fflush(stdin);
			gets(string);
			
			ck = 0;
			
			while(ck != 1)
			{
				if(string[i] == '\0')
				{
					printf("값을 입력하세요.\n");
					
					ck = 0;
					fflush(stdin);
					gets(string);
				}else {
					ck = 1;
				}
			}
			
			continue; 
		}
		
		i++;
	}		
}
