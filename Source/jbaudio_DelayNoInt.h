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
        DelayNoInt()
        {
            setMaxSize (16);
        }
        
        // allocate size, call this before using this delay!
        void setMaxSize (int powerOfTwo)
        {
            assert (powerOfTwo >= 0);
            array_.resize ((int)std::exp2f (powerOfTwo));
            clear();
            mask_ = (int)array_.size() - 1;
        }
        
        inline void clear()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
        }
        
        inline void push (float sample)
        {
            array_[writeIndex_--] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float get (int samplesDelay) const
        {
            assert (samplesDelay >= 1.0f && samplesDelay <= array_.size());
            return array_ [(writeIndex_ + samplesDelay) & mask_];
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_ = 0;
    };
}
