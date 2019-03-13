/*
 
 DelayNoInt
 Waveguide Library - JB Audio
 
 Description: Delay without interpolation
 
 */

#pragma once

#include <vector>
#include <cassert>

namespace jbaudio
{
    class DelayNoInt
    {
    public:
        DelayNoInt() {}
        
        // allocate size, call this before using this delay!
        void setMaxSize (int powerOfTwo)
        {
            assert (powerOfTwo >= 0);
            array_.resize ((int)std::exp2f (powerOfTwo));
            array_.clear();
            mask_ = array_.size() - 1;
        }
        
        inline void clear()
        {
            array_.clear();
        }
        
        inline void push (float sample)
        {
            array_[writeIndex_--] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = size_ - 1;
        }
        
        inline float get (int samplesDelay) const
        {
            assert (samplesDelay >= 1.0f && samplesDelay <= array_.size());
            return array_ [(writeIndex_ + samplesDelay) & mask_];
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        static constexpr int mask_ = size_ - 1;
        int writeIndex_ = 0;
    };
}
