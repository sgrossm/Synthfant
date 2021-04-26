/*
  ==============================================================================

    PhaserComponent.cpp
    Created: 21 Apr 2021 3:18:19pm
    Author:  lazlo

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PhaserComponent.h"

//==============================================================================
PhaserComponent::PhaserComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
    juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID)
{
    setSliderWithLabel(rateSlider, rateLabel, apvts, rateID, rateSliderAttachment);
    setSliderWithLabel(depthSlider, depthLabel, apvts, depthID, depthSliderAttachment);
    setSliderWithLabel(centerFreqSlider, centerFreqLabel, apvts, centerFreqID, centerFreqSliderAttachment);
    setSliderWithLabel(fdbkSlider, fdbkLabel, apvts, fdbkID, fdbkSliderAttachment);
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixID, mixSliderAttachment);
}

PhaserComponent::~PhaserComponent()
{
}

void PhaserComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.setFont(20.0f);
    g.drawText("Phaser", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 180,
        bounds.getHeight(), 5.0f, 5.0f);
    g.setColour(juce::Colours::lightblue);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 180,
        bounds.getHeight(), 5.0f);
}

void PhaserComponent::resized()
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
    centerFreqSlider.setBounds(depthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    centerFreqLabel.setBounds(centerFreqSlider.getX(), centerFreqSlider.getY() - labelYOffset,
        centerFreqSlider.getWidth(), labelHeight);
    fdbkSlider.setBounds(centerFreqSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fdbkLabel.setBounds(fdbkSlider.getX(), fdbkSlider.getY() - labelYOffset,
        fdbkSlider.getWidth(), labelHeight);
    mixSlider.setBounds(fdbkSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() - labelYOffset,
        mixSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void PhaserComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
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