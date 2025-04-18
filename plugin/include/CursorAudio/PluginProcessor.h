// PluginProcessor.h
#pragma once

#include <JuceHeader.h>

class CursorAudioPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    CursorAudioPluginAudioProcessor();
    ~CursorAudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midi) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    const juce::String getName() const override               { return JucePlugin_Name; }
    bool acceptsMidi() const override                         { return JucePlugin_WantsMidiInput; }
    bool producesMidi() const override                        { return JucePlugin_ProducesMidiOutput; }
    bool isMidiEffect() const override                        { return JucePlugin_IsMidiEffect; }
    double getTailLengthSeconds() const override              { return 0.0; }

    //==============================================================================
    int getNumPrograms() override                             { return 1; }
    int getCurrentProgram() override                          { return 0; }
    void setCurrentProgram (int) override                     {}
    const juce::String getProgramName (int) override          { return {}; }
    void changeProgramName (int, const juce::String&) override{}

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    /** Call to begin writing a WAV file */
    void startRecording();

    /** Call to finish and close the WAV file */
    void stopRecording();

    /** True while a recording is active */
    bool isRecording() const noexcept
    {
        return threadedWriter != nullptr;
    }

private:
    double currentSampleRate = 44100.0;
    juce::AudioBuffer<float> tempBuffer;
    std::unique_ptr<juce::FileOutputStream> fileStream;
    juce::AudioFormatWriter* rawWriter = nullptr;
    std::unique_ptr<juce::AudioFormatWriter::ThreadedWriter> threadedWriter;
    juce::TimeSliceThread fileWriterThread { "Audio File Writer Thread" };
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CursorAudioPluginAudioProcessor)
};
