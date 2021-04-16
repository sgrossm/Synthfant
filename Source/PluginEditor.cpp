/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuzzleMirrorSynthAudioProcessorEditor::PuzzleMirrorSynthAudioProcessorEditor (PuzzleMirrorSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC1", "OSC1FMFREQUENCY", "OSC1FMDEPTH"), 
    adsrComponent(audioProcessor.apvts)
{
    setSize (600, 500);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsrComponent);
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
    const auto y = 25;
    osc.setBounds(x, y, 300, 200);
    adsrComponent.setBounds(osc.getRight(), y, 280, 200);
}

