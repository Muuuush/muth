#ifndef MUTH_VEC2_H
#define MUTH_VEC2_H

#include <string>
#include <sstream>

namespace Muth
{
    template<typename T>
    struct Vec2
    {   
    public:
        T x;
        T y;

    public:
        inline Vec2() : x(0), y(0) {}
        inline Vec2(const T &x, const T &y) : x(x), y(y) {}
        inline Vec2(const T *values) : x(values[0]), y(values[1]) {}
    
    public:
        inline T& operator[] (const size_t &idx) { return idx? y : x; }

        inline std::string to_string(const std::string &separator = " ") const
        {
            std::stringstream ss;
            ss << x << separator << y;
            return std::move(ss.str());
        }

    public:
        inline T length_square() const { return x * x + y * y; }
        inline T length() const
        {
            if (std::is_same<T, float>::value)
                return sqrtf(this->length_square());
            return sqrt(this->length_square());
        }
        inline Vec2<T> normalized() const { return (*this) / this->length(); }
        inline T projection(const Vec2<T> &vec) const { return this->dot(vec) / vec.length(); }
        inline Vec2<T> projection_vector(const Vec2<T> &vec) const { return vec.normalized() * this->projection(vec); }
        inline T dot(const Vec2<T> &other) const { return x * other.x + y * other.y; }
    
    public:
        inline Vec2<T> &operator+= (const Vec2<T> &other) { *this = (*this) + other; return *this; }
        inline Vec2<T> &operator-= (const Vec2<T> &other) { *this = (*this) - other; return *this; }
        inline Vec2<T> &operator*= (T lambda) { *this = (*this) * lambda; return *this; }
        inline Vec2<T> &operator/= (T lambda) { *this = (*this) / lambda; return *this; }
    };

    template <typename T>
    inline Vec2<T> operator+(const Vec2<T> &left, const Vec2<T> &right)
    {
        return { left.x + right.x, left.y + right.y };
    }

    template <typename T>
    inline Vec2<T> operator-(const Vec2<T> &left, const Vec2<T> &right)
    {
        return { left.x - right.x, left.y - right.y };
    }

    template <typename T>
    inline Vec2<T> operator*(const Vec2<T> &vec, T lambda)
    {
        return { vec.x * lambda, vec.y * lambda };
    }

    template <typename T>
    inline Vec2<T> operator/(const Vec2<T> &vec, T lambda)
    {
        return { vec.x / lambda, vec.y / lambda };
    }

    template <typename T>
    inline Vec2<T> operator*(T lambda, const Vec2<T> &vec)
    {
        return { vec.x * lambda, vec.y * lambda };
    }

    template <typename T>
    inline T operator*(const Vec2<T> &left, const Vec2<T> &right)
    {
        return left.dot(right);
    }

    template <typename T>
    inline Vec2<T> operator-(const Vec2<T> &vec)
    {
        return { -vec.x, -vec.y };
    }

    template <typename T>
    inline std::ostream &operator<<(std::ostream &out, const Vec2<T> &vec)
    {
        return out << vec.to_string();
    }

    template<typename T>
    inline T cross(Vec2<T> left, Vec2<T> right)
    {
        return left[0] * right[1] - left[1] * right[0];
    }
} // namespace Muth

#endif