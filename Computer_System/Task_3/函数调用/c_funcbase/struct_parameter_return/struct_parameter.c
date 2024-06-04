#include <stdio.h>
struct student {
	int  age;
	int  score;
	int  chinese ;
	int  english;
};

struct student modify_score(struct student s, int score)
{
	s.score = score;
	return s;
}

int main()
{
	struct student s1;
	struct student s2;
	s1.age = 20;
	s1.score = 90;
	s1.chinese = 75;
	s1.english = 80;
	s2 = modify_score(s1, 100);
	printf("%d %d \n", s2.age, s2.score);
	return 0;
}