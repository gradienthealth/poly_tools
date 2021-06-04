#ifndef _VEC3_H_
    #define _VEC3_H_

#include <ostream>

template <typename T>
class Vec3
{
    public:
        T x, y, z;

    public:
        Vec3();
        Vec3(T _x, T _y, T _z);

        Vec3 operator+(const Vec3 &other) const;
        Vec3 operator+(const T &val) const;

        void operator+=(const Vec3 &other);
        void operator+=(const T &val);

        Vec3 operator-(const Vec3 &other) const;
        Vec3 operator-(const T &val) const;

        void operator-=(const Vec3 &other);
        void operator-=(const T &val);

        Vec3 operator*(const Vec3 &other) const;
        Vec3 operator*(const T &val) const;

        void operator*=(const Vec3 &other);
        void operator*=(const T &val);

        Vec3 operator/(const Vec3 &other) const;
        Vec3 operator/(const T &val) const;

        void operator/=(const Vec3 &other);
        void operator/=(const T &val);      

        T sum(void);
        double magnitude(void);
        void normalize(void);

        static double dist(const Vec3 &v1, const Vec3 &v2);
        static double dot(const Vec3 &v1, const Vec3 &v2);
        static Vec3 cross(const Vec3 &v1, const Vec3 &v2);

        friend std::ostream& operator<<(std::ostream& os, Vec3<T> const& vec);
};

template <typename T>
Vec3<T>::Vec3() 
{ 
    this->x = 0;
    this->y = 0;
    this->z = 0;
};

template <typename T>
Vec3<T>::Vec3(T x, T y, T z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const Vec3<T> &other) const
{
    return Vec3<T>(
        this->x + other.x, 
        this->y + other.y, 
        this->z + other.z
    );
}

template <typename T>
Vec3<T> Vec3<T>::operator+(const T &val) const
{
    return Vec3<T>(
        this->x + val, 
        this->y + val, 
        this->z + val
    );
}

template <typename T>
void Vec3<T>::operator+=(const Vec3<T> &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

template <typename T>
void Vec3<T>::operator+=(const T &val)
{
    this->x += val;
    this->y += val;
    this->z += val;
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const Vec3<T> &other) const
{
    return Vec3<T>(
        this->x - other.x, 
        this->y - other.y, 
        this->z - other.z
    );
}

template <typename T>
Vec3<T> Vec3<T>::operator-(const T &val) const
{
    return Vec3<T>(
        this->x - val, 
        this->y - val, 
        this->z - val
    );
}

template <typename T>
void Vec3<T>::operator-=(const Vec3<T> &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}

template <typename T>
void Vec3<T>::operator-=(const T &val)
{
    this->x -= val;
    this->y -= val;
    this->z -= val;
}

template <typename T>
Vec3<T> Vec3<T>::operator*(const Vec3<T> &other) const
{
    return Vec3<T>(
        this->x*other.x, 
        this->y*other.y, 
        this->z*other.z
    );
}

template <typename T>
Vec3<T> Vec3<T>::operator*(const T &val) const
{
    return Vec3<T>(
        this->x*val, 
        this->y*val, 
        this->z*val
    );
}

template <typename T>
void Vec3<T>::operator*=(const Vec3<T> &other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

template <typename T>
void Vec3<T>::operator*=(const T &val)
{
    this->x *= val;
    this->y *= val;
    this->z *= val;
}

template <typename T>
Vec3<T> Vec3<T>::operator/(const Vec3<T> &other) const
{
    if (   val other.x == 0
        || val other.y == 0
        || val other.z == 0)
        return;

    return Vec3<T>(
        this->x/other.x, 
        this->y/other.y, 
        this->z/other.z
    );
}

template <typename T>
Vec3<T> Vec3<T>::operator/(const T &val) const
{
    if (val == 0)
        return;

    return Vec3<T>(
        this->x/val, 
        this->y/val, 
        this->z/val
    );
}

template <typename T>
void Vec3<T>::operator/=(const Vec3<T> &other)
{
    if (   val other.x == 0
        || val other.y == 0
        || val other.z == 0)
        return;
    
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}

template <typename T>
void Vec3<T>::operator/=(const T &val)
{
    if (val == 0)
        return;

    this->x /= val;
    this->y /= val;
    this->z /= val;
}

template <typename T>
double Vec3<T>::magnitude(void)
{
    return sqrt(
          (this->x * this->x) 
        + (this->y * this->y) 
        + (this->z * this->z)
    );
}

template <typename T>
T Vec3<T>::sum(void)
{
    this->x + this->y + this->z;
}

template <typename T>
void Vec3<T>::normalize(void)
{
    T mag = this->magnitude();
    if (mag != 0)
    {
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}

template <typename T>
double Vec3<T>::dist(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return (v1-v2).magnitude();
}

template <typename T>
double Vec3<T>::dot(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return (v1*v2).sum();
}

template <typename T>
Vec3<T> Vec3<T>::cross(const Vec3<T> &v1, const Vec3<T> &v2)
{
    return Vec3<T>(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x,
    );
}

template <typename T>
std::ostream& operator<<(std::ostream& os, Vec3<T> const& vec)
{ 
    return os << "[ " << vec.x << ', ' << vec.xy << ', ' << vec.z << ' ] ';
}

#endif /* #ifndef _VEC3_H_ */