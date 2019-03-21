/*
 
 DelayLin
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"

#include <array>
#include <cassert>

namespace jbaudio
{
    //==============================================================================
    template <int Pow> // 2^Pow
    class DelayLin
    {
    public:
        DelayLin() {}
        
        inline void clear()
        {
            array_.fill (0.0f);
        }
        
        inline void push (float sample)
        {
            array_[writeIndex_--] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = size_ - 1;
        }
        
        inline void setDelayLength (float samples)
        {
            assert (samples >= 1.0f && samples <= size_);
            
            delayInt_ = (int)samples;
            delayFract_ = samples - delayInt_;
        }
        
        inline float get() const
        {
            const int lower = (writeIndex_ + delayInt_) & mask_;
            const int upper = (lower + 1) & mask_;
            
            return (1.0f - delayFract_) * array_ [lower] + delayFract_ * array_ [upper];
        }
        
        static constexpr int size_ = ConstexprPow2f <Pow>::value_;
        
    private:
        std::array <float, size_> array_ {};
        static constexpr int mask_ = size_ - 1;
        int writeIndex_ = 0;
        
        int delayInt_ = 1;
        float delayFract_ = 0.0f;
    };
}
