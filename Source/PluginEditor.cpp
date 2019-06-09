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
    
    // Menu initialization
    mFilterBox = new ComboBox;
    
    mFilterBox->addItem("LPF", 1);
    mFilterBox->addItem("HPF", 2);
    mFilterBox->addItem("BPF", 3);
    mFilterBox->setJustificationType (Justification::centred);
    addAndMakeVisible (mFilterBox);
    
    mFilterType = new AudioProcessorValueTreeState::ComboBoxAttachment (p.getValueTreeState(), "filter", *mFilterBox);
    
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
}

void InfiniteIrfilterAudioProcessorEditor::resized()
{
    const int removal = 40;
    
    Rectangle<int> componentSpace = getLocalBounds().reduced(removal);
    
    // Going to be implemented later
    float width  = componentSpace.getWidth();
    float height = componentSpace.getHeight();
    
    const int dialSize = 100;
    
    // I'm still figuring out this coordinate system, but this works for now
    mFilterBox->setBounds (componentSpace.removeFromTop(removal));
    mCutoffSlider->setBounds (removal, removal + 50, dialSize, dialSize);
    mQualitySlider->setBounds (width - 60, removal + 50, dialSize, dialSize);
}
