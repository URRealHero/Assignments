#include <iostream>
#include <cstring>
#include <iterator>
using namespace std;

typedef struct Student{
  char name[15];
  short age;
  float score;
  char remark[200];
} student;
const int N = 5;
const int M = 1e5;

int pack_student_bytebybyte(student *s,int sno, char *buf);
int pack_student_whole(student *s, int sno, char *buf);
void restore_student(char *buf,int len, student *s);

inline void printfloat_16(const float fnum){
  unsigned int *p = (unsigned int *)&fnum;
  for(int i = 31 ; i >= 0 ; i--){
    cout << ((*p >> i) & 1);
    if(i == 31 || i == 23) cout << " ";
  }
  cout << endl;
}

int main(){
  student old_s[N];
  student new_s[N];
  memset(old_s,0,sizeof(old_s));
  memset(new_s,0,sizeof(new_s));
  char buf[M];
  old_s[0] = {"Pu Shu", 19 , 22, "Best"};
  old_s[1] = {"Zhang San", 20, 23, "Good"};
  old_s[2] = {"Li Si", 21, 24, "Good"};
  old_s[3] = {"Wang Wu", 22, 25, "Good"};
  old_s[4] = {"Zhao Liu", 23, 26, "Good"};

  int before_cp = sizeof(old_s);
  int after_cp = pack_student_bytebybyte(old_s,2,buf);
  after_cp += pack_student_whole(old_s+2,3,buf+after_cp);
  // PuShu Score 编码 41 B0 00 00 --> 0100 0001 1011 0000 0000 0000 0000 0000 --> 1.011... * 2^(bin(10000011)-bin(01111111))
  // 上式等价为 10110_bin == 22_dec 正确 
  // 打印第0个学生的16进制score编码
  cout << "PuShu Score: ";
  printfloat_16(old_s[0].score);
  cout << "Before Compression: " << before_cp << " bytes" << endl;
  cout << "After Compression: " << after_cp << " bytes" << endl;
  restore_student(buf,after_cp,new_s);

  // for(int i = 0 ; i < N ; i++){
  //   printf("%s %d %.2f %s\n",new_s[i].name,new_s[i].age,new_s[i].score,new_s[i].remark);
  // }

  cout << std::hex;
  for(int i = 0 ; i < 20 ; i ++){
    cout  << (static_cast<short>(buf[i]) & 0xff) << " ";
  }
  cout << endl;
  // 输出与观察一致
  return 0;

}

/*
存放规律
字符串 name 和 remark 按序存放，以'\0' 结尾
age，float 在内存中小端存放 低字节在前
*/


int pack_student_bytebybyte(student *s, int n, char *buf){
  int now_add = 0;
  for(int i = 0 ; i < n ; i++){
    char * cp = s[i].name;
    // 复制name
    while(*cp != '\0') buf[now_add++] = *cp++;
    buf[now_add++] = '\0';
    // 复制age (小端存放)
    cp = (char *)&s[i].age;
    for(int i = 0 ; i < 2 ; i++)
      buf[now_add++] = *cp++;
    // 复制float 四个字节
    cp = (char *)&s[i].score;
    for(int i = 0 ; i < 4 ; i++)
      buf[now_add++] = *cp++;
    cp = s[i].remark;
    while(*cp != '\0') buf[now_add++] = *cp++;
    buf[now_add++] = '\0';
  }
  return  now_add;
}


int pack_student_whole(student *s, int n, char * buf){
  int now_add = 0;
  for(int i = 0 ; i < n ; i++){
	strcpy(buf+now_add,s[i].name);
	now_add += strlen(s[i].name)+1;
  *(short *)(buf+now_add) = s[i].age;
  now_add += 2;
  *(float *)(buf+now_add) = s[i].score;
  now_add += 4;
  strcpy(buf+now_add,s[i].remark);
  now_add += strlen(s[i].remark)+1;
  }
  return now_add;
}


void restore_student(char * buf, int len, student *s){
  int now_add = 0;
  int i = 0;
  while(1){
    if (now_add >= len) return;
    strcpy(s[i].name,buf+now_add);
    now_add += strlen(s[i].name)+1;
    s[i].age = *(short *)(buf+now_add);
    now_add += 2;
    s[i].score = *(float *)(buf+now_add);
    now_add += 4;
    strcpy(s[i].remark,buf+now_add);
    now_add += strlen(s[i].remark)+1;
    i++;
  }
}
