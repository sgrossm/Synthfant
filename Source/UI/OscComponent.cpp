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
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, juce::String fmFreqID, juce::String fmDepthID)
{
    juce::StringArray waveChoices = { "Sine", "Saw", "Square" };
    waveformSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(waveformSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, waveformSelector);

    waveformLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveformLabel.setFont(15.0f);
    waveformLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(waveformLabel);

    setSliderWithLabel(fmFrequencySlider, fmFrequencyLabel, apvts, fmFreqID, fmFrequencySliderAttachment);
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthID, fmDepthSliderAttachment);
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
    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void OscComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    waveformSelector.setBounds(10, startYPos + 5, 90, 30);
    waveformLabel.setBounds(10, startYPos - labelYOffset, 90, labelHeight);
    
    fmFrequencySlider.setBounds(waveformSelector.getRight(), startYPos, sliderWidth, sliderHeight);
    fmFrequencyLabel.setBounds(fmFrequencySlider.getX(), fmFrequencySlider.getY() - labelYOffset,
        fmFrequencySlider.getWidth(), labelHeight);
    fmDepthSlider.setBounds(fmFrequencySlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset,
        fmDepthSlider.getWidth(), labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}