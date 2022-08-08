#pragma once
#ifndef ORBITAL_MECHANICS_H
#define ORBITAL_MECHANICS_H

#define MAX_ITER 10000

#include "planet.h"
#include "utilities.h"

namespace orbit{
    void ephemeris(const Planet& planet, const double T, double* r, double* v);
    void lambert();
    void patched_conic(const double* Vin, const double* Vout, const double* Vplanet, const Planet& planet, double& dV, double& delta, double& peri);
}

#endif // ORBITAL_MECHANICS_H