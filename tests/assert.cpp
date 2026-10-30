#include "assert.hpp"

#include <cstdio>

static size_t failed_count = 0;
static size_t true_count = 0;

int assert_fail(const char* expr, const char* file, size_t line)
{
    fprintf(stderr, "\033[31;1m%s:%zu: %s FAILED\033[0m\n", file, line, expr);
    failed_count++;
    return 0;
}

int assert_true(const char* expr, const char* file, size_t line)
{
    fprintf(stderr, "\033[32;1m%s:%zu: %s SUCCESS\033[0m\n", file, line, expr);
    true_count++;
    return 0;
}

int assert_(int function, const char* expr, const char* file, size_t line)
{
    if (function)
    {
        return assert_true(expr, file, line);
    }
    else
    {
        return assert_fail(expr, file, line);
    }
}

size_t get_true_tests()
{
    return true_count;
}
size_t get_failed_tests()
{
    return failed_count;
}