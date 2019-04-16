/*
 
 Tube
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "jbaudio_OnePoleZDF.h"

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
            delay_.clear();
            lowpass_.reset();
            length_.reset();
            cutoff_.reset();
            lastOut_ = 0.0f;
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
        
        inline float push (float input)
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
            
            delay_.push (input);
            
            return lastOut_ = pipeOut;
        }
        
        inline float getLastOut() const
        {
            return lastOut_;
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
        
        float lastOut_;
        
        jbaudio::DelayHermite delay_;
        
        jbaudio::LogSmoother cutoff_ {5000.0f};
        jbaudio::OnePoleZDF lowpass_;
        
        jbaudio::LogSmoother length_ {60.0f};
        
    };
}
