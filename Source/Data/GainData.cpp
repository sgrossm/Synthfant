/*
  ==============================================================================

    GainData.cpp
    Created: 24 Apr 2021 4:47:13pm
    Author:  lazlo

  ==============================================================================
*/

#include "GainData.h"
void GainData::prepare(const juce::dsp::ProcessSpec& spec)
{
    gain.prepare(spec);
    isPrepared = true;
}

void GainData::setGainLevel(const float newGain)
{
    gain.setGainDecibels(newGain);
}

void GainData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void GainData::reset()
{
    gain.reset();
}