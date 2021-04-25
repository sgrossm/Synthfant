/*
  ==============================================================================

    ChorusComponent.h
    Created: 24 Apr 2021 3:24:53pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
        juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    juce::Slider rateSlider;
    juce::Slider depthSlider;
    juce::Slider centerDelaySlider;
    juce::Slider fdbkSlider;
    juce::Slider mixSlider;
    juce::Label rateLabel{ "Rate", "Rate" };
    juce::Label depthLabel{ "Depth", "Depth" };
    juce::Label centerDelayLabel{ "Center Delay", "Center Delay" };
    juce::Label fdbkLabel{ "Feedback", "Feedback" };
    juce::Label mixLabel{ "Mix", "Mix" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centerDelaySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fdbkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
