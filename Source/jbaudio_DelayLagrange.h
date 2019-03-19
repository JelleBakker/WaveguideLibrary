/*
 
 DelayLagrange
 Waveguide Library - JB Audio
 
 Description: Delay without interpolation
 
 */

#pragma once

//#include "jbaudio_LagrangeInterpolation.h"
//#include <vector>
//#include <cassert>
//
//namespace jbaudio
//{
//    class DelayLagrange
//    {
//    public:
//        DelayLagrange()
//        {
//            setOrder (4);
//            setMaxSize (16); // 65536
//        }
//        
//        // higher order means better interpolation but more cpu cost
//        // the incoming signal cannot be delayed by a number of samples less then the order
//        // 4 is a good default order to use
//        void setOrder (int order)
//        {
//            assert (order > 2);
//            order_ = order;
//        }
//        
//        void allocateSize (int powerOfTwo)
//        {
//            const auto newSize = (int)std::exp2f (powerOfTwo);
//            assert (newSize >= order_);
//            array_.resize (newSize);
//            array_.clear();
//            mask_ = (int)array_.size() - 1;
//        }
//        
//        inline void clear()
//        {
//            array_.clear();
//        }
//        
//        inline void push (float sample)
//        {
//            array_[writeIndex_--] = sample;
//            if (writeIndex_ == -1)
//                writeIndex_ = (int)array_.size() - 1;
//        }
//        
//        inline float get (float samplesDelay) const
//        {
//            assert (samplesDelay >= 1.0f && samplesDelay <= array_.size());
//            
//            
//            
//            return array_ [(writeIndex_ + samplesDelay) & mask_];
//        }
//        
//    private:
//        int order_;
//        std::vector <float> array_;
//        int mask_;
//        int writeIndex_ = 0;
//    };
//}
