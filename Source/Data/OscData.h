/*
  ==============================================================================

    OscData.h
    Created: 12 Apr 2021 4:03:12pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& proc);
    void setOscillatorWaveform(const int waveformChoice);
    void setOscillatorFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void processFMOsc(juce::dsp::AudioBlock<float>& block);
    void setFMParameters(const float frequency, const float depth);

private:
    juce::dsp::Oscillator<float> fmOscillator{ [](float x) { return std::sin(x); } };
    int lastMidiNotePressed { 0 };
    float fmModulator { 0.0f };
    float fmDepth { 0.0f };
};