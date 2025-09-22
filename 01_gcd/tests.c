#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/internal/test.h>

Test(misc, failing) {
    cr_assert(0);
}

Test(misc, passing) {
    cr_assert(1);
}
