/*
  ==============================================================================

    ADSRData.h
    Created: 12 Apr 2021 2:09:44pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ADSRData : public juce::ADSR 
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
    juce::ADSR::Parameters adsrParams;
};