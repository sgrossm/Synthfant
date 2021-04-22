/*
  ==============================================================================

    DelayLine.h
    Created: 21 Apr 2021 3:22:10pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class DelayLine
{
public:
    void clear();
    int getSize();
    void resize(int newSize);
    float getBack();
    void set(int delay, float newValue);
    void push(float value);

private:
    std::vector<float> ringBuffer;
    int leastRecentIndex = 0;
};