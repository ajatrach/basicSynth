/*
  ==============================================================================

    SynthVoice.h
    Created: 15 Jun 2023 11:16:25am
    Author:  ajatr

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"


//synthVoice is inheriting the juce class SynthesiserVoice
class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;

    //this is not coming from Synthesizer voice, so we are not calling override
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float > & outputBuffer, int startSample, int numSamples) override;
    void update(const float attack, const float decay, const float sustain, const float release);
    OscData& getOscillator() { return osc; }
private:

    AdsrData adsr;
    juce::AudioBuffer<float> synthBuffer;

    //create constructor- we use lambda func
    //constuct the oscillator
 
    OscData osc;
    //juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi; } };

    //create a gain 
    juce::dsp::Gain<float> gain;

    //boolean to make sure preparetoplay is instantiated
    bool isPrepared{ false };
};