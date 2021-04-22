/*
  ==============================================================================

    ConvolutionData.h
    Created: 21 Apr 2021 1:34:21pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ReverbData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void updateReverb(const float roomSize, const float damping, const float wetLevel,
        const float dryLevel, const float width, const float freezeMode);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Reverb reverb;
    juce::Reverb::Parameters reverbParameters;
    bool isPrepared{ false };
};