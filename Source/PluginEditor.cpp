/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PuzzleMirrorSynthAudioProcessorEditor::PuzzleMirrorSynthAudioProcessorEditor (PuzzleMirrorSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC"), adsrComponent(audioProcessor.apvts)
{
    setSize (400, 300);
    addAndMakeVisible(osc);
    addAndMakeVisible(adsrComponent);
}

PuzzleMirrorSynthAudioProcessorEditor::~PuzzleMirrorSynthAudioProcessorEditor()
{
}

//==============================================================================
void PuzzleMirrorSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);;
}

void PuzzleMirrorSynthAudioProcessorEditor::resized()
{
    osc.setBounds(10, 10, 100, 30);
    adsrComponent.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}

