#include <stdio.h>

int fac(int num);

int main()
{
	int num;
	
	printf("팩토리얼 연산을 할 숫자를 입력해주세요.\n");
	scanf("%d", &num);
	printf("답은 %d입니다.\n", fac(num));
	 
	return 0;
}

int fac(int num)
{
	if(num == 1)
	{
		return num;
	}
	return num*fac(num-1);
}
