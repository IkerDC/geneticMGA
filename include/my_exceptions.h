#ifndef MY_EXCEPTIONS_H
#define MY_EXCEPTIONS_H

#include <exception>

struct UnknowPLanet : public std::exception {
    const char* what() const throw () {
        return "Unrecognized planet.";
    }
};

struct PlanetUnreferended : public std::exception {
    const char* what() const throw () {
        return "The planet instance redferenced on the current flyby instance has been destroyed. Nullptr.";
    }
};

struct negativeTime : public std::exception {
    const char* what() const throw () {
        return "Time cannot be negative.";
    }
};

#endif //MY_EXCEPTIONS_H