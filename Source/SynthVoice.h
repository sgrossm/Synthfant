/*
  ==============================================================================

    SynthVoice.h
    Created: 12 Apr 2021 10:42:08am
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <SynthSound.h>
#include "Data/OscData.h"
#include "Data/ADSRData.h"
#include "Data/FilterData.h"
#include "Data/WaveshaperData.h"
#include "Data/ReverbData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound*) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void updateFilter(const int filterType, const float cutoff, const float resonance);
    void updateDistortion(const int distortionType);

    OscData& getOscillator() { return osc; }
    ADSRData& getADSR() { return adsr; }
    FilterData& getFilter() { return filter; }
    ADSRData& getFilterADSR() { return filterADSR;  }

private:
    juce::AudioBuffer<float> synthBuffer;
    OscData osc;
    ADSRData adsr;
    ADSRData filterADSR;
    FilterData filter;
    WaveshaperData distortion;
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};
