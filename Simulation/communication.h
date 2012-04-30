#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include "Globals.h"
#include "body.h"

typedef std::vector<Body> domain; //  all the balls in the current processor
void pass_information(const domain &mydomain,const vi &stat, int myrank, boost::mpi::communicator &world)
{
    // depending on the status send the objects to neighbors
    REP(i,0,stat.size())
    {
        if(stat[i] != 0)
        {
            // if the stat==1 send to upper o/w lower
            // world.send ....
        }
    }

}
#endif
