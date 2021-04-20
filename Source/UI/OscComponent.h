/*
  ==============================================================================

    OscComponent.h
    Created: 12 Apr 2021 4:21:16pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, 
        juce::String fmFreqID, juce::String fmDepthID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    juce::ComboBox waveformSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
    juce::Label waveformLabel {"Wave type", "Wave type"};

    juce::Slider fmFrequencySlider;
    juce::Slider fmDepthSlider;
    juce::Label fmFrequencyLabel { "FM Frequency", "FM Frequency" };
    juce::Label fmDepthLabel { "FM Depth", "FM Depth" };
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
