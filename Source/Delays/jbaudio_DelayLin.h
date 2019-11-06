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
 
 DelayLin
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "../jbaudio_Maths.h"
#include <vector>
#include <cassert>

namespace jbaudio
{
    class DelayLin
    {
    public:
        DelayLin()
        {
            setMaxSize (16);
        }
        
        // ================================================================================
        inline void reset()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
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
        
        inline float get (float samplesDelay) const
        {
            assert (clampLength (samplesDelay) == samplesDelay);
            
            int delayInt = (int)samplesDelay;
            float delayFract = samplesDelay - delayInt;
            
            const int lower = (writeIndex_ + delayInt) & mask_;
            const int upper = (lower + 1) & mask_;
            
            return array_[(size_t)lower] + (array_[(size_t)upper] - array_[(size_t)lower]) * delayFract;
        }
        
        inline float getClipped (float samplesDelay) const
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
    };
}
