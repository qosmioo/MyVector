#include "test.h"

void tests () {
    constructors_check_1();
    constructors_check_2();
    constructor_move();
    operations_check_1();
    get_elem_check();
    to_array_check();
    operators_check ();
    math_operations_1();
    math_operations_0 ();
    math_empty_vec();
    math_operations_2 ();
    math_operations_3 ();
    math_operations_4 ();
    iterator_increment();
    iterator_begin_end ();
    iterator_next();
    iterator_value ();
    iterator_operators();
    addition ();
    iterator_operators_2 ();
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
        MyVector<int> vec_new(-len);
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    // конструктор копирования
    MyVector <int> vec_init ({1, 3, 2, 0, 5});
    MyVector<int> new_vec (vec_init);
    std::cout << "copy constructor" << std::endl;
    std::cout << "basic vector: " << vec_init << "new vector: " << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (vec_init[i] != new_vec[i]) {
            std::cerr << "copy constuctor error" << std::endl;
        }
    }
    MyVector<int> vecc(vec);
    std::cout << vecc << std::endl;
}

void constructors_check_2 () {
    // проверка на инициализацию листом
    const std::initializer_list<int> lst = {1, 2, 3, 4, 5};
    MyVector <int> vec (lst);
    std::cout << "initializer list" << std::endl << "list: ";
    for (auto i : lst) {
        std::cout << i << " ";
    }
    std::cout << std::endl << vec;
    int j = 0;
    for (auto i : lst) {
        if (i != vec[j]) {
            std::cerr << "constructor error." << std::endl;
        }
        j++;
    }
    std::cout << "trying empty list" << std::endl;
    MyVector <int> vecc({});
    std::cout << vecc << std::endl;
}
template<typename T>
MyVector<T> create_vec(MyVector<T> &vec) {
    MyVector <T> vector (vec);
    return vector;
}

void constructor_move () {
    std::cout << "move constructor check" << std::endl;
    MyVector <int> vec ({1, 2, 3});
    MyVector <int> temp_vec(vec);
    std::cout << vec << "new vec: ";
    MyVector <int> new_vec = create_vec(vec);
    std::cout << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (temp_vec[i] != new_vec[i]) {
            std::cerr << "move constructor error.";
        }
    }
    std::cout << "trying empty vector: " << std::endl;

    try {
        MyVector <int> empty_vec(1);
        MyVector <int> temp_vec_2(empty_vec);
        std::cout << temp_vec_2 << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
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
    std::cout << "trying empty vector" << std::endl;
    MyVector <int> vec;
    std::cout << "vector size = " << vec.get_length() << std::endl;
    // для пустого !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
    // проверка set_elem()
    std::cout << "set elem check" << std::endl;
    const int elem = 5;
    const int ind = 2;
    vec_1.set_elem(ind, elem);
    std::cout << "expected element: " << elem << std::endl << "actual element: " << vec_1[ind] << std::endl;
    std::cout << "trying index: " << ind + 5 << std::endl;
    try {
        vec_1.set_elem(ind + 5, elem);
    } catch (Exceptions &ex) {
        std::cout << ex;
    }
    std::cout << std::endl;
}

void get_elem_check() {
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

}
void to_array_check () {
    MyVector<int> vec({1, 2, 3, 4, 5});
    // проверка to_array()
    std::cout << "to array check" << std::endl;
    const int* array = vec.to_array();
    std::cout << "vector: " << vec << "array: (";
    for (int i = 0; i < vec.get_length(); ++i) {
        std::cout << array[i];
        if (i != vec.get_length() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << ")"<< std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (vec[i] != array[i]) {
            std::cerr << "transition error.";
        }
    }
    std::cout << std::endl;
    delete []array;

    std::cout << "trying empty vector" << std::endl;
    MyVector<int> new_vec;

    int *arr = new_vec.to_array();
    if (arr == nullptr) {
        std::cout << "arr is NULL" << std::endl << std::endl;
    } else {
        std::cerr << "to_array error.";
    }

}
void operators_check () {
    // перегрузка[]
    std::cout << "operator [] check" << std::endl;
    int num[3] = {5, 4, 7};
    MyVector <int> vector({num[0], num[1], num[2]});
    std::cout << vector << "vec[0] = " << vector[0] <<", vec[1] = " << vector[1] << ", vec[2] = " << vector[2]
        << std::endl << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != num[i]) {
            std::cerr << "operator [] error.";
        }
    }
    // =========
    std::cout << "operator = check" <<std::endl;
    MyVector<int> vec({3, 2, 4, 5, 6});
    MyVector <int> new_vec = vec;
    std::cout << "first vector: " << vec << "second vector: " << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (vec[i] != new_vec[i]) {
            std::cerr << "operator = error.";
        }
    }
    MyVector<int> new_vecc({3, 4,5, 5, 6, 7});
    new_vecc = vec;
    std::cout << new_vecc << std::endl;

    std::cout << "trying empty vec" << std::endl;

    try {
        MyVector<int> vecc;
        new_vec = vecc;
        std::cout << vecc;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void math_operations_0 () {
    // перегрузка операторов

    std::cout << "operator -= check:" << std::endl;
    MyVector <int> basic_vec ({6, 4, 9, 4, 5});
    MyVector <int> vector ({1, 4, 9, 7, 2});
    MyVector <int> temp_vec(vector);
    std::cout << "first vector: "<< vector << "second vector: " << basic_vec;
    vector -= basic_vec;
    std::cout << "vector -= basic_vec: "<< vector << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != temp_vec[i] - basic_vec[i]) {
            std::cerr << "operator -= error.";
        }
    }
    temp_vec = basic_vec;
    vector = basic_vec;
    std::cout << "trying -= equal vectors:" << std::endl << "first vector: " << vector << "second vector: " << basic_vec;
    vector -= basic_vec;
    std::cout << "result: " << vector << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != temp_vec[i] - basic_vec[i]) {
            std::cerr << "operator -= error.";
        }
    }
    std::cout << "trying sizes 4 and 5" << std::endl;
    try {
        MyVector <int> false_vec {1, 2, 3, 4};
        vector -= false_vec;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }

    std::cout << "trying vec -= vec" << std::endl << basic_vec;
    basic_vec -= basic_vec;
    std::cout << basic_vec << std::endl;

    std::cout << "trying vec -= empty vec" << std::endl;
    try {
        MyVector<int> vecc;
        basic_vec -= vecc;
        std::cout << basic_vec << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }

}

void math_operations_1 () {
    // перегрузка операторов

    std::cout << "operator += check" << std::endl;
    MyVector <int> basic_vec ({1, 2, 3, 4, 5});
    MyVector <int> vector ({1, 4, 9, 12, 4});
    MyVector <int> temp_vec(vector);
    std::cout << "first vector: "<< vector << "second vector: " << basic_vec;
    vector += basic_vec;
    std::cout << "vector += basic_vec: "<< vector << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != temp_vec[i] + basic_vec[i]) {
            std::cerr << "operator += error.";
        }
    }

    temp_vec = basic_vec;
    vector = basic_vec;
    std::cout << "trying += equal vectors:" << std::endl <<"first vector: " << vector << "second vector: " << basic_vec;
    vector += basic_vec;
    std::cout <<"result: " << vector << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != temp_vec[i] + basic_vec[i]) {
            std::cerr << "operator += error.";
        }
    }

    std::cout << "trying sizes 4 and 5" << std::endl;
    try {
        MyVector <int> false_vec {1, 2, 3, 4};
        vector += false_vec;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
    std::cout << "trying add vec += vec" << std::endl << vector;
    vector += vector;
    std::cout << vector << std::endl;

    std::cout << "trying vec += empty vec" << std::endl;
    try {
        MyVector<int> vecc;
        vector += vecc;
        std::cout <<vector << std::endl;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }

}

void math_operations_2 () {
    MyVector <int> vector ({1, 2, 3, 4, 5});
    MyVector <int> temp_vec (vector);
    int num = 5;
    std::cout << vector << "multiplication by " << num << std::endl;
    vector *= num;
    std::cout << "result: " << vector << std::endl;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != temp_vec[i] * num) {
            std::cerr << "operator *= error";
        }
    }
    MyVector <int> new_vec ({5, 15, 20, 0, 10});
    temp_vec = new_vec;
    std::cout  << "vector: " << new_vec << "division by " << num << std::endl;
    new_vec /= num;
    std::cout << "result: " << new_vec << std::endl;
    for (int i = 0; i < new_vec.get_length(); ++i) {
        if (new_vec[i] != temp_vec[i] / num) {
            std::cerr << "operator /= error";
        }
    }
    std::cout <<"trying num = 0" << std::endl;
    try {
        num = 0;
        vector /= num;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void math_empty_vec () {
    std::cout << "trying empty vectors" << std::endl;
    MyVector <int> vec_1;
    MyVector <int> vec_2;
    std::cout << "vector 1 + vector 2:" << std::endl;
    vec_1 += vec_2;
    std::cout << vec_1;

    std::cout << "vector 1 - vector 2:" << std::endl;
    vec_1 -= vec_2;
    std::cout << vec_1;

    std::cout << "vector*num: " << std::endl;
    int num = 5;
    vec_1 *= num;
    std::cout << vec_1;

    std::cout << "vector/num: " << std::endl;
    vec_1 /= num;
    std::cout << vec_1 << std::endl;
}

void math_operations_3 () {
    MyVector <int> vec_1 ({1, 2, 3, 4, 5});
    MyVector <int> vec_2 ({3, 2, 1, 0, 8});
    MyVector <int> vec_3 = vec_1 + vec_2;
    std::cout << "first vector: " << vec_1 << "second vector: " << vec_2 << "vec_1 + vec_2 = " << vec_3 << std::endl;
    for (int i = 0; i < vec_1.get_length(); ++i) {
        if (vec_3[i] != vec_1[i] + vec_2[i]) {
            std::cerr << "operator + error.";
        }
    }
    vec_3 = vec_1 - vec_2;
    std::cout << "first vector: " << vec_1 << "second vector: " << vec_2 << "vec_1 - vec_2 = " << vec_3 << std::endl;
    for (int i = 0; i < vec_1.get_length(); ++i) {
        if (vec_3[i] != vec_1[i] - vec_2[i]) {
            std::cerr << "operator - error.";
        }
    }

}

void math_operations_4 () {
    MyVector <int> vec ({-4, 2, 6, -2, 8});
    int num = 3;
    MyVector <int> new_vec = vec * num;
    std::cout << vec << "multiply by " << num << std::endl << "result: " << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (new_vec[i] != vec[i] * num) {
            std::cerr << "operator * error.";
        }
    }
    num = 2;
    new_vec = vec / num;
    std::cout << vec << "divide by " << num << std::endl << "result: " << new_vec << std::endl;
    for (int i = 0; i < vec.get_length(); ++i) {
        if (new_vec[i] != vec[i] / num) {
            std::cerr << "operator / error.";
        }
    }
    num = 0;
    std::cout << "trying num = 0" << std::endl;
    try {
        new_vec = vec / num;
    } catch (Exceptions &ex) {
        std::cout << ex << std::endl;
    }
}

void iterator_begin_end () {
    std::cout << "iterator begin check" << std::endl;
    MyVector <int> vector ({1, 4, 6, 3, 2});
    Iterator <int> it_1= vector.iterator_begin();
    bool flag = true;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != *it_1) {
            std::cerr << "iterator begin error.";
            flag = false;
        }
        ++it_1;
    }
    flag ? std::cout << "test passed" << std::endl : std::cout << "test not passed" << std::endl;
    std::cout << "iterator end check" << std::endl;
    Iterator <int> it_2 = vector.iterator_end();
    --it_2;
    it_2.is_end() ? std::cout << "test passed" << std::endl : std::cout << "test not passed" << std::endl;
}

void iterator_next () {
    std::cout << "iterator next check" << std::endl;
    MyVector <int> vector ({4, 3, 1, 2, 8});
    Iterator <int> it = vector.iterator_begin();
    bool flag = true;
    for (int i = 0; i < vector.get_length(); ++i) {
        if (vector[i] != it.value()) {
            std::cerr << "iterator next error.";
            flag = false;
        }
        it.next();
    }
    flag ? std::cout << "test passed" << std::endl << std::endl: std::cout << "test not passed" << std::endl;
}
void iterator_value () {
    std::cout << "iterator value check" << std::endl;
    MyVector <int> vector ({4, 1, 0, 6, 8});
    bool flag = true;
    for (Iterator <int> it = vector.iterator_begin(); !it.is_end(); ++it) {
        if (*it != it.value()) {
            std::cerr << "iterator value error.";
            flag = false;
        } else {
            std::cout << it.value() << " ";
        }
    }
    flag ? std::cout << "test passed" << std::endl << std::endl : std::cout << "test not passed" << std::endl;
}

void iterator_operators () {
    std::cout << "iterator operator == and operator != check" << std::endl;
    MyVector <int> vector ({4, 1, 0, 6, 8});
    bool flag = true;
    Iterator <int> it_1 = vector.iterator_begin();
    Iterator <int> it_2 = vector.iterator_begin();
    for (; !it_1.is_end() && !it_2.is_end();) {
        if (*it_1 == *it_2) {
        } else if (*it_1 != *it_2){
            std::cerr << "iterator operators error.";
            flag = false;
        }
        ++it_1;
        ++it_2;
    }
    flag ? std::cout << "test passed" << std::endl << std::endl : std::cout << "test not passed" << std::endl;
}

void iterator_increment () {
    std::cout << "iterator increment check" << std::endl;
    MyVector <int> vector ({5});
    Iterator <int> it = vector.iterator_begin();
    if (*it != vector[0]) {
        std::cerr << "iterator increment error.";
    } else {
        std::cout << "test passed" << std::endl << std::endl;
    }
}

void check_test_add (MyVector<int> vector, MyVector <int> basic_vec) {
    for (int i = vector.get_length() - basic_vec.get_length(); i < vector.get_length(); ++i) {
        if (vector[i] != basic_vec[i - vector.get_length() + basic_vec.get_length()]) {
            std::cerr << "addition error.";
        }
    }
}

void addition () {
    // перегрузка операторов
    MyVector <int> basic_vec ({6, 4, 9, 4, 5});
    MyVector <int> vector ({1, 4, 9, 7, 2});
    MyVector <int> temp_vec(vector);
    std::cout << "first vector: "<< vector << "second vector: " << basic_vec;
    vector.addition(basic_vec);
    std::cout << "vector += basic_vec: "<< vector << std::endl;
    check_test_add(vector, basic_vec);

    std::cout << "trying sizes 4 and 5" << std::endl;
    MyVector <int> false_vec {1, 2, 3, 4};
    vector.addition(false_vec);
    std::cout << vector << std::endl;
    check_test_add(vector, false_vec);

    std::cout << "trying vec + vec" << std::endl << vector;
    vector.addition(vector);
    std::cout << vector << std::endl;
    check_test_add(vector, vector);

    std::cout << "trying vec + empty vec" << std::endl;
    MyVector<int> vecc;
    vector.addition(vecc);
    std::cout << vector << std::endl;
}

void iterator_operators_2 () {
    MyVector <int> vec1 ({1, 3, 2, 0, 5});
    MyVector <int> vec2 ({1, 3, 2, 0, 5});
    Iterator <int> i_vec1 = vec1.iterator_begin();
    Iterator <int> i_vec2 = vec2.iterator_begin();
    if (i_vec1 != i_vec2) {
        std::cout << "diff vectors: test passed" << std::endl;
    } else {
        std::cout << "diff vectors: test not passed" << std::endl;
    }
    if (i_vec1 == i_vec1) {
        std::cout << "equal vectors: test passed" << std::endl;
    } else {
        std::cout << "diff vectors: test not passed" << std::endl;
    }
}
