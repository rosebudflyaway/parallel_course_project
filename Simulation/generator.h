#ifndef GENERATOR_H
#define GENERATOR_H

#include "vector3.h"
#include "body.h"
#include "Globals.h"

void one_sphere(vector<Body> &mydomain, double radius, int rank,int boundary)
{
    // X range for the center of the sphere : 0 to p-1
    // Y range for the center of the sphere  : [rank-rank+1)
    // Z range for the center of the sphere : [0-p)
    float x = RangeFloat(0,boundary);
    float y = RangeFloat(rank,rank+1);
    float z = RangeFloat(0,boundary);
    mydomain.push_back(vector3(x,y,z));
}
void generate_spheres(vector<Body> &mydomain, double radius, int num, int rank, int boundary)
{
    /*
     * mydomain :  holder for all the spheres
     * radius : radius of the sphere
     * num : number of spheres to generate
     * rank : rank of the processor which calls this function
     * boundary: size of the universe = nprocs
     */

    REP(i,0,num)
    {
        // generate a sphere and push it back
        one_sphere(mydomain,radius,num,rank);
    }
}

void prune_layers(vector<Body> &mydomain,float factor)
{
    // remove factor random bodies from the domain
    int retain = mydomain.size()*factor;
    std::random_shuffle(all(mydomain));
    mydomain.erase(mydomain.begin()+retain,mydomain.end());
}

void fill_layers(vector<Body> &mydomain,double r,int rank,int boundary,float retain=0.1)
{
    /*
     * First pack the domain of the current rank with the spheres
     * Random shuffle the elements in the vector
     * Remove the elements at the end
     */
    for(float k=r; k < boundary-r; k+=2*r)
    {
        for(float j=rank+r; j < rank+1-r; j+= 2*r)
        {
            for(float i=r;i<boundary-r;i+=2*r)
            {
                mydomain.push_back(Body(vector3(i,j,k)));
                //std::cout<<i<<","<<j<<","<<k<<std::endl;
            }
        }
    }
    prune_layers(mydomain,retain);

}

#endif

