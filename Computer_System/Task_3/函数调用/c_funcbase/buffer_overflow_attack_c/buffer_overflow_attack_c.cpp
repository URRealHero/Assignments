// buffer_overflow_attack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// https://www.cnblogs.com/fanzhidongyzby/archive/2013/08/10/3250405.html
// 编译开关：基本运行时检查：默认值
//           安全检查：禁用
#include <iostream>
using namespace std;

int  global_ebp;
int global_eip;
void hacker()
{
    int a[2];
    cout << "hello，hacker" << endl;
 //   a[2] = global_ebp;
    a[3] = global_eip;
}

void (*p)() = hacker;

void f()
{
    cout << "call f ..." << endl;
    int  a[2];
    printf("ha %d \n", p);
    global_ebp = a[2];
    global_eip = a[3];
    scanf_s("%d", &a[3]);
}

int main()
{
    int  x = 10;
    cout << " execute f()...." << endl;
    f();
    cout << " f() over " << endl;
    x += 5;
    cout << "x = " << x << endl;
    return 0;
}
