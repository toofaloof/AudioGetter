// PluginEditor.cpp
#include "CursorAudio/PluginProcessor.h"
#include "CursorAudio/PluginEditor.h"

CursorAudioPluginAudioProcessorEditor::CursorAudioPluginAudioProcessorEditor (CursorAudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Button setup
    recordButton.addListener (this);
    addAndMakeVisible (recordButton);

    // Status label setup
    statusLabel.setJustificationType (juce::Justification::centred);
    statusLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible (statusLabel);

    // Editor window size
    setSize (200, 80);

    // Start a timer to update the status label at 20 Hz
    startTimerHz (20);
}

CursorAudioPluginAudioProcessorEditor::~CursorAudioPluginAudioProcessorEditor()
{
    stopTimer();
    recordButton.removeListener (this);
}

void CursorAudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // background
    g.fillAll (juce::Colours::darkgrey);
}

void CursorAudioPluginAudioProcessorEditor::resized()
{
    auto r = getLocalBounds().reduced (10);
    recordButton.setBounds (r.removeFromTop (30).removeFromLeft (80));
    statusLabel.setBounds (r.removeFromTop (30));
}

void CursorAudioPluginAudioProcessorEditor::buttonClicked (juce::Button* button)
{
    if (button == &recordButton)
    {
        if (! audioProcessor.isRecording())
        {
            audioProcessor.startRecording();
            recordButton.setButtonText ("Stop");
        }
        else
        {
            audioProcessor.stopRecording();
            recordButton.setButtonText ("Record");
        }
    }
}

void CursorAudioPluginAudioProcessorEditor::timerCallback()
{
    // Update the label every tick
    if (audioProcessor.isRecording())
        statusLabel.setText ("Recording...", juce::dontSendNotification);
    else
        statusLabel.setText ("Stopped",     juce::dontSendNotification);
}
