/*
  ==============================================================================

    AdsrData.cpp
    Created: 5 Dec 2023 12:55:24pm
    Author:  ajatr

  ==============================================================================
*/

#include "AdsrData.h"
void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release) {
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    setParameters(adsrParams);
};