#include <juce_core/juce_core.h>
#include <juce_events/juce_events.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>

class MainComponent : public juce::AudioAppComponent, public juce::Timer
{
private:
    juce::Label label_;
    double amplitude_ = 0.05;
    double phase_ = 0.0;
    double phaseIncrement_ = 0.0;

    juce::AudioBuffer<float> buffer_{ 2, 44100 };

public:
    MainComponent()
    {
        setSize(200, 100);
        addAndMakeVisible(label_);
        label_.setText("Hello, JUCE!", juce::NotificationType::dontSendNotification);
        setAudioChannels(0, 2); // 0 input channels, 2 output channels
    }

    void timerCallback() override
    {
        auto level = std::sin(phase_);
        auto sample = static_cast<float>(level * amplitude_);
        phase_ += phaseIncrement_;
        if (phase_ >= 2 * juce::MathConstants<double>::pi)
            phase_ -= 2 * juce::MathConstants<double>::pi;
        buffer_.addSample(0, 0, sample);
        buffer_.addSample(1, 0, sample);
    }

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override
    {
        phaseIncrement_ = 440.0 * 2 * juce::MathConstants<double>::pi / sampleRate;
    }
    
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        auto numSamples = bufferToFill.numSamples;
        for (auto i = 0; i < numSamples; ++i)
        {
            auto level = std::sin(phase_);
            auto sample = static_cast<float>(level * amplitude_);
            phase_ += phaseIncrement_;
            if (phase_ >= 2 * juce::MathConstants<double>::pi)
                phase_ -= 2 * juce::MathConstants<double>::pi;
            bufferToFill.buffer->addSample(0, i, sample);
            bufferToFill.buffer->addSample(1, i, sample);
        }
    }

    void releaseResources() override {}

    void paint(juce::Graphics& g) override {}

    void resized() override
    {
        label_.setBounds(getLocalBounds().reduced(10, 10));
    }
};


class SimpleJuceApplication : public juce::JUCEApplication
{
public:
    SimpleJuceApplication() {}

    const juce::String getApplicationName() override
    {
        return "Simple JUCE Application";
    }

    const juce::String getApplicationVersion() override
    {
        return "1.0.0";
    }

    void initialise(const juce::String&) override
    {
        mainWindow_ = std::make_unique<juce::DocumentWindow>(
            getApplicationName(),
            juce::Colours::white,
            juce::DocumentWindow::allButtons);

        mainWindow_->setContentOwned(new MainComponent(), true);

        mainWindow_->setResizable(true, true);
        mainWindow_->centreWithSize(400, 300);
        mainWindow_->setVisible(true);
    }

    void shutdown() override {}

    void systemRequestedQuit() override
    {
        quit();
    }

private:
    std::unique_ptr<juce::DocumentWindow> mainWindow_;
};

START_JUCE_APPLICATION(SimpleJuceApplication)