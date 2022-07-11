#ifndef FLYBY_H
#define FLYBY_H

#include "planet.h"
#include "my_exceptions.h"
#include "utilities.h"

class FlyBy{
private:
    const Planet* planet;
    const float T;
    double v_planet[3];
    double v_in[3];
    double v_out[3];

    // Output from the Flyby 
    float peri;
    float alpha;
    double dv[3];

public:
    FlyBy(Planet* p, float T);
    ~FlyBy();
    void set_planet_v(double* v);
    void set_incoming_v(double* v);
    void set_outgoing_v(double* v);
    void compute_flyby();
    void get_deltaV(double* dv);
    double get_total_deltaV() const;
    float get_periphasis() const;
};

#endif //FLYBY_H