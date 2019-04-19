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
