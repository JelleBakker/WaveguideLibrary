/*
 
 OnePoleZDF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <cmath>

namespace jbaudio
{
    class OnePoleZDF
    {
    public:
        OnePoleZDF()
        {
            setSampleRate (44100.0f);
        }
        
        inline void reset()
        {
            z1_ = 0.0f;
        }
        
        inline void setSampleRate (float sr)
        {
            sampleRate_ = sr;
            setFreq (freq_);
        }
        
        inline void setFreq (float f)
        {
            f = std::clamp (f, 0.01f, sampleRate_ - 1.0f); // -1.0f needed?
            freq_ = f;
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
            cancelDenormals (z1_);
            return b;
        }
        
        inline float tickHP (float input)
        {
            return input - tickLP (input);
        }
        
        inline float getPhaseDelay (float freq)
        {
            float im = freq / freq_;
            float re = 1.0f;
            float a = 1.0f / (re * re + im * im);
            im = -im * a;
            re = re * a;
            // TODO
            
        }
        
    private:
        float freq_ = 1000.0f;
        float g_;
        float sampleRate_;
        
        float z1_ = 0.0f;
    };
}
