#include "header.h"

user user_data[50];
int user_count = -1;

int main()
{
	load();
	command();
	
	return 0;
}

void load() //���� �ҷ����� �Լ� 
{	
	FILE *fp = fopen("user_data.txt", "r");
	
	if(fp == NULL) //������ �������� ���� ��� ���� ���� 
	{
		fp = fopen("user_data.txt", "w");
	}
	while(!feof(fp))
	{
		user_count++;
		fscanf(fp, "%s %s", user_data[user_count].user_name, user_data[user_count].password);
		
		if(!strcmp(user_data[user_count].user_name, "")) //���� �������� ���� ��� ���� ī��Ʈ �� ���� 
		{
			user_count--;
		}
	}
	
	fclose(fp);
}

void save() //����ü �迭 �� ���Ͽ� �����ϰ� ���α׷� ���� 
{
	int i;
	
	FILE *fp = fopen("user_data.txt", "w");
	
	for(i = 0; i <= user_count; i++)
	{
		fprintf(fp, "%s %s\n", user_data[i].user_name, user_data[i].password);
	}
	
	fclose(fp);
	
	exit(0); // ���α׷� ���� ���� 
}

void command()
{
	char user_cmd[100];
	char *cmd[30];
	int count_index, login_flag = 0, i;
	
	while(1)
	{
		if(login_flag == 1)
		{
			printf("mysql> ");
		}
		
		count_index = 0;
		gets(user_cmd);
		
		char *str = strtok(user_cmd, " ");
		
		while(str != NULL)
		{
			cmd[count_index] = str;
			count_index++;
			
			str = strtok(NULL, " ");
		}
		
		if(!strcmp(cmd[0], "mysql") && !strcmp(cmd[1], "-u") && !strcmp(cmd[3], "-p"))
		{
			printf("abc");
		}
		else {
			printf("ERROR : UNKOWN COMMAND \'");
			for(i = 0; i < count_index; i++)
			{
				printf("%s ", cmd[i]);
			}
			printf("\b \b\'\n"); // �Է��� ��ɾ� �ڿ� ���� ���� �ʰ� ó������ 
			continue;
		}
	}
}
