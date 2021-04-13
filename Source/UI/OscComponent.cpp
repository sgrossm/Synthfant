/*
  ==============================================================================

    OscComponent.cpp
    Created: 12 Apr 2021 4:21:16pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveID)
{
    juce::StringArray waveChoices = { "Sine", "Saw", "Square" };
    waveformSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(waveformSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, waveformSelector);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

}

void OscComponent::resized()
{
    waveformSelector.setBounds(0, 0, 90, 20);
}
