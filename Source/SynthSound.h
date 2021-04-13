/*
  ==============================================================================

    SynthSound.h
    Created: 12 Apr 2021 10:42:29am
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};