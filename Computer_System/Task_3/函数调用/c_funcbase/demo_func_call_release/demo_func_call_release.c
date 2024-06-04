#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int fpadd(int* x, int y)
{
	int u, v, w;
	u = *x + 10;
	v = y + 25;
	w = u + v;
	return w;
}

int fadd(int x, int y)
{
	int u, v, w;
	u = x + 10;
	v = y + 25;
	scanf("%d", &u);
	w = u + v;
	return w;
}

int main()
{
	int  a = 100;    // 0x 64
	int  b = 200;    // 0x C8
	int  sum = 0;
	scanf("%d", &a);
	scanf("%d", &b);
	sum = fadd(a, b);
	printf("%d\n", sum);
	int* p;
	p = &a;
	sum = fpadd(p, b);
	return 0;
}
