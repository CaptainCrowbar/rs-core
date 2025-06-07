# Physical constants

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/constants.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

# Introduction

All of the constants defined here follow the conventions of the standard
`<numbers>` header. Each constant is defined in two forms:

```c++
constexpr double name = [value as double];
template <std::floating_point T> constexpr T name_v = [value as T];
```

For the physical and astronomical constants, long and short versions of the
constant names are provided. The short names (but not the full names) are in
the `RS::Constants` sub-namespace to avoid name collisions when the symbols
are not needed.

The values quoted here are illustrative, mostly quoted to 4 significant
figures. The values actually supplied in the header are accurate to the
precision of the type or to the best known precision, whichever is
appropriate.

## Conversion factors

| Constant         | Value                      |
| --------         | -----                      |
| `arcsec`         | 4.848×10<sup>-6</sup> rad  |
| `arcmin`         | 2.909×10<sup>-4</sup> rad  |
| `degree`         | 0.01745 rad                |
| `inch`           | 0.0254 m                   |
| `foot`           | 0.3048 m                   |
| `yard`           | 0.9144 m                   |
| `mile`           | 1609 m                     |
| `nautical_mile`  | 1852 m                     |
| `ounce`          | 0.02835 kg                 |
| `pound`          | 0.4536 kg                  |
| `short_ton`      | 907.2 kg                   |
| `long_ton`       | 1016 kg                    |
| `pound_force`    | 4.448 N                    |
| `erg`            | 10<sup>-7</sup> J          |
| `foot_pound`     | 1.356 J                    |
| `calorie`        | 4.184 J                    |
| `kilocalorie`    | 4184 J                     |
| `ton_tnt`        | 4.184×10<sup>9</sup> J     |
| `horsepower`     | 745.7 W                    |
| `mmHg`           | 133.3 Pa                   |
| `atmosphere`     | 101300 Pa                  |
| `zero_celsius`   | 273.15 K                   |

## Physical constants

Sources:

* [CODATA recommended values](https://physics.nist.gov/cuu/Constants/)

Values related to quantity of substance are given in kilomoles to avoid
intrusive factors of 1000 in expressions.

| Constant                     | Symbol       | Value                                                                |
| --------                     | ------       | -----                                                                |
| `alpha_particle_mass`        | `m_alpha`    | 6.645×10<sup>-27</sup> kg                                            |
| `atomic_mass_constant`       | `m_u`        | 1.661×10<sup>-27</sup> kg                                            |
| `avogadro_constant`          | `N_A`        | 6.022×10<sup>26</sup> kmol<sup>-1</sup>                              |
| `boltzmann_constant`         | `k`          | 1.381×10<sup>-23</sup> J/K                                           |
| `electron_mass`              | `m_e`        | 9.109×10<sup>-31</sup> kg                                            |
| `elementary_charge`          | `ec`         | 1.602×10<sup>-19</sup> C                                             |
| `fine_structure_constant`    | `alpha`      | 7.297×10<sup>-3</sup> dimensionless                                  |
| `first_radiation_constant`   | `c_1`        | 3.742×10<sup>-16</sup> W m<sup>2</sup>                               |
| `gravitational_constant`     | `G`          | 6.674×10<sup>-11</sup> m<sup>3</sup> kg<sup>-1</sup> s<sup>-2</sup>  |
| `josephson_constant`         | `K_J`        | 4.836×10<sup>14</sup> Hz V<sup>-1</sup>                              |
| `molar_gas_constant`         | `R`          | 8314 J kmol<sup>-1</sup> K<sup>-1</sup>                              |
| `neutron_mass`               | `m_n`        | 1.675×10<sup>-27</sup> kg                                            |
| `planck_constant`            | `h`          | 6.626×10<sup>-34</sup> J s                                           |
| `proton_mass`                | `m_p`        | 1.673×10<sup>-27</sup> kg                                            |
| `rydberg_constant`           | `R_inf`      | 1.097×10<sup>7</sup> m<sup>-1</sup>                                  |
| `second_radiation_constant`  | `c_2`        | 0.01439×10<sup>-2</sup> m K                                          |
| `speed_of_light`             | `c`          | 2.998×10<sup>8</sup> m/s                                             |
| `stefan_boltzmann_constant`  | `sigma`      | 5.670×10<sup>-8</sup> W m<sup>-2</sup> K<sup>-4</sup>                |
| `vacuum_impedance`           | `Z_0`        | 376.7 Ω                                                              |
| `vacuum_permeability`        | `mu_0`       | 1.257×10<sup>-6</sup> N A<sup>-2</sup>                               |
| `vacuum_permittivity`        | `epsilon_0`  | 8.854×10<sup>-12</sup> F m<sup>-1</sup>                              |
| `von_klitzing_constant`      | `R_K`        | 25810 Ω                                                              |
| `wien_constant`              | `b_W`        | 2.898×10<sup>-3</sup> m K                                            |

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
