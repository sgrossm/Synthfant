/*
  ==============================================================================

    ReverbComponent.h
    Created: 21 Apr 2021 1:59:10pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ReverbComponent  : public juce::Component
{
public:
    ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String reverbRoomID, 
        juce::String reverbDampID, juce::String reverbWetID, juce::String reverbDryID, 
        juce::String reverbWidthID, juce::String reverbFreezeID);
    ~ReverbComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    juce::Slider roomSizeSlider;
    juce::Slider dampingSlider;
    juce::Slider wetSlider;
    juce::Slider drySlider;
    juce::Slider widthSlider;
    juce::Slider freezeSlider;
    juce::Label roomSizeLabel{ "Room Size", "Room Size" };
    juce::Label dampingLabel{ "Damping", "Damping" };
    juce::Label wetLabel{ "Wet", "Wet" };
    juce::Label dryLabel{ "Dry", "Dry" };
    juce::Label widthLabel{ "Width", "Width" };
    juce::Label freezeLabel{ "Freeze Mode", "Freeze Mode" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> roomSizeSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> dampingSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> wetSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> drySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> widthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freezeSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReverbComponent)
};
