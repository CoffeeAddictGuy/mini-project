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

// Integer factorization

void sieveOfEratosthenes(int *array, int n) {
  for (int i = 0; i < n; i++) {
    if (array[i] != 0) {
      int k = array[i];
      for (int j = i + k; j < n; j += k)
        array[j] = 0;
    }
  }
}

