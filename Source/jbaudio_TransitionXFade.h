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
 
 TransitionXFade
 Waveguide Library - JB Audio
 
 */

#pragma once

// Based on the method described in patent:
// https://patentimages.storage.googleapis.com/49/7f/81/c134de24dd69b8/WO1998010355A1.pdf
namespace jbaudio
{
    class TransitionXFade
    {
    public:
        enum class State { Idle, FadingToB, FadingToA };
        
        TransitionXFade()
        {
            setSampleRate (44100.0f);
            setTime (0.02f);
            reset();
        }
        
        inline void reset()
        {
            nextTapNeedsFade_ = false;
            if (state_ == State::FadingToB)
                xfadeValue_ = 1.0f;
            else if (state_ == State::FadingToA)
                xfadeValue_ = 0.0f;
            state_ = State::Idle;
            assert (tapValue_ == 0.0f || tapValue_ == 1.0f);
        }
        
        void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        inline void setTime (float seconds)
        {
            assert (seconds > 0.0f;)
            incr_ = 1.0f / (seconds * sampleRate_);
        }
        
        // this class doesn't care what unit this is, it can be samples, pitch whatever it needs to x-fade between
        inline void gotoNextTapForced()
        {
            nextTapNeedsFade_ = false;
            setNextTap (target);
        }
        
        inline void gotoNextTap()
        {
            if (nextTapNeedsFade_)
            {
                if (xfadeValue_ == 0.0f)
                {
                    assert (state_ == State::Idle);
                    state_ == State::FadingToB;
                }
                else if (xfadeValue_ == 1.0f)
                {
                    assert (state_ == State::Idle);
                    state_ == State::FadingToA;
                }
                else
                {
                    // not finished yet.. try again later :)
                }
            }
            else
            {
                if (state_ != State::Idle)
                {
                    
                }
            }
        }
        
        inline void tick (float& tapAMultiplier, float& tapBMultiplier)
        {
            
        }
        
    private:
        float sampleRate_;
        
        State state_;
        
        bool nextTapNeedsFade_;
        
        float incr_;
        float xfadeValue_;
    };
}
