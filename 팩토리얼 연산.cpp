#include <stdio.h>

int fac(int num);

int main()
{
	int num;
	
	printf("���� �ϳ��� �Է����ּ���.\n");
	scanf("%d", &num);
	printf("���丮�� ������ ���� %d�Դϴ�.\n", fac(num));
	
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
