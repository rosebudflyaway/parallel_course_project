#ifndef GLOBALS_H
#define GLOBALS_H

#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <time.h>
#include "stdio.h"

using namespace std;
#define tr(container, it) for(typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define all(c) c.begin(), c.end()
#define present(container, element) (container.find(element) != container.end())
#define cpresent(container, element) (find(all(container),element) != container.end())
#define REP(i, a, b) for (int i = (int)a; i < (int)b; i++)
#define PER(i, a, b) for (int i = (int)a; i < (int)b; i--)
#define vi(a) vector<int> a

typedef vector<double> vd;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<vector<double> > vvd;
typedef vector<string> vs;
typedef map<string,long long> msl; // map of string and long long
typedef map<string,bool> msb; // map of string and bool


void print_vi(const vi& x);
void print_vvi(const vvi& x);

float RangeFloat(float min, float max);
#endif
