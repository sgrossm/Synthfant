/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 25 Apr 2021 2:38:14pm
    Author:  lazlo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class CustomLookAndFeel  : public juce::LookAndFeel_V4
{
public:
    CustomLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }
    ~CustomLookAndFeel() override
    {

    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colours::orange);
        g.fillEllipse(rx, ry, rw, rw);

        // inner ellipse
        g.setColour(juce::Colours::coral);
        g.fillEllipse(rx + 5, ry + 5, rw - 10, rw - 10);

        // outline
        g.setColour(juce::Colours::chartreuse);
        g.drawEllipse(rx, ry, rw, rw, 1.0f);

        juce::Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 5.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colours::yellow);
        g.fillPath(p);
    }

    //void drawLinearSlider(juce::Graphics& g,
    //    int x, int y,
    //    int w, int h,
    //    float sliderPos,
    //    float minSliderPos,
    //    float maxSliderPos,
    //    const juce::Slider::SliderStyle style,
    //    juce::Slider& slider)
    //{
    //    g.fillAll(juce::Colours::red);

    //    g.setColour(juce::Colours::red.withMultipliedAlpha(slider.isEnabled() ? 1.0f : 0.3f));

    //    float alpha = 0.35f;

    //    if (slider.isEnabled())
    //        alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.7f;

    //    const juce::Colour fill(slider.findColour(juce::Slider::thumbColourId).withAlpha(alpha));
    //    const juce::Colour outline(juce::Colours::black.withAlpha(slider.isEnabled() ? 0.7f : 0.35f));
    //    
    //}

    void drawComboBox(juce::Graphics& g, int width, int height,
        const bool isButtonDown,
        int buttonX, int buttonY,
        int buttonW, int buttonH,
        juce::ComboBox& box)
    {
        g.fillAll(box.findColour(juce::ComboBox::backgroundColourId));

        g.setColour(box.findColour((isButtonDown) ? juce::ComboBox::buttonColourId
            : juce::ComboBox::backgroundColourId));
        g.fillRect(buttonX, buttonY, buttonW, buttonH);

        g.setColour(box.findColour(juce::ComboBox::outlineColourId));
        g.drawRect(0, 0, width, height);

        const float arrowX = 0.2f;
        const float arrowH = 0.3f;

        if (box.isEnabled())
        {
            juce::Path p;
            p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.45f - arrowH),
                buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                buttonX + buttonW * arrowX, buttonY + buttonH * 0.45f);

            p.addTriangle(buttonX + buttonW * 0.5f, buttonY + buttonH * (0.55f + arrowH),
                buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                buttonX + buttonW * arrowX, buttonY + buttonH * 0.55f);

            g.setColour(box.findColour((isButtonDown) ? juce::ComboBox::backgroundColourId
                : juce::ComboBox::buttonColourId));
            g.fillPath(p);
        }
    }
};
