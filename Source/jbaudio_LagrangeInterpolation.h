/*
 
 This file is part of the JB Audio Waveguide C++ Library
 
 =============================================
 MIT License
 
 Copyright (c) 2019 JB Audio
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 =============================================
 
 */

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
