/*
 
 Maths
 Waveguide Library - JB Audio
 
 */

#pragma once

namespace jbaudio
{
    
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
    
// Credits to Martijn Zwartjes
constexpr void cancelDenormals (float& f)
{
    f += 1E-18;
}
    
};
