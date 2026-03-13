# Astronomical Constants and Functions

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/astronomy.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Astronomical constants

Sources:

* [IAU current best estimates](https://iau-a3.gitlab.io/NSFA/NSFA_cbe.html)
* [IERS useful constants](https://hpiers.obspm.fr/eop-pc/models/constants.html)

| Constant                          | Symbol      | Value                     |
| --------                          | ------      | -----                     |
| `astronomical_unit`               | `au`        | 1.496×10<sup>11</sup> m   |
| `light_year`                      | `ly`        | 9.461×10<sup>15</sup> m   |
| `parsec`                          | `pc`        | 3.086×10<sup>16</sup> m   |
| `earth_mass`                      | `M_earth`   | 5.972×10<sup>24</sup> kg  |
| `earth_radius`                    | `R_earth`   | 6.378×10<sup>6</sup> m    |
| `standard_gravity`                | `g_0`       | 9.807 m s<sup>-2</sup>    |
| `julian_day`                      | `jd`        | 86400 s                   |
| `sidereal_day`                    | `d_sid`     | 86160 s                   |
| `tropical_year`                   | `y_trop`    | 3.156×10<sup>7</sup> s    |
| `julian_year`                     | `jy`        | 3.156×10<sup>7</sup> s    |
| `sidereal_year`                   | `y_sid`     | 3.156×10<sup>7</sup> s    |
| `lunar_mass`                      | `M_moon`    | 7.346×10<sup>22</sup> kg  |
| `lunar_radius`                    | `R_moon`    | 1.738×10<sup>6</sup> m    |
| `lunar_distance`                  | `a_moon`    | 3.844×10<sup>8</sup> m    |
| `sidereal_month`                  | `sid_mon`   | 2.361×10<sup>6</sup> s    |
| `synodic_month`                   | `syn_mon`   | 2.551×10<sup>6</sup> s    |
| `jupiter_mass`                    | `M_jup`     | 1.899×10<sup>27</sup> kg  |
| `jupiter_radius`                  | `R_jup`     | 7.149×10<sup>7</sup> m    |
| `solar_mass`                      | `M_sun`     | 1.988×10<sup>30</sup> kg  |
| `solar_radius`                    | `R_sun`     | 6.957×10<sup>8</sup> m    |
| `solar_temperature`               | `T_sun`     | 5772 K                    |
| `solar_luminosity`                | `L_sun`     | 3.828×10<sup>26</sup> W   |
| `solar_visual_magnitude`          | `Mv_sun`    | 4.81 mag                  |
| `solar_bolometric_magnitude`      | `Mbol_sun`  | 4.74 mag                  |
| `solar_bolometric_correction`     | `BC_sun`    | -0.07 mag                 |
| `bolometric_luminosity_constant`  | `L_0`       | 3.013×10<sup>28</sup> W   |
| `age_of_universe`                 | `t_0`       | 4.351×10<sup>17</sup> s   |

## Astronomical formulae

All of these assume that all arguments, and the return value, are expressed in
SI units (apart from stellar magnitudes).

```c++
template <std::floating_point T>
    constexpr T mass_from_radius_density(T r, T d) noexcept;
template <std::floating_point T>
    constexpr T radius_from_mass_density(T m, T d) noexcept;
template <std::floating_point T>
    constexpr T density_from_mass_radius(T m, T r) noexcept;
```

Relationship between radius, density, and mass of a sphere.

```c++
template <std::floating_point T>
    constexpr T gravity_from_mass_radius(T m, T r) noexcept;
```

Relationship between mass, radius, and surface gravity of a body.

```c++
template <std::floating_point T>
    T distance_from_mass_period(T m, T p) noexcept;
template <std::floating_point T>
    T period_from_mass_distance(T m, T a) noexcept;
```

Relationship between primary mass, semimajor axis, and orbit period.

Formula: _G M P<sup>2</sup> = 4 π<sup>2</sup> a<sup>3</sup>_

```c++
template <std::floating_point T>
    T hill_radius(T m1, T m2, T a) noexcept;
```

Radius of the Hill sphere for a planet. Here `m1` is the mass of the primary
(star), `m2` is the mass of the secondary (planet).

Formula: _r = a (m<sub>2</sub> / 3 m<sub>1</sub>)<sup>1/3</sup>_

```c++
template <std::floating_point T>
    T luminosity_from_radius_temperature(T r, T t) noexcept;
template <std::floating_point T>
    T radius_from_luminosity_temperature(T l, T t) noexcept;
template <std::floating_point T>
    T temperature_from_luminosity_radius(T l, T r) noexcept;
```

Relationship between radius, effective temperature, and luminosity of a star.

Formula: _L = 4 π σ r<sup>2</sup> T<sup>4</sup>_

```c++
template <std::floating_point T>
    constexpr T main_sequence_lifetime(T m, T l) noexcept;
```

Estimated main sequence lifetime of a star, given its mass and main sequence
luminosity.

```c++
template <std::floating_point T>
    constexpr T schwarzschild_radius(T m) noexcept;
```

Schwarzschild radius of a black hole, given its mass.

Formula: _r = 2 G M / c<sup>2</sup>_

```c++
template <std::floating_point T>
    T delta_magnitude_to_ratio(T dm) noexcept;
template <std::floating_point T>
    T ratio_to_delta_magnitude(T r) noexcept;
template <std::floating_point T>
    T bolometric_magitude_to_luminosity(T m) noexcept;
template <std::floating_point T>
    T bolometric_luminosity_to_magnitude(T l) noexcept;
```

Relationship between stellar magnitude and luminosity.

```c++
template <std::floating_point T>
    T temperature_to_bc(T t) noexcept;
```

Estimated bolometric correction for a star, given its effective temperature.

Source: [Guillermo Torres (2010), "On the Use of Empirical Bolometric Corrections for Stars"](https://arxiv.org/abs/1008.3913v1)

```c++
template <std::floating_point T>
    T planet_distance_to_temperature(T l, T a) noexcept;
template <std::floating_point T>
    T planet_temperature_to_distance(T l, T t) noexcept;
template <std::floating_point T>
    T planet_distance_to_illumination(T l, T a) noexcept;
template <std::floating_point T>
    T planet_illumination_to_temperature(T i) noexcept;
```

Relationship between the luminosity of a star, the distance of a planet, the
illumination per unit area, and the equilibrium temperature (assuming a
blackbody planet).
