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
 
 MouthPiece
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "Filters/jbaudio_OnePoleZDF.h"
#include "Smoothers/jbaudio_LogSmoother.h"

namespace jbaudio
{
    // Simple single reed mouth piece
    class MouthPiece
    {
    public:
        MouthPiece()
        {
            setSampleRate (44100.0f);
            reset();
        }
        
        inline void reset()
        {
            pressure_.reset();
        }
        
        void setSampleRate (float sr)
        {
            if (sr > 0)
            {
                sampleRate_ = sr;
                pressure_.setSampleRate (sr);
                pressure_.setAttackAndReleaseTime (0.01f);
            }
        }
        
        inline float tick (float tubeFeedback)
        {
            // exciter
            float p = pressure_.tick();
            float a = tubeFeedback - p;
            const float output = p + a * (clamp (0.7f - 0.3f * a, -1.0f, 1.0f));
            return output;
        }
        
        inline void setPressure (float p)
        {
            pressure_.setTarget (shapePressure (clamp (p, 0.0f, 1.0f)));
        }
        
    private:
        float sampleRate_;
        
        jbaudio::LogSmoother pressure_;
        
        static inline float shapePressure (float p)
        {
            return std::powf (p, 0.2f);
            return p;
        }
    };
}
