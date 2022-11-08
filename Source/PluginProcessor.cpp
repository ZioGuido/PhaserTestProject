/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserTestProjectAudioProcessor::PhaserTestProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    using Attributes = AudioProcessorValueTreeStateParameterAttributes;
    auto* automationParameter = new AudioProcessorValueTreeState::Parameter("Rate", "Rate", { 0.f, 1.f, 0.001f }, 0.1f, Attributes().withMeta(true));
    automationParameter->addListener(this);
    addParameter(automationParameter);


    effect.reset(new CPhaser(44100.f));
}

PhaserTestProjectAudioProcessor::~PhaserTestProjectAudioProcessor()
{
}

//==============================================================================
const juce::String PhaserTestProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PhaserTestProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PhaserTestProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PhaserTestProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PhaserTestProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PhaserTestProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PhaserTestProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PhaserTestProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PhaserTestProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void PhaserTestProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PhaserTestProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    effect.reset(new CPhaser(sampleRate));

}

void PhaserTestProjectAudioProcessor::releaseResources()
{
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PhaserTestProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PhaserTestProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    midiMessages.clear();

    if (!effect) return;

    for (int s = 0; s < buffer.getNumSamples(); ++s)
    {
        float l = buffer.getSample(0, s);
        float r = l;
        if (totalNumInputChannels == 2)
            r = buffer.getSample(1, s);

        float mono = (l + r) * 0.5f;
        effect->Process(mono);
        l = r = mono;

        buffer.setSample(0, s, l);
        if (totalNumOutputChannels == 2)
            buffer.setSample(1, s, r);
    }
}

//==============================================================================
bool PhaserTestProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PhaserTestProjectAudioProcessor::createEditor()
{
    auto* editor = new PhaserTestProjectAudioProcessorEditor(*this);
    removeAllActionListeners();
    addActionListener(editor);
    return editor;
}

//==============================================================================
void PhaserTestProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{

}

void PhaserTestProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PhaserTestProjectAudioProcessor();
}
