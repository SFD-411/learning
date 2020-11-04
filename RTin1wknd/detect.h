/*
 * =====================================================================================
 *
 *       Filename:  detect.h
 *
 *    Description: Reflection 
 *
 *        Version:  1.0
 *        Created:  09/03/20 10:22:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Richard Christopher 
 *   Organization:  Brand Media
 *
 * =====================================================================================
 */

#include "ray.h"

struct detection{
    vec3 point;
    vec3 normal;
    double t;
}

class reflection{
    public:
        virtual bool collide(const ray &r, double t_min, double t_max, detection &rec) const = 0;
};
