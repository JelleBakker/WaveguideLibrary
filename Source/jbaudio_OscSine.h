/*
 
 OscSine
 Waveguide Library - JB Audio
 
 */

#pragma once


namespace jbaudio
{
    class OscSine
    {
    public:
        OscSine()
        {
            setSampleRate (44100.0f);
            setFreq (440.0f);
            setVolume (1.0f);
            reset();
        }
        
        void reset()
        {
            phase_ = 0.0f;
        }
        
        void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        inline void setFreq (float f)
        {
            incr_ = (f / sampleRate_) * twoPi;
        }
        
        inline void setVolume (float v)
        {
            volume_ = v;
        }
        
        inline float tick()
        {
            phase_ += incr_;
            if (phase_ > twoPi)
                phase_ -= twoPi;
            return std::sinf (phase_) * volume_;
        }
        
    private:
        float sampleRate_;
        float incr_;
        float phase_;
        float volume_;
    };
}
