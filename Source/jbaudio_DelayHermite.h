/*
 
 DelayHermite
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_HermiteInterpolation.h"
#include <cmath>
#include <cassert>
#include <vector>

namespace jbaudio
{
    class DelayHermite
    {
    public:
        static constexpr float minLength_ = 2.0f;
        
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
            array_.resize ((size_t)size, 0.0f);
            mask_ = size - 1;
            writeIndex_ = 0;
        }
        
        inline void push (float sample)
        {
            array_ [size_t (writeIndex_--)] = sample;
            if (writeIndex_ == -1)
                writeIndex_ = (int)array_.size() - 1;
        }
        
        inline float getClipped (float numSamples) const
        {
            return get (std::max (minLength_, numSamples));
        }
        
        inline float get (float numSamples) const
        {
            assert (numSamples >= minLength_);
            const int asInt = (int) numSamples;
            const float x = numSamples - asInt;
            const float y0 = array_ [size_t ((writeIndex_ + asInt - 1) & mask_)];
            const float y1 = array_ [size_t ((writeIndex_ + asInt) & mask_)];
            const float y2 = array_ [size_t ((writeIndex_ + asInt + 1) & mask_)];
            const float y3 = array_ [size_t ((writeIndex_ + asInt + 2) & mask_)];
            
            return HermiteInterpolation::calculatePointV4 (x, y0, y1, y2, y3);
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_ = 0;
    };
}
