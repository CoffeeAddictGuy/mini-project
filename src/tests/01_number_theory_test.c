#include <stdio.h>
#include <criterion/criterion.h>
#include <number_theory.h>

void setup(void) {
  puts("Tests for number theory module");
}

Test(number_theory, gcd) {
  cr_expect_eq(gcd(12, 8), 4);
  cr_expect_eq(gcd(7, 3), 1);
  cr_expect_eq(gcd(42, 56), 14);
  cr_expect_eq(gcd(100, 25), 25);
  cr_expect_eq(gcd(17, 13), 1);
}

Test(number_theory, lcm) {

}
