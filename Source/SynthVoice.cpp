/*
  ==============================================================================

    SynthVoice.cpp
    Created: 12 Apr 2021 10:42:08am
    Author:  lazlo

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
    osc.setOscillatorFrequency(midiNoteNumber);
    adsr.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    adsr.noteOff();

    if (!allowTailOff || !adsr.isActive())
        clearCurrentNote();
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) 
{

}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    osc.prepareToPlay(spec);
    gain.prepare(spec);

    gain.setGainLinear(0.15f);

    isPrepared = true;
}

void SynthVoice::update(const float attack, const float decay, const float sustain, const float release)
{
    adsr.updateADSR(attack, decay, sustain, release);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };    // audio block is an alias for outputBuffer
    osc.processNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    for (int channels = 0; channels < outputBuffer.getNumChannels(); ++channels)
    {
        outputBuffer.addFrom(channels, startSample, synthBuffer, channels, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
        
    }
}