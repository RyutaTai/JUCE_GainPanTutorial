/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainPanTutorialAudioProcessorEditor::GainPanTutorialAudioProcessorEditor (GainPanTutorialAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    
    addAndMakeVisible(webComponent);
#if 1
    webComponent.goToURL("http://localhost:5173/");
#else
    webComponent.goToURL(juce::WebBrowserComponent::getResourceProviderRoot());
#endif

	setSize(170, 650);
    //setSize (400, 300);
}

GainPanTutorialAudioProcessorEditor::~GainPanTutorialAudioProcessorEditor()
{
}

//==============================================================================
void GainPanTutorialAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

}

void GainPanTutorialAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    webComponent.setBounds(getLocalBounds());

}

std::optional<juce::WebBrowserComponent::Resource>
GainPanTutorialAudioProcessorEditor::getResource(const juce::String& url)
{
    const auto urlToRetrive = url == "/" 
                                    ? juce::String{ "index.html" }
                                    : url.fromFirstOccurrenceOf("/", false, false);
    
    static auto streamZip = juce::MemoryInputStream(juce::MemoryBlock(BinaryData::assets_zip, BinaryData::assets_zipSize), true);

    static juce::ZipFile archive{ streamZip };

    if (auto* entry = archive.getEntry(urlToRetrive))
    {
        auto entryStream = rawToUniquePtr(archive.createStreamForEntry(*entry));
        std::vector<std::byte> result((size_t)entryStream->getTotalLength());
        entryStream->setPosition(0);
        entryStream->read(result.data(), result.size());

        auto mine = getMimeForExtension(entry->filename.fromLastOccurrenceOf(".", false, false).toLowerCase());
        return juce::WebBrowserComponent::Resource{ std::move(result), std::move(mine) };
    }
    return std::nullopt;
}

const char* GainPanTutorialAudioProcessorEditor::getMimeForExtension(const juce::String& extension)
{
    static const std::unordered_map<juce::String, const char*>mineMap =
    {
        {{"htm"},"text/html"},
        {{"html"},"text/html"},
        {{"txt"},"text/plain"},
        {{"jpg"},"image/jpeg"},
        {{"jpeg"},"image/jpeg"},
        {{"svg"},"image/svg+xml"},
        {{"ico"},"image/vnd.microsoft.icon"},
        {{"json"},"application/json"},
        {{"png"},"image/png"},
        {{"css"},"text/css"},
        {{"map"},"application/json"},
        {{"js"},"text/javascript"},
        {{"woff2"},"font/woff2"}
    };

    if (const auto it = mineMap.find(extension.toLowerCase()); it != mineMap.end())
    {
        return it->second;
    }

    jassertfalse;
    return "";
}