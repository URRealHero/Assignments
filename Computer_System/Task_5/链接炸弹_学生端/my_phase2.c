#include <stdio.h>

int foo(int a, int b) {
	return a + b;
}

int bar(int a, int b) {
	return a - b;
}

int main(){
	int a = 10;
	int b = 20;
	int c = foo(a, b);
	int d = bar(a, b);
	printf("c = %d\n", c);
	printf("d = %d\n", d);
	return 0;
}
