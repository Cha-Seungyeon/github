#include <stdio.h>

int fac(int num);

int main()
{
	int num;
	
	printf("���丮�� ������ �� ���ڸ� �Է����ּ���.\n");
	scanf("%d", &num);
	printf("���� %d�Դϴ�.\n", fac(num));
	 
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
