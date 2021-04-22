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
    filterADSR.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) 
{
    adsr.noteOff();
    filterADSR.noteOff();
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
    filterADSR.setSampleRate(sampleRate);
    filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
    adsr.setSampleRate(sampleRate);
    
    distortion.prepare(spec);    

    gain.prepare(spec);
    gain.setGainDecibels(-6.0f);
    isPrepared = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) 
{
    jassert(isPrepared);

    if (!isVoiceActive())
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };    // audio block is an alias for outputBuffer
    osc.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    filterADSR.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    distortion.process(synthBuffer);

    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    

    for (int channels = 0; channels < outputBuffer.getNumChannels(); ++channels)
    {
        outputBuffer.addFrom(channels, startSample, synthBuffer, channels, 0, numSamples);

        if (!adsr.isActive())
            clearCurrentNote();
        
    }
}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    auto modulator = filterADSR.getNextSample();
    filter.updateFilterParameters(filterType, cutoff, resonance, modulator);
}

void SynthVoice::updateDistortion(const int distortionType)
{
    distortion.updateDistortion(distortionType);
}