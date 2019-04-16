/*
 
 DCBlock
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "jbaudio_OnePoleZDF.h"

namespace jbaudio
{
    class DCBlock
    {
    public:
        DCBlock()
        {
            setSampleRate (44100.0f);
        }
        
        inline void reset()
        {
            onepole_.reset();
        }
        
        inline void setSampleRate (float sr)
        {
            onepole_.setSampleRate (sr);
            onepole_.setFreq (5.0f);
        }
        
        inline float tick (float input)
        {
            return onepole_.tickHP (input);
        }
        
    private:
        OnePoleZDF onepole_;
    };
}
