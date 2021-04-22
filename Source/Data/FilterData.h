/*
  ==============================================================================

    FilterData.h
    Created: 18 Apr 2021 11:19:25pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateFilterParameters(const int filterType, const float frequency, const float resonance,
        const float modulator);
    void resetFilter();
private:
    juce::dsp::StateVariableTPTFilter <float> filter;
    bool isPrepared{ false };
};