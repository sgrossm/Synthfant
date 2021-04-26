/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
PuzzleMirrorSynthAudioProcessorEditor::PuzzleMirrorSynthAudioProcessorEditor(PuzzleMirrorSynthAudioProcessor& p)
    : AudioProcessorEditor(&p),
    audioProcessor(p),
    osc(audioProcessor.apvts, "OSC1", "OSC1FMFREQUENCY", "OSC1FMDEPTH"),
    adsrComponent("Volume Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
    filter(audioProcessor.apvts, "FILTERTYPE", "FILTERCUTOFF", "FILTERRESONANCE"),
    filterADSR("Filter Envelope", audioProcessor.apvts, "FILTERATTACK", "FILTERDECAY", "FILTERSUSTAIN", "FILTERRELEASE"),
    reverb(audioProcessor.apvts, "REVERBROOM", "REVERBDAMP", "REVERBWET", "REVERBDRY", "REVERBWIDTH", "REVERBFREEZE"),
    phaser(audioProcessor.apvts, "PHASERRATE", "PHASERDEPTH", "PHASERCENTERFREQ", "PHASERFEEDBACK", "PHASERMIX"),
    distortion(audioProcessor.apvts, "DISTORTIONTYPE"),
    chorus(audioProcessor.apvts, "CHORUSRATE", "CHORUSDEPTH", "CHORUSCENTERDELAY", "CHORUSFEEDBACK", "CHORUSMIX"),
    comp(audioProcessor.apvts, "THRESHOLD", "RATIO", "COMPATTACK", "COMPRELEASE"),
    gain(audioProcessor.apvts, "GAIN")
{
    
    setLookAndFeel(&customLook);
    setSize (1280, 660);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterADSR);
    addAndMakeVisible(comp);
    addAndMakeVisible(reverb);
    addAndMakeVisible(phaser);
    addAndMakeVisible(distortion);
    addAndMakeVisible(chorus);
    addAndMakeVisible(gain);
    
    logo = juce::ImageCache::getFromMemory(BinaryData::baby_png, BinaryData::baby_pngSize);
    logoComponent.setImage(logo);
    addAndMakeVisible(logoComponent);
}

PuzzleMirrorSynthAudioProcessorEditor::~PuzzleMirrorSynthAudioProcessorEditor()
{
    setLookAndFeel(nullptr);
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::antiquewhite);
}

void PuzzleMirrorSynthAudioProcessorEditor::resized()
{
    const auto x = 5;
    const auto y = 35;
    const auto width = 300;
    const auto height = 200;

    osc.setBounds(x, y, width, height);
    adsrComponent.setBounds(osc.getRight(), y, width, height);
    filter.setBounds(x, 240, width, height);
    filterADSR.setBounds(filter.getRight(), 240, width, height);
    comp.setBounds(x, 440, width + 320, height);
    reverb.setBounds(adsrComponent.getRight(), y, width + 400, height);
    phaser.setBounds(filterADSR.getRight(), 240, width + 380, height);
    distortion.setBounds(phaser.getRight() - 170, 240, width - 150, height);
    chorus.setBounds(filterADSR.getRight(), 440, width + 380, height);
    gain.setBounds(x + width + 160, 440, width - 180, height);
    logoComponent.setBounds(chorus.getRight() - 200, 440, 200, 200);
}

