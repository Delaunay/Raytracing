#ifndef RAYTRACING_UTILS_HEADER_
#define RAYTRACING_UTILS_HEADER_

#include "Vector.h"
#include <random>

namespace raytracing{

    // return a number between [-1; 1]
    // use C++11 to generate better random number
    double rand_num(double min = -1, double max = 1){
        static std::mt19937 random_engine; // no seed
        static std::uniform_real_distribution<double> uniform(0, 1);
        return uniform(random_engine) * (max - min) + min;
    }

    // Return a Random vector
    Vector3d random_vector(double min = -1, double max = 1){
        return Vector3d(rand_num(min, max), rand_num(min, max), rand_num(min, max));
    }

}


#endif
