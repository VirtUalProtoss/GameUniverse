#include "mouseListener.h"

using namespace Ogre;
using namespace OIS;

//исполнение MouseListener
mouseListener::mouseListener(){
	mMouse = 0;
}

bool mouseListener::mousePressed( const MouseEvent &e, MouseButtonID id ) {
	LogManager::getSingleton().logMessage( "mousePressed" );
	return true;
}

bool mouseListener::mouseReleased( const MouseEvent &e, MouseButtonID id ) {
	LogManager::getSingleton().logMessage( "mouseReleased" );
	return true;
}

bool mouseListener::mouseMoved( const MouseEvent &e ) {
	//LogManager::getSingleton().logMessage( "mouseMoved" );
	return true;
}

bool mouseListener::frameStarted( const FrameEvent& evt ) {
	mMouse->capture();
	return true;
}
