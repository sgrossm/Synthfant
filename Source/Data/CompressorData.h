/*
  ==============================================================================

    CompressorData.h
    Created: 24 Apr 2021 4:02:25pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CompressorData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setCompressorParameters(const float threshold, const float ratio,
        const float attack, const float release);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Compressor<float> comp;
    bool isPrepared{ false };
};