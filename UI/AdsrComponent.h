/*
  ==============================================================================

    AdsrComponent.h
    Author:  ajatr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    //we can pass a reference to apvts as an argument to the constructor of adsr
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //internal method to set params
    void setSliderParams(juce::Slider& slider);
    //need to create sliders and combobox to control parameters
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    //for code cleanliness
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    //need Attachments to connect parameter data to the display side
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
