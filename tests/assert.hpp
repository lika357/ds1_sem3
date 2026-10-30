#pragma once
#include <cstddef>
#include <cstdio>

int assert_fail(const char* expr, const char* file, size_t line);
int assert_true(const char* expr, const char* file, size_t line);
int assert_(int function, const char* expr, const char* file, size_t line);
size_t get_true_tests();
size_t get_failed_tests();

#define assert_func(func) assert_((func), #func, __FILE__, __LINE__)