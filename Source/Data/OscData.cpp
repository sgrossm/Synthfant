/*
  ==============================================================================

    OscData.cpp
    Created: 12 Apr 2021 4:03:12pm
    Author:  lazlo

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& proc)
{
    prepare(proc);
}

void OscData::setOscillatorWaveform(const int waveformChoice)
{
    // Sin Wave: std::sin(x); 
    // Saw wave: x / juce::MathConstants<float>::pi;
    // Square wave  x < 0.0f ? -1.0f : 1.0f; 

    switch (waveformChoice)
    {
        case 0:
            // Sin wave
            initialise([](float x) { return std::sin(x); });
            break;

        case 1:
            // Saw wave
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;

        case 2:
            // Square wave
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; }); 
            break;

        default:
            jassertfalse;
            break;
    }
}

void OscData::setOscillatorFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
}

void OscData::processNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float>(block));
}
