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
    void processNextAudioBlock(juce::dsp::AudioBlock<float>& block);

private:

};