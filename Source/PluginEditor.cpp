/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InfiniteIrfilterAudioProcessorEditor::InfiniteIrfilterAudioProcessorEditor (InfiniteIrfilterAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    mCutoffSlider = new Slider (Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
    mQualitySlider = new Slider (Slider::RotaryVerticalDrag, Slider::TextBoxBelow);
    
    addAndMakeVisible (mCutoffSlider);
    addAndMakeVisible (mQualitySlider);
    
    mCutoffAttachment = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), "cutoff", *mCutoffSlider);
    mQualityAttachment = new AudioProcessorValueTreeState::SliderAttachment (p.getValueTreeState(), "quality", *mQualitySlider);
    
    setSize (400, 300);
}

InfiniteIrfilterAudioProcessorEditor::~InfiniteIrfilterAudioProcessorEditor()
{
}

//==============================================================================
void InfiniteIrfilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void InfiniteIrfilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
