/*
  ==============================================================================

    SynthVoice.cpp
    Created: 15 Jun 2023 11:16:25am
    Author:  ajatr

  ==============================================================================
*/

#include "SynthVoice.h"

//will return true if we have a sound loaded up
bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    //check if synthsound is casting as a synthesizer sound
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;

}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    //set the osc freq
    osc.setWaveFrequency(midiNoteNumber);
    //starts adsr attack
    adsr.noteOn();

}
void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
    if (!allowTailOff || !adsr.isActive()) {
        clearCurrentNote();
    }

}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {


}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {

}

//based on oscillator preparetoplay
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);
    //processspec is a way we can pass information into the oscillator
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    //now pass these into oscillator (pass a reference to the spec object
    osc.prepareToPlay(spec);
    //prepare gain
    gain.prepare(spec);
    
    //set up gain (volume)
    gain.setGainLinear(0.3f);

    isPrepared = true;
}

//need to connect this to AudioProcessorValueTreeState (in processor.cpp)
//we will call this method in the process block
void SynthVoice::update(const float attack, const float decay, const float sustain, const float release) {
    adsr.updateADSR(attack, decay, sustain, release);
}

//renderNextBlock is being called in processBlock method in pluginProcessor
void SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) {
    //checks if preparetoplay is called, otherwise stops execution
    jassert(isPrepared);

    //leave the method if the voice is not active
    if (!isVoiceActive())
        return;

    //we want to replace content every callback, and we do not want any new allocations
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    //from oscillator process block
    //audioblock is the same thing as the outputbuffer. audioblock is an alias
    //output buffer will contain the data provided by process
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
    //processes oscillator
    osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

    //apply adsr
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    //will pause the application if the start sample is not 0
    //if (startSample != 0)
    //    jassertfalse;

    //add synth buffer info to output buffer
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel) {
        //if there is audio already inside the buffer, we are readjusting
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        if (!adsr.isActive()) {
            //if the sound finishes during the course of the current block, it has to tell the synthesiser it has finished
            clearCurrentNote();
        }
    }
}