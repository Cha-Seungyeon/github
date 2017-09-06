#include "base.h"

void master(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	wbtn *W_tmp;
	wbtn *tmp;
	
	int select, re, turn;
	
	system("cls");
	
	printf("\n\n관리자모드\n");
	printf("메뉴를 선택하세요.\n");
	printf("1. 현재 웹툰 목록 보기\n"); 
	printf("2. 웹툰 추가\n");
	printf("3. 웹툰 삭제\n");
	printf("4. 리뷰 삭제\n");
	printf("5. 리뷰 메모리 삭제\n");
	printf("6. 롤백\n"); 
	printf("7. 프로그램 종료\n");
	fflush(stdin);
	scanf("%d", &select);
	
	while(select != 1 && select != 2 && select != 3 && select != 4 && select != 5 && select != 6 && select != 7) {
		printf("메뉴에 나온 숫자만 입력하세요.\n");
		printf("다시 입력하세요.\n"); 
		fflush(stdin); 
		scanf("%d", &select);
	}
	
	switch(select) {
		case 1:
			
			system("cls");
			
			printf("\n\n");
			
			for(W_tmp=W_head->next; W_tmp->next!=NULL; W_tmp=W_tmp->next) {
				printf("%d %s\n", W_tmp->index, W_tmp->name);
			}
			
			printf("\n-----------------------------------------\n1. 돌아가기\n");
			fflush(stdin);
			scanf("%d", &turn);
			
			while(turn!=1) {
				printf("이전으로 돌아가려면 1번을 입력해주세요.\n");
				printf("다시 입력하세요.\n");
				fflush(stdin);
				scanf("%d", &turn);
			}
			
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 2:
			W_count = add_wbtn(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail); 
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 3:
			W_count = del_wbtn(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 4:
			R_count = master_wbtn(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 5:
			R_count = del_memory(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 6:
			re = back(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			
			if(re == 1) {
				W_count--;
			}else if(re == 2) {
				W_count++;
			}else if(re == 3) {
				R_count++;
			}else {
				R_count = R_count + re;
			}
			
			master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
			break;
		case 7:
			
			system("cls");
			
			printf("\n\n프로그램을 종료합니다.");
			getch();
			
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			exit(1);
	}
}

int add_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {
	int check=0;
	char name[50];
	
	wbtn *tmp;
	
	system("cls");
	 
	printf("\n\n이름 : ");
	fflush(stdin);
	gets(name);
	
	for(tmp=W_head->next; tmp->next!=NULL; tmp=tmp->next) {
		if(strcmp(tmp->name, name)==0) {
			printf("같은 이름을 가진 웹툰이 이미 존재합니다.\n");
			getch();
			return W_count;
		}else {
			check++;
		}
	}

	if(check==W_count) {

		wbtn *W_add;
		
		W_add = (wbtn *)malloc(sizeof(wbtn));

		W_count = add_Wnode(W_head, W_tail, W_add, W_count);
		
		W_add->index = (W_add->pre->index)+1;
		strcpy(W_add->name, name);
		W_add->story = 0;
		W_add->style = 0;
		W_add->gag = 0;

		rlbk *B_add;
	
		B_add = (rlbk *)malloc(sizeof(rlbk));
	
		B_add->level = 1;
		B_add->del_ck = 0;
		B_add->index = W_add->index;
		strcpy(B_add->name, W_add->name);
		strcpy(B_add->id, "");
		strcpy(B_add->review, "");
		B_add->yy = 0;
		B_add->mm = 0;
		B_add->dd = 0;
		B_add->story = W_add->story;
		B_add->style = W_add->style;
		B_add->gag = W_add->gag;
	
		add_Bnode(B_head, B_tail, B_add);
		
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
		
		return W_count;
	}
	
	
}

int del_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	int select, check=0, i, ck;
	
	wbtn *tmp;
	
	system("cls");
	
	for(tmp = W_head->next; tmp->next != NULL; tmp = tmp->next) {
		printf("%d %s\n", tmp->index, tmp->name);
	}
	
	ck=0;
	
	printf("삭제할 웹툰의 번호를 입력하세요.\n");
	fflush(stdin);
	scanf("%d", &select);
	
	for(i=1; i<=W_count; i++)
	{
		if(select == i)
		{
			ck = 1;
			break;
		}
	}
	
	while(ck != 1) {
	    printf("올바른 숫자를 입력하세요.\n");
	    printf("다시 입력해주세요.\n"); 
	    fflush(stdin);
	    scanf("%d", &select);
	    
		for(i=1; i<=W_count; i++) {
	        if(select == i) {
	            ck = 1;
			    break;
		    }
	    }
	}
	
	
	for(tmp = W_head->next; tmp->next != NULL; tmp = tmp->next) {
		if(tmp->index == select) {
			
			rlbk *B_add;
	
			B_add = (rlbk *)malloc(sizeof(rlbk));
	
			B_add->level = 2;
			B_add->del_ck = 0;
			B_add->index = tmp->index;
			strcpy(B_add->name, tmp->name);
			strcpy(B_add->id, "");
			strcpy(B_add->review, "");
			B_add->yy = 0;
			B_add->mm = 0;
			B_add->dd = 0;
			B_add->story = tmp->story;
			B_add->style = tmp->style;
			B_add->gag = tmp->gag;
		
			add_Bnode(B_head, B_tail, B_add);
			
			W_count = del_Wnode(W_head, W_tail, tmp, W_count);
			
			printf("삭제되었습니다.\n");
			getch();
			
			save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
			
			return W_count;
			
			break;
		}else {
			check++;
		}
	}
	if(check == W_count) {
		
		printf("삭제할 웹툰이 없습니다.\n");
		getch();
		
		return W_count;
		
	}
}

int master_wbtn(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	int check=0;
	int now_wbtn;
	int ck, i, select;
	
	char wbtn_name[30], del_id[20];
	
	wbtn *W_tmp;
	view *R_tmp;
	
	system("cls");
	
	printf("\n\n");
	for(W_tmp=W_head->next; W_tmp->next!=NULL; W_tmp=W_tmp->next) {
		printf("%d %s\n", W_tmp->index, W_tmp->name);
	}
	
	ck = 0;
	
	printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
	printf("삭제할 리뷰가 있는 웹툰의 번호를 입력하세요.\n");
	fflush(stdin);
	scanf("%d", &now_wbtn);
	 
	for(i=1; i<=W_count; i++)
	{
		if(now_wbtn == i)
		{
			ck = 1;
			break;
		}
	}
		
	while(ck != 1) {
	    printf("올바른 숫자를 입력하세요.\n");
	    fflush(stdin);
	    scanf("%d", &now_wbtn);
	    
		for(i=1; i<=W_count; i++) {
	        if(now_wbtn == i) {
	            ck = 1;
			    break;
		    }
	    }
	}
	
	for(W_tmp = W_head->next; W_tmp->next != NULL; W_tmp = W_tmp->next) {
		if(W_tmp->index == now_wbtn) {
				strcpy(wbtn_name, W_tmp->name);
				break;
		}
	}
	
	system("cls");
	
	printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
	
	for(R_tmp=R_head->next; R_tmp->next!=NULL; R_tmp=R_tmp->next) {
		if(strcmp(wbtn_name, R_tmp->name)==0) {
			printf("\nID : %s\n", R_tmp->id);
			printf("%s\n", R_tmp->review);
			printf("날짜 : %d %d %d\n", R_tmp->yy, R_tmp->mm, R_tmp->dd);
		}else {
			check++;
		}
	}
	
	printf("\n\n-------------------------------------------------------------------------------------------------------------------\n");
		
	if(check == R_count) {
		
		printf("리뷰가 없습니다.\n");
		getch();
		
		master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
		
		return R_count;
		
	}else {
		
		printf("1. 리뷰 삭제\n");
		printf("2. 메인화면으로\n");
		fflush(stdin);
		scanf("%d", &select);
		
		while(select != 1 && select != 2)
		{
			printf("메뉴에 나온 숫자만 입력하세요.\n");
			printf("다시 입력하세요.\n"); 
			fflush(stdin); 
			scanf("%d", &select);
		}
		
		switch(select)
		{
			case 1:
				printf("\n리뷰를 삭제할 아이디를 입력하세요.\n");
		
				fflush(stdin);
				gets(del_id);
	
				R_count = del_review(del_id, wbtn_name, M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
	
				return R_count;
				break;
			case 2:
				master(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count, B_head, B_tail);
				
				return R_count;
				break;
		}
	}
}

int daysum(int year,int month, int day)
{
	int i;
	int leapyear=0;
	int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	int sum=0;
	
	for(i=1;i<=year-1;i++) //작년까지 윤년 체크 
	{
		if((i%4==0 && i%100 !=0) || i%400==0)
		{
			leapyear++;
		}
	}
	
	if((year%4==0 && year%100 !=0) || year%400==0) //금년 윤년 체크 
	{
		mon[1]=29;
	}
	
	sum=(366 * leapyear)+(365 * ((year-1)-leapyear)); //일 수 계산(year) 

	for(i=0;i<month;i++) //일 수 계산 (month)
	{
		sum=sum+mon[i];
	}
	
	sum=sum+day; //일 수 계산 (day) 
	
	return sum;
}

int del_memory(info *M_head, info *M_tail, int M_count, wbtn *W_head, wbtn *W_tail, int W_count, view *R_head, view *R_tail, int R_count, rlbk *B_head, rlbk *B_tail) {

	view *tmp;
	
	int del, check=0, del_ck=1;
	int yy, mm, dd;
	
	time_t t;
   	struct tm *pt;
      
   	time(&t);
   	pt = localtime(&t);
      
   	yy = pt->tm_year+1900;
   	mm = pt->tm_mon+1;
   	dd = pt->tm_mday;
	
	system("cls");
	
	printf("\n오늘을 기준으로 작성된 지 며칠이 지난 리뷰를 삭제할지 입력해주세요. [양수]\n");
	fflush(stdin);
	scanf("%d", &del);
	
	while(del < 0) {
		printf("범위에 맞는 수를 입력하세요.\n");
		printf("다시 입력하세요.\n");
		fflush(stdin);
		scanf("%d", &del); 
	}
	
	for(tmp = R_head->next; tmp->next != NULL; tmp = tmp->next) {
		if(daysum(yy, mm, dd) - daysum(tmp->yy, tmp->mm, tmp->dd) >= del) {
		
			rlbk *B_add;
	
			B_add = (rlbk *)malloc(sizeof(rlbk));
	
			B_add->level = 4;
			B_add->del_ck = del_ck;
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
            
            del_ck++;
            check = 1;
         }
    }
      
    if(check == 0) {
		
		printf("삭제할 리뷰가 없습니다.\n");
		getch();
        
		return R_count; 
		
    }else {
    	
		printf("삭제되었습니다.\n");
    	getch();
        
		save(M_head, M_tail, M_count, W_head, W_tail, W_count, R_head, R_tail, R_count);
        
		return R_count; 
		
    }
    
}
