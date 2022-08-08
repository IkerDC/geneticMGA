#include "utilities.h"


void minus2(const double* v1, const double* v2, double* out){
    for(unsigned int i = 0; i < 3; i++){
        out[i] = v1[i] - v2[i];
    }
}


double norm(const double* v1){
    double out = 0.0;
    for(unsigned int i = 0; i < 3; i++){
        out += v1[i] * v1[i];
    }
    return std::sqrt(out);
}


double distance(const double* v1, const double* v2){
    double out = 0.0;
    for(unsigned int i = 0; i < 3; i++){
        out += (v1[i] - v2[i]) * (v1[i] - v2[i]);
    }
    return std::sqrt(out);
}


double dot_prod(const double* v1, const double* v2){
    double out = 0.0;
    for(unsigned int i = 0; i < 3; i++){
        out += v1[i] * v2[i]; 
    }
    return out;
}


double vec2(const double* v1){
    double out = 0.0;
    for(unsigned int i = 0; i < 3; i++){
        out += v1[i] * v1[i]; 
    }
    return out;
}

void rotate_eph(double w, double W, double i, double P, double Q, double* vec){
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