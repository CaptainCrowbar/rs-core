#include "rs-core/astronomy.hpp"
#include "rs-core/unit-test.hpp"
#include <cmath>

using namespace RS;
using namespace RS::Constants;

void test_rs_core_astronomy_constants() {

    TEST_NEAR(astronomical_unit,  1.495'978'707e11,  10);
    TEST_NEAR(julian_year,        31'557'600.0,      1e-3);
    TEST_NEAR(solar_mass,         1.988'42e30,       1e20);
    TEST_NEAR(au,                 1.495'978'707e11,  10);
    TEST_NEAR(jy,                 31'557'600.0,      1e-3);
    TEST_NEAR(M_sun,              1.988'42e30,       1e20);

}

void test_rs_core_astronomy_mass_density() {

    auto d = 5000.0;
    auto m = 20'943'952.0;
    auto r = 10.0;

    TEST_NEAR(mass_from_radius_density(r, d), m, 1);
    TEST_NEAR(radius_from_mass_density(m, d), r, 1e-4);
    TEST_NEAR(density_from_mass_radius(m, r), d, 0.01);

}

void test_rs_core_astronomy_surface_gravity() {

    TEST_NEAR(gravity_from_mass_radius(M_earth, R_earth), 9.8, 0.01);

}

void test_rs_core_astronomy_orbital_period() {

    TEST_NEAR(distance_from_mass_period(M_sun, jy), au, 1e7);
    TEST_NEAR(period_from_mass_distance(M_sun, au), jy, 1000);

}

void test_rs_core_astronomy_hill_sphere() {

    TEST_NEAR(hill_radius(M_sun, M_earth, au), 1.497e9, 1e6);
    TEST_NEAR(hill_radius(M_sun, M_jup, 5.20336 * au), 5.315e10, 1e7);

}

void test_rs_core_astronomy_stellar_luminosity() {

    TEST_NEAR(luminosity_from_radius_temperature(R_sun, T_sun), L_sun, 1e21);
    TEST_NEAR(radius_from_luminosity_temperature(L_sun, T_sun), R_sun, 1000);
    TEST_NEAR(temperature_from_luminosity_radius(L_sun, R_sun), T_sun, 0.01);

}

void test_rs_core_astronomy_stellar_lifetime() {

    TEST_NEAR(main_sequence_lifetime(M_sun, L_sun), 1e10 * jy, jy);

}

void test_rs_core_astronomy_schwarzschild_radius() {

    TEST_NEAR(schwarzschild_radius(M_sun), 2953, 1);
}

void test_rs_core_astronomy_magnitude_luminosity() {

    TEST_NEAR(delta_magnitude_to_ratio(-5.0), 100, 1e-4);
    TEST_EQUAL(delta_magnitude_to_ratio(0.0), 1);
    TEST_NEAR(delta_magnitude_to_ratio(5.0), 0.01, 1e-8);
    TEST_NEAR(ratio_to_delta_magnitude(100.0), -5, 1e-6);
    TEST_EQUAL(ratio_to_delta_magnitude(1.0), 0);
    TEST_NEAR(ratio_to_delta_magnitude(0.01), 5, 1e-6);
    TEST_NEAR(bolometric_magitude_to_luminosity(Mbol_sun - 5), L_sun * 100, L_sun * 1e-4);
    TEST_NEAR(bolometric_magitude_to_luminosity(Mbol_sun), L_sun, L_sun * 1e-6);
    TEST_NEAR(bolometric_magitude_to_luminosity(Mbol_sun + 5), L_sun * 0.01, L_sun * 1e-8);
    TEST_NEAR(bolometric_luminosity_to_magnitude(L_sun * 100), Mbol_sun - 5, 1e-6);
    TEST_NEAR(bolometric_luminosity_to_magnitude(L_sun), Mbol_sun, 1e-6);
    TEST_NEAR(bolometric_luminosity_to_magnitude(L_sun * 0.01), Mbol_sun + 5, 1e-6);

}

void test_rs_core_astronomy_bolometric_correction() {

    TEST_NEAR(temperature_to_bc(std::pow(10.0, 4.70)), -4.49, 0.005);  // O3
    TEST_NEAR(temperature_to_bc(5772.0), -0.08, 0.005);                // Sun
    TEST_NEAR(temperature_to_bc(std::pow(10.0, 3.48)), -4.85, 0.005);  // M9

}

void test_rs_core_astronomy_planet_temperature() {

    TEST_NEAR(planet_distance_to_temperature(L_sun, au * 0.01), 2783.30, 0.01);
    TEST_NEAR(planet_distance_to_temperature(L_sun, au), 278.330, 0.001);
    TEST_NEAR(planet_distance_to_temperature(L_sun, au * 100), 27.8330, 0.0001);
    TEST_NEAR(planet_temperature_to_distance(L_sun, 2783.30), au * 0.01, 1e-8 * au);
    TEST_NEAR(planet_temperature_to_distance(L_sun, 278.330), au, 1e-6 * au);
    TEST_NEAR(planet_temperature_to_distance(L_sun, 27.8330), au * 100, 1e-4 * au);
    TEST_NEAR(planet_distance_to_illumination(L_sun, au * 0.01), 1.36117e7, 100);
    TEST_NEAR(planet_distance_to_illumination(L_sun, au), 1361.17, 0.01);
    TEST_NEAR(planet_distance_to_illumination(L_sun, au * 100), 0.136117, 1e-6);
    TEST_NEAR(planet_illumination_to_temperature(1.36117e7), 2783.30, 0.01);
    TEST_NEAR(planet_illumination_to_temperature(1361.17), 278.330, 0.001);
    TEST_NEAR(planet_illumination_to_temperature(0.136117), 27.8330, 0.0001);

}
