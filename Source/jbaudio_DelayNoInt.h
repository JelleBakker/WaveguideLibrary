/*
 
 DelayNoInt
 Waveguide Library - JB Audio
 
 Description: Delay without interpolation
 
 */

#pragma once

#include <cmath>
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
        
        void setMaxSize (int powerOfTwo)
        {
            assert (powerOfTwo >= 0);
            array_.resize ((size_t)std::exp2f (powerOfTwo));
            clear();
            mask_ = (int)array_.size() - 1;
            writeIndex_ = 0;
        }
        
        inline void clear()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
        }
        
        inline void push (float sample)
        {
            array_[size_t (writeIndex_--)] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float get (int samplesDelay) const
        {
            assert (samplesDelay >= 1.0f && samplesDelay <= (int)array_.size());
            return array_ [size_t ((writeIndex_ + samplesDelay) & mask_)];
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_;
    };
}
