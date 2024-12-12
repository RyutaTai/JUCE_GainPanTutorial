/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

/*----- í«â¡ -----*/
struct SinglePageBrowser :juce::WebBrowserComponent
{
    using WebBrowserComponent::WebBrowserComponent;

    // Prevent page loads from navigating away from our single page web app
    bool pageAboutToLoad(const juce::String& newURL) override 
    {
        return newURL == juce::String("http://localhost:5173/") ||
            newURL == getResourceProviderRoot();
    }

};

/*----- í«â¡èIÇÌÇË -----*/

//==============================================================================
/**
*/
class GainPanTutorialAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    GainPanTutorialAudioProcessorEditor (GainPanTutorialAudioProcessor&);
    ~GainPanTutorialAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainPanTutorialAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainPanTutorialAudioProcessorEditor)
};
