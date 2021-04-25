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
    for (int i = 0; i < 5; ++i)
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
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();
    reverb.prepare(spec);
    phaser.prepare(spec);
    chorus.prepare(spec);
    comp.prepare(spec);

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
            auto& waveformChoice = *apvts.getRawParameterValue("OSC1");

            // FM processing
            auto& fmFrequency = *apvts.getRawParameterValue("OSC1FMFREQUENCY");
            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");

            // ADSR
            auto& attack = *apvts.getRawParameterValue("ATTACK");
            auto& decay = *apvts.getRawParameterValue("DECAY");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
            auto& release = *apvts.getRawParameterValue("RELEASE");

            // Filter 
            auto& filterType = *apvts.getRawParameterValue("FILTERTYPE");
            auto& filterCutoff = *apvts.getRawParameterValue("FILTERCUTOFF");
            auto& filterResonance = *apvts.getRawParameterValue("FILTERRESONANCE");

            // Filter ADSR
            auto& filterAttack = *apvts.getRawParameterValue("FILTERATTACK");
            auto& filterDecay = *apvts.getRawParameterValue("FILTERDECAY");
            auto& filterSustain = *apvts.getRawParameterValue("FILTERSUSTAIN");
            auto& filterRelease = *apvts.getRawParameterValue("FILTERRELEASE");

            // Distortion
            auto& distortionType = *apvts.getRawParameterValue("DISTORTIONTYPE");
            
            // Gain
            auto& gainVal = *apvts.getRawParameterValue("GAIN");

            voice->getOscillator().setOscillatorWaveform(waveformChoice);            
            voice->getOscillator().setFMParameters(fmFrequency, fmDepth);
            voice->getADSR().updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
            voice->updateFilter(filterType, filterCutoff, filterResonance);
            voice->getFilterADSR().updateADSR(filterAttack.load(), filterDecay.load(), filterSustain.load(), filterRelease.load());
            voice->updateDistortion(distortionType);
            voice->getGain().setGainLevel(gainVal);
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    
    // Reverb
    reverb.process(buffer);
    auto& reverbSize = *apvts.getRawParameterValue("REVERBROOM");
    auto& reverbDamp = *apvts.getRawParameterValue("REVERBDAMP");
    auto& reverbWet = *apvts.getRawParameterValue("REVERBWET");
    auto& reverbDry = *apvts.getRawParameterValue("REVERBDRY");
    auto& reverbWidth = *apvts.getRawParameterValue("REVERBWIDTH");
    auto& reverbFreeze = *apvts.getRawParameterValue("REVERBFREEZE");
    reverb.updateReverb(reverbSize, reverbDamp, reverbWet, reverbDry, reverbWidth, reverbFreeze);
    
    // Phaser 
    phaser.process(buffer);
    auto& phaserRate = *apvts.getRawParameterValue("PHASERRATE");
    auto& phaserDepth = *apvts.getRawParameterValue("PHASERDEPTH");
    auto& phaserCenterFreq = *apvts.getRawParameterValue("PHASERCENTERFREQ");
    auto& phaserFeedback = *apvts.getRawParameterValue("PHASERFEEDBACK");
    auto& phaserMix = *apvts.getRawParameterValue("PHASERMIX");
    phaser.setPhaserParameters(phaserRate, phaserDepth, phaserCenterFreq,
        phaserFeedback, phaserMix);

    //Chorus 
    chorus.process(buffer);
    auto& chorusRate = *apvts.getRawParameterValue("CHORUSRATE");
    auto& chorusDepth = *apvts.getRawParameterValue("CHORUSDEPTH");
    auto& chorusCenter = *apvts.getRawParameterValue("CHORUSCENTERDELAY");
    auto& chorusFeedback = *apvts.getRawParameterValue("CHORUSFEEDBACK");
    auto& chorusMix = *apvts.getRawParameterValue("CHORUSMIX");
    chorus.setChorusParameters(chorusRate, chorusDepth, chorusCenter,
        chorusFeedback, chorusMix);

    // Compressor
    comp.process(buffer);
    auto& threshold = *apvts.getRawParameterValue("THRESHOLD");
    auto& ratio = *apvts.getRawParameterValue("RATIO");
    auto& attack = *apvts.getRawParameterValue("COMPATTACK");
    auto& release = *apvts.getRawParameterValue("COMPRELEASE");
    comp.setCompressorParameters(threshold, ratio, attack, release);
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
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator 1",
        juce::StringArray{ "Sine", "Saw", "Square" }, 0));

    // FM 
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQUENCY", "Osc 1 FM Frequency",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f}, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f}, 0.0f));

    // ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.01f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release",
        juce::NormalisableRange<float>{0.01f, 5.0f, 0.01f }, 0.25f));

    // Filter 
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTERTYPE", "Filter Type",
        juce::StringArray{ "lowpass", "bandpass", "highpass" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERCUTOFF", "Filter Cutoff",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.01f, 0.6f }, 20000.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRESONANCE", "Filter Resonance",
        juce::NormalisableRange<float>{1.0f, 10.0f, 0.01f }, 1.0f));


    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERATTACK", "Filter Attack",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERDECAY", "Filter Decay",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERSUSTAIN", "Filter Sustain",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTERRELEASE", "Filter Release",
        juce::NormalisableRange<float>{0.01f, 5.0f, 0.01f }, 0.25f));

    // Waveshaper
    params.push_back(std::make_unique<juce::AudioParameterChoice>("DISTORTIONTYPE", "Distortion Type",
        juce::StringArray{ "None", "Velvet", "Cheesebread", "Sandy Toes" }, 0));

    // Reverb
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBROOM", "Reverb Room",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDAMP", "Reverb Damp",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWET", "Reverb Wet",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBDRY", "Reverb Dry",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBWIDTH", "Reverb Width",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("REVERBFREEZE", "Reverb Freeze",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));

    // Phaser
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASERRATE", "Phaser Rate",
        juce::NormalisableRange<float>{0.0f, 50.0f, 0.01f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASERDEPTH", "Phaser Depth",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASERCENTERFREQ", "Phaser Center Frequency",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.1f, 0.6f }, 500.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASERFEEDBACK", "Phaser Feedback",
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("PHASERMIX", "Phaser Mix",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));

    // Chorus
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSRATE", "Chorus Rate",
        juce::NormalisableRange<float>{0.0f, 100.0f, 0.01f, 0.1f }, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSDEPTH", "Chorus Depth",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSCENTERDELAY", "Chorus Center Delay",
        juce::NormalisableRange<float>{1.0f, 100.0f, 0.1f}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSFEEDBACK", "Chorus Feedback",
        juce::NormalisableRange<float>{-1.0f, 1.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("CHORUSMIX", "Chorus Mix",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.1f }, 0.0f));

    // Compressor
    params.push_back(std::make_unique<juce::AudioParameterFloat>("THRESHOLD", "Threshold",
        juce::NormalisableRange<float>{-32.0f, 0.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("RATIO", "Ratio",
        juce::NormalisableRange<float>{1.0f, 4.0f, 0.1f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPATTACK", "Comp Attack",
        juce::NormalisableRange<float>{0.0f, 1200.0f, 0.1f }, 20.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("COMPRELEASE", "Comp Release",
        juce::NormalisableRange<float>{0.01f, 170.0f, 0.1f }, 70.0f));

    // Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 
        juce::NormalisableRange<float>{-64.0f, -6.0f, 0.1f}, -12.0f));

    return { params.begin(), params.end() };
}