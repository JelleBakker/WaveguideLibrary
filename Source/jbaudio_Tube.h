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
 
 Tube
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "Filters/jbaudio_OnePoleZDF.h"
#include "Smoothers/jbaudio_LogSmoother.h"
#include "Delays/jbaudio_DelayHermite.h"

namespace jbaudio
{
    // Simple tube
    class Tube
    {
    public:
        Tube()
        {
            setSampleRate (44100.0f);
            reset();
        }
        
        inline void reset()
        {
            delay_.reset();
            lowpass_.reset();
            length_.reset();
            cutoff_.reset();
        }
        
        void setSampleRate (float sr)
        {
            if (sr > 0)
            {
                sampleRate_ = sr;
                lowpass_.setSampleRate (sr);
                length_.setSampleRate (sr);
                length_.setAttackAndReleaseTime (0.003f);
                cutoff_.setSampleRate (sr);
                cutoff_.setAttackAndReleaseTime (0.003f);
            }
        }
        
        inline void push (float input)
        {
            delay_.push (input);
        }
        
        inline float get()
        {
            float freq = jbaudio::pitchToFreq (length_.tick()); // de freq die je wilt horen
            float delayLen = sampleRate_ / freq; // de delay lengte voor die freq
            lowpass_.setFreq (cutoff_.tick());
            float phaseDel = lowpass_.getPhaseDelayLP (freq); // de phase delay voor die freq
            float samplesDel = delayLen * (-phaseDel / jbaudio::twoPi); // aantal samples delay voor die freq
            delayLen *= 0.5f; // omdat na 1 keer de delay de golf geinverteerd plaats vindt
            delayLen -= samplesDel; // compenseer voor phase delay lengte
            float pipeOut = delay_.getClipped (delayLen);
            pipeOut = lowpass_.tickLP (pipeOut);
            pipeOut *= -0.95f;
            return pipeOut;
        }
        
        inline void setLength (float pitch)
        {
            length_.setTarget (pitch);
        }
        
        inline void setCutoff (float freq)
        {
            cutoff_.setTarget (freq);
        }
        
    private:
        float sampleRate_;
        
        jbaudio::DelayHermite delay_;
        
        jbaudio::LogSmoother cutoff_ {5000.0f};
        jbaudio::OnePoleZDF lowpass_;
        
        jbaudio::LogSmoother length_ {60.0f};
        
    };
}
