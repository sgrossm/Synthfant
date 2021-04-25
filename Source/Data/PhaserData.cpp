/*
  ==============================================================================

    PhaserData.cpp
    Created: 21 Apr 2021 3:17:53pm
    Author:  lazlo

  ==============================================================================
*/

#include "PhaserData.h"

void PhaserData::prepare(const juce::dsp::ProcessSpec& spec)
{
    phaser.prepare(spec);
    isPrepared = true;
}

void PhaserData::setPhaserParameters(const float rate, const float depth, const float centerFreq,
    const float fdbk, const float mix)
{
    phaser.setRate(rate);
    phaser.setDepth(depth);
    phaser.setCentreFrequency(centerFreq);
    phaser.setFeedback(fdbk);
    phaser.setMix(mix);
}

void PhaserData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    phaser.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void PhaserData::reset()
{
    phaser.reset();
}