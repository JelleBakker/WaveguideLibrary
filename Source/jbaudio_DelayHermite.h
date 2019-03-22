/*
 
 DelayHermite
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_HermiteInterpolation.h"
#include <cassert>
#include <vector>

namespace jbaudio
{
    class DelayHermite
    {
    public:
        DelayHermite()
        {
            setMaxSize (16);
        }
        
        inline void clear()
        {
            std::fill (array_.begin(), array_.end(), 0.0f);
        }
        
        void setMaxSize (int powerOf2)
        {
            int size = std::max ((int)std::exp2f (powerOf2), 4);
            array_.resize (size, 0.0f);
            mask_ = size - 1;
            writeIndex_ = 0;
        }
        
        inline void push (float sample)
        {
            array_ [writeIndex_--] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float get (float numSamples) const
        {
            assert (numSamples >= 2.0f);
            const int asInt = (int) numSamples;
            const float x = numSamples - asInt;
            const float y0 = array_ [(writeIndex_ + asInt - 1) & mask_];
            const float y1 = array_ [(writeIndex_ + asInt) & mask_];
            const float y2 = array_ [(writeIndex_ + asInt + 1) & mask_];
            const float y3 = array_ [(writeIndex_ + asInt + 2) & mask_];
            
            return HermiteInterpolation::calculatePoint (x, y0, y1, y2, y3);
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_ = 0;
    };
}
