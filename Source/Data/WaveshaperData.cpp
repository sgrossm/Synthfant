/*
  ==============================================================================

    WaveshaperData.cpp
    Created: 20 Apr 2021 10:38:59am
    Author:  lazlo

  ==============================================================================
*/

#include "WaveshaperData.h"

void WaveshaperData::prepare(juce::dsp::ProcessSpec& proc)
{
    distortion.prepare(proc);
}

void WaveshaperData::process(juce::AudioBuffer<float>& buffer)
{
    juce::dsp::AudioBlock<float> block(buffer);
    distortion.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void WaveshaperData::updateDistortion(const int distortionType)
{
    switch (distortionType)
    {
    case 0:
        // None
        distortion.functionToUse = [](float x) { return x; };
        break;

    case 1: 
        // Soft Clipping
        distortion.functionToUse = [](float x) { return juce::jlimit<float>(-0.8f, 0.8f, x);};
        break;

    case 2:
        // Hard-Clipping
        distortion.functionToUse = [](float x) {return juce::jlimit<float>(-0.3f, 0.3f, x);};
        break;

    case 3:
        // Arctangent nonlinearity
        distortion.functionToUse = [](float x) {return (2.0f / juce::MathConstants<float>::pi) * atan(x* 10);};
        break;

    default:
        jassertfalse;
        break;
    }
}

void WaveshaperData::reset()
{
    distortion.reset();
}