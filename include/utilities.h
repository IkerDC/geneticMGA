#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#define UA 149597870691.0
#define DAY2SEC 86400.0

#define MERCURY 1
#define VENUS 2
#define EARTH 3
#define MARS 4
#define JUPITER 5
#define SATURN 6
#define URANUS 7
#define NEPTUNE 8

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
