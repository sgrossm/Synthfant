/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/ADSRComponent.h"
#include "UI/OscComponent.h"
#include "UI/FilterComponent.h"

//==============================================================================
/**
*/
class PuzzleMirrorSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PuzzleMirrorSynthAudioProcessorEditor (PuzzleMirrorSynthAudioProcessor&);
    ~PuzzleMirrorSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //juce::MidiKeyboardComponent keyboardComponent;
    PuzzleMirrorSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    ADSRComponent adsrComponent;
    FilterComponent filter;
    ADSRComponent filterADSR;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuzzleMirrorSynthAudioProcessorEditor)
};
