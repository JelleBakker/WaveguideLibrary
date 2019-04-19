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
 
 SmootherLin
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <algorithm>
#include <cassert>

namespace jbaudio
{
    // based on juce LinearSmoothedValue
    class SmootherLin
    {
    public:
        SmootherLin (float initialValue = 0.0f)
        {
            setSampleRate (44100.0f);
            setTime (0.01f);
            
            setTargetForced (initialValue);
        }
        
        inline void reset()
        {
            setTargetForced (target_);
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            sampleRate_ = sr;
        }
        
        inline void setTime (float seconds)
        {
            setNumSteps (int (seconds * sampleRate_));
        }
        
        inline void setNumSteps (int numSteps)
        {
            assert (numSteps >= 1);
            numSteps_ = numSteps;
            numStepsInv_ = 1.0f / numSteps_;
        }
        
        inline void setTarget (float t)
        {
            if (target_ != t)
            {
                target_ = t;
                incr_ = (target_ - currentValue_) * numStepsInv_;
                counter_ = numSteps_;
            }
        }
        
        inline void setTargetForced (float t)
        {
            currentValue_ = target_ = t;
            counter_ = 0;
        }
        
        inline float getTarget() const
        {
            return target_;
        }
        
        inline float tick()
        {
            if (counter_ > 0)
            {
                currentValue_ += incr_;
                counter_--;
                return currentValue_;
            }
            else return target_;
        }
        
    private:
        float sampleRate_;
        
        float currentValue_;
        float target_;
        
        int counter_;
        int numSteps_;
        float numStepsInv_;
        float incr_;
    };
}
