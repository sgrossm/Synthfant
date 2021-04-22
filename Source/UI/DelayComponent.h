/*
  ==============================================================================

    DelayComponent.h
    Created: 21 Apr 2021 3:18:05pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DelayComponent  : public juce::Component
{
public:
    DelayComponent();
    ~DelayComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DelayComponent)
};
