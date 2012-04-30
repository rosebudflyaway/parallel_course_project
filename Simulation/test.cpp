#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Globals.h"
#include "body.h"
#include "vector3.h"
#include "TimeTracker.h"

int main(int argc,const char* argv[])
{
    vector3 v(1,2,3);
    Body b(v);
    b.print();
    std::srand(time(NULL));
    std::cout<<RangeFloat(1,2)<<std::endl;
    Tracker track;
    track.print_all();
    return 0;
}
