#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include "Globals.h"
#include "generator.h"
#include "communication.h"
#include "boundary.h"
#include "body.h"
#include "vector3.h"
#include "solver.h"

#define PRINT

namespace mpi = boost::mpi;


float retain; // number of spheres per processor initially
double radius; // radius of each sphere
int iterations; // number of iterations of the entire simulation
bool print=false;

typedef std::vector<Body> domain; //  all the balls in the current processor

void print_usage(char *prog) 
{
    std::cerr<<"Usage: "<<prog<<" -np nprocs -F retain -R radius -I iterations -[P] print"<<std::endl;
    exit(0);
}

void parse_args(int argc, char* argv[]) 
{
    if(argc<4) 
    {
        print_usage(argv[0]);
    }

    for (int i=1; i < argc; ++i)
    {
        if (strcmp(argv[i], "-F") == 0)
        {
            retain = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "-R") == 0)
        {
            radius = atof(argv[++i]);
        }
        else if (strcmp(argv[i], "-I") == 0)
        {
            iterations = atoi(argv[++i]);
        }
        else if (strcmp(argv[i], "-P") == 0)
        {
            print = true;
        }
    }
}//end parse_args()



int main(int argc, char* argv[])
{
    /*****************************************  Variables ***************************/
    domain mydomain;
    domain neighbors;
    vi stat;
    int myrank;
    int nprocs;

    /***************************************** Initializing *************************/
    parse_args(argc,argv);
    mpi::environment env(argc, argv);
    mpi::communicator world;
    myrank = world.rank();
    nprocs = world.size();
    //generate_spheres(mydomain,radius,retain,myrank,nprocs);
    fill_layers(mydomain,radius,myrank,nprocs,retain);

    /*************************************** Simulation *****************************/
    REP(iter,0,iterations)
    {
        /*
         * Step 1 : Determine which of the bodies move out of the boundary
         */
        cross_boundary(mydomain,stat,myrank);
        /*
         * Step 2 : Send the upper and lower information to correspondint processes
         */
        pass_information(mydomain,stat,myrank,world);
        /*
         * Receive information from the neighbors
         */
        receive_information(neighbors,myrank,world);
        /*
         * Step 3 : Call solver 
         */
        solve(mydomain);
        /*
         * Step 4 :
         * Barrier
         */
        /*
         * Step : 5 Send the updated information of all my neighbors to their parents
         * (here only send the force resulted from the collision with the remote neighber) 
         */
        send_information(neighbors,myrank,world);
        /*
         * Step 6 : Calculate the new velocties for all the bodies that crossed the boundary
         * */
        compute_new_velocities(stat);


    }

    if(myrank>0)
    std::cout << "I am process " << world.rank() << " of " << world.size()
        << "." << mydomain.size()<<std::endl;
    return 0;
}
