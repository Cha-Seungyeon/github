#include <stdio.h>

int fac(int num);

int main()
{
	int num;
	
	printf("정수 하나를 입력해주세요.\n");
	scanf("%d", &num);
	printf("팩토리얼 연산의 답은 %d입니다.\n", fac(num));
	
	return 0;
}

int fac(int num)
{
	int i, result;
	
	result = num;
	
	for(i = result-1; i > 0; i--)
	{
		result = result * i;
	}
	
	return result;
}
