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
    fmOscillator.prepare(proc);
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

        case 3:
            // White noise
            initialise([](float x) { return juce::Random::getSystemRandom().nextFloat() * x - x/2;});
            break;

        default:
            jassertfalse;
            break;
    }
}

void OscData::setOscillatorFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmModulator);
    lastMidiNotePressed = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    processFMOsc(block);
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::processFMOsc(juce::dsp::AudioBlock<float>& block)
{
    for (auto channels = 0; channels < block.getNumChannels(); ++channels)
    {
        for (auto samples = 0; samples < block.getNumSamples(); ++samples)
        {
            fmModulator = fmOscillator.processSample(block.getSample(channels, samples)) * fmDepth;
        }
    }
}

void OscData::setFMParameters(const float frequency, const float depth)
{
    fmOscillator.setFrequency(frequency);
    fmDepth = depth;
    auto currentFrequency = juce::MidiMessage::getMidiNoteInHertz(lastMidiNotePressed) + fmModulator;
    setFrequency(currentFrequency >= 0 ? currentFrequency : currentFrequency * -1.0f);
}
