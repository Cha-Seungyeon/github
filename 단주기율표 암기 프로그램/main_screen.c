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
		
		printf("\n%14s ��, �� �� �� �� �� !\n\n", member_data[login_user].name);
		printf("==========================================\n\n");
		printf("\t1. �� �� �� ��\n\n");
		printf("\t2. �� �� �� ȣ T E S T\n\n");
		printf("\t3. �� �� �� ȣ T E S T\n\n");
		printf("\t4. �� �� �� �� T E S T\n\n");
		printf("\t5. T E S T �� ��  �� ��\n\n"); 
		printf("\t6. ��  �� �� �� ��\n\n"); 
		printf("\t7. �� �� �� ��  �� ��\n\n");
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
				printf("\n�� �� �� ��  �� �� �� �� �� ��\n");
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
		count = 1; // ������Ȳ �ʱ�ȭ 
			
		while(count < 4)
		{
			system("cls");
			printf("\n\t�� �� �� Ȳ : %d / 3\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%d   %s   %s\n\n", learning_data[i].index, learning_data[i].name, learning_data[i].symbol); // ���� ������ֱ� 
			printf("==========================================\n\n");
			printf("\n\t�� �� �� ȣ : ");
			fflush(stdin);
			scanf("%d", &index);
			printf("\n\n\t�� �� �� �� : ");
			fflush(stdin);
			scanf("%s", name);
			printf("\n\n\t�� �� �� ȣ : ");
			fflush(stdin);
			scanf("%s", symbol);
			
			if(index != learning_data[i].index || strcmp(name, learning_data[i].name) != 0 || strcmp(symbol, learning_data[i].symbol) != 0) // �ùٸ��� �Է��ߴ��� Ȯ�� 
			{
				printf("\n==========================================\n\n");
				printf("\n    �� �� �� ��  �� �� �� �� �� ��\n");
				getch();
				
				continue; // ���� ������Ȳ�� ���� �ٽ� �Է��ϱ� 
			} 
			
			count++; // ��Ȯ�ϰ� �Է������� ������Ȳ 1 ���� 
			
			if(4-count == 0) // 3�� ���� �Ϸ����� ��� 
			{
				printf("\n==========================================\n\n");
				printf("       �� �� �� ��  �� �� �� �� �� !", 4-count);
				getch();
			}
			else { // ���� ������Ȳ ǥ�����ֱ� 
				printf("\n==========================================\n\n");
				printf("       %d ��  �� �� �� �� �� !", 4-count);
				getch();
			}	
		}
	}
	
	system("cls"); // �н� ���������� ���ƴٴ� �ȳ��� ��� 
	
	printf("\n==========================================\n\n");
	printf("�� �� ��  �� �� �� �� ��  �� ġ �� �� �� �� !");
	printf("\n==========================================\n\n");
	
	getch();
}

void index_test(int login_user)
{
	int number[20] = {0,};
	int i, random_index, index, correct_count = 0, count = 1;
	
	srand(time(NULL)); // ���� �õ� �ʱ�ȭ 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() % 20; // 0~19 ������ �� �������� 
		if(number[random_index] == 1) // �̹� ���Դ� ����� �ٽ� ���� 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // ������ �Ȱ��� ���ڰ� �������� �ʵ��� ǥ��
			
			system("cls");
			printf("\n\t�� �� �� Ȳ : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8s%6s\n\n", learning_data[random_index].name, learning_data[random_index].symbol); // ���� ��� 
			printf("\n==========================================\n\n");
			printf("\n\t�� �� �� ȣ : ");
			fflush(stdin);
			scanf("%d", &index);
			printf("\n\n==========================================\n\n");
			
			if(learning_data[random_index].index == index) // ����ڰ� �Է��� ���� ��ȣ�� ������ �´��� �� 
			{
				correct_count++;
				printf("\t�� �� �� �� �� !");
				getch();
			}
			else { // Ʋ���� ��� 
				printf("\t�� �� �� �� �� !\n\n");
				printf("\t�� �� :  %d ", learning_data[random_index].index);
				getch();
			}
			
			count++; // ������Ȳ ī��Ʈ ���� 1 ���� 
			
			if(count == 21)
			{
				system("cls"); // �׽�Ʈ ���������� ���ƴٴ� �ȳ��� ��� 
	
				printf("\n\t==========================================\n\n");
				printf("\t�� �� ��  �� �� �� �� ��  �� ġ �� �� �� �� !\n\n");
				printf("\t    �� �� ��  �� �� ��  %d ��  �� �� �� !\n", correct_count);
				printf("\n\t==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // �׽�Ʈ ī��Ʈ ���� 1 ���� 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // ���� �ð��� �� ������ ���

	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	
	//���ο� �׽�Ʈ ��� ��� 
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
	
	srand(time(NULL)); // ���� �õ� �ʱ�ȭ 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() %20; // 1~20 ������ �� �������� 
		if(number[random_index] == 1) // �̹� ���Դ� ����� �ٽ� ���� 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // ������ �Ȱ��� ���ڰ� �������� �ʵ��� ǥ��
			
			system("cls");
			printf("\n\t�� �� �� Ȳ : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8d%6s\n\n", learning_data[random_index].index, learning_data[random_index].symbol); // ���� ��� 
			printf("\n==========================================\n\n");
			printf("\n\t�� �� �� �� : ");
			fflush(stdin);
			scanf("%s", name);
			printf("\n\n==========================================\n\n");
			
			if(!strcmp(learning_data[random_index].name, name)) // ����ڰ� �Է��� ���� �̸��� ������ �´��� �� 
			{
				correct_count++;
				printf("\t�� �� �� �� �� !");
				getch();
			}
			else { // Ʋ���� ��� 
				printf("\t�� �� �� �� �� !\n\n");
				printf("\t�� �� :  %s", learning_data[random_index].name);
				getch();
			}
			
			count++; // ������Ȳ ī��Ʈ ���� 1 ���� 
			
			if(count == 21)
			{
				system("cls"); // �׽�Ʈ ���������� ���ƴٴ� �ȳ��� ��� 
	
				printf("\n\t==========================================\n\n");
				printf("\t�� �� ��  �� �� �� �� ��  �� ġ �� �� �� �� !\n\n");
				printf("\t    �� �� ��  �� �� ��  %d ��  �� �� �� !\n", correct_count);
				printf("\n==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // �׽�Ʈ ī��Ʈ ���� 1 ���� 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // ���� �ð��� �� ������ ���

	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	
	//���ο� �׽�Ʈ ��� ��� 
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
	
	srand(time(NULL)); // ���� �õ� �ʱ�ȭ 
	
	for(i = 0; i < 20; i++)
	{
		random_index = rand() %20; // 1~20 ������ �� �������� 
		if(number[random_index] == 1) // �̹� ���Դ� ����� �ٽ� ���� 
		{
			i--;
			continue;
		}
		else {
			number[random_index] = 1; // ������ �Ȱ��� ���ڰ� �������� �ʵ��� ǥ��
			 
			system("cls");
			printf("\n\t�� �� �� Ȳ : %d / 20\n", count);
			printf("\n==========================================\n\n");
			printf("\n\t%8d%6s\n\n", learning_data[random_index].index, learning_data[random_index].name); // ���� ��� 
			printf("\n==========================================\n\n");
			printf("\n\t�� �� �� ȣ : ");
			fflush(stdin);
			scanf("%s", symbol);
			printf("\n\n==========================================\n\n");
			
			if(!strcmp(learning_data[random_index].symbol, symbol)) // ����ڰ� �Է��� ���� ��ȣ�� ������ �´��� �� 
			{
				correct_count++;
				printf("\t�� �� �� �� �� !");
				getch();
			}
			else { // Ʋ���� ��� 
				printf("\t�� �� �� �� �� !\n\n");
				printf("\t�� �� :  %s", learning_data[random_index].symbol);
				getch();
			}
			
			count++; // ������Ȳ ī��Ʈ ���� 1 ���� 
			
			if(count == 21)
			{
				system("cls"); // �׽�Ʈ ���������� ���ƴٴ� �ȳ��� ��� 
	
				printf("\n\t==========================================\n\n");
				printf("\t�� �� ��  �� �� �� �� ��  �� ġ �� �� �� �� !\n\n");
				printf("\t    �� �� ��  �� �� ��  %d ��  �� �� �� !\n", correct_count);
				printf("\n\t==========================================\n\n");
				
				getch();
			}
		}
	}
	
	result_count++; // �׽�Ʈ ī��Ʈ ���� 1 ���� 
	
	time_t timer;
	struct tm *t;
	
	timer = time(NULL); // ���� �ð��� �� ������ ���

	t = localtime(&timer); // �� ������ �ð��� �и��Ͽ� ����ü�� �ֱ�
	
	//���ο� �׽�Ʈ ��� ��� 
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
		
	printf("\n\t\t  T E S T  �� ��  Ȯ ��\n\n");
	printf("\t==============================================\n\n");
	printf("\t T E S T �� �� | ��  ��  ��  ¥ | �� �� �� ��\n\n"); 
	
	for(i = 1; i <= result_count; i++)
	{
		if(!strcmp(result_data[i].id, member_data[login_user].id)) // ���� �α��� �� ���̵�� ���� ����� ���̵� ��ġ�ϸ� 
		{
			flag = 1;
			switch(result_data[i].type)
			{
				case INDEX_TEST:
					printf("\t �� ȣ T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
				case NAME_TEST:
					printf("\t �� �� T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
				case SYMBOL_TEST:
					printf("\t �� ȣ T E S T | %4d - %2d - %2d | %5d\n\n", result_data[i].yyyy, result_data[i].mm, result_data[i].dd, result_data[i].correct);
					break;
			}
		}
	}
	
	if(flag == 0)
	{
		system("cls");
		printf("\n\t\t  T E S T  �� ��  Ȯ ��\n\n");
		printf("\t==============================================\n\n");
		printf("\t    �� �� �� ��  �� �� �� �� �� �� �� ��.\n\n");
	}
	
	printf("\t==============================================\n\n");
	getch();
}
