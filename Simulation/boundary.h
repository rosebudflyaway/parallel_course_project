/*
 * Author : Pranay Anchuri
 * Date : 04/24/2012
 * Email : anchupa@cs.rpi.edu
 */
#ifndef BOUNDARY_h
#define BOUNDARY_h

#include "Globals.h"
#include "vector3.h"
#include "body.h"

int status(Body &bd,int rank)
{
    /*
     * Returns 0 : if the current position doesnt cross the boundary
     * 1 : if the if the body belongs to the rank above the current one and -1 if it belongs to rank below
     * Compute pos.y-radius and return the value based on the value
     * */
    float y = bd.get_y();
    if(y>rank+1)
        return 1;
    else if(y<rank)
        return -1;
    else
        return 0;
}
void cross_boundary(vector<Body> &domain, vector<int> &stat,int myrank)
{
    // for each body find whether it still remains to be in the same domain or needs to sent to neighbors
    // Iterate over each body in the vector and copy if it crosses the boundary
    tr(domain,it)
    {
        stat.push_back(status(*it,myrank));
    }
}

#endif
