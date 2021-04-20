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
    distortion(audioProcessor.apvts, "DISTORTIONTYPE")
{
    setSize (620, 550);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsrComponent);
    addAndMakeVisible(filter);
    addAndMakeVisible(filterADSR);
    addAndMakeVisible(distortion);
}

PuzzleMirrorSynthAudioProcessorEditor::~PuzzleMirrorSynthAudioProcessorEditor()
{
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
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
    distortion.setBounds(x, 440, width, height);
}

