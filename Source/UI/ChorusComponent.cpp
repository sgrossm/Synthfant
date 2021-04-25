/*
  ==============================================================================

    ChorusComponent.cpp
    Created: 24 Apr 2021 3:24:53pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
    juce::String depthID, juce::String centerDelayID, juce::String fdbkID, juce::String mixID)
{
    setSliderWithLabel(rateSlider, rateLabel, apvts, rateID, rateSliderAttachment);
    setSliderWithLabel(depthSlider, depthLabel, apvts, depthID, depthSliderAttachment);
    setSliderWithLabel(centerDelaySlider, centerDelayLabel, apvts, centerDelayID, centerDelaySliderAttachment);
    setSliderWithLabel(fdbkSlider, fdbkLabel, apvts, fdbkID, fdbkSliderAttachment);
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixID, mixSliderAttachment);
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colours::black);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Chorus", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 180,
        bounds.getHeight(), 5.0f, 2.0f);
}

void ChorusComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    rateSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() - labelYOffset,
        rateSlider.getWidth(), labelHeight);
    depthSlider.setBounds(rateSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    depthLabel.setBounds(depthSlider.getX(), depthSlider.getY() - labelYOffset,
        depthSlider.getWidth(), labelHeight);
    centerDelaySlider.setBounds(depthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    centerDelayLabel.setBounds(centerDelaySlider.getX(), centerDelaySlider.getY() - labelYOffset,
        centerDelaySlider.getWidth(), labelHeight);
    fdbkSlider.setBounds(centerDelaySlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fdbkLabel.setBounds(fdbkSlider.getX(), fdbkSlider.getY() - labelYOffset,
        fdbkSlider.getWidth(), labelHeight);
    mixSlider.setBounds(fdbkSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() - labelYOffset,
        mixSlider.getWidth(), labelHeight);
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void ChorusComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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