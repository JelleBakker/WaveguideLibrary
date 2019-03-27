/*
 
 WaveShaper
 Waveguide Library - JB Audio
 
 */

#pragma once

#include <cmath>
#include <cassert>

namespace jbaudio
{
    class WaveShaper
    {
    public:
        // Laurent de Soras
        // http://www.musicdsp.org/en/latest/Effects/86-waveshaper-gloubi-boulga.html
        static float gloubiBoulga (float input)
        {
            const float x = input * 0.686306f;
            const float a = 1.0f + std::expf (std::sqrtf (std::fabs (x)) * -0.75f);
            return (std::expf (x) - std::expf (-x * a)) / (std::expf (x) + std::expf (-x));
        }
        
        // reaktor
        static float tanh (float input, float level)
        {
            assert (level > 0.0f);
            input /= level;
            input = std::tanhf (input); // todo: approximation
            input *= level;
            return input;
        }
        
    private:
    };
}
