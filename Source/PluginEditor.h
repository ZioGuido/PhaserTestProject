
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class PhaserTestProjectAudioProcessorEditor  : public juce::AudioProcessorEditor,
    public juce::ActionListener
{
public:
    PhaserTestProjectAudioProcessorEditor (PhaserTestProjectAudioProcessor&);
    ~PhaserTestProjectAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    PhaserTestProjectAudioProcessor& audioProcessor;

    std::unique_ptr<Slider> sld_Rate;

    void actionListenerCallback(const String& message)
    {
        if (message == "UpdateUI")
        {
            sld_Rate->setValue(audioProcessor.getParameters()[0]->getValue());
        }
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserTestProjectAudioProcessorEditor)
};
