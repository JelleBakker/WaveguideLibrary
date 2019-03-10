/*
 
 DelayLin
 Waveguide Library - JB Audio
 
 */

#include <array>
#include <cassert>

namespace jbaudio
{
    
//==============================================================================
template <int N>
struct ConstexprPow2f
{
    static constexpr int value_ = 2.0f * ConstexprPow2f <N-1>::value_;
};
    
template<>
struct ConstexprPow2f <0>
{
    static constexpr int value_ = 1;
};

//==============================================================================
template <int Pow> // 2^Pow
class DelayLin
{
public:
    DelayLin() {}
    
    inline void clear()
    {
        array_.fill (0.0f);
    }
    
    inline void push (float sample)
    {
        array_[writeIndex_++] = sample;
        writeIndex_ &= mask_;
    }
    
    inline float get (float samplesDelay) const
    {
        assert (samplesDelay >= 1.0f && samplesDelay <= size_);
        
        float l;
        const float fract = std::modf (samplesDelay, &l);
        
        int upper = writeIndex_ - static_cast <int> (l);
        if (upper < 0) upper += size_;
        int lower = upper - 1;
        if (lower < 0) lower += size_;
        
        std::cout << "writeindex: " << writeIndex_ << "\n";
        std::cout << "lower: " << lower << " upper: " << upper << " fract: " << fract << "\n";
        
        return (1.0f - fract) * array_ [upper] + fract * array_ [lower];
    }
    
    static constexpr int size_ = ConstexprPow2f <Pow>::value_;
    
private:
    std::array <float, size_> array_ {};
    static constexpr int mask_ = size_ - 1;
    int writeIndex_ = 0;
};
    
}
