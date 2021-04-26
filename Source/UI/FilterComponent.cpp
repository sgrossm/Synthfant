/*
  ==============================================================================

    FilterComponent.cpp
    Created: 19 Apr 2021 3:05:18pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID,
    juce::String filterCutoffID, juce::String filterResonanceID)
{
    juce::StringArray filterChoices = { "lowpass", "bandpass", "hipass" };
    filterSelector.addItemList(filterChoices, 1);
    addAndMakeVisible(filterSelector);

    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeID, filterSelector);

    filterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    filterTypeLabel.setFont(15.0f);
    filterTypeLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterTypeLabel);

    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, apvts, filterCutoffID, filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider, filterResonanceLabel, apvts, filterResonanceID, filterResonanceAttachment);
}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 5.0f);
    g.setColour(juce::Colours::lightblue);
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);
}

void FilterComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterSelector.setBounds(10, startYPos + 5, 90, 30);
    filterTypeLabel.setBounds(10, startYPos - labelYOffset, 90, labelHeight);

    filterCutoffSlider.setBounds(filterSelector.getRight(), startYPos, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
        filterCutoffSlider.getWidth(), labelHeight);
    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
        filterResonanceSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment)
{
    slider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::black);
    addAndMakeVisible(slider);

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}