/*
 
 ADSR
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <cassert>

namespace jbaudio
{
    class ADSR
    {
    public:
        ADSR()
        {
            setSampleRate (44100.0f);
            setAttackTime (0.01f);
            setDecayTime (0.05f);
            setSustainLevel (0.7f);
            setReleaseTime (0.1f);
            reset();
        }
        
        inline void reset()
        {
            isAttackStage_ = false;
            value_ = 0.0f;
            add_ = 0.0f;
            mult_ = 1.0f;
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            sampleRate_ = sr;
        }
        
        inline void setAttackTime (float seconds)
        {
            attackNumSamples_ = std::max (1, int (seconds * sampleRate_));
        }
        
        inline void setDecayTime (float seconds)
        {
            decayMult_ = powXGrt0ToY (0.5f, 1.0f / (std::max (1.0f, seconds * sampleRate_)));
        }
        
        inline void setSustainLevel (float level0to1)
        {
            assert (level0to1 >= 0.0f && level0to1 <= 1.0f);
            sustainLevel_ = level0to1;
        }
        
        inline void setReleaseTime (float seconds)
        {
            releaseMult_ = powXGrt0ToY (0.5f, 1.0f / (std::max (1.0f, seconds * sampleRate_)));
        }
        
        inline void triggerStart (float velocity0to1)
        {
            assert (velocity0to1 >= 0.0f && velocity0to1 <= 1.0f);
            
            if (velocity0to1 < value_)
            {
                enterDecayStage();
            }
            else
            {
                isAttackStage_ = true;
                mult_ = 1.0f;
                velocity_ = velocity0to1;
                add_ = (velocity_ - value_) / attackNumSamples_;
            }
        }
        
        inline void triggerStop()
        {
            // enter release stage
            mult_ = releaseMult_;
            add_ = 0.0f;
            isAttackStage_ = false;
        }
        
        inline float tick()
        {
            value_ *= mult_;
            value_ += add_;
            
            if (isAttackStage_ && value_ >= velocity_)
                enterDecayStage();
            
            cancelDenormals (value_);
            return value_;
        }
        
    private:
        float sampleRate_;
        
        // params
        int attackNumSamples_;
        float decayMult_;
        float sustainLevel_;
        float releaseMult_;
        
        // state
        float velocity_;
        float value_;
        float add_;
        float mult_;
        bool isAttackStage_;
        
        inline void enterDecayStage()
        {
            isAttackStage_ = false;
            mult_ = decayMult_;
            const float sustainScaled = sustainLevel_ * velocity_;
            add_ = sustainScaled - (sustainScaled * decayMult_);
        }
    };
}
