#include "MyVector/iterator.h"
#include "MyVector/vector.h"
#include "MyVector/exceptions.h"

void constructors_check_1 ();
void constructors_check_2 ();
void operations_check_1 ();
void operations_check_2 ();

int main() {
    constructors_check_1();
    constructors_check_2();
    operations_check_1();
    operations_check_2();
    return 0;
}

void constructors_check_1 () {
    const int len = 5;
    // конструктор от длины
    MyVector<int> vec(len);
    std::cout << "length constructor" << std::endl;
    std::cout << "expected length: 5, " << "actual length: " << vec.get_length() << std::endl;
    // проверка get_length
    if (vec.get_length() != len) {
        std::cerr << "error with length constructor" << std::endl;
    }
    // проверка на отрицательную длину
    std::cout << "trying size: " << -len << std::endl;
    try {
        MyVector<int> vec(-len);
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    // конструктор копирования
    MyVector<int> new_vec (vec);
    std::cout << "copy constructor" << std::endl;
    std::cout << "basic vector: " << vec << "new vector: " << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (vec[i] != new_vec[i]) {
            std::cerr << "copy constuctor error" << std::endl;
        }
    }
}

void constructors_check_2 () {
    // проверка на инициализацию листом
    const std::initializer_list<int> lst = {1, 2, 3, 4, 5};
    MyVector <int> vec (lst);
    std::cout << "initializer list" << std::endl << "expected vec: vector ";
    for (auto i : lst) {
        std::cout << i << " ";
    }
    std::cout << std::endl <<"actual vec: " << vec;
    int j = 0;
    for (auto i : lst) {
        if (i != vec[j]) {
            std::cerr << "constructor error." << std::endl;
        }
        j++;
    }
    std::cout << std::endl;
}

void operations_check_1 () {
    // проверка get_len()
    const int len = 5;
    MyVector<int> vec_1(len);
    MyVector<int> vec_2(len);
    std::cout << "get_length check" << std::endl;
    std::cout << "first vec length: " << vec_1.get_length() << std::endl
        << "second vec length: " << vec_2.get_length() << std::endl << std::endl;
    if (vec_1.get_length() != vec_2.get_length()) {
        std::cerr << "get_len error." << std::endl;
    }
    // проверка set_elem()
    std::cout << "set elem check" << std::endl;
    const int elem = 5;
    const int ind = 2;
    vec_1.set_elem(ind, elem);
    std::cout << "expected element: " << elem << std::endl << "actual element: " << vec_1[ind] << std::endl;
    std::cout << "trying index: " << -ind << std::endl;
    try {
        vec_1.set_elem(-ind, elem);
    } catch (Exceptions &ex) {
        std::cout << ex;
    }
    std::cout << std::endl;
}

void operations_check_2 () {
    // проверка get_elem()
    MyVector<int> vec({1, 2, 3, 4, 5});
    const int index = 2;
    std::cout << "get_elem check" << std::endl;
    std::cout << "expected elem: " << vec[index - 1] << std::endl << "actual elem: " << vec.get_elem(index) << std::endl;
    std::cout << "trying index: " << -index << std::endl;
    try {
        std::cout << vec.get_elem(-index) << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    // проверка to_array()
    std::cout << "to array check" << std::endl;
    const int* array = vec.to_array();
    std::cout << "expected array: " << vec << "actual array: ";
    for (int i = 0; i < vec.get_length(); ++i) {
        std::cout << array[i] << " ";
    }
    for (int i = 0; i < vec.get_length(); ++i) {
        if (vec[i] != array[i]) {
            std::cerr << "transition error.";
        }
    }
    std::cout << std::endl;
    delete []array;
}
