/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class InfiniteIrfilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    InfiniteIrfilterAudioProcessorEditor (InfiniteIrfilterAudioProcessor&);
    ~InfiniteIrfilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    InfiniteIrfilterAudioProcessor& processor;
    
    ScopedPointer<Slider> mCutoffSlider;
    ScopedPointer<Slider> mQualitySlider;
    
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mCutoffAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mQualityAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfiniteIrfilterAudioProcessorEditor)
};
