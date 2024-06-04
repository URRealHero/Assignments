#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
using namespace std;

int  return_address;

int fsum(int n, ...)
{
	int result = 0;
	int* p;
	p = &n;
	p++;
	for (int i=0;i<n;i++)
	   result += *p;
	return result;
}

void fopt()
{
	int array[5] ;
	int sum = 0;
	int i;
	for (i = 0;i < 5;i++)
		scanf_s("%d", &array[i]);
	for (i = 0;i < 5;i++)
		sum += array[i];
	printf("%d\n", sum);
}

int fmin(int x, int y)
{
	int  t;
	if (x > y)  t = y;
	else  t = x;
	return  t;
}
void fmain()
{
	char buf[6] = "12345";  // '1'的ASCII是 0x31
	int  u = 0x20221204;
	int  v = -32;
	int  w = 0;
	w = fmin(u, v);
	w = *(int*)(buf + 1);
}

void func1( )
{
	cout << "hello" << endl;
	__asm {
		pop edi
		pop esi
		pop ebx
		mov esp,ebp
		pop ebp
		jmp return_address
	}
}


void f()
{
	int a[2];
	return_address = a[3];
	//  此处输入 func1 的地址
	scanf("%d", &a[3]);
}

int global[5] = { 10,20,30,40,50 };
int main(int argc, char* argv[])
{
	int result;
	result= fsum(1, 10);
	result = fsum(2, 10, 20);

	int local[5] = { 10,20,30,40,50 };
	int i = 2;
	int* p;
	global[i] = 25;
	
	fopt();

	*(global + 2) = 25;
	p = &global[2];
	*p = 25;	
	local[i] = 25;
	fmain();
	printf("func1 address : %p %d\n", func1,func1);
	printf("请输入上一行显示的 数 \n");
	f();

	printf("game over\n");
	return 0;
}