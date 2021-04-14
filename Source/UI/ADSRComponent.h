/*
  ==============================================================================

    ADSRComponent.h
    Created: 12 Apr 2021 2:09:08pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ADSRComponent  : public juce::Component
{
public:
    ADSRComponent(juce::AudioProcessorValueTreeState& apvts);
    ~ADSRComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
                            juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    juce::Label attackLabel { "Attack", "A" };
    juce::Label decayLabel { "Decay", "D" };
    juce::Label sustainLabel {"Sustain", "S"};
    juce::Label releaseLabel {"Release", "R"};

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    // when exit UI, unique_ptr marks memory as free to use
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ADSRComponent)
};
