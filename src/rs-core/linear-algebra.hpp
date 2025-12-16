#pragma once

#include "rs-core/enum.hpp"
#include "rs-core/global.hpp"
#include "rs-core/hash.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <numeric>
#include <tuple>
#include <utility>

namespace RS {

    // Supporting types

    RS_ENUM(MatrixLayout, int, column, row)

    // Vector class

    template <typename T, std::size_t N>
    class Vector {

    public:

        static_assert(N >= 1);

        using value_type = T;
        using iterator = T*;
        using const_iterator = const T*;

        static constexpr std::size_t dim = N;

        constexpr Vector() noexcept: array_{T{}} {}
        constexpr explicit Vector(T x) noexcept: array_{} { for (auto& y: *this) { y = x; } }
        template <std::convertible_to<T> U, std::convertible_to<T> V, std::convertible_to<T>... Args>
            constexpr Vector(U x, V y, Args... args) noexcept requires (sizeof...(Args) + 2 == N):
            array_{static_cast<T>(x), static_cast<T>(y), static_cast<T>(args)...} {}
        constexpr explicit Vector(const T* ptr) noexcept: array_{} { for (auto i = 0uz; i < N; ++i) { array_[i] = ptr[i]; } }
        template <std::convertible_to<T> U> constexpr explicit Vector(const Vector<U, N>& v) noexcept:
            array_{} { for (auto i = 0uz; i < N; ++i) { array_[i] = T(v[i]); } }

        constexpr Vector(const Vector& v) noexcept = default;
        constexpr Vector(Vector&& v) noexcept = default;
        constexpr Vector& operator=(const Vector& v) noexcept = default;
        constexpr Vector& operator=(Vector&& v) noexcept = default;

        constexpr T& operator[](std::size_t i) noexcept { return array_[i]; }
        constexpr const T& operator[](std::size_t i) const noexcept { return array_[i]; }
        constexpr T& x() noexcept { return (*this)[0]; }
        constexpr const T& x() const noexcept { return (*this)[0]; }
        constexpr T& y() noexcept requires (N >= 2) { return (*this)[1]; }
        constexpr const T& y() const noexcept requires (N >= 2) { return (*this)[1]; }
        constexpr T& z() noexcept requires (N >= 3) { return (*this)[2]; }
        constexpr const T& z() const noexcept requires (N >= 3) { return (*this)[2]; }
        constexpr T& w() noexcept requires (N >= 4) { return (*this)[3]; }
        constexpr const T& w() const noexcept requires (N >= 4) { return (*this)[3]; }

        constexpr T* begin() noexcept { return array_.data(); }
        constexpr const T* begin() const noexcept { return array_.data(); }
        constexpr T* end() noexcept { return begin() + N; }
        constexpr const T* end() const noexcept { return begin() + N; }

        constexpr Vector operator+() const noexcept { return *this; }
        constexpr Vector operator-() const noexcept { auto v = *this; for (auto& x: v) { x = - x; } return v; }
        constexpr Vector& operator+=(const Vector& v) noexcept { for (auto i = 0uz; i < N; ++i) { (*this)[i] += v[i]; } return *this; }
        constexpr Vector& operator-=(const Vector& v) noexcept { for (auto i = 0uz; i < N; ++i) { (*this)[i] -= v[i]; } return *this; }
        constexpr Vector& operator*=(const Vector& v) noexcept { for (auto i = 0uz; i < N; ++i) { (*this)[i] *= v[i]; } return *this; }
        constexpr Vector& operator/=(const Vector& v) noexcept { for (auto i = 0uz; i < N; ++i) { (*this)[i] /= v[i]; } return *this; }
        constexpr Vector& operator*=(T x) noexcept { for (auto& y: *this) { y *= x; } return *this; }
        constexpr Vector& operator/=(T x) noexcept { for (auto& y: *this) { y /= x; } return *this; }
        constexpr friend Vector operator+(const Vector& u, const Vector& v) noexcept { auto w = u; w += v; return w; }
        constexpr friend Vector operator-(const Vector& u, const Vector& v) noexcept { auto w = u; w -= v; return w; }
        constexpr friend Vector operator*(const Vector& u, const Vector& v) noexcept { auto w = u; w *= v; return w; }
        constexpr friend Vector operator*(const Vector& v, T x) noexcept { auto w = v; w *= x; return w; }
        constexpr friend Vector operator*(T x, const Vector& v) noexcept { auto w = v; w *= x; return w; }
        constexpr friend Vector operator/(const Vector& u, const Vector& v) noexcept { auto w = u; w /= v; return w; }
        constexpr friend Vector operator/(const Vector& v, T x) noexcept { auto w = v; w /= x; return w; }

        constexpr T dot(const Vector& v) const noexcept { return std::inner_product(begin(), end(), v.begin(), T{0}); }
        constexpr Vector cross(const Vector& v) const noexcept requires (N == 3)
            { auto& u = *this; return {u[1] * v[2] - u[2] * v[1], u[2] * v[0] - u[0] * v[2], u[0] * v[1] - u[1] * v[0]}; }
        constexpr friend T operator%(const Vector& u, const Vector& v) noexcept { return u.dot(v); }
        constexpr Vector& operator^=(const Vector& v) noexcept requires (N == 3) { return *this = cross(v); }
        constexpr friend Vector operator^(const Vector& u, const Vector& v) noexcept requires (N == 3) { return u.cross(v); }
        constexpr friend bool operator==(const Vector& u, const Vector& v) noexcept = default;

        constexpr T angle(const Vector& v) const noexcept
            { using std::acos; using std::sqrt; return is_null() || v.is_null() ? T{0} : acos(*this % v / sqrt(r2() * v.r2())); }
        constexpr Vector dir() const noexcept { return is_null() ? null() : *this / r(); }
        constexpr bool empty() noexcept { return false; }
        constexpr bool is_null() const noexcept { return *this == null(); }
        constexpr Vector project(const Vector& v) const noexcept { return v.is_null() ? Vector{} : *this * ((*this % v) / r2()); }
        constexpr Vector reject(const Vector& v) const noexcept { return v - project(v); }
        constexpr T r() const noexcept { return std::sqrt(r2()); }
        constexpr T r2() const noexcept { return dot(*this); }
        constexpr std::size_t size() const noexcept { return N; }
        constexpr std::size_t hash() const noexcept { return hash_mix(*this); }

        constexpr static Vector null() noexcept { return {}; }
        constexpr static Vector unit(std::size_t i) noexcept { Vector v; v[i] = T{1}; return v; }

    private:

        std::array<T, N> array_;

    };

    using Byte2 = Vector<std::uint8_t, 2>;
    using Byte3 = Vector<std::uint8_t, 3>;
    using Byte4 = Vector<std::uint8_t, 4>;
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

    template <typename T, std::size_t N>
    constexpr Vector<T, N> clampv(const Vector<T, N>& x, const Vector<T, N>& min, const Vector<T, N>& max) noexcept {
        Vector<T, N> y;
        for (auto i = 0uz; i < N; ++i) {
            y[i] = std::clamp(x[i], min[i], max[i]);
        }
        return y;
    }

    template <typename T, std::size_t N>
    constexpr Vector<T, N> minv(const Vector<T, N>& x, const Vector<T, N>& y) noexcept {
        Vector<T, N> z;
        for (auto i = 0uz; i < N; ++i) {
            z[i] = std::min(x[i], y[i]);
        }
        return z;
    }

    template <typename T, std::size_t N>
    constexpr Vector<T, N> maxv(const Vector<T, N>& x, const Vector<T, N>& y) noexcept {
        Vector<T, N> z;
        for (auto i = 0uz; i < N; ++i) {
            z[i] = std::max(x[i], y[i]);
        }
        return z;
    }

    template <typename T, std::size_t N>
    constexpr std::pair<Vector<T, N>, Vector<T, N>> minmaxv(const Vector<T, N>& x, const Vector<T, N>& y) noexcept {
        std::pair<Vector<T, N>, Vector<T, N>> pair;
        for (auto i = 0uz; i < N; ++i) {
            std::tie(pair.first[i], pair.second[i]) = std::minmax(x[i], y[i]);
        }
        return pair;
    }

    template <typename T, std::size_t N, typename U>
    constexpr Vector<T, N> lerp(const Vector<T, N>& a, const Vector<T, N>& b, U x) noexcept {
        Vector<T, N> result;
        for (auto i = 0uz; i < N; ++i) {
            result[i] = std::lerp(a[i], b[i], x);
        }
        return result;
    }

    // Matrix class

    namespace Detail {

        template <typename T, std::size_t N, MatrixLayout L>
        struct MatrixLayoutTraits;

        template <typename T, std::size_t N>
        struct MatrixLayoutTraits<T, N, MatrixLayout::column> {

            using V = Vector<T, N>;

            static constexpr T& get_ref(T* ptr, std::size_t r, std::size_t c) noexcept { return ptr[r + N * c]; }
            static constexpr const T& get_ref(const T* ptr, std::size_t r, std::size_t c) noexcept { return ptr[r + N * c]; }
            static constexpr V get_column(const T* ptr, std::size_t c) noexcept { return V(ptr + N * c); }

            static constexpr V get_row(const T* ptr, std::size_t r) noexcept {
                V v;
                for (auto i = 0uz, j = r; i < N; ++i, j += N) {
                    v[i] = ptr[j];
                }
                return v;
            }

            static constexpr void set_column(T* ptr, std::size_t c, const T* src) noexcept {
                for (auto i = 0uz, j = N * c; i < N; ++i, ++j) {
                    ptr[j] = src[i];
                }
            }

            static constexpr void set_row(T* ptr, std::size_t r, const T* src) noexcept {
                for (auto i = r, j = 0uz; j < N; i += N, ++j) {
                    ptr[i] = src[j];
                }
            }

            static constexpr void swap_columns(T* ptr, std::size_t c1, std::size_t c2) noexcept {
                if (c1 != c2) {
                    auto i = N * c1, j = N * c2;
                    for (auto k = 0uz; k < N; ++k) {
                        std::swap(ptr[i + k], ptr[j + k]);
                    }
                }
            }

            static constexpr void swap_rows(T* ptr, std::size_t r1, std::size_t r2) noexcept {
                if (r1 != r2) {
                    for (; r1 < N * N; r1 += N, r2 += N) {
                        std::swap(ptr[r1], ptr[r2]);
                    }
                }
            }

        };

        template <typename T, std::size_t N>
        struct MatrixLayoutTraits<T, N, MatrixLayout::row> {

            using V = Vector<T, N>;

            static constexpr T& get_ref(T* ptr, std::size_t r, std::size_t c) noexcept { return ptr[N * r + c]; }
            static constexpr const T& get_ref(const T* ptr, std::size_t r, std::size_t c) noexcept { return ptr[N * r + c]; }

            static constexpr V get_column(const T* ptr, std::size_t c) noexcept {
                V v;
                for (auto i = 0uz, j = c; i < N; ++i, j += N) {
                    v[i] = ptr[j];
                }
                return v;
            }

            static constexpr V get_row(const T* ptr, std::size_t r) noexcept { return V(ptr + N * r); }

            static constexpr void set_column(T* ptr, std::size_t c, const T* src) noexcept {
                for (auto i = c, j = 0uz; j < N; i += N, ++j) {
                    ptr[i] = src[j];
                }
            }

            static constexpr void set_row(T* ptr, std::size_t r, const T* src) noexcept {
                for (auto i = 0uz, j = N * r; i < N; ++i, ++j) {
                    ptr[j] = src[i];
                }
            }

            static constexpr void swap_columns(T* ptr, std::size_t c1, std::size_t c2) noexcept {
                if (c1 != c2) {
                    for (; c1 < N * N; c1 += N, c2 += N) {
                        std::swap(ptr[c1], ptr[c2]);
                    }
                }
            }

            static constexpr void swap_rows(T* ptr, std::size_t r1, std::size_t r2) noexcept {
                if (r1 != r2) {
                    auto i = N * r1, j = N * r2;
                    for (auto k = 0uz; k < N; ++k) {
                        std::swap(ptr[i + k], ptr[j + k]);
                    }
                }
            }

        };

    }

    template <typename T, std::size_t N, MatrixLayout L = MatrixLayout::column>
    class Matrix {

    private:

        static_assert(N >= 1);

        static constexpr MatrixLayout alt_layout = L == MatrixLayout::column ? MatrixLayout::row : MatrixLayout::column;

        using layout_traits = Detail::MatrixLayoutTraits<T, N, L>;

    public:

        using value_type = T;
        using vector_type = Vector<T, N>;
        using alt_matrix = Matrix<T, N, alt_layout>;

        static constexpr std::size_t dim = N;
        static constexpr std::size_t cells = N * N;
        static constexpr MatrixLayout layout = L;

        constexpr Matrix() noexcept: array_{T{}} {}
        constexpr explicit Matrix(T x) noexcept: array_{} { for (auto& y: array_) { y = x; } }
        constexpr Matrix(T lead, T other) noexcept: Matrix(other) { for (auto i = 0uz; i < cells; i += N + 1) { array_[i] = lead; } }
        constexpr Matrix(const alt_matrix& alt) noexcept: array_{}
            { for (auto r = 0uz; r < N; ++r) { for (auto c = 0uz; c < N; ++c) { (*this)[r, c] = alt[r, c]; } } }
        template <std::convertible_to<T> U, std::convertible_to<T> V, std::convertible_to<T>... Args>
            constexpr Matrix(U x, V y, Args... args) requires (sizeof...(Args) + 2 == cells):
            array_{static_cast<T>(x), static_cast<T>(y), static_cast<T>(args)...} {}

        constexpr Matrix operator+() const noexcept { return *this; }
        constexpr Matrix operator-() const noexcept { auto m = *this; for (auto& x: m) { x = - x; } return m; }
        constexpr Matrix& operator+=(const Matrix& m) noexcept { for (auto i = 0uz; i < cells; ++i) { array_[i] += m.array_[i]; } return *this; }
        constexpr Matrix& operator-=(const Matrix& m) noexcept { for (auto i = 0uz; i < cells; ++i) { array_[i] -= m.array_[i]; } return *this; }
        constexpr Matrix& operator*=(T x) noexcept { for (auto& y: *this) { y *= x; } return *this; }
        constexpr Matrix& operator/=(T x) noexcept { for (auto& y: *this) { y /= x; } return *this; }
        constexpr Matrix& operator*=(const Matrix& m) noexcept { *this = *this * m; return *this; }
        constexpr friend Matrix operator+(const Matrix& m, const Matrix& n) noexcept { auto o = m; o += n; return o; }
        constexpr friend Matrix operator-(const Matrix& m, const Matrix& n) noexcept { auto o = m; o -= n; return o; }
        constexpr friend Matrix operator*(const Matrix& m, T x) noexcept { auto o = m; o *= x; return o; }
        constexpr friend Matrix operator*(T x, const Matrix& m) noexcept { auto o = m; o *= x; return o; }
        constexpr friend Matrix operator/(const Matrix& m, T x) noexcept { auto o = m; o /= x; return o; }
        constexpr friend bool operator==(const Matrix& m, const Matrix& n) noexcept = default;

        constexpr T& operator[](std::size_t r, std::size_t c) noexcept { return layout_traits::get_ref(begin(), r, c); }
        constexpr const T& operator[](std::size_t r, std::size_t c) const noexcept { return layout_traits::get_ref(begin(), r, c); }
        constexpr T* begin() noexcept { return array_.data(); }
        constexpr const T* begin() const noexcept { return array_.data(); }
        constexpr T* end() noexcept { return begin() + cells; }
        constexpr const T* end() const noexcept { return begin() + cells; }

        constexpr vector_type column(std::size_t c) const noexcept { return layout_traits::get_column(begin(), c); }
        constexpr vector_type row(std::size_t r) const noexcept { return layout_traits::get_row(begin(), r); }
        constexpr void set_column(std::size_t c, vector_type v) noexcept { layout_traits::set_column(begin(), c, v.begin()); }
        constexpr void set_row(std::size_t r, vector_type v) noexcept { layout_traits::set_row(begin(), r, v.begin()); }
        constexpr Matrix swap_columns(std::size_t c1, std::size_t c2) const noexcept;
        constexpr Matrix swap_rows(std::size_t r1, std::size_t r2) const noexcept;

        constexpr T det() const noexcept;
        constexpr bool empty() noexcept { return false; }
        constexpr Matrix inverse() const noexcept;
        constexpr std::size_t size() const noexcept { return cells; }
        constexpr Matrix transposed() const noexcept;
        constexpr std::size_t hash() const noexcept { return hash_mix(array_); }

        constexpr static Matrix identity() noexcept { return Matrix(T{1}, T{0}); }
        constexpr static Matrix null() noexcept { return {}; }

    private:

        std::array<T, cells> array_;

    };

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

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Matrix<T, N, L> operator*(const Matrix<T, N, L>& a, const Matrix<T, N, L>& b) noexcept {
        Matrix<T, N, L> m;
        for (auto r = 0uz; r < N; ++r) {
            for (auto c = 0uz; c < N; ++c) {
                for (auto i = 0uz; i < N; ++i) {
                    m[r, c] += a[r, i] * b[i, c];
                }
            }
        }
        return m;
    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Vector<T, N> operator*(const Matrix<T, N, L>& a, const Vector<T, N>& b) noexcept {
        Vector<T, N> v;
        for (auto r = 0uz; r < N; ++r) {
            for (auto c = 0uz; c < N; ++c) {
                v[r] += a[r, c] * b[c];
            }
        }
        return v;
    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Vector<T, N> operator*(const Vector<T, N>& a, const Matrix<T, N, L>& b) noexcept {
        Vector<T, N> v;
        for (auto r = 0uz; r < N; ++r) {
            for (auto c = 0uz; c < N; ++c) {
                v[c] += a[r] * b[r, c];
            }
        }
        return v;
    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Matrix<T, N, L> Matrix<T, N, L>::swap_columns(std::size_t c1, std::size_t c2) const noexcept {
        auto m = *this;
        layout_traits::swap_columns(m.begin(), c1, c2);
        return m;
    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Matrix<T, N, L> Matrix<T, N, L>::swap_rows(std::size_t r1, std::size_t r2) const noexcept {
        auto m = *this;
        layout_traits::swap_rows(m.begin(), r1, r2);
        return m;
    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr T Matrix<T, N, L>::det() const noexcept {

        auto& v = *this;

        if constexpr (N == 1) {

            return v[0,0];

        } else if constexpr (N == 2) {

            return v[0,0] * v[1,1] - v[0,1] * v[1,0];

        } else if constexpr (N == 3) {

            return v[0,0] * v[1,1] * v[2,2]
                 + v[0,1] * v[1,2] * v[2,0]
                 + v[0,2] * v[1,0] * v[2,1]
                 - v[0,2] * v[1,1] * v[2,0]
                 - v[0,1] * v[1,0] * v[2,2]
                 - v[0,0] * v[1,2] * v[2,1];

        } else if constexpr (N == 4) {

            return v[0,0] * v[1,1] * v[2,2] * v[3,3]
                 + v[0,0] * v[2,1] * v[3,2] * v[1,3]
                 + v[0,0] * v[3,1] * v[1,2] * v[2,3]
                 + v[1,0] * v[0,1] * v[3,2] * v[2,3]
                 + v[1,0] * v[2,1] * v[0,2] * v[3,3]
                 + v[1,0] * v[3,1] * v[2,2] * v[0,3]
                 + v[2,0] * v[0,1] * v[1,2] * v[3,3]
                 + v[2,0] * v[1,1] * v[3,2] * v[0,3]
                 + v[2,0] * v[3,1] * v[0,2] * v[1,3]
                 + v[3,0] * v[0,1] * v[2,2] * v[1,3]
                 + v[3,0] * v[1,1] * v[0,2] * v[2,3]
                 + v[3,0] * v[2,1] * v[1,2] * v[0,3]
                 - v[0,0] * v[1,1] * v[3,2] * v[2,3]
                 - v[0,0] * v[2,1] * v[1,2] * v[3,3]
                 - v[0,0] * v[3,1] * v[2,2] * v[1,3]
                 - v[1,0] * v[0,1] * v[2,2] * v[3,3]
                 - v[1,0] * v[2,1] * v[3,2] * v[0,3]
                 - v[1,0] * v[3,1] * v[0,2] * v[2,3]
                 - v[2,0] * v[0,1] * v[3,2] * v[1,3]
                 - v[2,0] * v[1,1] * v[0,2] * v[3,3]
                 - v[2,0] * v[3,1] * v[1,2] * v[0,3]
                 - v[3,0] * v[0,1] * v[1,2] * v[2,3]
                 - v[3,0] * v[1,1] * v[2,2] * v[0,3]
                 - v[3,0] * v[2,1] * v[0,2] * v[1,3];

        } else {

            static_assert(dependent_false<T>, "Matrix determinant is not implemented for N>4");

        }

    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Matrix<T, N, L> Matrix<T, N, L>::inverse() const noexcept {

        auto& m = *this;

        if constexpr (N == 1) {

            return {T{1} / m[0,0]};

        } else if constexpr (N == 2) {

            Matrix n;
            n[0,0] = m[1,1];
            n[0,1] = - m[0,1];
            n[1,0] = - m[1,0];
            n[1,1] = m[0,0];
            return n / m.det();

        } else if constexpr (N == 3) {

            Matrix n;
            n[0,0] = m[1,1] * m[2,2] - m[1,2] * m[2,1];
            n[0,1] = m[0,2] * m[2,1] - m[0,1] * m[2,2];
            n[0,2] = m[0,1] * m[1,2] - m[0,2] * m[1,1];
            n[1,0] = m[1,2] * m[2,0] - m[1,0] * m[2,2];
            n[1,1] = m[0,0] * m[2,2] - m[0,2] * m[2,0];
            n[1,2] = m[0,2] * m[1,0] - m[0,0] * m[1,2];
            n[2,0] = m[1,0] * m[2,1] - m[1,1] * m[2,0];
            n[2,1] = m[0,1] * m[2,0] - m[0,0] * m[2,1];
            n[2,2] = m[0,0] * m[1,1] - m[0,1] * m[1,0];
            return n / m.det();

        } else if constexpr (N == 4) {

            // http://stackoverflow.com/questions/2624422/efficient-4x4-matrix-inverse-affine-transform

            T s0 = m[0,0] * m[1,1] - m[1,0] * m[0,1];
            T s1 = m[0,0] * m[1,2] - m[1,0] * m[0,2];
            T s2 = m[0,0] * m[1,3] - m[1,0] * m[0,3];
            T s3 = m[0,1] * m[1,2] - m[1,1] * m[0,2];
            T s4 = m[0,1] * m[1,3] - m[1,1] * m[0,3];
            T s5 = m[0,2] * m[1,3] - m[1,2] * m[0,3];
            T c5 = m[2,2] * m[3,3] - m[3,2] * m[2,3];
            T c4 = m[2,1] * m[3,3] - m[3,1] * m[2,3];
            T c3 = m[2,1] * m[3,2] - m[3,1] * m[2,2];
            T c2 = m[2,0] * m[3,3] - m[3,0] * m[2,3];
            T c1 = m[2,0] * m[3,2] - m[3,0] * m[2,2];
            T c0 = m[2,0] * m[3,1] - m[3,0] * m[2,1];
            T invdet = T{1} / (s0 * c5 - s1 * c4 + s2 * c3 + s3 * c2 - s4 * c1 + s5 * c0);
            Matrix n;
            n[0,0] = (m[1,1] * c5 - m[1,2] * c4 + m[1,3] * c3) * invdet;
            n[0,1] = (- m[0,1] * c5 + m[0,2] * c4 - m[0,3] * c3) * invdet;
            n[0,2] = (m[3,1] * s5 - m[3,2] * s4 + m[3,3] * s3) * invdet;
            n[0,3] = (- m[2,1] * s5 + m[2,2] * s4 - m[2,3] * s3) * invdet;
            n[1,0] = (- m[1,0] * c5 + m[1,2] * c2 - m[1,3] * c1) * invdet;
            n[1,1] = (m[0,0] * c5 - m[0,2] * c2 + m[0,3] * c1) * invdet;
            n[1,2] = (- m[3,0] * s5 + m[3,2] * s2 - m[3,3] * s1) * invdet;
            n[1,3] = (m[2,0] * s5 - m[2,2] * s2 + m[2,3] * s1) * invdet;
            n[2,0] = (m[1,0] * c4 - m[1,1] * c2 + m[1,3] * c0) * invdet;
            n[2,1] = (- m[0,0] * c4 + m[0,1] * c2 - m[0,3] * c0) * invdet;
            n[2,2] = (m[3,0] * s4 - m[3,1] * s2 + m[3,3] * s0) * invdet;
            n[2,3] = (- m[2,0] * s4 + m[2,1] * s2 - m[2,3] * s0) * invdet;
            n[3,0] = (- m[1,0] * c3 + m[1,1] * c1 - m[1,2] * c0) * invdet;
            n[3,1] = (m[0,0] * c3 - m[0,1] * c1 + m[0,2] * c0) * invdet;
            n[3,2] = (- m[3,0] * s3 + m[3,1] * s1 - m[3,2] * s0) * invdet;
            n[3,3] = (m[2,0] * s3 - m[2,1] * s1 + m[2,2] * s0) * invdet;
            return n;

        } else {

            static_assert(dependent_false<T>, "Matrix inverse is not implemented for N>4");

        }

    }

    template <typename T, std::size_t N, MatrixLayout L>
    constexpr Matrix<T, N, L> Matrix<T, N, L>::transposed() const noexcept {
        Matrix m;
        for (auto r = 0uz; r < N; ++r) {
            for (auto c = 0uz; c < N; ++c) {
                m[r, c] = (*this)[c, r];
            }
        }
        return m;
    }

    // Quaternion class

    template <typename T>
    class Quaternion {

    public:

        using value_type = T;

        constexpr Quaternion() noexcept: array_{} {}
        constexpr Quaternion(T a) noexcept: array_{a, T{0}, T{0}, T{0}} {}
        constexpr Quaternion(T a, T b, T c, T d) noexcept: array_{a, b, c, d} {}
        constexpr Quaternion(T a, const Vector<T, 3>& v) noexcept: array_{a, v.x(), v.y(), v.z()} {}

        constexpr T& operator[](std::size_t i) noexcept { return array_[i]; }
        constexpr const T& operator[](std::size_t i) const noexcept { return array_[i]; }
        constexpr T& a() noexcept { return array_[0]; }
        constexpr const T& a() const noexcept { return array_[0]; }
        constexpr T& b() noexcept { return array_[1]; }
        constexpr const T& b() const noexcept { return array_[1]; }
        constexpr T& c() noexcept { return array_[2]; }
        constexpr const T& c() const noexcept { return array_[2]; }
        constexpr T& d() noexcept { return array_[3]; }
        constexpr const T& d() const noexcept { return array_[3]; }
        constexpr T* begin() noexcept { return array_.data(); }
        constexpr const T* begin() const noexcept { return array_.data(); }
        constexpr T* end() noexcept { return begin() + 4; }
        constexpr const T* end() const noexcept { return begin() + 4; }

        constexpr Quaternion operator+() const noexcept { return *this; }
        constexpr Quaternion operator-() const noexcept { return {- a(), b(), c(), d()}; }
        constexpr Quaternion operator~() const noexcept { return conj(); }
        constexpr Quaternion& operator+=(const Quaternion& q) noexcept { for (auto i = 0uz; i < 4uz; ++i) { array_[i] += q.array_[i]; } return *this; }
        constexpr Quaternion& operator-=(const Quaternion& q) noexcept { for (auto i = 0uz; i < 4uz; ++i) { array_[i] -= q.array_[i]; } return *this; }
        constexpr Quaternion& operator*=(T x) noexcept { for (auto& y: *this) { y *= x; } return *this; }
        constexpr Quaternion& operator/=(T x) noexcept { for (auto& y: *this) { y /= x; } return *this; }
        constexpr Quaternion& operator*=(const Quaternion& q) noexcept { *this = *this * q; return *this; }
        constexpr friend Quaternion operator+(const Quaternion& q, const Quaternion& r) noexcept { auto s = q; s += r; return s; }
        constexpr friend Quaternion operator-(const Quaternion& q, const Quaternion& r) noexcept { auto s = q; s -= r; return s; }
        constexpr friend Quaternion operator*(const Quaternion& q, T x) noexcept { auto s = q; s *= x; return s; }
        constexpr friend Quaternion operator*(T x, const Quaternion& q) noexcept { auto s = q; s *= x; return s; }
        constexpr friend Quaternion operator/(const Quaternion& q, T x) noexcept { auto s = q; s /= x; return s; }
        constexpr friend bool operator==(const Quaternion& q, const Quaternion& r) noexcept = default;

        constexpr Quaternion conj() const noexcept { return {a(), - b(), - c(), - d()}; }
        constexpr Quaternion conj(const Quaternion& p) const noexcept { return *this * p * conj(); }
        constexpr T norm() const noexcept { using std::sqrt; return sqrt(norm2()); }
        constexpr T norm2() const noexcept { auto sum = T{0}; for (auto x: *this) { sum += x * x; } return sum; }
        constexpr Quaternion reciprocal() const noexcept { return conj() / norm2(); }
        constexpr T scalar_part() const noexcept { return a(); }
        constexpr Vector<T, 3> vector_part() const noexcept { return {b(), c(), d()}; }
        constexpr Quaternion versor() const noexcept { return *this / norm(); }
        constexpr Vector<T, 4> to_vector() const noexcept { return {a(), b(), c(), d()}; }
        constexpr static Quaternion from_vector(const Vector<T, 4>& v) noexcept { return {v.x(), v.y(), v.z(), v.w()}; }
        constexpr std::size_t hash() const noexcept { return hash_mix(array_); }

    private:

        std::array<T, 4> array_;

    };

    using Qfloat = Quaternion<float>;
    using Qdouble = Quaternion<double>;
    using Qldouble = Quaternion<long double>;

    template <typename T>
    constexpr Quaternion<T> operator*(const Quaternion<T>& x, const Quaternion<T>& y) noexcept {
        return {
            x.a() * y.a() - x.b() * y.b() - x.c() * y.c() - x.d() * y.d(),
            x.a() * y.b() + x.b() * y.a() + x.c() * y.d() - x.d() * y.c(),
            x.a() * y.c() - x.b() * y.d() + x.c() * y.a() + x.d() * y.b(),
            x.a() * y.d() + x.b() * y.c() - x.c() * y.b() + x.d() * y.a()
        };
    }

    // Coordinate transformations

    template <typename T>
    Vector<T, 2> cartesian_to_polar(const Vector<T, 2>& xy) noexcept {
        using std::atan2;
        return {xy.r(), atan2(xy[1], xy[0])};
    }

    template <typename T>
    Vector<T, 2> polar_to_cartesian(const Vector<T, 2>& rt) noexcept {
        using std::cos;
        using std::sin;
        return {rt[0] * cos(rt[1]), rt[0] * sin(rt[1])};
    }

    template <typename T>
    Vector<T, 3> cartesian_to_cylindrical(const Vector<T, 3>& xyz) noexcept {
        using std::atan2;
        using std::sqrt;
        return {sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]), atan2(xyz[1], xyz[0]), xyz[2]};
    }

    template <typename T>
    Vector<T, 3> cartesian_to_spherical(const Vector<T, 3>& xyz) noexcept {
        using std::atan2;
        using std::sqrt;
        T rho = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]);
        return {xyz.r(), atan2(xyz[1], xyz[0]), atan2(rho, xyz[2])};
    }

    template <typename T>
    Vector<T, 3> cylindrical_to_cartesian(const Vector<T, 3>& rpz) noexcept {
        using std::cos;
        using std::sin;
        return {rpz[0] * cos(rpz[1]), rpz[0] * sin(rpz[1]), rpz[2]};
    }

    template <typename T>
    Vector<T, 3> cylindrical_to_spherical(const Vector<T, 3>& rpz) noexcept {
        using std::atan2;
        using std::sqrt;
        return {sqrt(rpz[0] * rpz[0] + rpz[2] * rpz[2]), rpz[1], atan2(rpz[0], rpz[2])};
    }

    template <typename T>
    Vector<T, 3> spherical_to_cartesian(const Vector<T, 3>& rpt) noexcept {
        using std::cos;
        using std::sin;
        T rho = rpt[0] * sin(rpt[2]);
        return {rho * cos(rpt[1]), rho * sin(rpt[1]), rpt[0] * cos(rpt[2])};
    }

    template <typename T>
    Vector<T, 3> spherical_to_cylindrical(const Vector<T, 3>& rpt) noexcept {
        using std::cos;
        using std::sin;
        return {rpt[0] * sin(rpt[2]), rpt[1], rpt[0] * cos(rpt[2])};
    }

    // Projective geometry

    template <typename T>
    inline Vector<T, 4> vector4(const Vector<T, 3>& v, T w) noexcept {
        return {v.x(), v.y(), v.z(), w};
    }

    template <typename T>
    inline Vector<T, 4> point4(const Vector<T, 3>& v) noexcept {
        return vector4(v, T{1});
    }

    template <typename T>
    inline Vector<T, 4> normal4(const Vector<T, 3>& v) noexcept {
        return vector4(v, T{0});
    }

    template <typename T>
    inline Vector<T, 3> point3(const Vector<T, 4>& v) noexcept {
        Vector<T, 3> u{v.x(), v.y(), v.z()};
        if (v.w() != T{0}) {
            u /= v.w();
        }
        return u;
    }

    template <typename T>
    inline Vector<T, 3> normal3(const Vector<T, 4>& v) noexcept {
        return {v.x(), v.y(), v.z()};
    }

    template <typename T, MatrixLayout L>
    Matrix<T, 4, L> make_transform(const Matrix<T, 3, L>& m, const Vector<T, 3>& v) noexcept {
        auto t = Matrix<T, 4, L>::identity();
        for (auto r = 0uz; r < 3uz; ++r) {
            for (auto c = 0uz; c < 3uz; ++c) {
                t[r, c] = m[r, c];
            }
            t[r, 3] = v[r];
        }
        return t;
    }

    template <typename T, MatrixLayout L>
    inline Matrix<T, 4, L> normal_transform(const Matrix<T, 4, L>& m) noexcept {
        return m.inverse().transposed();
    }

    // Primitive transformations

    template <typename T>
    Matrix<T, 3> rotate3(T angle, std::size_t index) noexcept {
        auto c = std::cos(angle);
        auto s = std::sin(angle);
        auto m = Matrix<T, 3>::identity();
        switch (index) {
            case 0:   m[1,1] = c; m[1,2] = -s; m[2,1] = s; m[2,2] = c; break;
            case 1:   m[0,0] = c; m[0,2] = s; m[2,0] = -s; m[2,2] = c; break;
            case 2:   m[0,0] = c; m[0,1] = -s; m[1,0] = s; m[1,1] = c; break;
            default:  break;
        }
        return m;
    }

    template <typename T>
    Matrix<T, 4> rotate4(T angle, std::size_t index) noexcept {
        auto c = std::cos(angle);
        auto s = std::sin(angle);
        auto m = Matrix<T, 4>::identity();
        switch (index) {
            case 0:   m[1,1] = c; m[1,2] = -s; m[2,1] = s; m[2,2] = c; break;
            case 1:   m[0,0] = c; m[0,2] = s; m[2,0] = -s; m[2,2] = c; break;
            case 2:   m[0,0] = c; m[0,1] = -s; m[1,0] = s; m[1,1] = c; break;
            default:  break;
        }
        return m;
    }

    template <typename T>
    Matrix<T, 3> scale3(T t) noexcept {
        return Matrix<T, 3>{t, T{0}};
    }

    template <typename T>
    Matrix<T, 3> scale3(const Vector<T, 3>& v) noexcept {
        Matrix<T, 3> m;
        for (auto i = 0uz; i < 3uz; ++i) {
            m[i, i] = v[i];
        }
        return m;
    }

    template <typename T>
    Matrix<T, 4> scale4(T t) noexcept {
        Matrix<T, 4> m{t, T{0}};
        m[3, 3] = T{1};
        return m;
    }

    template <typename T>
    Matrix<T, 4> scale4(const Vector<T, 3>& v) noexcept {
        Matrix<T, 4> m;
        for (auto i = 0uz; i < 3uz; ++i) {
            m[i, i] = v[i];
        }
        m[3, 3] = T{1};
        return m;
    }

    template <typename T>
    Matrix<T, 4> translate4(const Vector<T, 3>& v) noexcept {
        auto m = Matrix<T, 4>::identity();
        for (auto i = 0uz; i < 3uz; ++i) {
            m[i, 3] = v[i];
        }
        return m;
    }

    // Quaternion transformations

    namespace Detail {

        template <typename T, std::size_t N>
        void build_matrix(const Quaternion<T>& q, Matrix<T, N>& m) noexcept {
            m[0, 0] = q.a() * q.a() + q.b() * q.b() - q.c() * q.c() - q.d() * q.d();
            m[0, 1] = T{2} * q.b() * q.c() - T{2} * q.a() * q.d();
            m[0, 2] = T{2} * q.a() * q.c() + T{2} * q.b() * q.d();
            m[1, 0] = T{2} * q.a() * q.d() + T{2} * q.b() * q.c();
            m[1, 1] = q.a() * q.a() - q.b() * q.b() + q.c() * q.c() - q.d() * q.d();
            m[1, 2] = T{2} * q.c() * q.d() - T{2} * q.a() * q.b();
            m[2, 0] = T{2} * q.b() * q.d() - T{2} * q.a() * q.c();
            m[2, 1] = T{2} * q.a() * q.b() + T{2} * q.c() * q.d();
            m[2, 2] = q.a() * q.a() - q.b() * q.b() - q.c() * q.c() + q.d() * q.d();
        }

    }

    template <typename T>
    Vector<T, 3> rotate(const Quaternion<T>& q, const Vector<T, 3>& v) noexcept {
        return q.conj({T{0}, v}).vector_part();
    }

    template <typename T>
    Quaternion<T> q_rotate(T angle, const Vector<T, 3>& axis) noexcept {
        using std::cos;
        using std::sin;
        if (axis.is_null()) {
            return T{1};
        }
        angle /= T{2};
        return {cos(angle), sin(angle) * axis.dir()};
    }

    template <typename T>
    Matrix<T, 3> rotate3(const Quaternion<T>& q) noexcept {
        Matrix<T, 3> m;
        Detail::build_matrix(q, m);
        return m;
    }

    template <typename T>
    Matrix<T, 4> rotate4(const Quaternion<T>& q) noexcept {
        Matrix<T, 4> m;
        Detail::build_matrix(q, m);
        m[3, 3] = T{1};
        return m;
    }

    template <typename T>
    Matrix<T, 3> rotate3(T angle, const Vector<T, 3>& axis) noexcept {
        return rotate3(q_rotate(angle, axis));
    }

    template <typename T>
    Matrix<T, 4> rotate4(T angle, const Vector<T, 3>& axis) noexcept {
        return rotate4(q_rotate(angle, axis));
    }

}

namespace std {

    template <typename T, std::size_t N>
    struct formatter<RS::Vector<T, N>>:
    formatter<T> {
        template <typename FormatContext>
        auto format(const RS::Vector<T, N>& v, FormatContext& ctx) const {
            const std::formatter<T>& t_format = *this;
            auto out = ctx.out();
            auto ch = '[';
            for (auto x: v) {
                *out++ = ch;
                out = t_format.format(x, ctx);
                ch = ',';
            }
            *out++ = ']';
            return out;
        }
    };

    template <typename T, std::size_t N, RS::MatrixLayout L>
    struct std::formatter<RS::Matrix<T, N, L>>:
    std::formatter<T> {
        template <typename FormatContext>
        auto format(RS::Matrix<T, N, L> m, FormatContext& ctx) const {
            const std::formatter<T>& t_format = *this;
            auto out = ctx.out();
            auto ch1 = '[';
            for (auto r = 0uz; r < N; ++r) {
                *out++ = ch1;
                ch1 = ',';
                auto ch2 = '[';
                for (auto c = 0uz; c < N; ++c) {
                    *out++ = ch2;
                    ch2 = ',';
                    out = t_format.format(m[r, c], ctx);
                }
                *out++ = ']';
            }
            *out++ = ']';
            return out;
        }
    };

    template <typename T>
    struct formatter<RS::Quaternion<T>>:
    formatter<T> {
        template <typename FormatContext>
        auto format(const RS::Quaternion<T>& q, FormatContext& ctx) const {
            const std::formatter<T>& t_format = *this;
            auto out = ctx.out();
            *out++ = 'Q';
            auto ch = '[';
            for (auto x: q) {
                *out++ = ch;
                out = t_format.format(x, ctx);
                ch = ',';
            }
            *out++ = ']';
            return out;
        }
    };

    template <typename T, std::size_t N>
    struct greater<RS::Vector<T, N>> {
        bool operator()(const RS::Vector<T, N>& x, const RS::Vector<T, N>& y) const noexcept {
            return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end(), std::greater<T>());
        }
    };

    template <typename T, std::size_t N>
    struct less<RS::Vector<T, N>> {
        bool operator()(const RS::Vector<T, N>& x, const RS::Vector<T, N>& y) const noexcept {
            return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end(), std::less<T>());
        }
    };

    template <typename T, std::size_t N>
    struct hash<RS::Vector<T, N>> {
        std::size_t operator()(const RS::Vector<T, N>& v) const noexcept {
            return v.hash();
        }
    };

    template <typename T, std::size_t N, RS::MatrixLayout L>
    struct hash<RS::Matrix<T, N, L>> {
        std::size_t operator()(const RS::Matrix<T, N, L>& m) const noexcept {
            return m.hash();
        }
    };

    template <typename T>
    struct hash<RS::Quaternion<T>> {
        std::size_t operator()(const RS::Quaternion<T>& q) const noexcept {
            return q.hash();
        }
    };

}
