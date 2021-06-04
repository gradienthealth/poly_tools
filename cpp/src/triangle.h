#ifndef _TRIANGLE_H_
    #define _TRIANGLE_H_

#include "vec3.h"

template <typename T>
class Triangle
{
    public:

    Triangle();
    Triangle(Vec3<T> p1, Vec3<T> p2, Vec3<T> p3);
    void draw();
    ~Triangle();

    Vec3<T> p1, p2, p3;

};

template <typename T>
Triangle<T>::Triangle() 
{ 
    this->p1 = Vec3<T>();
    this->p2 = Vec3<T>();
    this->p3 = Vec3<T>();
};

template <typename T>
Triangle<T>::Triangle(Vec3<T> p1, Vec3<T> p2, Vec3<T> p3)
{
    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
}

#endif /* #ifndef _TRIANGLE_H_ */