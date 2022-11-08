
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PhaserTestProjectAudioProcessorEditor::PhaserTestProjectAudioProcessorEditor (PhaserTestProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    sld_Rate.reset(new Slider(Slider::RotaryHorizontalVerticalDrag, Slider::TextBoxBelow));
    sld_Rate->setRange(0.0, 1.0, 0.01);
    sld_Rate->onValueChange = [&] { audioProcessor.getParameters()[0]->setValueNotifyingHost(sld_Rate->getValue()); };
    addAndMakeVisible(sld_Rate.get());

    setSize(250, 400);

    actionListenerCallback("UpdateUI");
}

PhaserTestProjectAudioProcessorEditor::~PhaserTestProjectAudioProcessorEditor()
{
}

//==============================================================================
void PhaserTestProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::orange.darker(0.1f));
}

void PhaserTestProjectAudioProcessorEditor::resized()
{
    if (sld_Rate) 
        sld_Rate->centreWithSize(200, 200);
}
