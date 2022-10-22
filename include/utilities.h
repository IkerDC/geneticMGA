#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>
#include <string>
#include <ctime>
#include <bitset>
#include "astro.h"

#define MAX_BIT_SIZE 11  // 2048 (max time per leg ~ 11 years).

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

float rand_d();

int rand_rng(int min, int max);

std::string int2bitStr(const int x);

int bitStr2int(const std::string x);

std::string uniformBitstrCross(const std::string s1, const std::string s2);


#endif //UTILITIES_H
