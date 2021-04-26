/*
  ==============================================================================

    CompressorComponent.cpp
    Created: 24 Apr 2021 4:02:40pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CompressorComponent.h"

//==============================================================================
CompressorComponent::CompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String thresholdID,
    juce::String ratioID, juce::String attackID, juce::String releaseID)
{
    setSliderWithLabel(thresholdSlider, thresholdLabel, apvts, thresholdID, thresholdSliderAttachment);
    setSliderWithLabel(ratioSlider, ratioLabel, apvts, ratioID, ratioSliderAttachment);
    setSliderWithLabel(attackSlider, attackLabel, apvts, attackID, attackSliderAttachment);
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseID, releaseSliderAttachment);
}

CompressorComponent::~CompressorComponent()
{
}

void CompressorComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Compressor", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 180,
        bounds.getHeight(), 5.0f, 5.0f);
    g.setColour(juce::Colours::lightblue);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 180,
        bounds.getHeight(), 5.0f);
}

void CompressorComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    thresholdSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    thresholdLabel.setBounds(thresholdSlider.getX(), thresholdSlider.getY() - labelYOffset,
        thresholdSlider.getWidth(), labelHeight);
    ratioSlider.setBounds(thresholdSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    ratioLabel.setBounds(ratioSlider.getX(), ratioSlider.getY() - labelYOffset,
        ratioSlider.getWidth(), labelHeight);
    attackSlider.setBounds(ratioSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - labelYOffset,
        attackSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(attackSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - labelYOffset,
        releaseSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void CompressorComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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