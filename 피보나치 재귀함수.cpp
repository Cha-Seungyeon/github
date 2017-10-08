#include <stdio.h>

int fib(int num);

int main()
{
	int num;
	
	printf("몇 번째 피보나치 수를 구하시겠습니까?\n");
	scanf("%d", &num);
	printf("답은 %d 입니다.\n", fib(num)); 
	
	return 0;
}

int fib(int num)
{
	if(num == 0 || num == 1)
	{
		return num;
	}
	
	return fib(num-1) + fib(num-2);
}
