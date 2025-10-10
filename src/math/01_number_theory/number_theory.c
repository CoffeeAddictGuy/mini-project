#include <number_theory.h>
#include <stdio.h>
#include <stdlib.h>

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

void sieveOfEratosthenes(int *array, int n) {
  for (int i = 0; i < n; i++) {
    if (array[i] != 0) {
      int k = array[i];
      for (int j = i + k; j < n; j += k)
        array[j] = 0;
    }
  }
}

// Integer factorization
void trialDivision(int n) {
  if (n < 2) {
    printf("Neither prime nor composite\n");
    return;
  }

  int i, j = 0;
  for (i = 2; i < n / 2; i++) {
    if (i * i <= n && j != 1) {
      if (n % i == 0) {
        printf("Composite number\n");
        return;
      }
    }
  }
  printf("A prime number\n");
}
