/*
  ==============================================================================

    PhaserComponent.h
    Created: 21 Apr 2021 3:18:19pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PhaserComponent  : public juce::Component
{
public:
    PhaserComponent();
    ~PhaserComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserComponent)
};
