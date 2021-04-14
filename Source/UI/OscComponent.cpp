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

    waveformLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveformLabel.setFont(15.0f);
    waveformLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(waveformLabel);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Waveform", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    waveformSelector.setBounds(10, startY - 15, 90, 30);
    waveformLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);
}
