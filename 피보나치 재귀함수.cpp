#include <stdio.h>

int fib(int num);

int main()
{
	int num;
	
	printf("�� ��° �Ǻ���ġ ���� ���Ͻðڽ��ϱ�?\n");
	scanf("%d", &num);
	printf("���� %d �Դϴ�.\n", fib(num)); 
	
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
