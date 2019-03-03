/*
 
 OnePoleZDF
 Waveguide Library - JB Audio
 
 */

#include <cmath>

namespace jbaudio
{
    static constexpr float pi = 3.14159265358979f;
    
    class OnePoleZDF
    {
    public:
        
        void reset()
        {
            z1_ = 0.0f;
        }
        
        void setSampleRate (float sr)
        {
            sampleRate_ = sr;
        }
        
        void setFreq (float f)
        {
            f = std::clamp (f, 0.01f, sampleRate_ - 1.0f); // -1.0f needed?
            f *= pi / sampleRate_;
            f = std::min (f, 0.5f * pi);
            f = std::tan (f);
            g_ = f / (1.0f + f);
        }
        
        float tickLP (float input)
        {
            auto a = (input - z1_) * g_;
            auto b = a + z1_;
            z1_ = a + b;
            return b;
        }
        
        float tickHP (float input)
        {
            return input - tickLP (input);
        }
        
    private:
        float g_ = 0.0f;
        float sampleRate_ = 44100.0f;
        
        float z1_ = 0.0f;
    };
}
