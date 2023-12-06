/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
//initiallizer method- these components need to be in the same order as the private section in PluginEditor.h
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc(audioProcessor.apvts, "OSC1WAVETYPE"), adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
   //make osc visible
    addAndMakeVisible(osc);
    //make adsr visible
    addAndMakeVisible(adsr);


}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    //g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::black);
}

void TapSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any subcomponents in your editor..
    //set osc bounds
    osc.setBounds(10, 10, 100, 30);
    //set adsr bounds - the 4 sliders are sitting in the adsr component
    adsr.setBounds(getWidth()/2, 0, getWidth()/2, getHeight());
}

