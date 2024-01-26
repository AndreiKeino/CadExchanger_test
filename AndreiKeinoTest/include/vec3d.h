#ifndef VEC3D_H
#define VEC3D_H
#include <iostream>
#include "types.h"

using namespace std;

class Vec3D 
{
protected:
    Float e[3];
  public:
    

    Vec3D(): e{0.0, 0.0, 0.0} {}
    Vec3D(Float x, Float y, Float z = 0.0) : e{x, y, z} {}
    Vec3D(const Vec3D& v): e{v.e[0], v.e[1], v.e[2]} {}
    Vec3D(const Vec3D&& v): e{v.e[0], v.e[1], v.e[2]} {}

    Float x() const { return e[0]; }
    Float y() const { return e[1]; }
    Float z() const { return e[2]; }

    Float operator[](int i) const { return e[i]; }
    Float& operator[](int i) { return e[i]; }
    
};

inline std::ostream& operator<<(std::ostream& out, const Vec3D& v) 
{
    return out << "Vec3D: (x, y, z) = (" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

class Point3D : public Vec3D
{
public:
    Point3D(): Vec3D() {}
    Point3D(Float x, Float y, Float z = 0.0) : Vec3D(x, y, z) {}
    Point3D(const Point3D& v): Vec3D(static_cast<const Vec3D&>(v)) {}
    Point3D(const Point3D&& v) : Vec3D(static_cast<const Vec3D&&>(v)) {}
};

inline std::ostream& operator<<(std::ostream& out, const Point3D& v)
{
    return out << "Point3D: (x, y, z) = (" << v[0] << ", " << v[1] << ", " << v[2] << ")";
}

#endif
