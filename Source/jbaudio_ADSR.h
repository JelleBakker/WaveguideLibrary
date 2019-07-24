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
 
 ADSR
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <algorithm>
#include <cassert>

namespace jbaudio
{
    class ADSR
    {
    public:
        enum class Stage
        {
            Idle,
            Attack,
            Decay,
            Release
        };
        
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
            sustainLevelScaled_ = sustainLevel_ * velocity_;
        }
        
        inline void setReleaseTime (float seconds)
        {
            releaseMult_ = powXGrt0ToY (0.5f, 1.0f / (std::max (1.0f, seconds * sampleRate_)));
        }
        
        inline void triggerGate (float velocity)
        {
            if (velocity > 0.0f)
            {
                velocity_ = velocity;
                sustainLevelScaled_ = sustainLevel_ * velocity_;
                // start
                if (value_ > velocity)
                    stage_ = Stage::Decay;
                else
                    stage_ = Stage::Attack;
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
                {
                    float diff = (value_ - sustainLevelScaled_);
                    cancelDenormals (diff);
                    value_ = sustainLevelScaled_ + diff * decayMult_;
                    break;
                }
                    
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
        
        inline Stage getStage() const
        {
            return stage_;
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
        float sustainLevelScaled_;
        float value_;
        Stage stage_;
    };
}
