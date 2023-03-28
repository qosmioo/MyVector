#ifndef VECTOR_EXCEPTIONS_H
#define VECTOR_EXCEPTIONS_H
#include <iostream>
#include <utility>

class Exceptions {
private:
    std::string text;
public:
    explicit Exceptions(std::string str) {text = std::move(str);}
    friend std::ostream & operator << (std::ostream &os, Exceptions &exc);
};

#endif //VECTOR_EXCEPTIONS_H
