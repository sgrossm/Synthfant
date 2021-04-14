/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuzzleMirrorSynthAudioProcessor::PuzzleMirrorSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif 
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    for (int i = 0; i < 4; ++i)
        synth.addVoice(new SynthVoice());

    synth.addSound(new SynthSound());
}

PuzzleMirrorSynthAudioProcessor::~PuzzleMirrorSynthAudioProcessor()
{

}

//==============================================================================
const juce::String PuzzleMirrorSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PuzzleMirrorSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PuzzleMirrorSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PuzzleMirrorSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PuzzleMirrorSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PuzzleMirrorSynthAudioProcessor::getNumPrograms()
{
    return 1;  
}

int PuzzleMirrorSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PuzzleMirrorSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PuzzleMirrorSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void PuzzleMirrorSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
}

void PuzzleMirrorSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PuzzleMirrorSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void PuzzleMirrorSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); ++i)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {
            // Osc select
            auto& waveformChoice = *apvts.getRawParameterValue("OSC");

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            voice->update(attack.load(), decay.load(), sustain.load(), release.load());
            voice->getOscillator().setOscillatorWaveform(waveformChoice);
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool PuzzleMirrorSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PuzzleMirrorSynthAudioProcessor::createEditor()
{
    return new PuzzleMirrorSynthAudioProcessorEditor (*this);
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PuzzleMirrorSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PuzzleMirrorSynthAudioProcessor();
}


// Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout PuzzleMirrorSynthAudioProcessor::createParams()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Osc waveform selection
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator",
        juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 0.01f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain",
        juce::NormalisableRange<float>{0.00f, 1.0f, 0.01f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release",
        juce::NormalisableRange<float>{0.01f, 5.0f, 0.01f }, 0.25f));



    return { params.begin(), params.end() };
}