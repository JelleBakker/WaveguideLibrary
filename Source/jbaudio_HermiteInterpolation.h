/*
 
 HermiteInterpolation
 Waveguide Library - JB Audio
 
 Description: Hermite interpolation
 https://www.musicdsp.org/en/latest/Other/93-hermite-interpollation.html?highlight=hermite
 
 */

#pragma once

#include <array>

namespace jbaudio
{
    class HermiteInterpolation
    {
    public:
        static constexpr float calculatePoint (float x, float y0, float y1, float y2, float y3)
        {
            float c0 = y1;
            float c1 = 0.5f * (y2 - y0);
            float c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
            float c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);
            
            return ((c3 * x + c2) * x + c1) * x + c0;
        }
        
    private:
    };
}
