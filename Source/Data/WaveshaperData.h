/*
  ==============================================================================

    WaveshaperData.h
    Created: 20 Apr 2021 10:38:59am
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class WaveshaperData 
{
public:
    void prepare(juce::dsp::ProcessSpec& proc);
    void process(juce::AudioBuffer<float>& buffer);
    void updateDistortion(const int distortionType);
    void reset();

private:
    juce::dsp::WaveShaper<float> distortion;
    juce::dsp::Gain<float> preGain;
    juce::dsp::Gain<float> postGain;
};