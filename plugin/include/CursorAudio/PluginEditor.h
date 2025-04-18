// PluginEditor.h
#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class CursorAudioPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                              private juce::Button::Listener,
                                              private juce::Timer
{
public:
    CursorAudioPluginAudioProcessorEditor (CursorAudioPluginAudioProcessor&);
    ~CursorAudioPluginAudioProcessorEditor() override;

    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    // Button listener callback
    void buttonClicked (juce::Button* button) override;
    // Timer to refresh the status label
    void timerCallback() override;

    CursorAudioPluginAudioProcessor& audioProcessor;

    juce::TextButton recordButton { "Record" };
    juce::Label      statusLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CursorAudioPluginAudioProcessorEditor)
};
