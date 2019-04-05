/*
 
 SVF
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <algorithm>

namespace jbaudio
{
    class SVF
    {
    public:
        SVF()
        {
            setSampleRate (44100.0f);
            setFreqAndRes (1000.0f, 0.5f);
            reset();
        }
        
        inline void reset()
        {
            buf1_ = 0.0f;
            buf2_ = 0.0f;
            lastLP_ = 0.0f;
            lastBP_ = 0.0f;
            lastHP_ = 0.0f;
        }
        
        inline void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        // it's more efficient to combine the two than calling them seperately
        inline void setFreqAndRes (float f, float r)
        {
            wDiv2_ = bilinearTransform (f, sampleRate_);
            r = std::min (r, 0.96875f);
            r = 1.0f - r;
            twoR_ = r + r;
            resOrFreqChanged();
        }
        
        inline void setFreq (float f)
        {
            wDiv2_ = bilinearTransform (f, sampleRate_);
            resOrFreqChanged();
        }
        
        inline void setRes (float r)
        {
            assert (r <= 0.96875f);
            r = 1.0f - r;
            twoR_ = r + r;
            resOrFreqChanged();
        }
        
        inline void tick (float input)
        {
            float a = buf1_ * d_ + buf2_;
            lastHP_ = (input - a) / a_;
            
            float b = lastHP_ * wDiv2_;
            lastBP_ = b + buf1_;
            buf1_ = lastBP_ + b;
            
            float c = lastBP_ * wDiv2_;
            lastLP_ = c + buf2_;
            buf2_ = lastLP_ + c;
        }
        
        inline float tickLP (float input)
        {
            tick (input);
            return lastLP_;
        }
        
        inline float tickBP (float input)
        {
            tick (input);
            return lastBP_;
        }
        
        inline float tickHP (float input)
        {
            tick (input);
            return lastHP_;
        }
        
        inline float getLastLP() const { return lastLP_; }
        inline float getLastBP() const { return lastBP_; }
        inline float getLastHP() const { return lastHP_; }
        
        inline float getPhaseDelayLP (float freq)
        {
            assert (false); // todo
            return 0.0f;
        }
        
    private:
        float sampleRate_;
        
        float wDiv2_;
        float twoR_;
        float d_;
        float a_;
        
        float buf1_;
        float buf2_;
        
        float lastLP_;
        float lastBP_;
        float lastHP_;
        
        inline void resOrFreqChanged()
        {
            d_ = twoR_ + wDiv2_;
            a_ = d_ * wDiv2_ + 1.0f;
        }
    };
}

