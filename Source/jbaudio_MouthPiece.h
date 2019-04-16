/*
 
 MouthPiece
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "jbaudio_OnePoleZDF.h"

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
            float p = shapePressure (pressure_.tick());
            float a = tubeFeedback - p;
            return p + a * (0.7f - 0.3f * a);
        }
        
        inline void setPressure (float p)
        {
            pressure_.setTarget (p);
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
