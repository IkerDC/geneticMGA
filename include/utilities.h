#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <string>
#include <ctime>
#include "curl/curl.h"

#include "astro.h"

void minus2(const double* v1, const double* v2, double* out);

double norm(const double* v1);

double distance(const double* v1, const double* v2);

double dot_prod(const double* v1, const double* v2);

double vec2(const double* v1);

void rotate_eph(double w, double W, double i, double P, double Q, double* vec);

void cross_prod(const double* v1, const double* v2, double* out);

double tofabn(const double &sigma,const double &alfa,const double &beta);

void vers(const double* v1, double* v2);

double x2tof(const double &x, const double &s, const double &c, bool prograde);

double deg2rad(const double x);

double rad2deg(const double x);



#endif //UTILITIES_H
