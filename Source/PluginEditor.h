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
#include "UI/DistortionComponent.h"
#include "UI/ReverbComponent.h"
#include "UI/PhaserComponent.h"
#include "UI/ChorusComponent.h"
#include "UI/CompressorComponent.h"
#include "UI/GainComponent.h"

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
    PuzzleMirrorSynthAudioProcessor& audioProcessor;
    OscComponent osc;
    ADSRComponent adsrComponent;
    FilterComponent filter;
    ADSRComponent filterADSR;
    ReverbComponent reverb;
    PhaserComponent phaser;
    DistortionComponent distortion;
    ChorusComponent chorus;
    CompressorComponent comp;
    GainComponent gain;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PuzzleMirrorSynthAudioProcessorEditor)
};
