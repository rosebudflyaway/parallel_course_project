#include <climits>
#include <iostream>

#include <ctime>

int main(int argc, char* const argv[])
{
    srand(time(NULL));
    for ( int i = 0; i < 100; i++ )
    {
        std::cout << "Value: " << (4.0 * (rand() / (double)RAND_MAX)) << std::endl;
    }

    return 0;
}
