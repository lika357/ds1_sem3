#include "tests.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>

#include "DynamicArray.hpp"
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"
#include "assert.hpp"

namespace
{
struct Counter
{
    static inline int alive = 0;
    Counter()
    {
        ++alive;
    }
    Counter(const Counter&)
    {
        ++alive;
    }
    ~Counter()
    {
        --alive;
    }
};

bool IndexThrows(DynamicArray<int>& a, size_t i)
{
    try
    {
        (void)a[i];
    }
    catch (const std::out_of_range&)
    {
        return true;
    }
    return false;
}
}

void test_unique_ctor()
{
    UniquePtr<int> p(new int(42));
    assert_func(p.get() != nullptr);
    assert_func(*p == 42);
}

void test_unique_deletes_object()
{
    {
        UniquePtr<Counter> p(new Counter());
        assert_func(Counter::alive == 1);
    }
    assert_func(Counter::alive == 0);
}

void test_unique_move_ctor()
{
    UniquePtr<int> a(new int(5));
    UniquePtr<int> b(std::move(a));
    assert_func(a.get() == nullptr);
    assert_func(b.get() != nullptr);
    assert_func(*b == 5);
}

void test_unique_move_assign()
{
    {
        UniquePtr<Counter> a(new Counter());
        UniquePtr<Counter> b(new Counter());
        assert_func(Counter::alive == 2);
        b = std::move(a);
        assert_func(Counter::alive == 1);
        assert_func(a.get() == nullptr);
    }
    assert_func(Counter::alive == 0);
}

void test_unique_deref_arrow()
{
    UniquePtr<std::string> s(new std::string("abc"));
    assert_func(*s == "abc");
    assert_func(s->size() == 3);
}

void test_unique_get()
{
    UniquePtr<int> p(new int(10));
    assert_func(p.get() != nullptr);
    assert_func(*p.get() == 10);
}

void test_unique_release()
{
    UniquePtr<Counter> p(new Counter());
    Counter* raw = p.release();
    assert_func(p.get() == nullptr);
    assert_func(Counter::alive == 1);
    delete raw;
    assert_func(Counter::alive == 0);
}

void test_unique_reset()
{
    UniquePtr<Counter> p(new Counter());
    p.reset(new Counter());
    assert_func(Counter::alive == 1);
    p.reset();
    assert_func(Counter::alive == 0);
    assert_func(p.get() == nullptr);
}

void test_unique_array()
{
    UniquePtr<int[]> arr(new int[3]{1, 2, 3});
    arr[1] = 20;
    assert_func(arr[0] == 1);
    assert_func(arr[1] == 20);
    assert_func(arr[2] == 3);
}

void test_unique_array_move()
{
    UniquePtr<int[]> arr(new int[2]{7, 8});
    UniquePtr<int[]> moved(std::move(arr));
    assert_func(arr.get() == nullptr);
    assert_func(moved[1] == 8);
}

void test_shared_empty()
{
    SharedPtr<int> p;
    assert_func(p.get() == nullptr);
    assert_func(p.use_count() == 0);
}

void test_shared_ctor()
{
    SharedPtr<int> p(new int(1));
    assert_func(p.get() != nullptr);
    assert_func(*p == 1);
    assert_func(p.use_count() == 1);
}

void test_shared_copy_ctor()
{
    SharedPtr<int> a(new int(1));
    {
        SharedPtr<int> b = a;
        assert_func(a.use_count() == 2);
        assert_func(b.get() == a.get());
        assert_func(*b == 1);
    }
    assert_func(a.use_count() == 1);
}

void test_shared_copy_assign()
{
    SharedPtr<int> a(new int(1));
    SharedPtr<int> b(new int(2));
    b = a;
    assert_func(*b == 1);
    assert_func(a.use_count() == 2);
}

void test_shared_self_assign()
{
    SharedPtr<int> a(new int(1));
    SharedPtr<int>& ref = a;
    a = ref;
    assert_func(a.use_count() == 1);
    assert_func(*a == 1);
}

void test_shared_move_ctor()
{
    SharedPtr<int> a(new int(7));
    SharedPtr<int> b(std::move(a));
    assert_func(a.get() == nullptr);
    assert_func(a.use_count() == 0);
    assert_func(b.use_count() == 1);
    assert_func(*b == 7);
}

void test_shared_move_assign()
{
    SharedPtr<int> a(new int(1));
    SharedPtr<int> b(new int(2));
    b = std::move(a);
    assert_func(*b == 1);
    assert_func(b.use_count() == 1);
    assert_func(a.get() == nullptr);
}

void test_shared_last_owner_deletes()
{
    {
        SharedPtr<Counter> a(new Counter());
        {
            SharedPtr<Counter> b = a;
            assert_func(Counter::alive == 1);
        }
        assert_func(Counter::alive == 1);
    }
    assert_func(Counter::alive == 0);
}

void test_shared_reset()
{
    {
        SharedPtr<Counter> a(new Counter());
        SharedPtr<Counter> b = a;
        a.reset();
        assert_func(Counter::alive == 1);
        assert_func(a.get() == nullptr);
        assert_func(b.use_count() == 1);
        b.reset(new Counter());
        assert_func(Counter::alive == 1);
    }
    assert_func(Counter::alive == 0);
}

void test_shared_array()
{
    SharedPtr<int[]> a(new int[2]{5, 6});
    SharedPtr<int[]> b = a;
    b[0] = 50;
    assert_func(a[0] == 50);
    assert_func(a[1] == 6);
    assert_func(a.use_count() == 2);
}

void test_dyn_empty()
{
    DynamicArray<int> a;
    assert_func(a.GetSize() == 0);
}

void test_dyn_size_ctor()
{
    DynamicArray<int> a(5);
    assert_func(a.GetSize() == 5);
    assert_func(a[0] == 0);
    assert_func(a[4] == 0);
}

void test_dyn_strings()
{
    DynamicArray<std::string> a(2);
    a[0] = "hello";
    a[1] = "world";
    assert_func(a[0] == "hello");
    assert_func(a[1] == "world");
}

void test_dyn_deep_copy()
{
    DynamicArray<int> a(3);
    a[0] = 1;
    DynamicArray<int> b = a;
    b[0] = 100;
    assert_func(a[0] == 1);
    assert_func(b[0] == 100);
    assert_func(b.GetSize() == 3);
}

void test_dyn_copy_assign()
{
    DynamicArray<int> a(2);
    a[1] = 9;
    DynamicArray<int> b(5);
    b = a;
    assert_func(b.GetSize() == 2);
    assert_func(b[1] == 9);
}

void test_dyn_move()
{
    DynamicArray<int> a(3);
    a[2] = 9;
    DynamicArray<int> b = std::move(a);
    assert_func(a.GetSize() == 0);
    assert_func(b.GetSize() == 3);
    assert_func(b[2] == 9);
}

void test_dyn_out_of_range()
{
    DynamicArray<int> a(3);
    assert_func(IndexThrows(a, 3));
    assert_func(IndexThrows(a, 100));
    assert_func(!IndexThrows(a, 2));
}

void test_dyn_resize()
{
    DynamicArray<int> a(2);
    a[0] = 1;
    a[1] = 2;
    a.Resize(4);
    assert_func(a.GetSize() == 4);
    assert_func(a[0] == 1);
    assert_func(a[1] == 2);
    assert_func(a[3] == 0);
    a.Resize(1);
    assert_func(a.GetSize() == 1);
    assert_func(a[0] == 1);
    a.Resize(0);
    assert_func(a.GetSize() == 0);
}