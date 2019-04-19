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
 
 WaveShaper
 Waveguide Library - JB Audio
 
 */

#pragma once

#include <cmath>
#include <cassert>

namespace jbaudio
{
    class WaveShaper
    {
    public:
        // Laurent de Soras
        // http://www.musicdsp.org/en/latest/Effects/86-waveshaper-gloubi-boulga.html
        static float gloubiBoulga (float input)
        {
            const float x = input * 0.686306f;
            const float a = 1.0f + std::expf (std::sqrtf (std::fabs (x)) * -0.75f);
            return (std::expf (x) - std::expf (-x * a)) / (std::expf (x) + std::expf (-x));
        }
        
        // reaktor
        static float tanh (float input, float level)
        {
            assert (level > 0.0f);
            input /= level;
            input = std::tanhf (input); // todo: approximation
            input *= level;
            return input;
        }
        
    private:
    };
}
