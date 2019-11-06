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
 
 DelayAP
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "../jbaudio_Maths.h"
#include <vector>
#include <cassert>

namespace jbaudio
{
    // https://ccrma.stanford.edu/~jos/pasp/First_Order_Allpass_Interpolation.html
    class DelayAP
    {
    public:
        DelayAP()
        {
            setMaxSize (16);
        }
        
        // ================================================================================
        inline void reset()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
            apZ1_ = 0.0f;
        }
        
        // ================================================================================
        void setMaxSize (int powerOfTwo)
        {
            assert (powerOfTwo >= 0);
            array_.resize ((size_t)std::exp2f (powerOfTwo), 0.0f);
            reset();
            mask_ = (int)array_.size() - 1;
            writeIndex_ = 0;
        }
        
        // ================================================================================
        inline void push (float sample)
        {
            array_[size_t (writeIndex_--)] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float get (float samplesDelay)
        {
            assert (samplesDelay == clampLength (samplesDelay));
            int apM = (int)samplesDelay;
            float fract = samplesDelay - apM;
            if (fract < 0.1f)
            {
                fract += 1.0f; // delta range of [0.1, 1.1]
                apM -= 1;
            }
            const float apN = (1.0f - fract) / (1.0f + fract);
            
            const float a = array_[size_t ((writeIndex_ + apM) & mask_)];
            
            const float b = apZ1_ * -apN + a;
            const float output = b * apN + apZ1_;
            apZ1_ = b;
            return output;
        }
        
        inline float getClipped (float samplesDelay)
        {
            return get (clampLength (samplesDelay));
        }
        
        // ================================================================================
        inline int getMinDelayLengthSamples() const
        {
            return 1;
        }
        
        inline int getMaxDelayLengthSamples() const
        {
            return (int)array_.size();
        }
        
        inline float clampLength (float samplesDelay) const
        {
            return clamp (samplesDelay, (float)getMinDelayLengthSamples(), (float)getMaxDelayLengthSamples());
        }
        
    private:
        std::vector <float> array_;
        
        int mask_;
        int writeIndex_;
        
        float apZ1_ = 0.0f;
    };
}
