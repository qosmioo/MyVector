#ifndef TEST_H
#define TEST_H
#include "MyVector/iterator.h"
#include "MyVector/vector.h"
#include "MyVector/exceptions.h"

void tests ();
void check_test_add (MyVector<int> vector, MyVector <int> basic_vec);
void constructors_check_1 ();
void constructors_check_2 ();
void operations_check_1 ();
void get_elem_check ();
void to_array_check ();
void operators_check ();
void addition ();
void math_operations_0 ();
void math_operations_1 ();
void math_operations_2 ();
void math_empty_vec ();
void math_operations_3 ();
void math_operations_4 ();
void iterator_begin_end ();
void iterator_next ();
void iterator_value ();
void iterator_operators ();
void iterator_increment ();
void constructor_move ();
void iterator_operators_2 ();

#endif // TEST_H
