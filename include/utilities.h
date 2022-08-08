#ifndef UTILITIES_H
#define UTILITIES_H

#include <cmath>

void minus2(const double* v1, const double* v2, double* out);

double norm(const double* v1);

double distance(const double* v1, const double* v2);

double dot_prod(const double* v1, const double* v2);

double vec2(const double* v1);

void rotate_eph(double w, double W, double i, double P, double Q, double* vec);


static double fb_vel(const double* v_rel_in, const double* v_rel_out, double safe_rad, double mu)
{
    double Vin2 = v_rel_in[0] * v_rel_in[0] + v_rel_in[1] * v_rel_in[1] + v_rel_in[2] * v_rel_in[2];
    double Vout2 = v_rel_out[0] * v_rel_out[0] + v_rel_out[1] * v_rel_out[1] + v_rel_out[2] * v_rel_out[2];
    // eq_V2 = Vin2 - Vout2;

    double e_min = 1 + safe_rad / mu * Vin2;
    double alpha = acos((v_rel_in[0] * v_rel_out[0] + v_rel_in[1] * v_rel_out[1] + v_rel_in[2] * v_rel_out[2])
                        / sqrt(Vin2 * Vout2));
    double ineq_delta = alpha - 2 * asin(1 / e_min);

    double dV = 0.0;
    if (ineq_delta > 0.0)
        dV = sqrt(Vout2 + Vin2 - 2.0 * sqrt(Vout2 * Vin2) * cos(ineq_delta));
    else
        dV = fabs(sqrt(Vout2) - sqrt(Vin2));

    return dV;
}


#endif //UTILITIES_H
