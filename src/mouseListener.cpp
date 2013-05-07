#include "mouseListener.h"

using namespace Ogre;
using namespace OIS;

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

//исполнение MouseListener
mouseListener::mouseListener(){
	mMouse = 0;
}

bool mouseListener::mousePressed( const MouseEvent &e, MouseButtonID id ) {
	LogManager::getSingleton().logMessage( "mousePressed" );
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
	return true;
}

bool mouseListener::mouseReleased( const MouseEvent &e, MouseButtonID id ) {
	LogManager::getSingleton().logMessage( "mouseReleased" );
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
	return true;
}

bool mouseListener::mouseMoved( const MouseEvent &e ) {
	//LogManager::getSingleton().logMessage( "mouseMoved" );
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(e.state.X.rel, e.state.Y.rel);
    // Scroll wheel.
    if (e.state.Z.rel)
        sys.injectMouseWheelChange(e.state.Z.rel / 120.0f);
	return true;
}

bool mouseListener::frameStarted( const FrameEvent& evt ) {
	mMouse->capture();
	return true;
}
