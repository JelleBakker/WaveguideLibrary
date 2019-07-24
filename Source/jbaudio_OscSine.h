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
 
 OscSine
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"

namespace jbaudio
{
    class OscSine
    {
    public:
        OscSine()
        {
            setSampleRate (44100.0f);
            setFreq (440.0f);
            setVolume (1.0f);
            reset();
        }
        
        void reset()
        {
            phase_ = 0.0f;
        }
        
        void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        inline void setFreq (float f)
        {
            incr_ = (f / sampleRate_) * twoPi;
        }
        
        inline void setVolume (float v)
        {
            volume_ = v;
        }
        
        inline float tick()
        {
            phase_ += incr_;
            if (phase_ > twoPi)
                phase_ -= twoPi;
            return std::sinf (phase_) * volume_;
        }
        
        inline float getWithoutTicking()
        {
            return std::sinf (phase_) * volume_;
        }
        
    private:
        float sampleRate_;
        float incr_;
        float phase_;
        float volume_;
    };
}
