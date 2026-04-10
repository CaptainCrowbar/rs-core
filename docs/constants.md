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
| `minute`         | 60 s                       |
| `hour`           | 3600 s                     |
| `day`            | 86'400 s                   |
| `week`           | 604'800 s                  |
| `year`           | 31'557'600 s               |
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
| `atmosphere`     | 101'300 Pa                 |
| `zero_celsius`   | 273.15 K                   |

## Physical constants

Sources:

* [CODATA recommended values](https://physics.nist.gov/cuu/Constants/)

| Constant                     | Symbol       | Value                                                                |
| --------                     | ------       | -----                                                                |
| `alpha_particle_mass`        | `m_alpha`    | 6.645×10<sup>-27</sup> kg                                            |
| `atomic_mass_constant`       | `m_u`        | 1.661×10<sup>-27</sup> kg                                            |
| `avogadro_constant`          | `N_A`        | 6.022×10<sup>23</sup> mol<sup>-1</sup>                               |
| `boltzmann_constant`         | `k`          | 1.381×10<sup>-23</sup> J/K                                           |
| `electron_mass`              | `m_e`        | 9.109×10<sup>-31</sup> kg                                            |
| `elementary_charge`          | `ec`         | 1.602×10<sup>-19</sup> C                                             |
| `fine_structure_constant`    | `alpha`      | 7.297×10<sup>-3</sup> dimensionless                                  |
| `first_radiation_constant`   | `c_1`        | 3.742×10<sup>-16</sup> W m<sup>2</sup>                               |
| `gravitational_constant`     | `G`          | 6.674×10<sup>-11</sup> m<sup>3</sup> kg<sup>-1</sup> s<sup>-2</sup>  |
| `josephson_constant`         | `K_J`        | 4.836×10<sup>14</sup> Hz V<sup>-1</sup>                              |
| `molar_gas_constant`         | `R`          | 8.314 J mol<sup>-1</sup> K<sup>-1</sup>                              |
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
