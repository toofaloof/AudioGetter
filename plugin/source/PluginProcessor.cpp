// PluginProcessor.cpp
#include "CursorAudio/PluginProcessor.h"
#include "CursorAudio/PluginEditor.h"

CursorAudioPluginAudioProcessor::CursorAudioPluginAudioProcessor()
    : AudioProcessor (BusesProperties()
       #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
            .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        #endif
            .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
       #endif
    )
{
}

CursorAudioPluginAudioProcessor::~CursorAudioPluginAudioProcessor()
{
    stopRecording();
}

void CursorAudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    currentSampleRate = sampleRate;
    tempBuffer.setSize (getTotalNumInputChannels(), samplesPerBlock);
}

void CursorAudioPluginAudioProcessor::releaseResources()
{
    stopRecording();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool CursorAudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    return layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo()
        && layouts.getMainInputChannelSet()  == juce::AudioChannelSet::stereo();
}
#endif

void CursorAudioPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                    juce::MidiBuffer&)
{
    juce::ScopedNoDenormals noDenormals;
    auto numSamples = buffer.getNumSamples();

    for (auto ch = getTotalNumInputChannels(); ch < getTotalNumOutputChannels(); ++ch)
        buffer.clear (ch, 0, numSamples);

    if (threadedWriter)
    {
        tempBuffer.makeCopyOf (buffer, true);
        threadedWriter->write (tempBuffer.getArrayOfReadPointers(), numSamples);
    }
}

void CursorAudioPluginAudioProcessor::startRecording()
{
    if (threadedWriter) 
        return; // already recording

    // Choose output file
    auto docs = juce::File::getSpecialLocation (juce::File::userDocumentsDirectory);
    auto file = docs.getChildFile ("CursorSession.wav");
    file.deleteFile();  // overwrite any old file

    // Create and own the FileOutputStream temporarily
    fileStream = std::make_unique<juce::FileOutputStream>(file);
    if (! fileStream->openedOk())
        return;

    // Create the WAV writer; this takes ownership of the stream on success
    juce::WavAudioFormat wavFormat;
    rawWriter = wavFormat.createWriterFor (
        fileStream.get(),
        currentSampleRate,
        static_cast<unsigned int>(getTotalNumOutputChannels()),
        16, {}, 0);

    if (rawWriter)
    {
        // **TRANSFER** ownership of the stream to the writer (only it will delete it)
        fileStream.release();  // <— critical to avoid double‐free :contentReference[oaicite:8]{index=8}

        // Start background thread and wrap the writer
        fileWriterThread.startThread();
        threadedWriter.reset (new juce::AudioFormatWriter::ThreadedWriter (
            rawWriter,
            fileWriterThread,
            32768
        ));
    }
    else
    {
        // On failure, release our stream so it's properly deleted here
        fileStream.reset();
    }
}

void CursorAudioPluginAudioProcessor::stopRecording()
{
    // First destroy the writer (which flushes and deletes the stream)
    threadedWriter.reset();
    rawWriter = nullptr;
    // Our unique_ptr no longer owns anything, so no double‐delete occurs
    fileStream.reset();

    // Stop the writing thread gracefully
    fileWriterThread.stopThread (2000);
}

void CursorAudioPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::MemoryOutputStream m (destData, true);
    m.writeBool (isRecording());
}

void CursorAudioPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    juce::MemoryInputStream m (data,
                               static_cast<size_t>(sizeInBytes),
                               false);
    if (m.readBool())
        startRecording();
    else
        stopRecording();
}

juce::AudioProcessorEditor* CursorAudioPluginAudioProcessor::createEditor()
{
    return new CursorAudioPluginAudioProcessorEditor (*this);
}

bool CursorAudioPluginAudioProcessor::hasEditor() const
{
    return true;
}

// This creates new instances of the plugin
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new CursorAudioPluginAudioProcessor();
}
