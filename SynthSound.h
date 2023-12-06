/*
  ==============================================================================

    SynthSound.h
    Created: 15 Jun 2023 11:16:56am
    Author:  ajatr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};