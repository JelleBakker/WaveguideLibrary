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
 
 HermiteInterpolation
 Waveguide Library - JB Audio
 
 Description: Hermite interpolation
 https://www.musicdsp.org/en/latest/Other/93-hermite-interpollation.html?highlight=hermite
 
 */

#pragma once

#include <array>

namespace jbaudio
{
    class HermiteInterpolation
    {
    public:
        static constexpr float calculatePointV1 (float x, float y0, float y1, float y2, float y3)
        {
            float c0 = y1;
            float c1 = 0.5f * (y2 - y0);
            float c2 = y0 - 2.5f * y1 + 2.f * y2 - 0.5f * y3;
            float c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);
            
            return ((c3 * x + c2) * x + c1) * x + c0;
        }
        
        static constexpr float calculatePointV2 (float x, float y0, float y1, float y2, float y3)
        {
            float c0 = y1;
            float c1 = 0.5f * (y2 - y0);
            float c3 = 1.5f * (y1 - y2) + 0.5f * (y3 - y0);
            float c2 = y0 - y1 + c1 - c3;
            
            return ((c3 * x + c2) * x + c1) * x + c0;
        }
        
        static constexpr float calculatePointV3 (float x, float y0, float y1, float y2, float y3)
        {
            float c0 = y1;
            float c1 = 0.5f * (y2 - y0);
            float y0my1 = y0 - y1;
            float c3 = (y1 - y2) + 0.5f * (y3 - y0my1 - y2);
            float c2 = y0my1 + c1 - c3;
            
            return ((c3 * x + c2) * x + c1) * x + c0;
        }
        
        static constexpr float calculatePointV4 (float frac_pos, float xm1, float x0, float x1, float x2)
        {
            const float    c     = (x1 - xm1) * 0.5f;
            const float    v     = x0 - x1;
            const float    w     = c + v;
            const float    a     = w + v + (x2 - x0) * 0.5f;
            const float    b_neg = w + a;
            
            return ((((a * frac_pos) - b_neg) * frac_pos + c) * frac_pos + x0);
        }
        
    private:
    };
}
