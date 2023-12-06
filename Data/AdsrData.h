/*
  ==============================================================================

    AdsrData.h
    Created: 5 Dec 2023 12:55:24pm
    Author:  ajatr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
//inherits from ADSR
class AdsrData : public juce::ADSR {
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams;
};