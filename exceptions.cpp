#include "exceptions.h"

std::ostream & operator << (std::ostream &os, Exceptions &exc) {
    os << "error: " << exc.text << std::endl;
    return os;
}