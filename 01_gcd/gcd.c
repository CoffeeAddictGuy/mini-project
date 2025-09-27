#include <stdio.h>

int gcd(int first, int second) {
    while (second != 0) {
        int temp = first %= second;
        first = second;
        second = temp;
    }
    return first;
}

int main() {
    int a = 102;
    int b = 465;
    int res = gcd(a, b);
    printf("Result: %d\n", res);    
    return 0;
}
