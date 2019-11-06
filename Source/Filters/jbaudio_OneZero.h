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
 
 OneZero
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "jbaudio_OnePoleZDF.h"

// TODO
namespace jbaudio
{
    class OneZero
    {
    public:
        OneZero()
        {
            setSampleRate (44100.0f);
            setFreq (22040.0f);
        }
        
        inline void reset()
        {
            z1_ = 0.0f;
        }
        
        inline void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        inline void setFreq (float freq)
        {
            assert (false); // not working yet
            assert (freq = clampFreq (freq));
            b1_ = std::sinf (freq * twoPi / sampleRate_) * 0.5f;
            b0_ = 1.0f - b1_;
        }
        
        inline void setFreqClipped (float freq)
        {
            setFreq (clampFreq (freq));
        }
        
        inline float clampFreq (float freq) const
        {
            return clamp (freq, getMinFreq(), getMaxFreq());
        }
        
        // a one zero filter cannot have a cutoff freq smaller than samplerate / 4
        inline float getMinFreq() const
        {
            return sampleRate_ * 0.25f;
        }
        
        inline float getMaxFreq() const
        {
            return sampleRate_ * 0.5f;
        }
        
        inline float tickLP (float input)
        {
            return 0.0f;
        }
        
        inline float tickHP (float input)
        {
            return input - tickLP (input);
        }
        
    private:
        float sampleRate_;
        float z1_;
        float b0_;
        float b1_;
    };
}
