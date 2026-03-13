#pragma once

#include "rs-core/arithmetic.hpp"
#include "rs-core/constants.hpp"
#include "rs-core/global.hpp"
#include <array>
#include <cmath>
#include <concepts>
#include <numbers>
#include <span>

namespace RS {

    // Astronomical constants
    // IAU current best estimates: https://iau-a3.gitlab.io/NSFA/NSFA_cbe.html
    // IERS useful constants: https://hpiers.obspm.fr/eop-pc/models/constants.html

    RS_CORE_DEFINE_CONSTANT_2(astronomical_unit,               au,        1.495'978'707e11);        // m
    RS_CORE_DEFINE_CONSTANT_2(light_year,                      ly,        9.460'730'472'580'8e15);  // m
    RS_CORE_DEFINE_CONSTANT_2(parsec,                          pc,        3.085'677'581'49e16);     // m
    RS_CORE_DEFINE_CONSTANT_2(earth_mass,                      M_earth,   5.972'19e24);             // kg
    RS_CORE_DEFINE_CONSTANT_2(earth_radius,                    R_earth,   6'378'136.6);             // m
    RS_CORE_DEFINE_CONSTANT_2(standard_gravity,                g_0,       9.806'65);                // m s^-2
    RS_CORE_DEFINE_CONSTANT_2(julian_day,                      jd,        86'400.0);                // s
    RS_CORE_DEFINE_CONSTANT_2(sidereal_day,                    d_sid,     86'164.090'530'832'88);   // s
    RS_CORE_DEFINE_CONSTANT_2(tropical_year,                   y_trop,    31'556'925.25);           // s
    RS_CORE_DEFINE_CONSTANT_2(julian_year,                     jy,        31'557'600.0);            // s
    RS_CORE_DEFINE_CONSTANT_2(sidereal_year,                   y_sid,     31'558'149.76);           // s
    RS_CORE_DEFINE_CONSTANT_2(lunar_mass,                      M_moon,    7.345'81e22);             // kg
    RS_CORE_DEFINE_CONSTANT_2(lunar_radius,                    R_moon,    1.738'1e6);               // m
    RS_CORE_DEFINE_CONSTANT_2(lunar_distance,                  a_moon,    3.843'99e8);              // m
    RS_CORE_DEFINE_CONSTANT_2(sidereal_month,                  sid_mon,   2'360'591.6);             // s
    RS_CORE_DEFINE_CONSTANT_2(synodic_month,                   syn_mon,   2'551'442.9);             // s
    RS_CORE_DEFINE_CONSTANT_2(jupiter_mass,                    M_jup,     1.898'52e27);             // kg
    RS_CORE_DEFINE_CONSTANT_2(jupiter_radius,                  R_jup,     7.149'2e7);               // m
    RS_CORE_DEFINE_CONSTANT_2(solar_mass,                      M_sun,     1.988'42e30);             // kg
    RS_CORE_DEFINE_CONSTANT_2(solar_radius,                    R_sun,     6.957e8);                 // m
    RS_CORE_DEFINE_CONSTANT_2(solar_temperature,               T_sun,     5772.0);                  // K
    RS_CORE_DEFINE_CONSTANT_2(solar_luminosity,                L_sun,     3.828e26);                // W
    RS_CORE_DEFINE_CONSTANT_2(solar_visual_magnitude,          Mv_sun,    4.81);                    // mag
    RS_CORE_DEFINE_CONSTANT_2(solar_bolometric_magnitude,      Mbol_sun,  4.74);                    // mag
    RS_CORE_DEFINE_CONSTANT_2(solar_bolometric_correction,     BC_sun,    -0.07);                   // mag
    RS_CORE_DEFINE_CONSTANT_2(bolometric_luminosity_constant,  L_0,       3.012'8e28);              // W
    RS_CORE_DEFINE_CONSTANT_2(age_of_universe,                 t_0,       4.350'8e17);              // s

    // Astronomical formulae

    namespace Detail {

        template <std::floating_point T>
        constexpr T period_factor = Constants::G_v<T> / (T{4} * std::numbers::pi_v<T> * std::numbers::pi_v<T>);

        template <std::floating_point T>
        constexpr T luminosity_factor = T{4} * std::numbers::pi_v<T> * Constants::sigma_v<T>;

    }

    // Mass and density
    // m = (4/3) π r^3 d

    template <std::floating_point T>
    constexpr T mass_from_radius_density(T r, T d) noexcept {
        return d * sphere_volume_from_radius(r);
    }

    template <std::floating_point T>
    constexpr T radius_from_mass_density(T m, T d) noexcept {
        return sphere_radius_from_volume(m / d);
    }

    template <std::floating_point T>
    constexpr T density_from_mass_radius(T m, T r) noexcept {
        return m / sphere_volume_from_radius(r);
    }

    // Surface gravity
    // g = G m / r^2

    template <std::floating_point T>
    constexpr T gravity_from_mass_radius(T m, T r) noexcept {
        using namespace RS::Constants;
        return G_v<T> * m / (r * r);
    }

    // Orbital period
    // G M P^2 = 4 π^2 a^3

    template <std::floating_point T>
    T distance_from_mass_period(T m, T p) noexcept {
        using namespace RS::Detail;
        return std::cbrt(period_factor<T> * p * p * m);
    }

    template <std::floating_point T>
    T period_from_mass_distance(T m, T a) noexcept {
        using namespace RS::Detail;
        return std::sqrt(std::pow(a, T{3}) / (period_factor<T> * m));
    }

    // Hill sphere
    // r = a (m2 / 3 m1) ^ (1/3)
    // m1 is the primary, m2 is the body of interest

    template <std::floating_point T>
    T hill_radius(T m1, T m2, T a) noexcept {
        return a * std::cbrt(m2 / (T{3} * m1));
    }

    // Stellar luminosity
    // L = 4 π σ r^2 T^4

    template <std::floating_point T>
    T luminosity_from_radius_temperature(T r, T t) noexcept {
        using namespace RS::Detail;
        return r * r * std::pow(t, T{4}) * luminosity_factor<T>;
    }

    template <std::floating_point T>
    T radius_from_luminosity_temperature(T l, T t) noexcept {
        using namespace RS::Detail;
        return std::sqrt(l / (luminosity_factor<T> * std::pow(t, T{4})));
    }

    template <std::floating_point T>
    T temperature_from_luminosity_radius(T l, T r) noexcept {
        using namespace RS::Detail;
        return std::pow(l / (r * r * luminosity_factor<T>), static_cast<T>(0.25));
    }

    // Main sequence lifetime

    template <std::floating_point T>
    constexpr T main_sequence_lifetime(T m, T l) noexcept {
        using namespace RS::Constants;
        return (static_cast<T>(1e10) * jy_v<T> * L_sun_v<T> / M_sun_v<T>) * (m / l);
    }

    // Schwarzschild radius
    // r = 2 G M / c^2

    template <std::floating_point T>
    constexpr T schwarzschild_radius(T m) noexcept {
        using namespace RS::Constants;
        return (T{2} * G_v<T> / (c_v<T> * c_v<T>)) * m;
    }

    // Magnitude and luminosity

    template <std::floating_point T>
    T delta_magnitude_to_ratio(T dm) noexcept {
        return std::pow(T{10}, static_cast<T>(-0.4) * dm);
    }

    template <std::floating_point T>
    T ratio_to_delta_magnitude(T r) noexcept {
        return static_cast<T>(-2.5) * std::log10(r);
    }

    template <std::floating_point T>
    T bolometric_magitude_to_luminosity(T m) noexcept {
        using namespace RS::Constants;
        return L_sun_v<T> * std::pow(T{10}, static_cast<T>(0.4) * (Mbol_sun_v<T> - m));
    }

    template <std::floating_point T>
    T bolometric_luminosity_to_magnitude(T l) noexcept {
        using namespace RS::Constants;
        return Mbol_sun_v<T> - static_cast<T>(2.5) * std::log10(l / L_sun_v<T>);
    }

    // Bolometric correction
    // Guillermo Torres (2010), "On The Use Of Empirical Bolometric Corrections For Stars", https://arxiv.org/abs/1008.3913v1

    template <std::floating_point T>
    T temperature_to_bc(T t) noexcept {

        static constexpr std::array coeffs1 {
            static_cast<T>(-0.190'537'291'496'456e5),
            static_cast<T>(+0.155'144'866'764'412e5),
            static_cast<T>(-0.421'278'819'301'717e4),
            static_cast<T>(+0.381'476'328'422'343e3)
        };

        static constexpr std::array coeffs2 {
            static_cast<T>(-0.370'510'203'809'015e5),
            static_cast<T>(+0.385'672'629'965'804e5),
            static_cast<T>(-0.150'651'486'316'025e5),
            static_cast<T>(+0.261'724'637'119'416e4),
            static_cast<T>(-0.170'623'810'323'864e3)
        };

        static constexpr std::array coeffs3 {
            static_cast<T>(-0.118'115'450'538'963e6),
            static_cast<T>(+0.137'145'973'583'929e6),
            static_cast<T>(-0.636'233'812'100'225e5),
            static_cast<T>(+0.147'412'923'562'646e5),
            static_cast<T>(-0.170'587'278'406'872e4),
            static_cast<T>(+0.788'731'721'804'990e2)
        };

        auto log_t = std::log10(t);
        std::span<const T> range;

        if (log_t <= static_cast<T>(3.7)) {
            range = {coeffs1.begin(), coeffs1.end()};
        } else if (log_t <= static_cast<T>(3.9)) {
            range = {coeffs2.begin(), coeffs2.end()};
        } else {
            range = {coeffs3.begin(), coeffs3.end()};
        }

        T x{1};
        T bc{0};

        for (auto c: range) {
            bc += c * x;
            x *= log_t;
        }

        return bc;

    }

    // Planet temperature and illumination

    template <std::floating_point T>
    T planet_distance_to_temperature(T l, T a) noexcept {
        using namespace RS::Detail;
        return std::pow(l / (a * a * luminosity_factor<T> * T{4}), static_cast<T>(0.25));
    }

    template <std::floating_point T>
    T planet_temperature_to_distance(T l, T t) noexcept {
        using namespace RS::Detail;
        return std::sqrt(l / (T{4} * luminosity_factor<T> * std::pow(t, T{4})));
    }

    template <std::floating_point T>
    T planet_distance_to_illumination(T l, T a) noexcept {
        return l / sphere_area_from_radius(a);
    }

    template <std::floating_point T>
    T planet_illumination_to_temperature(T i) noexcept {
        using namespace RS::Constants;
        return std::pow(i / (T{4} * sigma_v<T>), static_cast<T>(0.25));
    }

}
