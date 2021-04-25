/*
  ==============================================================================

    ChorusData.cpp
    Created: 24 Apr 2021 3:24:39pm
    Author:  lazlo

  ==============================================================================
*/

#include "ChorusData.h"

void ChorusData::prepare(const juce::dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
    isPrepared = true;
}

void ChorusData::setChorusParameters(const float rate, const float depth, const float centerDelay,
    const float fdbk, const float mix)
{
    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(centerDelay);
    chorus.setFeedback(fdbk);
    chorus.setMix(mix);
}

void ChorusData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    chorus.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void ChorusData::reset()
{
    chorus.reset();
}