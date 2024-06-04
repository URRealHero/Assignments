#include <stdio.h>
void printstuid();
void (*myprint)() = printstuid;

void printstuid() {
	printf("Student ID: U202215322\n");
}
