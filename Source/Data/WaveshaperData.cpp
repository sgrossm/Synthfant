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
        // Type 1
        preGain.setGainDecibels(50.0f);
        distortion.functionToUse = [](float x) { return juce::jlimit<float>(-0.1f, 0.1f, x);};
        postGain.setGainDecibels(-10.0f);
        break;

    case 2:
        // Type 2
        distortion.functionToUse = [](float x) {return tanh(x);};
        break;

    case 3:
        // Type 3
        distortion.functionToUse = [](float x) {return juce::jlimit<float>(-0.8f, 0.8f, x);};
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