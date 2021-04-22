/*
  ==============================================================================

    ConvolutionData.cpp
    Created: 21 Apr 2021 1:34:21pm
    Author:  lazlo

  ==============================================================================
*/

#include "ReverbData.h"

void ReverbData::prepare(const juce::dsp::ProcessSpec& spec)
{
    reverb.prepare(spec);
    isPrepared = true;
}

void ReverbData::updateReverb(const float roomSize, const float damping, const float wetLevel,
    const float dryLevel, const float width, const float freezeMode)
{
    reverbParameters.roomSize = roomSize;
    reverbParameters.damping = damping;
    reverbParameters.wetLevel = wetLevel;
    reverbParameters.dryLevel = dryLevel;
    reverbParameters.width = width;
    reverbParameters.freezeMode = freezeMode;

    reverb.setParameters(reverbParameters);
}

void ReverbData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    reverb.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void ReverbData::reset()
{
    reverb.reset();
}