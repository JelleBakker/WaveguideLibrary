/*
 
 DelayLin
 Waveguide Library - JB Audio
 
 */

#pragma once

#include "jbaudio_Maths.h"
#include <vector>
#include <cassert>

namespace jbaudio
{
    class DelayLin
    {
    public:
        DelayLin()
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
        
        inline float get (float samplesDelay) const
        {
            assert (samplesDelay >= 1.0f && samplesDelay <= array_.size());
            
            int delayInt = (int)samplesDelay;
            float delayFract = samplesDelay - delayInt;
            
            const int lower = (writeIndex_ + delayInt) & mask_;
            const int upper = (lower + 1) & mask_;
            
            return array_[(size_t)lower] + (array_[(size_t)upper] - array_[(size_t)lower]) * delayFract;
        }
        
    private:
        std::vector <float> array_;
        int mask_;
        int writeIndex_;
    };
}
