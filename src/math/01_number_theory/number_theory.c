#include <number_theory.h>

int gcd(int first, int second) {
    while (second != 0) {
        int temp = first %= second;
        first = second;
        second = temp;
    }
    return first;
}

int lcmByGCD(int a, int b) {
    int first = a;
    int second = b;
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }

    if (first * second < 0) 
        first = first * second * -1;
    else
        first = first * second;
    return first / a;
}

int lcm(int a, int b) {
    return 0;
}

int main() {
    int a = 102;
    int b = 465;
    int res = gcd(a, b);
    printf("Result: %d\n", res);    
    return 0;
}
