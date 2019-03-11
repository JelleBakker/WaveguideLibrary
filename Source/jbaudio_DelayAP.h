/*
 
 DelayAP
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"

#include <array>
#include <cassert>

namespace jbaudio
{
    
    
// https://ccrma.stanford.edu/~jos/pasp/First_Order_Allpass_Interpolation.html
//==============================================================================
template <int Pow> // 2^Pow
class DelayAP
{
public:
    DelayAP() {}
    
    inline void clear()
    {
        array_.fill (0.0f);
        apZ1_ = 0.0f;
    }
    
    inline void push (float sample)
    {
        array_[writeIndex_--] = sample;
        if (writeIndex_ == -1)
            writeIndex_ = size_ - 1;
    }
    
    inline void setDelayLenth (float length)
    {
        assert (length >= 1.0f && length <= size_);
        
        apM_ = (int)length;
        float fract = length - apM_;
        if (fract < 0.1f) fract += 1.0f; // delta range of [0.1, 1.1]
        apN_ = (1.0f - fract) / (1.0f + fract);
    }
    
    inline float get()
    {
        const float a = array_[(writeIndex_ + apM_) & mask_];
        
        const float b = apZ1_ * -apN_ + a;
        const float output = b * apN_ + apZ1_;
        apZ1_ = b;
        return output;
    }
    
    static constexpr int size_ = ConstexprPow2f <Pow>::value_;
    
private:
    std::array <float, size_> array_ {};
    static constexpr int mask_ = size_ - 1;
    int writeIndex_ = 0;
    
    int apM_ = 1;
    float apN_ = 0.0f;
    float apZ1_ = 0.0f;
};
    
}
