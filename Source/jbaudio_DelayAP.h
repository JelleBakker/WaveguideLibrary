/*
 
 DelayAP
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <vector>
#include <cassert>

namespace jbaudio
{
    // https://ccrma.stanford.edu/~jos/pasp/First_Order_Allpass_Interpolation.html
    class DelayAP
    {
    public:
        DelayAP()
        {
            setMaxSize (16);
        }
        
        void setMaxSize (int powerOfTwo)
        {
            assert (powerOfTwo >= 0);
            array_.resize ((int)std::exp2f (powerOfTwo));
            clear();
            mask_ = (int)array_.size() - 1;
            writeIndex_ = 0;
        }
        
        inline void clear()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
            apZ1_ = 0.0f;
        }
        
        inline void push (float sample)
        {
            array_[writeIndex_--] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = array_.size() - 1;
        }
        
        inline float get (float samplesDelay)
        {
            int apM = (int)samplesDelay;
            float fract = samplesDelay - apM;
            if (fract < 0.1f)
            {
                fract += 1.0f; // delta range of [0.1, 1.1]
                apM -= 1;
            }
            const float apN = (1.0f - fract) / (1.0f + fract);
            
            const float a = array_[(writeIndex_ + apM) & mask_];
            
            const float b = apZ1_ * -apN + a;
            const float output = b * apN + apZ1_;
            apZ1_ = b;
            return output;
        }
        
    private:
        std::vector <float> array_;
        
        int mask_;
        int writeIndex_;
        
        float apZ1_ = 0.0f;
    };
}
