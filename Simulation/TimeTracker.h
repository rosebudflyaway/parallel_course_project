/*
 * Author : Pranay Anchuri
 * Date : 04/25/2012
 * Email : anchupa@cs.rpi.edu
 */
#ifndef TIMETRACKER_H
#define TIMETRACKER_H

#include "Globals.h"
#include <string>
class Tracker
{
    private:
        msb status; // key is the string and the value is whether the timer is on
        map<string,vector<long long> > times; // vector of start and end times
    public:
        void start(string param);
        void end(string param);
        void print(string param);
        void print_all();
        unsigned long long rdtsc(void);
};
#endif
