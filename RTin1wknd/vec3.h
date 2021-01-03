/*
 * =====================================================================================
 *
 *       Filename:  vec3.h
 *
 *    Description:  Vec3 Class Rework
 *
 *        Version:  1.0
 *        Created:  08/30/20 04:28:34
 *       Revision:  Rebuild - Ray Tracing In One Weekend
 *       Compiler:  gcc
 *
 *         Author:  Richard Christopher, Peter Shirley 
 *   Organization:  Brand Media
 *
 * =====================================================================================
 */

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <algorithm>

class vec3{
public: 
    double e[3];

    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

    double x() const { return e[0]; }
    double r() const { return e[0]; }
    double y() const { return e[1]; }
    double g() const { return e[1]; }
    double z() const { return e[2]; }
    double b() const { return e[2]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i)  { return e[i]; }

    vec3& operator+=(const vec3 &v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t){
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t) { return *this *= 1/t; }

    double length() const { return sqrt(sqrLength()); }
    double sqrLength() const { return e[0]*e[0] + e[1]+e[1] + e[2]*e[2]; }
};

// using pnt3 = vec3;
// using color = vec3;

// Utility Functions
//

inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator*(double t, const vec3 &v){
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t){
    return t * v;
}

inline vec3 operator/(vec3 v, double t){
    return (1/t) * v;
}


inline double Dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0] * v2.e[0] +
           v1.e[1] * v2.e[1] +
           v1.e[2] * v2.e[2];
}

inline vec3 Cross(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

// divides a vector into into the square root of it's squared length
inline vec3 Unit(vec3 v){
    return v/v.length();
}

inline vec3 Clamp(vec3 &v, int max, int min){
    for(int i = 0; i < 3; i++){
        if(v[i] < min){
            v[i] = min;
        } else
        if(v[i] > max){
            v[i] = max;
        } else {
            v[i] = (int)v[i];
        }
    }
    return v;
}
