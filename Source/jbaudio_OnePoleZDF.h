/*
 
 OnePoleZDF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include <cmath>

namespace jbaudio
{
    
static constexpr float pi = 3.14159265358979f;

class OnePoleZDF
{
public:
    OnePoleZDF()
    {
        setSampleRate (44100.0f);
        setFreq (1000.0f);
    }
    
    inline void reset()
    {
        z1_ = 0.0f;
    }
    
    inline void setSampleRate (float sr)
    {
        sampleRate_ = sr;
    }
    
    inline void setFreq (float f)
    {
        f = std::clamp (f, 0.01f, sampleRate_ - 1.0f); // -1.0f needed?
        f *= pi / sampleRate_;
        f = std::min (f, 0.5f * pi);
        f = std::tan (f);
        g_ = f / (1.0f + f);
    }
    
    inline float tickLP (float input)
    {
        auto a = (input - z1_) * g_;
        auto b = a + z1_;
        z1_ = a + b;
        return b;
    }
    
    inline float tickHP (float input)
    {
        return input - tickLP (input);
    }
    
private:
    float g_ = 0.0f;
    float sampleRate_ = 44100.0f;
    
    float z1_ = 0.0f;
};

}
