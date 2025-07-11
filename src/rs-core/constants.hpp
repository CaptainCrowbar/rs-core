#pragma once

#include "rs-core/global.hpp"
#include <concepts>

#define RS_DEFINE_CONSTANT_1_(name, value) \
    template <std::floating_point T> constexpr T name ## _v = T(value ## l); \
    constexpr double name = name ## _v<double>;

#define RS_DEFINE_CONSTANT_2_(name, symbol, value) \
    template <std::floating_point T> constexpr T name ## _v = T(value ## l); \
    constexpr double name = name ## _v<double>; \
    namespace Constants { \
        template <std::floating_point T> constexpr T symbol ## _v = name ## _v<T>; \
        constexpr double symbol = symbol ## _v<double>; \
    }

namespace RS {

    // Conversion factors

    RS_DEFINE_CONSTANT_1_(arcsec,         4.84813'68110'95359'93589'91410'2358e-6);  // rad
    RS_DEFINE_CONSTANT_1_(arcmin,         2.90888'20866'57215'96153'94846'1415e-4);  // rad
    RS_DEFINE_CONSTANT_1_(degree,         1.74532'92519'94329'57692'36907'6849e-2);  // rad
    RS_DEFINE_CONSTANT_1_(inch,           0.0254);                                   // m
    RS_DEFINE_CONSTANT_1_(foot,           0.3048);                                   // m
    RS_DEFINE_CONSTANT_1_(yard,           0.9144);                                   // m
    RS_DEFINE_CONSTANT_1_(mile,           1609.344);                                 // m
    RS_DEFINE_CONSTANT_1_(nautical_mile,  1852.0);                                   // m
    RS_DEFINE_CONSTANT_1_(ounce,          0.028'349'523'125);                        // kg
    RS_DEFINE_CONSTANT_1_(pound,          0.453'592'37);                             // kg
    RS_DEFINE_CONSTANT_1_(short_ton,      907.184'74);                               // kg
    RS_DEFINE_CONSTANT_1_(long_ton,       1016.046'908'8);                           // kg
    RS_DEFINE_CONSTANT_1_(pound_force,    4.448'221'615'260'5);                      // N
    RS_DEFINE_CONSTANT_1_(erg,            1e-7);                                     // J
    RS_DEFINE_CONSTANT_1_(foot_pound,     1.355'817'948'331'400'4);                  // J
    RS_DEFINE_CONSTANT_1_(calorie,        4.184);                                    // J
    RS_DEFINE_CONSTANT_1_(kilocalorie,    4184.0);                                   // J
    RS_DEFINE_CONSTANT_1_(ton_tnt,        4.184e9);                                  // J
    RS_DEFINE_CONSTANT_1_(horsepower,     745.699'871'582'270'22);                   // W
    RS_DEFINE_CONSTANT_1_(mmHg,           133.322'387'415);                          // Pa
    RS_DEFINE_CONSTANT_1_(atmosphere,     101'325.0);                                // Pa
    RS_DEFINE_CONSTANT_1_(zero_celsius,   273.15);                                   // K

    // Physical constants
    // CODATA recommended values: https://physics.nist.gov/cuu/Constants/

    // Values related to quantity of substance are given in kilomoles to avoid
    // intrusive factors of 1000 in expressions.

    RS_DEFINE_CONSTANT_2_(alpha_particle_mass,        m_alpha,    6.644'657'3357e-27);    // kg
    RS_DEFINE_CONSTANT_2_(atomic_mass_constant,       m_u,        1.660'539'066'60e-27);  // kg
    RS_DEFINE_CONSTANT_2_(avogadro_constant,          N_A,        6.022'140'76e26);       // kmol^-1
    RS_DEFINE_CONSTANT_2_(boltzmann_constant,         k,          1.380'649e-23);         // J/K
    RS_DEFINE_CONSTANT_2_(electron_mass,              m_e,        9.109'383'7015e-31);    // kg
    RS_DEFINE_CONSTANT_2_(elementary_charge,          ec,         1.602'176'634e-19);     // C
    RS_DEFINE_CONSTANT_2_(fine_structure_constant,    alpha,      7.297'352'5693e-3);     // dimensionless
    RS_DEFINE_CONSTANT_2_(first_radiation_constant,   c_1,        3.741'771'852e-16);     // W m^2 (c_1 = 2π h c^2)
    RS_DEFINE_CONSTANT_2_(gravitational_constant,     G,          6.674'28e-11);          // m^3 kg^-1 s^-2
    RS_DEFINE_CONSTANT_2_(josephson_constant,         K_J,        4.835'978'484e14);      // Hz V^-1 (K_J = 2e/h)
    RS_DEFINE_CONSTANT_2_(molar_gas_constant,         R,          8'314.462'618);         // J kmol^-1 K^-1 (R = N_A k)
    RS_DEFINE_CONSTANT_2_(neutron_mass,               m_n,        1.674'927'498'04e-27);  // kg
    RS_DEFINE_CONSTANT_2_(planck_constant,            h,          6.626'070'15e-34);      // J s
    RS_DEFINE_CONSTANT_2_(proton_mass,                m_p,        1.672'621'923'69e-27);  // kg
    RS_DEFINE_CONSTANT_2_(rydberg_constant,           R_inf,      10'973'731.568'160);    // m^-1 (R_∞ = m_e e^4/8 ε_0^2 h^3 c)
    RS_DEFINE_CONSTANT_2_(second_radiation_constant,  c_2,        1.438'776'877e-2);      // m K (c_2 = h c/k)
    RS_DEFINE_CONSTANT_2_(speed_of_light,             c,          299'792'458.0);         // m/s
    RS_DEFINE_CONSTANT_2_(stefan_boltzmann_constant,  sigma,      5.670'374'419e-8);      // W m^-2 K^-4 (σ = π^2 k^4/60 ℏ^3 c^2)
    RS_DEFINE_CONSTANT_2_(vacuum_impedance,           Z_0,        376.730'313'668);       // Ω (Z_0 = μ_0 c)
    RS_DEFINE_CONSTANT_2_(vacuum_permeability,        mu_0,       1.256'637'062'12e-6);   // N A^-2 (μ_0 = 4π α ℏ/e^2 c)
    RS_DEFINE_CONSTANT_2_(vacuum_permittivity,        epsilon_0,  8.854'187'812'8e-12);   // F m^-1 (ε_0 = 1/μ_0 c^2)
    RS_DEFINE_CONSTANT_2_(von_klitzing_constant,      R_K,        25'812.807'45);         // Ω (R_K = h/e^2)
    RS_DEFINE_CONSTANT_2_(wien_constant,              b_W,        2.897'771'955e-3);      // m K

    // Astronomical constants
    // IAU current best estimates: https://iau-a3.gitlab.io/NSFA/NSFA_cbe.html
    // IERS useful constants: https://hpiers.obspm.fr/eop-pc/models/constants.html

    RS_DEFINE_CONSTANT_2_(astronomical_unit,               au,        1.495'978'707e11);        // m
    RS_DEFINE_CONSTANT_2_(light_year,                      ly,        9.460'730'472'580'8e15);  // m
    RS_DEFINE_CONSTANT_2_(parsec,                          pc,        3.085'677'581'49e16);     // m
    RS_DEFINE_CONSTANT_2_(earth_mass,                      M_earth,   5.972'19e24);             // kg
    RS_DEFINE_CONSTANT_2_(earth_radius,                    R_earth,   6'378'136.6);             // m
    RS_DEFINE_CONSTANT_2_(standard_gravity,                g_0,       9.806'65);                // m s^-2
    RS_DEFINE_CONSTANT_2_(julian_day,                      jd,        86'400.0);                // s
    RS_DEFINE_CONSTANT_2_(sidereal_day,                    d_sid,     86'164.090'530'832'88);   // s
    RS_DEFINE_CONSTANT_2_(tropical_year,                   y_trop,    31'556'925.25);           // s
    RS_DEFINE_CONSTANT_2_(julian_year,                     jy,        31'557'600.0);            // s
    RS_DEFINE_CONSTANT_2_(sidereal_year,                   y_sid,     31'558'149.76);           // s
    RS_DEFINE_CONSTANT_2_(lunar_mass,                      M_moon,    7.345'81e22);             // kg
    RS_DEFINE_CONSTANT_2_(lunar_radius,                    R_moon,    1.738'1e6);               // m
    RS_DEFINE_CONSTANT_2_(lunar_distance,                  a_moon,    3.843'99e8);              // m
    RS_DEFINE_CONSTANT_2_(sidereal_month,                  sid_mon,   2'360'591.6);             // s
    RS_DEFINE_CONSTANT_2_(synodic_month,                   syn_mon,   2'551'442.9);             // s
    RS_DEFINE_CONSTANT_2_(jupiter_mass,                    M_jup,     1.898'52e27);             // kg
    RS_DEFINE_CONSTANT_2_(jupiter_radius,                  R_jup,     7.149'2e7);               // m
    RS_DEFINE_CONSTANT_2_(solar_mass,                      M_sun,     1.988'42e30);             // kg
    RS_DEFINE_CONSTANT_2_(solar_radius,                    R_sun,     6.957e8);                 // m
    RS_DEFINE_CONSTANT_2_(solar_temperature,               T_sun,     5772.0);                  // K
    RS_DEFINE_CONSTANT_2_(solar_luminosity,                L_sun,     3.828e26);                // W
    RS_DEFINE_CONSTANT_2_(solar_visual_magnitude,          Mv_sun,    4.81);                    // mag
    RS_DEFINE_CONSTANT_2_(solar_bolometric_magnitude,      Mbol_sun,  4.74);                    // mag
    RS_DEFINE_CONSTANT_2_(solar_bolometric_correction,     BC_sun,    -0.07);                   // mag
    RS_DEFINE_CONSTANT_2_(bolometric_luminosity_constant,  L_0,       3.012'8e28);              // W
    RS_DEFINE_CONSTANT_2_(age_of_universe,                 t_0,       4.350'8e17);              // s

}

#undef RS_DEFINE_CONSTANT_1_
#undef RS_DEFINE_CONSTANT_2_
