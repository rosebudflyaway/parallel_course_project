#ifndef BODY_H
#define BODY_H

#include "vector3.h"
#include <iostream>
class Body
{
    private:
        vector3 position;
        vector3 force;
        vector3 velocity; 
        vd lambda;
        double mass;
        double radius;
    public:
        Body(const vector3 &p)
        {
            position = p;
        }
        Body(const vector3 &p, const vector3 &f)
        {
            // p,f,v are position force anc veclocity respectively
            position = p; force= f;
        }
        Body(const vector3 &p, const vector3 &f,const vector3 &v)
        {
            // p,f,v are position force anc veclocity respectively
            position = p; force= f; velocity = v;
        }
        float get_y()
        {
            return position.y;
        }
        double get_mass()
        {
            return mass;
        }
        double get_inertia()
        {
            return 0.4*mass*radius*radius;
        }
        void print()
        {
            std::cout<<"("<<position.x<<","<<position.y<<","<<position.z<<")"<<std::endl;
        }
        vector3 get_position()
        {
            return position;
        }
        vector3 get_velocity()
        {
            return velocity;
        }
        vector3 get_ext()
        {
            return force;
        }
};
#endif
