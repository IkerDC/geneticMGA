#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>

#define UA 149597870691.0
#define DAY2SEC 86400.0
#define MU_SUN 1.32712440018e+20
#define CORRECTION 0.827363

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

static void rotate_eph(double w, double W, double i, double P, double Q, double* vec){
    // rotate by argument of periapsis
    vec[0] = std::cos(w) * P - std::sin(w) * Q;
    vec[1] = std::sin(w) * P + std::cos(w) * Q;
    // rotate by inclination
    vec[2] = std::sin(i) * vec[1];
    vec[1] = std::cos(i) * vec[1];
    // rotate by longitude of ascending node
    double xtemp = vec[0];
    vec[0] = std::cos(W) * xtemp - std::sin(W) * vec[1];
    vec[1] = std::sin(W) * xtemp + std::cos(W) * vec[1];
}


#endif //UTILITIES_H
