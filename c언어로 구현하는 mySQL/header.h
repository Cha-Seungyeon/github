#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct _user
{
	char user_name[15];
	char password[50];
}user;

void load();
void save();
void command();
