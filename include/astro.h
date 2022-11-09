#ifndef ASTRO_H
#define ASTRO_H

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

#define PI 3.14159265359
#define EXP 2.71828182846

namespace kepler_orbits
{
    // JPL approximate ephemeris of plantes 1800 AD to 2050 AD
    static const float mercury[6] = {0.38709927, 0.20563593, 7.00497902, 252.25032350, 77.45779628, 48.33076593};
    static const float venus[6] = {0.72333566, 0.00677672, 3.39467605, 181.97909950, 131.60246718, 76.67984255};
    static const float earth[6] = {1.00000261, 0.01671123, -0.00001531, 100.46457166, 102.93768193, 0.0};
    static const float mars[6] = {1.52371034, 0.09339410, 1.84969142, -4.55343205, -23.94362959, 49.55953891};
    static const float jupiter[6] = {5.20288700, 0.04838624, 1.30439695, 34.39644051, 14.72847983, 100.47390909};
    static const float saturn[6] = {9.53667594, 0.05386179, 2.48599187, 49.95424423, 92.59887831, 113.66242448};
    static const float uranus[6] = {19.18916464, 0.04725744, 0.77263783, 313.23810451, 170.95427630, 74.01692503};
    static const float neptune[6] = {30.06992276, 0.00859048, 1.77004347, -55.12002969, 44.96476227, 131.78422574};

    // Cy values
    static const float mercury_cy[6] = {0.00000037, 0.00001906, -0.00594749, 149472.67411175, 0.16047689, -0.12534081};
    static const float venus_cy[6] = {0.00000390, -0.00004107, -0.00078890, 58517.81538729, 0.00268329, -0.27769418};
    static const float earth_cy[6] = {0.00000562, -0.00004392,  -0.01294668, 35999.37244981, 0.32327364, 0.0};
    static const float mars_cy[6] = {0.00001847, 0.00007882, -0.00813131, 19140.30268499, 0.44441088, -0.29257343};
    static const float jupiter_cy[6] = {-0.00011607, -0.00013253, -0.00183714, 3034.74612775, 0.21252668, 0.20469106};
    static const float saturn_cy[6] = {-0.00125060, -0.00050991,  0.00193609, 1222.49362201, -0.41897216, -0.28867794};
    static const float uranus_cy[6] = {-0.00196176, -0.00004397, -0.00242939, 428.48202785, 0.40805281, 0.04240589};
    static const float neptune_cy[6] = {0.00026291, 0.00005105, 0.00035372, 218.45945325, -0.32241464, -0.00508664};
} // namespace kepler_orbits

namespace planet_props{
    static const double mercury_mu = 2.2032e13;
    static const double venus_mu = 3.24859e14;
    static const double earth_mu = 3.986004418e14;
    static const double mars_mu = 4.282837e13;
    static const double jupiter_mu = 1.26686534e17;
    static const double saturn_mu = 3.7931187e16;
    static const double uranus_mu = 6.836529e15;
    static const double neptune_mu = 5.793939e15;

    static const double mercury_k = 1.05;
    static const double venus_k = 1.05;
    static const double earth_k = 1.05;
    static const double mars_k = 1.05;
    static const double jupiter_k = 1.05;
    static const double saturn_k = 1.05;
    static const double uranus_k = 1.05;
    static const double neptune_k = 1.05;
} // namespace planet_props

struct orbitalParameters{
    float a0, acy; // semi-major axis
    float e0, ecy; // eccentricity
    float I0, Icy; // inlcinations
    float L0, Lcy; // mean longitude
    float long_peri0, long_pericy; // longitude of preiphasis
    float long_node0, long_nodecy; // acending node lingitude
};
    
#endif //ASTRO_H