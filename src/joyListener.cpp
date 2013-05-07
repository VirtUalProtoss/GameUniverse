#include "joyListener.h"

using namespace Ogre;
using namespace OIS;

joyListener::joyListener() {
    mJoy = 0;
}

joyListener::~joyListener() {
    ;
}

bool joyListener::buttonPressed( const OIS::JoyStickEvent &arg, int button ) {
    ;
}
		
/** @remarks Joystick button up event */
bool joyListener::buttonReleased( const OIS::JoyStickEvent &arg, int button ) {
    ;
}

/** @remarks Joystick axis moved event */
bool joyListener::axisMoved( const OIS::JoyStickEvent &arg, int axis ) {
    ;
}

//-- Not so common control events, so are not required --//
//! Joystick Event, and sliderID
bool joyListener::sliderMoved( const OIS::JoyStickEvent &, int index) {
    ;
}

//! Joystick Event, and povID
bool joyListener::povMoved( const OIS::JoyStickEvent &arg, int index) {
    ;
}

//! Joystick Event, and Vector3ID
bool joyListener::vector3Moved( const OIS::JoyStickEvent &arg, int index) {
    ;
}

bool joyListener::frameStarted( const Ogre::FrameEvent& evt ) {
    ;
}
