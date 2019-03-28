/*
 
 Maths
 Waveguide Library - JB Audio
 
 */

#pragma once

#include <cassert>
#include <algorithm>
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
    
    inline float decibelToAmp (float dB, float minDB = -100.0f)
    {
        if (dB <= minDB)
            return 0.0f;
        static float a = std::log2f (10.0f);
        return std::exp2f (a * dB * 0.05f); // see powXGrt0toY
    }
    
    inline float ampToDecibel (float amp, float minDB = -100.0f)
    {
        if (amp > 0.0f)
            return std::max (minDB, std::log10f (amp) * 20.0f);
        return minDB;
    }
    
    inline float getRMSAmp (float* data, int num)
    {
        assert (num > 0);
        float sum = 0.0f;
        for (int i = 0; i < num; i++)
            sum += data[i] * data[i];
        return std::sqrtf (sum / num);
    }
    
    inline float getRMSDB (float* data, int num)
    {
        return ampToDecibel (getRMSAmp (data, num));
    }
    
    inline float getPeakAmp (float* data, int num)
    {
        float max = 0.0f;
        for (int i = 0; i < num; i++)
            max = std::max (max, std::fabsf (data[i]));
        return max;
    }
    
    inline float getPeakDB (float* data, int num)
    {
        return ampToDecibel (getPeakAmp (data, num));
    }
};
