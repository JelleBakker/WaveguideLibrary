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
 
 Compressor
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "Smoothers/jbaudio_EnvFollower.h"

namespace jbaudio
{
    // Thanks to the great paper "Digital Dynamic Range Compressor Design— A Tutorial and Analysis"
    class Compressor
    {
    public:
        class Helper
        {
        public:
            static constexpr float calculateOutput (float input, float threshold, float ratio)
            {
                if (input <= threshold)
                    return input;
                return threshold + (input - threshold) / ratio;
            }
            
            static constexpr float calculateOutput (float input, float threshold, float ratio, float knee)
            {
                // no reduction
                if ((input - threshold) <= -0.5f * knee)
                    return input;
                
                // full reduction
                if ((input - threshold) >= 0.5f * knee)
                    return threshold + (input - threshold) / ratio;
                
                // knee range
                // scale input to [0, knee]
                float a = input - threshold + knee * 0.5f;
                // quadratic as [0, knee * knee]
                a *= a;
                // quadratic as [0, knee * 0.5]
                a /= 2.0f * knee;
                
                return input + (1 / ratio - 1.0f) * a;
            }
        };
        
        Compressor()
        {
            setSampleRate (44100.0f);
            setThreshold (-10.0f);
            setRatio (3.0f);
            setKnee (5.0f);
            setAttackTime (0.01f);
            setReleaseTime (0.1f);
            reset();
        }
        
        inline void reset()
        {
            follower_.reset();
            lastReductionDB_ = 0.0f;
            lastReductionAmp_ = 1.0f;
        }
        
        void setSampleRate (float sr)
        {
            assert (sr > 0);
            follower_.setSampleRate (sr);
        }
        
        inline void setThreshold (float thresholdDB)
        {
            threshold_ = thresholdDB;
        }
        
        inline void setRatio (float r)
        {
            ratio_ = r;
        }
        
        inline void setKnee (float kneeDB)
        {
            knee_ = kneeDB;
        }
        
        inline void setAttackTime (float seconds)
        {
            follower_.setAttackTime (seconds);
        }
        
        inline void setReleaseTime (float seconds)
        {
            follower_.setReleaseTime (seconds);
        }
        
        inline float tick (float input)
        {
            const float asDB = ampToDecibel (std::fabsf (input));
            
            const float outDB = Helper::calculateOutput (asDB, threshold_, ratio_, knee_);
            const float reductionDB = asDB - outDB;
            
            lastReductionDB_ = -follower_.tickGrt0 (reductionDB);
            lastReductionAmp_ = decibelToAmp (lastReductionDB_);
            
            return input * lastReductionAmp_;
        }
        
        inline float getLastReductionDB() const
        {
            return lastReductionDB_;
        }
        
        inline float getLastReductionAmp() const
        {
            return lastReductionAmp_;
        }
        
    private:
        EnvFollower follower_;
        float threshold_;
        float ratio_;
        float knee_;
        
        float lastReductionDB_;
        float lastReductionAmp_;
    };
}

