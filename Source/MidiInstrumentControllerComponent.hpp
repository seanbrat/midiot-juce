//
//  MidiInstrumentControllerComponent.hpp
//  Midiot
//
//  Created by Sean Bratnober on 10/16/17.
//
//

#ifndef MidiInstrumentControllerComponent_hpp
#define MidiInstrumentControllerComponent_hpp

#include <stdio.h>


#include <queue>
#include <vector>

#include "GraphicsComponentBase.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

#include "NoteGridProperties.hpp"
#include "MidiClockUtilities.hpp"

using std::vector;

class NoteGridComponent;
class NoteGridViewport;
class NoteGridRulerComponent;

//==============================================================================
class MidiInstrumentControllerComponent  : public GraphicsComponentBase
{
public:
    enum GridResolution {
        Off = 0,
        ThirtySecondNote,
        SixteenthNote,
        EighthNote,
        QuarterNote,
        HalfNote,
        OneBar,
        TwoBar,
        FourBar,
        EightBar
    };
    
    
    MidiInstrumentControllerComponent ();
    ~MidiInstrumentControllerComponent();
    
    void resized() override;
    void mouseDrag(const MouseEvent& e) override;
    void mouseMove(const MouseEvent& e) override;
    void mouseUp (const MouseEvent& e) override;
    bool mouseGridStepPosition(int &x, int &y);
    void drawComponent (Graphics& g) override;
    
private:

};





#endif /* MidiInstrumentControllerComponent_hpp */