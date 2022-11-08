
#pragma once

#include <JuceHeader.h>

#include "DSP/Phase100.h"

//==============================================================================
/**
*/
class PhaserTestProjectAudioProcessor  : public juce::AudioProcessor,
    public juce::AudioProcessorParameter::Listener,
    public juce::ActionBroadcaster
{
public:
    //==============================================================================
    PhaserTestProjectAudioProcessor();
    ~PhaserTestProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    std::unique_ptr<CPhaser> effect;

private:


    //==============================================================================
    // AudioProcessorParameter::Listener - Receive parameter from host automation
    void parameterGestureChanged(int parameterIndex, bool gestureIsStarting) override { }
    void parameterValueChanged(int parameterIndex, float newValue) override
    {
        if (!effect) return;

        switch (parameterIndex)
        {
        case 0:
            effect->setRate(newValue * newValue * 20.f);
            break;
        }

        sendActionMessage("UpdateUI");
    }


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserTestProjectAudioProcessor)
};
