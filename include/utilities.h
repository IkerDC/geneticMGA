#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#define UA 149597870691.0
#define DAY2SEC 86400.0

enum class Planets{
    MERCURY,
    VENUS,
    EARTH,
    MARS,
    JUPITER,
    SATURN,
    URANUS,
    NEPTUNE
};

class Epoch{
private:
    float jd;
    float mjd;
    float mjd2000;

    void set_from_jd(float jd);
    void set_from_jd200(float jd);

public:
    Epoch(float tt, std::string mode);
    ~Epoch();
    
};


#endif //UTILITIES_H
