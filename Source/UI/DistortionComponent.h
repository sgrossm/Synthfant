/*
  ==============================================================================

    DistortionComponent.h
    Created: 20 Apr 2021 11:55:52am
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DistortionComponent  : public juce::Component
{
public:
    DistortionComponent(juce::AudioProcessorValueTreeState& apvts, juce::String distortionID);
    ~DistortionComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox distortionType;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> distortionTypeAttachment;
    juce::Label distortionLabel{ "Distortion type", "Distortion type" };

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionComponent)
};
