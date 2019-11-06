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
 
 OnePoleZDF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "../jbaudio_Maths.h"
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
            setFreqClipped (freq_);
        }
        
        inline void setFreq (float f)
        {
            freq_ = f;
            float a = bilinearTransform (f, sampleRate_);
            g_ = a / (1.0f + a);
        }
        
        inline void setFreqClipped (float f)
        {
            setFreq (clamp (f, 0.0f, sampleRate_ * 0.49f));
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
