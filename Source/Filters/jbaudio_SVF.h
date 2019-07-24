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
 
 SVF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "../jbaudio_Maths.h"
#include <algorithm>

namespace jbaudio
{
    class SVF
    {
    public:
        SVF()
        {
            setSampleRate (44100.0f);
            setFreqAndRes (1000.0f, 0.5f);
            reset();
        }
        
        inline void reset()
        {
            buf1_ = 0.0f;
            buf2_ = 0.0f;
            lastLP_ = 0.0f;
            lastBP_ = 0.0f;
            lastHP_ = 0.0f;
        }
        
        inline void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        // it's more efficient to combine the two than calling them seperately
        inline void setFreqAndRes (float f, float r)
        {
            wDiv2_ = bilinearTransform (f, sampleRate_);
            r = std::min (r, 0.96875f);
            r = 1.0f - r;
            twoR_ = r + r;
            resOrFreqChanged();
        }
        
        inline void setFreq (float f)
        {
            wDiv2_ = bilinearTransform (f, sampleRate_);
            resOrFreqChanged();
        }
        
        inline void setRes (float r)
        {
            assert (r <= 0.96875f);
            r = 1.0f - r;
            twoR_ = r + r;
            resOrFreqChanged();
        }
        
        inline void tick (float input)
        {
            float a = buf1_ * d_ + buf2_;
            lastHP_ = (input - a) / a_;
            
            float b = lastHP_ * wDiv2_;
            lastBP_ = b + buf1_;
            buf1_ = lastBP_ + b;
            
            float c = lastBP_ * wDiv2_;
            lastLP_ = c + buf2_;
            buf2_ = lastLP_ + c;
        }
        
        inline float tickLP (float input)
        {
            tick (input);
            return lastLP_;
        }
        
        inline float tickBP (float input)
        {
            tick (input);
            return lastBP_;
        }
        
        inline float tickHP (float input)
        {
            tick (input);
            return lastHP_;
        }
        
        inline float getLastLP() const { return lastLP_; }
        inline float getLastBP() const { return lastBP_; }
        inline float getLastHP() const { return lastHP_; }
        
        inline float getPhaseDelayLP (float freq)
        {
            assert (false); // todo
            return 0.0f;
        }
        
    private:
        float sampleRate_;
        
        float wDiv2_;
        float twoR_;
        float d_;
        float a_;
        
        float buf1_;
        float buf2_;
        
        float lastLP_;
        float lastBP_;
        float lastHP_;
        
        inline void resOrFreqChanged()
        {
            d_ = twoR_ + wDiv2_;
            a_ = d_ * wDiv2_ + 1.0f;
        }
    };
}

