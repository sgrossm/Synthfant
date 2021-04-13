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
#include "Data/ADSRData.h"
#include "Data/OscData.h"

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

    void update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator() { return osc; }

private:
    ADSRData adsr;
    juce::AudioBuffer<float> synthBuffer;

    OscData osc;
    //juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Gain<float> gain;
    bool isPrepared{ false };
};
