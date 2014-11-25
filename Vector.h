// Vector.h: interface for the Vector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTOR_H__C2EAE644_668E_4AF3_815D_94C8FEB090B6__INCLUDED_)
#define AFX_VECTOR_H__C2EAE644_668E_4AF3_815D_94C8FEB090B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <cmath>

class Vector  
{
public:

	Vector(double x = 0.0, double y = 0.0, double z = 0.0) : x(x), y(y), z(z) {};

	Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {};

	virtual ~Vector() {};

	union {
		double coordinate[3];
		struct {
			double x;
			double y;
			double z;
		};
	};

    Vector  operator -  (const Vector& v) const { return Vector(x - v.x,y - v.y,z - v.z); };

    Vector  operator +  (const Vector& v) const { return Vector(x + v.x,y + v.y,z + v.z); }

    Vector& operator += (const Vector& v) { x += v.x; y += v.y; z += v.z; return *this; };

	Vector& operator -= (const Vector& v) { x -= v.x; y -= v.y; z -= v.z; return *this; };

    Vector& operator *= (double a) { x *= a; y *= a; z *= a; return *this; };

	Vector& operator /= (double a) { x /= a; y /= a; z /= a; return *this; };

	Vector  operator *  (const Vector& v) { return Vector(x*v.x,y*v.y,z*v.z); };

	bool	operator == (const Vector& v) { return ((v.x == x) && (v.y == y) && (v.z == z)); };

	double getLength(void) {
		return sqrt(x*x + y*y + z*z);
	}

};

inline Vector operator * (const Vector& v,double a)
{
        return Vector(v.x*a,v.y*a,v.z*a);
}

inline Vector operator * (double a,const Vector& v)
{
        return Vector(v.x*a,v.y*a,v.z*a);
}

inline Vector operator / (const Vector& v,double a)
{
        return Vector(v.x/a,v.y/a,v.z/a);
}

inline Vector operator / (double a,const Vector& v)
{
        return Vector(v.x/a,v.y/a,v.z/a);
}

#endif // !defined(AFX_VECTOR_H__C2EAE644_668E_4AF3_815D_94C8FEB090B6__INCLUDED_)