/*
 
 LogSmoother
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <algorithm>
#include <cassert>

namespace jbaudio
{
    // Based on Reaktor Env Follower
    class EnvFollower
    {
    public:
        EnvFollower()
        {
            setSampleRate (44100.0f);
            setAttackTime (0.01f);
            setReleaseTime (0.05f);
            reset();
        }
        
        inline void reset()
        {
            z1_ = 0.0f;
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            sampleRate_ = sr;
        }
        
        inline void setAttackTime (float attackS)
        {
            attCoeff_ = time2Cutoff (attackS);
        }
        
        inline void setReleaseTime (float releaseS)
        {
            relCoeff_ = time2Cutoff (releaseS);
        }
        
        inline float tick (float input)
        {
            return tickGrt0 (std::fabsf (input));
        }
        
        inline float tickGrt0 (float input)
        {
            assert (input >= 0.0f);
            float diff = input - z1_;
            cancelDenormals (diff);
            return z1_ = z1_ + diff * (input > z1_ ? attCoeff_ : relCoeff_);
        }
        
    private:
        float sampleRate_;
        
        float z1_;
        
        float attCoeff_;
        float relCoeff_;
        
        inline float time2Cutoff (float seconds)
        {
            return 1.0f - std::exp2f (-1.0f / std::max (0.02f, sampleRate_ * seconds));
        }
    };
}
