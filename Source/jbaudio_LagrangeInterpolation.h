/*
 
 LagrangeInterpolation
 Waveguide Library - JB Audio
 
 Description: Lagrange interpolation
 https://en.wikipedia.org/wiki/Lagrange_polynomial
 https://ccrma.stanford.edu/~jos/Interpolation/Lagrange_Interpolation.html
 
 */

#pragma once

#include <array>

namespace jbaudio
{
    
class LagrangeInterpolation
{
public:
    // e.g calculatePoint ({1, 4, 9}, 2.5) returns 2.5 ^ 2 = 6,25
    template <int N>
    static inline float calculatePoint (std::array <float, N> points, float p)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i != j)
                {
                    points[i] *= (p - (j + 1)) / ((i + 1) - (j + 1));
                }
            }
        }
        float sum = points[0];
        for (int i = 1; i < N; i++)
            sum += points[i];
        return sum;
    }
    
private:
};
    
}
