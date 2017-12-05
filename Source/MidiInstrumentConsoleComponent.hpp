//
//  MidiInstrumentConsoleComponent.hpp
//  Midiot
//
//  Created by Sean Bratnober on 12/4/17.
//
//

#ifndef MidiInstrumentConsoleComponent_hpp
#define MidiInstrumentConsoleComponent_hpp

#include "../JuceLibraryCode/JuceHeader.h"

#include "DemoUtilities.h"

#include "MidiInstrumentEditorComponent.hpp"
#include "StepGridComponent.hpp"
#include "GraphicsComponentBase.hpp"

#include <vector>

#include <stdio.h>


#define USE_STEP_GRID       0

using std::vector;
using std::pair;

class MidiInstrumentConsoleComponent  : public Component,
private Button::Listener,
private ComboBox::Listener,
private MidiInputCallback,
private MidiKeyboardStateListener
{
public:
    MidiInstrumentConsoleComponent();
    ~MidiInstrumentConsoleComponent();
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
    // This is used to dispach an incoming message to the message thread
    class IncomingMessageCallback   : public CallbackMessage
    {
    public:
        IncomingMessageCallback (MidiInstrumentConsoleComponent* o, const MidiMessage& m, const String& s)
        : owner (o), message (m), source (s)
        {}
        
        void messageCallback() override
        {
            if (owner != nullptr)
                owner->addMessageToList (message, source);
                }
        
        Component::SafePointer<MidiInstrumentConsoleComponent> owner;
        MidiMessage message;
        String source;
    };
    
    
private:
    static String getMidiMessageDescription (const MidiMessage& m);
    
    void logMessage (const String& m);
    
    /** Starts listening to a MIDI input device, enabling it if necessary. */
    void setMidiInput (int index);
    
    /** Starts listening to a MIDI output device, enabling it if necessary. */
    void setMidiOutput (int index);
    
    void buttonClicked (Button* button) override;
    void comboBoxChanged (ComboBox* box) override;
    
    // These methods handle callbacks from the midi device + on-screen keyboard..
    void handleIncomingMidiMessage (MidiInput* source, const MidiMessage& message) override;
    void handleNoteOn (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff (MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override;
    
    void postMessageToList (const MidiMessage& message, const String& source);
    void addMessageToList (const MidiMessage& message, const String& source);
    
    //==============================================================================
    AudioDeviceManager deviceManager;           // [1]
    ComboBox midiInputList;                     // [2]
    Label midiInputListLabel;
    int lastInputIndex;                         // [3]
    bool isAddingFromMidiInput;                 // [4]
    
    MidiKeyboardState keyboardState;            // [5]
    MidiKeyboardComponent keyboardComponent;    // [6]
    
    ComboBox midiOutputList;
    Label midiOutputListLabel;
    int lastOutputIndex;
    MidiOutput *midiOutputDevice;
    
    TextEditor midiMessagesBox;
    double startTime;
    
    TextButton sysexDataDumpButton;
    Label sysexDataDumpLabel;
    
    TextButton sysexDataIdButton;
    Label sysexDataIdLabel;
    
    TextButton sysexDataPatchDumpButton;
    Label sysexDataPatchDumpLabel;
    
    TextButton readMidiFileButton;
    Label testLabel;
    
    StepGridComponent step_grid_component;
    MidiInstrumentEditorComponent note_grid_editor;
    
    OwnedArray<TextButton> gridButtons;
    
    MidiFile inputMidiFile;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidiInstrumentConsoleComponent);
};


#endif /* MidiInstrumentConsoleComponent_hpp */
