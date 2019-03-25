/*
 
 Maths
 Waveguide Library - JB Audio
 
 */

#pragma once
#include <cmath>

namespace jbaudio
{
    static constexpr float pi = 3.14159265358979f;
    static constexpr float twoPi = pi * 2.0f;
    
    template <int N>
    struct ConstexprPow2f
    {
        static constexpr int value_ = 2.0f * ConstexprPow2f <N-1>::value_;
    };
    
    template<>
    struct ConstexprPow2f <0>
    {
        static constexpr int value_ = 1;
    };
    
    // Credits to Martijn Zwartjes
    constexpr void cancelDenormals (float& f)
    {
        f += 1E-18;
    }
    
    // From Reaktor
    inline float powXGrt0ToY (float x, float y)
    {
        return std::exp2f (std::log2f (x) * y);
    }
    
    inline float pitchToFreq (float p)
    {
        return std::exp2f (p / 12.0f) * 8.1758f;
    }
    
    inline float freqToPitch (float f)
    {
        return 12.0f * std::log2f (f / 8.1758f);
    }
    
};
