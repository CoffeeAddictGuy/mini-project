#include <stdio.h>

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
    int a = 532;
    int b = 135;
    // lcm(a, b);
    printf("Result - %d\n",lcmByGCD(a, b));
    return 0;
}
