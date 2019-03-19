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
            reset();
            setSampleRate (44100.0f);
            setAttackTime (0.01f);
            setDecayTime (0.05f);
            setSustainLevel (0.7f);
            setReleaseTime (0.1f);
        }
        
        inline void reset()
        {
            stage_ = Stage::Idle;
            value_ = 0.0f;
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            sampleRate_ = sr;
        }
        
        inline void setAttackTime (float seconds)
        {
            attackIncr_ = 1.0f / std::max (1.0f, seconds * sampleRate_);
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
        
        inline void triggerGate (float velocity0to1)
        {
            assert (velocity0to1 >= 0.0f && velocity0to1 <= 1.0f);
            if (velocity0to1 > 0.0f)
            {
                // start
                if (value_ > velocity0to1)
                {
                    stage_ = Stage::Decay;
                }
                else
                {
                    stage_ = Stage::Attack;
                    velocity_ = velocity0to1;
                }
            }
            else
            {
                // stop
                stage_ = Stage::Release;
            }
        }
        
        inline float tick()
        {
            switch (stage_)
            {
                case Stage::Attack:
                    value_ += attackIncr_;
                    if (value_ >= velocity_)
                    {
                        value_ = velocity_;
                        stage_ = Stage::Decay;
                    }
                    break;
                    
                case Stage::Decay:
                    value_ = sustainLevel_ + (value_ - sustainLevel_) * decayMult_;
                    break;
                    
                case Stage::Release:
                    value_ *= releaseMult_;
                    if (value_ < 0.0001f)
                    {
                        value_ = 0.0f;
                        stage_ = Stage::Idle;
                    }
                    break;
                    
                case Stage::Idle:
                    break;
            };
            
            return value_;
        }
        
    private:
        float sampleRate_;
        
        // params
        float attackIncr_;
        float decayMult_;
        float sustainLevel_;
        float releaseMult_;
        
        // state
        float velocity_;
        float value_;
        enum class Stage
        {
            Idle,
            Attack,
            Decay,
            Release
        };
        Stage stage_;
    };
}
