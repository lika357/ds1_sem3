#include <iostream>

#include "assert.hpp"
#include "tests.hpp"

int main()
{
    test_unique_ctor();
    test_unique_deletes_object();
    test_unique_move_ctor();
    test_unique_move_assign();
    test_unique_deref_arrow();
    test_unique_get();
    test_unique_release();
    test_unique_reset();

    test_unique_array();
    test_unique_array_move();

    test_shared_empty();
    test_shared_ctor();
    test_shared_copy_ctor();
    test_shared_copy_assign();
    test_shared_self_assign();
    test_shared_move_ctor();
    test_shared_move_assign();
    test_shared_last_owner_deletes();
    test_shared_reset();

    test_shared_array();

    test_dyn_empty();
    test_dyn_size_ctor();
    test_dyn_strings();
    test_dyn_deep_copy();
    test_dyn_copy_assign();
    test_dyn_move();
    test_dyn_out_of_range();
    test_dyn_resize();

    std::cout << "true " << get_true_tests() << "\n";
    std::cout << "false " << get_failed_tests() << "\n";

    if (get_failed_tests() != 0)
    {
        return 1;
    }
    return 0;
}