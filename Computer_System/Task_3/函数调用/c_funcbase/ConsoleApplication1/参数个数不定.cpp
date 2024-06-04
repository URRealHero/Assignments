#include<stdio.h>

int fsum(long long n, ...) {
    long long* p = &n;
 //   int j = 2;
    long int j = 1;
    int sum = 0;
    for (int i = 0; i < n; i++, j += 1) {
        sum += *(p + j);
    }
    return sum;
}

int bitCount(int x) {
    int m1 = 0x11 | (0x11 << 8);
    int mask = m1 | (m1 << 16);
    int s = x & mask;
    s += x >> 1 & mask;
    s += x >> 2 & mask;
    s += x >> 3 & mask;
    /* Now combine high and low order sums */
    s = s + (s >> 16);

    /* Low order 16 bits now consists of 4 sums,
       each ranging between 0 and 8.
       Split into two groups and sum */
    mask = 0xF | (0xF << 8);
    s = (s & mask) + ((s >> 4) & mask);
    return (s + (s >> 8)) & 0x3F;

}

int main() {
    int u = bitCount(0x12345678);
    int result;
    result = fsum(2, 10, 20);     // 返回结果为 30
    printf("Result: %d\n", result);

    result = fsum(3, 1, 2, 4);   // 返回结果 7
    printf("Result: %d\n", result);

    result = fsum(4, 1, 2, 4, 5); // 返回结果 12
    printf("Result: %d\n", result);

    return 0;
}
