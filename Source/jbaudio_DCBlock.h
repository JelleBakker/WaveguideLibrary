/*
 
 This file is part of the JB Audio Waveguide C++ Library
 
 =============================================
 MIT License
 
 Copyright (c) 2019 JB Audio
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 =============================================
 
 */

/*
 
 DCBlock
 Waveguide Library - JB Audio
 
 */

#pragma once
#include "jbaudio_OnePoleZDF.h"

namespace jbaudio
{
    // Waveguides can create dc offsets so this object can be used to get rid of the dc offset
    // It's basically a highpass filter with a very low freq
    class DCBlock
    {
    public:
        DCBlock()
        {
            setSampleRate (44100.0f);
        }
        
        inline void reset()
        {
            onepole_.reset();
        }
        
        inline void setSampleRate (float sr)
        {
            onepole_.setSampleRate (sr);
            onepole_.setFreq (10.0f);
        }
        
        inline float tick (float input)
        {
            return onepole_.tickHP (input);
        }
        
    private:
        OnePoleZDF onepole_;
    };
}
