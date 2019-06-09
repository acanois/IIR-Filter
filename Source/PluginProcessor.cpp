/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
InfiniteIrfilterAudioProcessor::InfiniteIrfilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
        mStateTree (*this, nullptr, "ParameterState", {
                std::make_unique<AudioParameterFloat> ("cutoff", "Cutoff",
                    NormalisableRange<float> (20.0f, 20000.0f, 0.001f), mCutoff),
                std::make_unique<AudioParameterFloat> ("quality", "Quality",
                    NormalisableRange<float> (0.001f, 0.9f, 0.001f), mQuality),
                std::make_unique<AudioParameterInt> ("filterType", "FilterType",
                    1, 3, mFilterChoice),
            })
        {
}

InfiniteIrfilterAudioProcessor::~InfiniteIrfilterAudioProcessor()
{
}

//==============================================================================
const String InfiniteIrfilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool InfiniteIrfilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool InfiniteIrfilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool InfiniteIrfilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double InfiniteIrfilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int InfiniteIrfilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int InfiniteIrfilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void InfiniteIrfilterAudioProcessor::setCurrentProgram (int index)
{
}

const String InfiniteIrfilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void InfiniteIrfilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void InfiniteIrfilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    mSampleRate = sampleRate;
    
    dsp::ProcessSpec spec;
    spec.sampleRate = mSampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    mLowPass.prepare (spec);
    mLowPass.reset();
}

void InfiniteIrfilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool InfiniteIrfilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void InfiniteIrfilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Filter the output
    dsp::AudioBlock<float> block (buffer);
    
    float cutoff = *mStateTree.getRawParameterValue("cutoff");
    float quality = *mStateTree.getRawParameterValue("quality");
    
    *mLowPass.state = *dsp::IIR::Coefficients<float>::makeLowPass(mSampleRate, cutoff, quality);
    mLowPass.process(dsp::ProcessContextReplacing<float> (block));
}

AudioProcessorValueTreeState& InfiniteIrfilterAudioProcessor::getValueTreeState()
{
    return mStateTree;
}

//==============================================================================
bool InfiniteIrfilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* InfiniteIrfilterAudioProcessor::createEditor()
{
    return new InfiniteIrfilterAudioProcessorEditor (*this);
}

//==============================================================================
void InfiniteIrfilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void InfiniteIrfilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InfiniteIrfilterAudioProcessor();
}
