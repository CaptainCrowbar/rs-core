# Linear Algebra

_[Core utility library by Ross Smith](index.html)_

```c++
#include "rs-core/linear-algebra.hpp"
namespace RS;
```

## Contents

* TOC
{:toc}

## Supporting types

```c++
enum class MatrixLayout {
    column,
    row,
}
```

Flags indicating the internal layout of a matrix (column major or row major).
Column major is the default.

## Vector class

```c++
template <typename T, std::size_t N> class Vector;
```

An `N`-dimensional vector type.

```c++
using Byte2 = Vector<uint8_t, 2>;
using Byte3 = Vector<uint8_t, 3>;
using Byte4 = Vector<uint8_t, 4>;
using Int2 = Vector<int, 2>;
using Int3 = Vector<int, 3>;
using Int4 = Vector<int, 4>;
using Size2 = Vector<std::size_t, 2>;
using Size3 = Vector<std::size_t, 3>;
using Size4 = Vector<std::size_t, 4>;
using Float2 = Vector<float, 2>;
using Float3 = Vector<float, 3>;
using Float4 = Vector<float, 4>;
using Double2 = Vector<double, 2>;
using Double3 = Vector<double, 3>;
using Double4 = Vector<double, 4>;
using Ldouble2 = Vector<long double, 2>;
using Ldouble3 = Vector<long double, 3>;
using Ldouble4 = Vector<long double, 4>;
```

Predefined type aliases.

```c++
using Vector::value_type = T;
using Vector::iterator = T*;
using Vector::const_iterator = const T*;
```

Member types.

```c++
static constexpr std::size_t Vector::dim = N;
```

Member constants.

```c++
constexpr Vector::Vector() noexcept;
```

The default constructor sets all elements to zero.

```c++
constexpr explicit Vector::Vector(T x) noexcept;
```

Sets all of the vector's elements to the same value.

```c++
template <typename... Args> constexpr Vector::Vector(Args... args) noexcept;
```

This takes an explicit list of elements, and is only defined for the
appropriate number of arguments.

```c++
constexpr explicit Vector::Vector(const T* ptr) noexcept;
```

This copies the elements from the pointed-to data. Behaviour is undefined if
the pointer is null or does not point to an array of at least `N` elements.

```c++
template <typename U>
    constexpr explicit Vector::Vector(const Vector<U, N>& v) noexcept;
```

Converts a vector from one element type to another.

```c++
constexpr Vector::Vector(const Vector& v) noexcept;
constexpr Vector::Vector(Vector&& v) noexcept;
constexpr Vector::~Vector() noexcept;
constexpr Vector& Vector::operator=(const Vector& v) noexcept;
constexpr Vector& Vector::operator=(Vector&& v) noexcept;
```

Other life cycle functions.

```c++
constexpr T& Vector::operator[](std::size_t i) noexcept;
constexpr const T& Vector::operator[](std::size_t i) const noexcept;
constexpr T& Vector::x() noexcept;
constexpr const T& Vector::x() const noexcept;
constexpr T& Vector::y() noexcept;
constexpr const T& Vector::y() const noexcept;
constexpr T& Vector::z() noexcept;
constexpr const T& Vector::z() const noexcept;
constexpr T& Vector::w() noexcept;
constexpr const T& Vector::w() const noexcept;
```

Element access functions. For the index operator, behaviour is undefined if
`i>=N.` The `x(), y(), z()`, and `w()` functions return the first four
elements (or references to them), and are only defined if `N` is large
enough.

```c++
constexpr T* Vector::begin() noexcept;
constexpr const T* Vector::begin() const noexcept;
constexpr T* Vector::end() noexcept;
constexpr const T* Vector::end() const noexcept;
```

These return pointers to the beginning and past the end of the vector.

```c++
constexpr Vector Vector::operator+() const noexcept;
constexpr Vector Vector::operator-() const noexcept;
constexpr Vector& Vector::operator+=(const Vector& v) noexcept;
constexpr Vector& Vector::operator-=(const Vector& v) noexcept;
constexpr Vector& Vector::operator*=(const Vector& v) noexcept;
constexpr Vector& Vector::operator/=(const Vector& v) noexcept;
constexpr Vector operator+(const Vector& u, const Vector& v) noexcept;
constexpr Vector operator-(const Vector& u, const Vector& v) noexcept;
constexpr Vector operator*(const Vector& u, const Vector& v) noexcept;
constexpr Vector operator/(const Vector& u, const Vector& v) noexcept;
```

Element-wise arithmetic operators. Behaviour is undefined on division by
zero.

```c++
constexpr Vector& Vector::operator*=(T x) noexcept;
constexpr Vector& Vector::operator/=(T x) noexcept;
constexpr Vector operator*(const Vector& v, T x) noexcept;
constexpr Vector operator*(T x, const Vector& v) noexcept;
constexpr Vector operator/(const Vector& v, T x) noexcept;
```

Vector-scalar arithmetic operators. Behaviour is undefined on division by
zero.

```c++
constexpr T Vector::dot(const Vector& v) const noexcept;
constexpr Vector Vector::cross(const Vector& v) const noexcept;
constexpr T operator%(const Vector& u, const Vector& v) noexcept;
constexpr Vector& operator^=(Vector& u, const Vector& v) noexcept;
constexpr Vector operator^(const Vector& u, const Vector& v) noexcept;
```

Vector arithmetic operations. The `%` and `^` operators are synonyms for
`dot()` and `cross()` respectively. The `cross()` function and the `^`
operators are only defined if `N=3`.

```c++
constexpr bool operator==(const Vector& u, const Vector& v) noexcept;
constexpr bool operator!=(const Vector& u, const Vector& v) noexcept;
```

Comparison operators.

```c++
constexpr T Vector::angle(const Vector& v) const noexcept;
```

Returns the angle between two vectors, in the range `[0,π]`. This will return
zero if either vector is null. Behaviour is undefined if `T` is not a floating
point type.

```c++
constexpr Vector Vector::dir() const noexcept;
```

Returns a unit vector parallel to this vector (or an approximation to it,
given the limits of floating point arithmetic). Returns null if the vector is
null. Behaviour is undefined if `T` is not a floating point type.

```c++
constexpr bool Vector::empty() noexcept;
```

Always false.

```c++
constexpr bool Vector::is_null() const noexcept;
```

True if the vector is null (all elements are zero).

```c++
constexpr Vector Vector::project(const Vector& v) const noexcept;
constexpr Vector Vector::reject(const Vector& v) const noexcept;
```

These return the projection and rejection of `v` onto this vector
(the components of `v` parallel and orthogonal to this, respectively). If
this is null, `project()` returns null and `reject()` returns `v`.

```c++
constexpr T Vector::r() const noexcept;
constexpr T Vector::r2() const noexcept;
```

These return the length of the vector, or its square. The `r2()` function will
work with any arithmetic type (provided the result does not overflow), but
behaviour is undefined for `r()` if `T` is not a floating point type.

```c++
constexpr std::size_t Vector::size() const noexcept;
```

Returns `N`.

```c++
constexpr std::size_t Vector::hash() const noexcept;
template <typename T, std::size_t N> struct std::hash<Vector<T, N>>;
```

Hash function.

```c++
constexpr static Vector Vector::null() noexcept;
```

Returns a null vector (equivalent to `Vector(0)`).

```c++
constexpr static Vector Vector::unit(std::size_t index) noexcept;
```

Returns a unit vector along the specified axis. Behaviour is undefined if
`index>=N.`

```c++
constexpr Vector clampv(const Vector& x,
    const Vector& min, const Vector& max) noexcept;
constexpr Vector minv(const Vector& x, const Vector& y) noexcept;
constexpr Vector maxv(const Vector& x, const Vector& y) noexcept;
constexpr std::pair<Vector, Vector>
    minmaxv(const Vector& x, const Vector& y) noexcept;
```

These perform element-wise `clamp(), min()`, and `max()` operations on
vectors.

```c++
template <typename T, std::size_t N, typename U>
    constexpr Vector<T, N> lerp(const Vector<T, N>& u, const Vector<T, N>& v,
        U x) noexcept;
```

Elementwise linear interpolation. If `T` is an integer type, the results are
rounded to the nearest integer.

```c++
struct std::greater<Vector>;
struct std::less<Vector>;
```

Ordered comparison operators are not provided for vectors, since they have no
intrinsic order, but specializations of `std::greater` and `std::less` are
supplied to allow vectors to be used as the keys of a map. These perform
simple lexicographical comparison.

```c++
struct std::formatter<Vector>;
```

Formats a vector as a string, in the form `"[x,y,...]",` with the format spec
interpreted in the usual way for `T`.

## Matrix class

```c++
template <typename T, std::size_t N, MatrixLayout L = MatrixLayout::column>
    class Matrix;
```

An `NxN` square matrix type.

```c++
using Float2x2 = Matrix<float, 2>;
using Float3x3 = Matrix<float, 3>;
using Float4x4 = Matrix<float, 4>;
using Float2x2c = Matrix<float, 2, MatrixLayout::column>;
using Float3x3c = Matrix<float, 3, MatrixLayout::column>;
using Float4x4c = Matrix<float, 4, MatrixLayout::column>;
using Float2x2r = Matrix<float, 2, MatrixLayout::row>;
using Float3x3r = Matrix<float, 3, MatrixLayout::row>;
using Float4x4r = Matrix<float, 4, MatrixLayout::row>;
using Double2x2 = Matrix<double, 2>;
using Double3x3 = Matrix<double, 3>;
using Double4x4 = Matrix<double, 4>;
using Double2x2c = Matrix<double, 2, MatrixLayout::column>;
using Double3x3c = Matrix<double, 3, MatrixLayout::column>;
using Double4x4c = Matrix<double, 4, MatrixLayout::column>;
using Double2x2r = Matrix<double, 2, MatrixLayout::row>;
using Double3x3r = Matrix<double, 3, MatrixLayout::row>;
using Double4x4r = Matrix<double, 4, MatrixLayout::row>;
using Ldouble2x2 = Matrix<long double, 2>;
using Ldouble3x3 = Matrix<long double, 3>;
using Ldouble4x4 = Matrix<long double, 4>;
using Ldouble2x2c = Matrix<long double, 2, MatrixLayout::column>;
using Ldouble3x3c = Matrix<long double, 3, MatrixLayout::column>;
using Ldouble4x4c = Matrix<long double, 4, MatrixLayout::column>;
using Ldouble2x2r = Matrix<long double, 2, MatrixLayout::row>;
using Ldouble3x3r = Matrix<long double, 3, MatrixLayout::row>;
using Ldouble4x4r = Matrix<long double, 4, MatrixLayout::row>;
```

Predefined type aliases.

```c++
using Matrix::value_type = T;
using Matrix::vector_type = Vector<T, N>;
using Matrix::alt_matrix = Matrix<T, N, ...>;
```

Member types. The `alt_matrix` type is a matrix of the same size and element
type, but with the opposite layout.

```c++
static constexpr std::size_t Matrix::dim = N;
static constexpr std::size_t Matrix::cells = N * N;
static constexpr MatrixLayout Matrix::layout = L;
```

Member constants.

```c++
constexpr Matrix::Matrix() noexcept;
```

The default constructor sets all elements to zero.

```c++
constexpr explicit Matrix::Matrix(T x) noexcept;
```

Sets all elements to the same value.

```c++
constexpr Matrix::Matrix(T lead, T other) noexcept;
```

Sets the leading diagonal to one value, and all other elements to another.

```c++
constexpr Matrix::Matrix(const alt_matrix& m) noexcept;
```

Copies a matrix with the opposite layout.

```c++
template <typename... Args> constexpr Matrix::Matrix(Args... args) noexcept;
```

This constructor takes an explicit list of elements, which are copied in the
order of the matrix's internal layout (column by column or row by row); this
is defined only for the appropriate number of arguments.

```c++
constexpr Matrix::Matrix(const Matrix& m) noexcept;
constexpr Matrix::Matrix(Matrix&& m) noexcept;
constexpr Matrix::~Matrix() noexcept;
constexpr Matrix& Matrix::operator=(const Matrix& m) noexcept;
constexpr Matrix& Matrix::operator=(Matrix&& m) noexcept;
```

Other life cycle functions.

```c++
constexpr T& Matrix::operator()(std::size_t r, std::size_t c) noexcept;
constexpr const T& Matrix::operator()(std::size_t r, std::size_t c) const noexcept;
```

Element access functions. Behaviour is undefined if a row or column index is
greater than or equal to `N`.

```c++
constexpr T* Matrix::begin() noexcept;
constexpr const T* Matrix::begin() const noexcept;
constexpr T* Matrix::end() noexcept;
constexpr const T* Matrix::end() const noexcept;
```

These return pointers to the beginning and past the end of the matrix's
internal data, in the order implied by the layout parameter.

```c++
constexpr vector_type Matrix::column(std::size_t c) const noexcept;
constexpr vector_type Matrix::row(std::size_t r) const noexcept;
constexpr void Matrix::set_column(std::size_t c, vector_type v) noexcept;
constexpr void Matrix::set_row(std::size_t r, vector_type v) noexcept;
```

Query or set a complete row or column as a vector. Behaviour is undefined if a
row or column index is out of range.

```c++
constexpr T Matrix::det() const noexcept;
```

Returns the determinant of the matrix. (Currently this is only implemented for
`N<=4`).

```c++
constexpr bool Matrix::empty() noexcept;
```

Always false.

```c++
constexpr std::size_t Matrix::hash() const noexcept;
struct std::hash<Matrix>;
```

Hash functions.

```c++
constexpr Matrix Matrix::inverse() const noexcept;
```

Returns the inverse of the matrix. Behaviour is undefined if the determinant
is zero. (Currently this is only implemented for `N<=4`).

```c++
constexpr std::size_t Matrix::size() const noexcept;
```

Returns `N*N.`

```c++
constexpr Matrix Matrix::swap_columns(std::size_t c1, std::size_t c2) const noexcept;
constexpr Matrix Matrix::swap_rows(std::size_t r1, std::size_t r2) const noexcept;
```

Swap two rows or columns. Behaviour is undefined if a row or column index is
out of range.

```c++
constexpr Matrix Matrix::transposed() const noexcept;
```

Returns the transpose of the matrix.

```c++
constexpr Matrix Matrix::operator+() const noexcept;
constexpr Matrix Matrix::operator-() const noexcept;
constexpr Matrix& Matrix::operator+=(const Matrix& m) noexcept;
constexpr Matrix& Matrix::operator-=(const Matrix& m) noexcept;
constexpr Matrix& Matrix::operator*=(const Matrix& m) noexcept;
constexpr Matrix operator+(const Matrix& m, const Matrix& n) noexcept;
constexpr Matrix operator-(const Matrix& m, const Matrix& n) noexcept;
constexpr Matrix operator*(const Matrix& m, const Matrix& n) noexcept;
```

Matrix arithmetic operators.

```c++
constexpr vector_type
    operator*(const Matrix& m, const vector_type& v) noexcept;
constexpr vector_type
    operator*(const vector_type& m, const Matrix& v) noexcept;
```

Matrix-vector arithmetic operators.

```c++
constexpr Matrix& Matrix::operator*=(T x) noexcept;
constexpr Matrix& Matrix::operator/=(T x) noexcept;
constexpr Matrix operator*(const Matrix& m, T x) noexcept;
constexpr Matrix operator*(T x, const Matrix& m) noexcept;
constexpr Matrix operator/(const Matrix& m, T x) noexcept;
```

Matrix-scalar arithmetic operators.

```c++
constexpr bool operator==(const Matrix& m, const Matrix& n) noexcept;
constexpr bool operator!=(const Matrix& m, const Matrix& n) noexcept;
```

Comparison operators.

```c++
constexpr static Matrix identity() noexcept;
```

Returns the identity matrix (equivalent to `Matrix{1,0}`).

```c++
constexpr static Matrix null() noexcept;
```

Returns the zero matrix (equivalent to the default constructor).

```c++
struct std::formatter<Matrix>:
```

Formats a matrix as a string, in a form similar to
`"[[a,b,c],[d,e,f],[g,h,i]]",` with the format spec interpreted in the usual
way for `T`.

## Quaternion class

```c++
template <typename T> class Quaternion;
```

A quaternion class based on the scalar type `T`.

```c++
using Qfloat = Quaternion<float>;
using Qdouble = Quaternion<double>;
using Qldouble = Quaternion<long double>;
```

Predefined type aliases.

```c++
using Quaternion::value_type = T;
```

Member types.

```c++
constexpr Quaternion::Quaternion() noexcept;
```

The default constructor sets all components to zero.

```c++
constexpr Quaternion::Quaternion(T a) noexcept;
```

Sets the real component to the given value, and all other components to zero.

```c++
constexpr Quaternion::Quaternion(T a, T b, T c, T d) noexcept;
constexpr Quaternion::Quaternion(T a, const Vector<T, 3>& v) noexcept;
```

These set all four components explicitly.

```c++
constexpr Quaternion::Quaternion(const Quaternion& q) noexcept;
constexpr Quaternion::Quaternion(Quaternion&& q) noexcept;
constexpr Quaternion::~Quaternion() noexcept;
constexpr Quaternion& Quaternion::operator=(const Quaternion& q) noexcept;
constexpr Quaternion& Quaternion::operator=(Quaternion&& q) noexcept;
```

Other life cycle functions.

```c++
constexpr T& Quaternion::operator[](std::size_t i) noexcept;
constexpr const T& Quaternion::operator[](std::size_t i) const noexcept;
constexpr T& Quaternion::a() noexcept;
constexpr const T& Quaternion::a() const noexcept;
constexpr T& Quaternion::b() noexcept;
constexpr const T& Quaternion::b() const noexcept;
constexpr T& Quaternion::c() noexcept;
constexpr const T& Quaternion::c() const noexcept;
constexpr T& Quaternion::d() noexcept;
constexpr const T& Quaternion::d() const noexcept;
```

Element access functions. For the index operator, behaviour is undefined if
`i>3.`

```c++
constexpr T* Quaternion::begin() noexcept;
constexpr const T* Quaternion::begin() const noexcept;
constexpr T* Quaternion::end() noexcept;
constexpr const T* Quaternion::end() const noexcept;
```

These return pointers to the beginning and past the end of the internal
array.

```c++
constexpr Quaternion Quaternion::conj() const noexcept;
constexpr Quaternion Quaternion::conj(const Quaternion& q) const noexcept;
```

The first version returns the conjugate quaternion. The second version
performs the conjugation of `q` by this, returning _pqp<sup>-1</sup>_
(where `p=*this`).

```c++
constexpr std::size_t Quaternion::hash() const noexcept;
struct std::hash<Quaternion>;
```

Hash functions.

```c++
constexpr T Quaternion::norm() const noexcept;
constexpr T Quaternion::norm2() const noexcept;
```

Returns the quaternion's norm, or its square.

```c++
constexpr Quaternion Quaternion::reciprocal() const noexcept;
```

Returns the reciprocal of the quaternion. Behaviour is undefined if the
quaternion is zero.

```c++
constexpr T Quaternion::scalar_part() const noexcept;
constexpr Vector<T, 3> Quaternion::vector_part() const noexcept;
```

Return the scalar and vector parts of the quaternion.

```c++
constexpr Vector<T, 4> Quaternion::to_vector() const noexcept;
constexpr static Quaternion Quaternion::from_vector(const Vector<T, 4>& v) noexcept;
```

Conversion between a quaternion and a 4-vector.

```c++
constexpr Quaternion Quaternion::versor() const noexcept;
```

Returns the quaternion's versor (unit quaternion). Behaviour is undefined if
the quaternion is zero.

```c++
constexpr Quaternion Quaternion::operator+() const noexcept;
constexpr Quaternion Quaternion::operator-() const noexcept;
constexpr Quaternion& Quaternion::operator+=(const Quaternion& q) noexcept;
constexpr Quaternion& Quaternion::operator-=(const Quaternion& q) noexcept;
constexpr Quaternion& Quaternion::operator*=(const Quaternion& q) noexcept;
constexpr Quaternion operator+(const Quaternion& q, const Quaternion& r) noexcept;
constexpr Quaternion operator-(const Quaternion& q, const Quaternion& r) noexcept;
constexpr Quaternion operator*(const Quaternion& q, const Quaternion& r) noexcept;
```

Quaternion arithmetic operators.

```c++
constexpr Quaternion& Quaternion::operator*=(T x) noexcept;
constexpr Quaternion& Quaternion::operator/=(T x) noexcept;
constexpr Quaternion operator*(const Quaternion& q, T x) noexcept;
constexpr Quaternion operator*(T x, const Quaternion& q) noexcept;
constexpr Quaternion operator/(const Quaternion& q, T x) noexcept;
```

Quaternion-scalar arithmetic operators. Behaviour is undefined on division by
zero.

```c++
constexpr bool operator==(const Quaternion& q, const Quaternion& r) noexcept;
constexpr bool operator!=(const Quaternion& q, const Quaternion& r) noexcept;
```

Comparison operators.

```c++
struct std::formatter<Quaternion>;
```

Formats a quaternion as a string, in the form `"Q[x,y,...]",` with the format
spec interpreted in the usual way for `T`.

## Transforms

### Coordinate transformations

```c++
template <typename T> Vector<T, 2>
    cartesian_to_polar(const Vector<T, 2>& xy) noexcept;
        // (x,y) -> (r,θ)
template <typename T> Vector<T, 2>
    polar_to_cartesian(const Vector<T, 2>& rt) noexcept;
        // (r,θ) -> (x,y)
template <typename T> Vector<T, 3>
    cartesian_to_cylindrical(const Vector<T, 3>& xyz) noexcept;
        // (x,y,z) -> (ρ,φ,z)
template <typename T> Vector<T, 3>
    cartesian_to_spherical(const Vector<T, 3>& xyz) noexcept;
        // (x,y,z) -> (r,φ,θ)
template <typename T> Vector<T, 3>
    cylindrical_to_cartesian(const Vector<T, 3>& rpz) noexcept;
        // (ρ,φ,z) -> (x,y,z)
template <typename T> Vector<T, 3>
    cylindrical_to_spherical(const Vector<T, 3>& rpz) noexcept;
        // (ρ,φ,z) -> (r,φ,θ)
template <typename T> Vector<T, 3>
    spherical_to_cartesian(const Vector<T, 3>& rpt) noexcept;
        // (r,φ,θ) -> (x,y,z)
template <typename T> Vector<T, 3>
    spherical_to_cylindrical(const Vector<T, 3>& rpt) noexcept;
        // (r,φ,θ) -> (ρ,φ,z)
```

Transformations between coordinate systems in two or three dimensions.

### Projective geometry

```c++
template <typename T> Vector<T, 4>
    vector4(const Vector<T, 3>& v, T w) noexcept;
template <typename T> Vector<T, 4>
    point4(const Vector<T, 3>& v) noexcept;
template <typename T> Vector<T, 4>
    normal4(const Vector<T, 3>& v) noexcept;
```

Convert a 3-vector to a 4-vector. The `point4()` function sets `w` to 1;
`normal4()` sets it to zero.

```c++
template <typename T> Vector<T, 3>
    point3(const Vector<T, 4>& v) noexcept;
template <typename T> Vector<T, 3>
    normal3(const Vector<T, 4>& v) noexcept;
```

Convert a 4-vector to a 3-vector. The `point3()` function divides the first 3
coordinates by `w`, unless `w=0;` `normal3()` just discards `w` and returns
the truncated vector.

```c++
template <typename T, MatrixLayout L>
    Matrix<T, 4, L> make_transform(const Matrix<T, 3, L>& m,
        const Vector<T, 3>& v) noexcept;
```

Composes a `4x4` projective transformation matrix from a `3x3` matrix and a
translation vector.

    (a b c)             (a b c x)
    (d e f), (x y z) => (d e f y)
    (g h i)             (g h i z)
                        (0 0 0 1)

```c++
template <typename T, MatrixLayout L>
    Matrix<T, 4, L> normal_transform(const Matrix<T, 4, L>& m) noexcept;
```

Converts a point transform to a normal transform, returning the transpose of
the inverse of the matrix.

### Primitive transformations

```c++
template <typename T>
    Matrix<T, 3> rotate3(T angle, std::size_t index) noexcept;
template <typename T>
    Matrix<T, 4> rotate4(T angle, std::size_t index) noexcept;
```

Generate a rotation by the given angle as a 3D or projective matrix. The index
indicates the axis of rotation; behaviour is undefined if `index>2`.

```c++
template <typename T> Matrix<T, 3>
    rotate3(T angle, const Vector<T, 3>& axis) noexcept;
template <typename T> Matrix<T, 4>
    rotate4(T angle, const Vector<T, 3>& axis) noexcept;
```

Generate a rotation by the given angle, about the given axis, as a 3D or
projective matrix. These will return an identity matrix if either argument is
null.

```c++
template <typename T>
    Matrix<T, 3> scale3(T t) noexcept;
template <typename T>
    Matrix<T, 3> scale3(const Vector<T, 3>& v) noexcept;
template <typename T>
    Matrix<T, 4> scale4(T t) noexcept;
template <typename T>
    Matrix<T, 4> scale4(const Vector<T, 3>& v) noexcept;
```

Generate a proportional or triaxial scaling transformation as a 3D or
projective matrix.

```c++
template <typename T> Matrix<T, 4>
    translate4(const Vector<T, 3>& v) noexcept;
```

Generates a translation as a projective matrix. This is equivalent to
`make_transform(Matrix<T,3>::identity(),v).`

### Quaternion transformations

```c++
template <typename T> Vector<T, 3>
    rotate(const Quaternion<T>& q, const Vector<T, 3>& v) noexcept;
```

Apply the rotation represented by `q` to the vector `v`.

```c++
template <typename T> Quaternion<T>
    q_rotate(T angle, const Vector<T, 3>& axis) noexcept;
```

Generate the quaternion corresponding to a rotation by the given angle, about
the given axis.

```c++
template <typename T> Matrix<T, 3>
    rotate3(const Quaternion<T>& q) noexcept;
template <typename T> Matrix<T, 4>
    rotate4(const Quaternion<T>& q) noexcept;
```

Convert a quaternion into a 3-matrix or projective matrix representing the
same rotation.
