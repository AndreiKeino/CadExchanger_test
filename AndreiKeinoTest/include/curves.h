#ifndef CURVES_H
#define CURVES_H

#include "types.h"
#include "vec3d.h"
#include <cmath>
#include <vector>
#include <memory>
#include <random>
#include <ctime>

class ICurve
{
public:
    virtual Point3D coordinates(Float t) const = 0;
    virtual Vec3D derivatives(Float t) const = 0;
    virtual std::ostream& write(std::ostream& out) const = 0;
    virtual FloatVector parameters() const = 0;
    virtual ~ICurve() = default;
};

class Circle: public ICurve
{
    // https://en.wikipedia.org/wiki/Circle
protected:
    Float r = 1.0;
    
public:
    Circle(Float r): r(r) 
    {
        if (r <= 0)
        {
            throw std::domain_error("Circle radius value should be positive.");
        }        
    }
    
    Point3D coordinates(Float t) const override
    {
        return Point3D(r * cos(t), r * sin(t));
    }
    
    Vec3D derivatives(Float t) const override 
    {
        // https://en.wikipedia.org/wiki/Differentiation_of_trigonometric_functions
        return Vec3D(- r * sin(t), r * cos(t));
    }
    
    std::ostream& write(std::ostream& out) const override
    {
        return out << "Circle: radius = " << r;
    }
    
    FloatVector parameters() const override
    {
        return {r};
    }
    
};

class Ellipse: public ICurve
{
    // https://en.wikipedia.org/wiki/Ellipse
protected:
    Float a = 1.0;
    Float b = 1.0;
    
public:
    Ellipse(Float a, Float b): a(a), b(b)
    {
        if (a <= 0 || b <= 0)
        {
            throw std::domain_error("Ellipse width and height values should be positive.");
        }        
    }
    
    Point3D coordinates(Float t) const override
    {
        return Point3D(a * cos(t), b * sin(t));
    }
    
    Vec3D derivatives(Float t) const override 
    {
        // https://en.wikipedia.org/wiki/Differentiation_of_trigonometric_functions
        return Vec3D(- a * sin(t), b * cos(t));
    }
    
    std::ostream& write(std::ostream& out) const override
    {
        return out << "Ellipse: a = " << a << ", b = " << b;
    }
    
    FloatVector parameters() const override
    {
        return {a, b};
    }
    
    
};

class Helix: public ICurve
{
    // https://en.wikipedia.org/wiki/Helix
protected:
    Float a = 1.0;
    Float b = 1.0;
    
public:
    Helix(Float a, Float b): a(a), b(b)
    {
        if (a <= 0)
        {
            throw std::domain_error("Helix radius value should be positive.");
        }        
    }
    
    Point3D coordinates(Float t) const override
    {
        return Point3D(a * cos(t), a * sin(t), b * t);
    }
    
    Vec3D derivatives(Float t) const override
    {
        // https://en.wikipedia.org/wiki/Differentiation_of_trigonometric_functions
        return Vec3D(- a * sin(t), a * cos(t), b);
    }
    
    std::ostream& write(std::ostream& out) const override
    {
        return out << "Helix: a = " << a << ", b = " << b;
    }
    
    FloatVector parameters() const override
    {
        return {a, b};
    }    
    
};

inline std::ostream& operator<<(std::ostream& out, const ICurve& p)
{
    return (&p)->write(out);
}

using CurvePtr = std::shared_ptr<ICurve>;


class RandomCurveCreator
{
public:
    CurvePtr create_random_curve(Float min = 1e-11, Float max = 11)
    {
        
        std::random_device rd;  
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> float_dis(min, max);   
        std::uniform_int_distribution<> int_dis(0, 2);
        const int random_type = int_dis(gen);
        CurvePtr p = nullptr;
        
        switch(random_type)
        {
            case 0:
                p =  std::make_shared<Circle>(float_dis(gen));
                break;
            case 1:
                p = std::make_shared<Ellipse>(float_dis(gen), float_dis(gen));
                break;
            case 2:
                p = std::make_shared<Helix>(float_dis(gen), float_dis(gen));
                break;
            default:
                throw std::domain_error("Unknown curve type.");
                
        };
        
        return p;                
    }
};

#endif 
