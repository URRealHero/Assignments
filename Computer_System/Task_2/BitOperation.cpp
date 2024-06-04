#include <iostream>
#include <cmath>
using namespace std;

int absVal(int x){
    return (x+(x>>31)) ^ (x>>31);
}

int neg(int x){
    return ~x + 1;
}

int bitAnd(int x,int y){
    return ~(~x|~y);
}

int bitOr(int x,int y){
    return ~((~x)&(~y));    
}


int bitXor(int x, int y){
    return ~(~(x&(~y)) & ~((~x)&y));
}


int isTmax(int x){
    return !(x^~(x+1)) & !!(x+1); // 特判x == -1
}


int bitCount(int x){
        // 将相邻的两位相加，结果存储在这两位中的低位
        x = (x & 0x55555555) + ((x >> 1) & 0x55555555); // 0101
        // 将相邻的四位相加，结果存储在这四位中的低两位
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333); // 0011
        // 将相邻的八位相加，结果存储在这八位中的低四位
        x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F); // 0000 1111
        // 将相邻的十六位相加，结果存储在这十六位中的低八位
        x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF); // 00000000 11111111
        // 将相邻的三十二位相加，结果存储在这三十二位中的低十六位
        x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF); // 00000000 00000000 11111111 11111111
        // 此时，x的低十六位就是原始输入x中1的个数
        return x;
}

int bitMask(int highbit, int lowbit){
    return ((~0) << lowbit) & ~((~0) << (highbit+1));
}

int addOK(int x,int y){
//   return ((x>>31 & 1) ^ (y>>31 & 1)) | (((x>>31 & 1) & (y>>31 & 1)) ^ (x+y) >> 31 & 1;
    return (x>>31 & 1) ^ (y>>31 & 1) | !((x>>31&1) & (y>>31&1) ^ (x+y)>>31&1);
}

int byteswap(int x,int n,int m){
    int mask = 0x000000FF;
    int get_n = (mask << (n<<3)) & x;
    int get_m = (mask << (m << 3) ) & x;
    return (~((mask << (n<<3)) | (mask << (m<<3))) & x) | (((get_n >> (n<<3)) << (m<<3)) & (mask << (m<<3)) | ((get_m >> (m<<3)) << (n<<3)) & (mask << (n<<3)));

}

int main(){

    printf("Test absVal by abs\n");
    for(int i = -100 ; i <= 100 ; i++){
        if(absVal(i) != abs(i)){
            printf("Error at %d\n",i);
        }
    }
    printf("absVal test done\n");

    printf("Test neg by \'-\'\n");
    for(int i = -100 ; i <= 100 ; i++){
        if(neg(i) != -i){
            printf("Error at %d\n",i);
        }
    }
    printf("neg test done\n");

    printf("Test bitAnd by \'&\'\n");
    for(int i = -100 ; i <= 100 ; i++){
        for(int j = -100 ; j <= 100 ; j++){
            if(bitAnd(i,j) != (i&j)){
                printf("Error at %d %d\n",i,j);
            }
        }
    }
    printf("bitAnd test done\n");

    printf("Test bitOr by \'|\'\n");
    for(int i = -100 ; i <= 100 ; i++){
        for(int j = -100 ; j <= 100 ; j++){
            if(bitOr(i,j) != (i|j)){
                printf("Error at %d %d\n",i,j);
            }
        }
    }
    printf("bitOr test done\n");

    printf("Test bitXor by \'^\n");
    for(int i = -100 ; i <= 100 ; i++){
        for(int j = -100 ; j <= 100 ; j++){
            if(bitXor(i,j) != (i^j)){
                printf("Error at %d %d\n",i,j);
            }
        }
    }
    printf("bitXor test done\n");

    printf("Test isTmax by integar 0x7FFFFFFF,0x80000000,0xFFFFFFFF,0x7FFFFFFE\n");
    printf("Answer should be 1 0 0 0\n");
    printf("%d\n",isTmax(0x7FFFFFFF));
    printf("%d\n",isTmax(0x80000000));
    printf("%d\n",isTmax(0xFFFFFFFF));
    printf("%d\n",isTmax(0x7FFFFFFE));
    printf("isTmax test done\n");

    printf("Test BitCount By 0x12345678 and 0x87654321, answer should be 13\n");
    printf("%d\n",bitCount(0x12345678));
    printf("%d\n",bitCount(0x87654321));
    printf("BitCount test done\n");


    printf("Test addOK by 0x7FFFFFFF,1 ; 0x7FFFFFFF,0 ; 0x80000000,-1 ; 0x80000001,-1\n");
    printf("Answer should be 0 1 0 1\n");
    printf("%d\n",addOK(0x7FFFFFFF,1));
    printf("%d\n",addOK(0x7FFFFFFF,0));
    printf("%d\n",addOK(0x80000000,-1));
    printf("%d\n",addOK(0x80000001,-1));
    printf("addOK test done\n");


    printf("Test byteswap By 0x12345678,1,3, answer should be 0x56341278\n");
    printf("%x\n",byteswap(0x12345678,1,3));
    printf("Test byteswap By 0xDEEFBEAD,0,2, answer should be 0xDEEFBEAD\n");
    printf("%x\n",byteswap(0xDEEFBEAD,0,2));
    printf("byteswap test done\n");
    return 0;

}
