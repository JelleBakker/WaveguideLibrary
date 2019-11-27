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
    static constexpr float min3dBAmp = 0.7079457844f;
    
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
    inline void cancelDenormals (float& f)
    {
        f += 1E-18;
    }
    
    // From Reaktor
    inline float powXGrt0ToY (float x, float y)
    {
        return std::exp2f (std::log2f (x) * y);
    }
    
    static constexpr float c0Freq_ = 8.1757989156f;
    
    inline float pitchToFreq (float p)
    {
        return std::exp2f (p / 12.0f) * c0Freq_;
    }
    
    inline float freqToPitch (float f)
    {
        return 12.0f * std::log2f (f / c0Freq_);
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
    
    // https://en.wikibooks.org/wiki/Digital_Signal_Processing/Bilinear_Transform
    inline float bilinearTransformOpt (float f, float piDivSr)
    {
        float a = f * piDivSr;
        assert (a >= 0.0f && a <= 0.5f * pi);
        return std::tanf (f * piDivSr);
    }
    
    // pi / sr can be calculated once at sr change, then use the opt version
    inline float bilinearTransform (float f, float sr)
    {
        return bilinearTransformOpt (f, pi / sr);
    }
    
    template <typename T>
    inline const T& clamp (const T& value, const T& min, const T& max)
    {
        assert (min <= max);
        return value < min ? min : value > max ? max : value;
    }
    
    template <typename T>
    inline T map (T input, T inputMin, T inputMax, T targetMin, T targetMax)
    {
        return targetMin + (targetMax - targetMin) * ((input - inputMin) / (inputMax - inputMin));
    }
    
    
};
