/*
 
 OnePoleZDF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <algorithm>
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
            freq_ = f;
            float a = bilinearTransform (f, sampleRate_);
            g_ = a / (1.0f + a);
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
        
        inline float getPhaseDelayLP (float freq)
        {
            float a = freq / freq_;
            float re = 1.0f / (a * a + 1.0f);
            float im = -(a * re);
            
            return std::atan2f (im, re);
        }
        
    private:
        float freq_ = 1000.0f;
        float g_;
        float sampleRate_;
        
        float z1_ = 0.0f;
    };
    
    class OnePoleZDFHighShelf
    {
    public:
        OnePoleZDFHighShelf()
        {
            setFreqAndGainDB (2000.0f, 0.0f);
        }
        
        void setSampleRate (float sr)
        {
            onePole_.setSampleRate (sr);
        }
        
        inline void reset()
        {
            onePole_.reset();
        }
        
        inline void setFreqAndGainDB (float f, float dB)
        {
            setFreqAndGainAmp (f, decibelToAmp (dB));
        }
        
        inline void setFreqAndGainAmp (float f, float g)
        {
            gain_ = g - 1.0f;
            onePole_.setFreq (f * std::sqrtf (g));
        }

        inline float tick (float input)
        {
            return input + onePole_.tickHP (input) * gain_;
        }
        
    private:
        OnePoleZDF onePole_;
        float gain_;
    };
    
    class OnePoleZDFLowShelf
    {
    public:
        OnePoleZDFLowShelf()
        {
            setFreqAndGainDB (2000.0f, 0.0f);
        }
        
        void setSampleRate (float sr)
        {
            onePole_.setSampleRate (sr);
        }
        
        inline void reset()
        {
            onePole_.reset();
        }
        
        inline void setFreqAndGainDB (float f, float dB)
        {
            setFreqAndGainAmp (f, decibelToAmp (dB));
        }
        
        inline void setFreqAndGainAmp (float f, float g)
        {
            gain_ = g - 1.0f;
            onePole_.setFreq (f / std::sqrtf (g));
        }
        
        inline float tick (float input)
        {
            return input + onePole_.tickLP (input) * gain_;
        }
        
    private:
        OnePoleZDF onePole_;
        float gain_;
    };
}
