#pragma once
#include <JuceHeader.h>
//inherits oscillator class, so has the class functions
class OscData : public juce::dsp::Oscillator<float> {
public:
	void prepareToPlay(juce::dsp::ProcessSpec& spec);
	void setWaveType(const int choice);
	//(set frequency is a parent method so don't name it that unless you override)
	void setWaveFrequency(const int midiNoteNumber);
	void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
private:
};