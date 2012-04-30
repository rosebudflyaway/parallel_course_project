#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include <iostream>
#include "vec.h"
namespace mpi = boost::mpi;
int main(int argc, char* argv[])
{
    mpi::environment env(argc, argv);
    mpi::communicator world;
//    std::cout << "I am process " << world.rank() << " of " << world.size()
//<< "." << std::endl;
    if(world.rank()==0)
    {
        Vec v(2,3);
        world.send(1,0,v);
    }
    else
    {
        int val;
        Vec r;
        world.recv(0,0,r);
        std::cout<<r.get_x()<<std::endl;
        //std::cout<<"the value received is "<<val<<std::endl;
    }
return 0;
}
