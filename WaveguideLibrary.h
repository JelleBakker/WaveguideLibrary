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

// Some code that makes it possible to include this library as a JUCE module
/*******************************************************************************

 BEGIN_JUCE_MODULE_DECLARATION

  ID:               WaveguideLibrary
  vendor:           jbaudio
  version:          0.0.2
  name:             Waveguide library
  description:      Physical modelling waveguide lubrary
  website:          http://www.jb-audio.com
  license:          None

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once

#include "Source/jbaudio_ADSR.h"
#include "Source/jbaudio_Compressor.h"
#include "Source/jbaudio_LagrangeInterpolation.h"
#include "Source/jbaudio_LookupTable.h"
#include "Source/jbaudio_Maths.h"
#include "Source/jbaudio_MouthPiece.h"
#include "Source/jbaudio_OscSine.h"
#include "Source/jbaudio_WaveShaper.h"
#include "Source/jbaudio_Tube.h"
#include "Source/Delays/jbaudio_DelayAP.h"
#include "Source/Delays/jbaudio_DelayHermite.h"
#include "Source/Delays/jbaudio_DelayLin.h"
#include "Source/Delays/jbaudio_DelayNoInt.h"
#include "Source/Delays/jbaudio_HermiteInterpolation.h"
#include "Source/Filters/jbaudio_DCBlock.h"
#include "Source/Filters/jbaudio_OnePoleZDF.h"
#include "Source/Filters/jbaudio_OneZero.h"
#include "Source/Filters/jbaudio_SVF.h"
#include "Source/Smoothers/jbaudio_EnvFollower.h"
#include "Source/Smoothers/jbaudio_LogSmoother.h"
#include "Source/Smoothers/jbaudio_SmootherLin.h"
