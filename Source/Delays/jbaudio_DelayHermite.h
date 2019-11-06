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
 
 DelayHermite
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_HermiteInterpolation.h"
#include <cmath>
#include <cassert>
#include <vector>

namespace jbaudio
{
    class DelayHermite
    {
    public:
        DelayHermite()
        {
            setMaxSize (16);
        }
        
        // ================================================================================
        inline void reset()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
        }
        
        // ================================================================================
        void setMaxSize (int powerOf2)
        {
            int size = std::max ((int)std::exp2f (powerOf2), 4);
            array_.resize ((size_t)size, 0.0f);
            reset();
            mask_ = size - 1;
            writeIndex_ = 0;
        }
        
        // ================================================================================
        inline void push (float sample)
        {
            array_ [size_t (writeIndex_--)] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float get (float samplesDelay) const
        {
            assert (samplesDelay == clampLength (samplesDelay));
            const int asInt = (int) samplesDelay;
            const float x = samplesDelay - asInt;
            const float y0 = array_ [size_t ((writeIndex_ + asInt - 1) & mask_)];
            const float y1 = array_ [size_t ((writeIndex_ + asInt) & mask_)];
            const float y2 = array_ [size_t ((writeIndex_ + asInt + 1) & mask_)];
            const float y3 = array_ [size_t ((writeIndex_ + asInt + 2) & mask_)];
            
            return HermiteInterpolation::calculatePointV4 (x, y0, y1, y2, y3);
        }
        
        inline float getClipped (float samplesDelay) const
        {
            return get (clampLength (samplesDelay));
        }
        
        // ================================================================================
        inline int getMinDelayLengthSamples() const
        {
            return 2;
        }
        
        inline int getMaxDelayLengthSamples() const
        {
            return (int)array_.size() - 3;
        }
        
        inline float clampLength (float samplesDelay) const
        {
            return clamp (samplesDelay, (float)getMinDelayLengthSamples(), (float)getMaxDelayLengthSamples());
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_ = 0;
    };
}
