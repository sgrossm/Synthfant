/*
  ==============================================================================

    GainData.h
    Created: 24 Apr 2021 4:47:13pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class GainData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setGainLevel(const float newGain);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();
private:
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};