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
 
 LogSmoother
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "../jbaudio_Maths.h"
#include <algorithm>
#include <cassert>

namespace jbaudio
{
    // Based on Reaktor Env Follower
    class LogSmoother
    {
    public:
        LogSmoother (float initialValue = 0.0f)
        {
            setSampleRate (44100.0f);
            setAttackTime (0.01f);
            setReleaseTime (0.05f);
            setTarget (initialValue, true);
        }
        
        inline void reset()
        {
            z1_ = target_;
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            sampleRate_ = sr;
        }
        
        inline void setAttackAndReleaseTime (float seconds)
        {
            setAttackTime (seconds);
            setReleaseTime (seconds);
        }
        
        inline void setAttackAndReleaseTime (float attackS, float releaseS)
        {
            setAttackTime (attackS);
            setReleaseTime (releaseS);
        }
        
        inline void setAttackTime (float attackS)
        {
            attCoeff_ = time2Cutoff (attackS);
        }
        
        inline void setReleaseTime (float releaseS)
        {
            relCoeff_ = time2Cutoff (releaseS);
        }
        
        inline void setTarget (float t, bool force = false)
        {
            target_ = t;
            if (force)
                z1_ = t;
            coeff_ = target_ > z1_ ? &attCoeff_ : &relCoeff_;
        }
        
        inline float getTarget() const
        {
            return target_;
        }
        
        inline float tick()
        {
            float diff = target_ - z1_;
            cancelDenormals (diff);
            return z1_ = z1_ + diff * (*coeff_);
        }
        
    private:
        float sampleRate_;
        
        float target_ = 0.0f;
        float z1_;
        
        float attCoeff_;
        float relCoeff_;
        float* coeff_ { &attCoeff_ };
        
        inline float time2Cutoff (float seconds)
        {
            return 1.0f - std::exp2f (-1.0f / std::max (0.02f, sampleRate_ * seconds));
        }
    };
}
