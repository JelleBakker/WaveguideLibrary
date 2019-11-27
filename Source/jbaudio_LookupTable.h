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
 
 LookupTable
 Waveguide Library - JB Audio
 
 */

#pragma once

#include <functional>
#include <vector>

namespace jbaudio
{
    class LookupTable
    {
    public:
        LookupTable() = default;
        
        void reset() { data_.clear(); }
        
        inline bool isValid() const { return getTableSize() >= 2; }
        
        // make sure to call this from a non-real time thread cause this will allocate
        void init (std::function <float (size_t index)> func, size_t tableSize)
        {
            if (func != nullptr && tableSize >= 2)
            {
                data_.resize (tableSize);
                for (size_t i = 0; i < tableSize; i++)
                {
                    data_[i] = func (i);
                }
            }
            else assert (false);
        }
        
        inline size_t getTableSize() const { return data_.size(); }
        
        bool isWithinRange (float index) const { return index >= 0.0f && index <= data_.size() - 1; }
        
        inline float mapToTable (float f, float min, float max)
        {
            assert (isValid());
            return (data_.size() - 1) * ((f - min) / (max - min));
        }
        
        inline float mapToTableClipped (float f, float min, float max)
        {
            assert (isValid());
            return clamp (mapToTable (f, min, max), 0.0f, float (data_.size() - 1) - 0.0001f);
        }
        
        inline float get (float index) const
        {
            assert (isValid());
            assert (isWithinRange (index));
            
            const auto underIndex = int (index);
            const auto upperIndex = underIndex + 1;
            assert (isWithinRange (underIndex));
            assert (isWithinRange (upperIndex));
            
            const auto coeff = index - underIndex;
            return (1.0f - coeff) * data_[underIndex] + coeff * data_[upperIndex];
        }
        
        inline float getClipped (float index) const
        {
            assert (isValid());
            
            if (index < 0.0f) return data_[0];
            if (index >= data_.size() - 1) return data_ [data_.size() - 1];
            
            return get (index);
        }
        
    private:
        std::vector <float> data_;
    };
    
    class WaveShaperTable
    {
    public:
        WaveShaperTable()
        {
            init ([&] (float audio) { return tanhf (audio); }, 100);
        }
        
        void reset()
        {
            table_.reset();
        }
        
        void init (std::function <float (float audio)> func,
                   size_t tableSize,
                   float audioMin = -1.0f,
                   float audioMax = 1.0f)
        {
            if (func != nullptr)
            {
                table_.init (
                [func, tableSize, audioMin, audioMax] (size_t index)
                {
                    return func (map <float> (index, 0, tableSize - 1, audioMin, audioMax));
                },
                tableSize);
            }
        }
        
        
        inline float get (float audio)
        {
            assert (table_.isValid());
            return table_.get (table_.mapToTableClipped (audio, -1.0f, 1.0f));
        }
        
        const LookupTable& getLookupTable() const { return table_; }
        
    private:
        LookupTable table_;
        float audioMin_;
        float audioMax_;
    };
    
}
