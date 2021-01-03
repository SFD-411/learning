/*
 * =====================================================================================
 *
 *       Filename:  ray.h
 *
 *    Description: Ray Class 
 *
 *        Version:  1.0
 *        Created:  08/30/20 02:56:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Richard I Christopher 
 *   Organization:  Brand Media
 *
 * =====================================================================================
 */

#pragma once
#include "vec3.h"

class ray{
public:
    ray() {}
    ray(const vec3 &start, const vec3 &destination) : Origin(start), Direction(destination) {}
    vec3 origin() const {return Origin;}
    vec3 direction() const {return Direction;}
    vec3 pointParam(double t) const { return Origin + t * Direction; }

    vec3 Origin;
    vec3 Direction;
};
