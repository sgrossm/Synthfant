/*
  ==============================================================================

    FilterComponent.h
    Created: 19 Apr 2021 3:05:18pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID,
        juce::String filterCutoffID, juce::String filterResonanceID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    juce::Label filterTypeLabel { "Filter Type", "Filter Type" };

    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    juce::Label filterCutoffLabel{ "Cutoff", "Cutoff" };
    juce::Label filterResonanceLabel{ "Resonance", "Resonance" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
