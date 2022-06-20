#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <exception>

struct UnknowPLanet : public std::exception {
    const char* what() const throw () {
        return "Unrecognized planet.";
    }
};

#endif //MY_EXCEPTIONS_H