/*
  ==============================================================================

    PhaserData.h
    Created: 21 Apr 2021 3:17:53pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class PhaserData
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);
    void setPhaserParameters(const float rate, const float depth, const float centerFreq,
        const float fdbk, const float mix);
    void process(juce::AudioBuffer<float>& buffer);
    void reset();

private:
    juce::dsp::Phaser<float> phaser; 
    bool isPrepared { false };
};