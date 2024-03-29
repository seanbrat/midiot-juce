//
//  NoteGridViewport.cpp
//  Midiot
//
//  Created by Sean Bratnober on 10/19/17.
//
//

#include "NoteGridViewport.hpp"
#include "NoteGridComponent.hpp"

NoteGridViewport::NoteGridViewport(const String& componentName) :
Viewport(componentName),
linkedViewport(NULL),
note_grid_(NULL)
{
}

NoteGridViewport::~NoteGridViewport()
{
}

void NoteGridViewport::visibleAreaChanged(const Rectangle<int>& newVisibleArea)
{
    if (linkedViewport && isCurrentlyScrollingOnDrag())
    {
        linkedViewport->setViewPosition(this->getViewPositionX(), linkedViewport->getViewPositionY());
    }
}

void NoteGridViewport::linkViewport(NoteGridViewport* viewport)
{
    linkedViewport = viewport;
}

void NoteGridViewport::mouseWheelMove(const MouseEvent& e, const MouseWheelDetails& details)
{
    Viewport::mouseWheelMove(e, details);
    
    if (linkedViewport)
    {
        linkedViewport->setViewPosition(this->getViewPositionX(), linkedViewport->getViewPositionY());
    }
}


bool NoteGridViewport::autoScroll(int    mouseX,
                int 	mouseY,
                int 	distanceFromEdge,
                int 	maximumSpeed)
{
    printf("NoteGridViewport::autoScroll\n");
    bool retval = Viewport::autoScroll(mouseX, mouseY, distanceFromEdge, maximumSpeed);
    
    if (linkedViewport)
    {
        linkedViewport->setViewPosition(this->getViewPositionX(), linkedViewport->getViewPositionY());
    }
    
    return retval;
}
