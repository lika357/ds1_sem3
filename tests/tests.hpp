#pragma once

void test_unique_ctor();
void test_unique_deletes_object();
void test_unique_move_ctor();
void test_unique_move_assign();
void test_unique_deref_arrow();
void test_unique_get();
void test_unique_release();
void test_unique_reset();

void test_unique_array();
void test_unique_array_move();

void test_shared_empty();
void test_shared_ctor();
void test_shared_copy_ctor();
void test_shared_copy_assign();
void test_shared_self_assign();
void test_shared_move_ctor();
void test_shared_move_assign();
void test_shared_last_owner_deletes();
void test_shared_reset();

void test_shared_array();

void test_dyn_empty();
void test_dyn_size_ctor();
void test_dyn_strings();
void test_dyn_deep_copy();
void test_dyn_copy_assign();
void test_dyn_move();
void test_dyn_out_of_range();
void test_dyn_resize();