/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/AdsrComponent.h"
#include "UI/OscComponent.h"

//==============================================================================
/**
*/
class TapSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TapSynthAudioProcessorEditor (TapSynthAudioProcessor&);
    ~TapSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    //audioProcessor is a reference to our plugin's audio processor, which is how we get access to the apvts
    TapSynthAudioProcessor& audioProcessor;  //apvts is in the audio processor so we need to initialize it first before referencing apvts in adsr
    OscComponent osc;
    AdsrComponent adsr;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapSynthAudioProcessorEditor)
};
