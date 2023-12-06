#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec) {
	prepare(spec);
}


void OscData::setWaveType(const int choice) {
   //saw wave is  x/ juce::MathConstants<float>::pi
   //sine wave is    std::sin(x)
   //square wave is   x<0.0f  -1.0f : 1.0f
	switch (choice){
	case 0:
		//sine wave
		initialise([](float x) {return std::sin(x); });
		break;
	case 1:
		//saw wave
		initialise([](float x) {return x / juce::MathConstants<float>::pi; });
		break;
	case 2:
		//square wave [](float x) {return x / juce::MathConstants<float>::pi;
		initialise([](float x) {return x < 0.0f ? - 1.0f : 1.0f; });
		break;

	default:
		//means cases 0,1,2 didn't work
		jassertfalse;
		break;
	}
}

void OscData::setWaveFrequency(const int midiNoteNumber) {
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));

}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block) {
	process(juce::dsp::ProcessContextReplacing<float>(block));
}