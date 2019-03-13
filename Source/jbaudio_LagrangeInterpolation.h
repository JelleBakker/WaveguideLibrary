/*
 
 LagrangeInterpolation
 Waveguide Library - JB Audio
 
 Description: Lagrange interpolation
 
 */

#pragma once

#include <array>

namespace jbaudio
{
    class LagrangeInterpolation
    {
    public:
        template <int N>
        // e.g calculatePoint ({1, 4, 9}, 2.5) returns 2.5 ^ 2 = 6,25
        static float calculatePoint (std::array <float, N> points, float p)
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
            float sum = 0.0f;
            for (auto& s : h)
                sum += s;
            return sum;
        }
        
    private:
    };
}
