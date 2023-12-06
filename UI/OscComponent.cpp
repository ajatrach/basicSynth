/*
  ==============================================================================

    OscComponent.cpp
    Created: 6 Dec 2023 12:21:34am
    Author:  ajatr

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    //we add an item list
    juce::StringArray choices{ "Sine", "Saw", "Square" };
    oscWaveSelector.addItemList(choices, 1);
    addAndMakeVisible(oscWaveSelector);

    //make attachment
     //unique ptr ensures that when this memory is allocated efficiently-the object is disposed when the ptr goes out of scope

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */
    g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    oscWaveSelector.setBounds(0, 0, 90, 20);

}
