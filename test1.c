#include <stdio.h>

// 函数用于计算斐波那契数列的第 N 项
long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long a = 0;
    long long b = 1;
    long long result = 0;

    for (int i = 2; i <= n; i++) {
        result = a + b;
        a = b;
        b = result;
    }

    return result;
}

int main() {
    int n;
    // 读取输入的非负整数 n
    scanf("%d", &n);

    // 计算并输出斐波那契数列的第 N 项
    printf("%lld\n", fibonacci(n));

    return 0;
}




