#include "keyListener.h"

using namespace Ogre;
using namespace OIS;

//исполнение KeyListener
keyListener::keyListener() : mEscWasPressed( false ) {
	mKeyboard = 0;
}

bool keyListener::keyPressed( const KeyEvent &e ) {
	//клавиша нажата
	LogManager::getSingleton().logMessage( "key's been pressed" );
	if ( e.key == KC_ESCAPE ) {
		//этой клавишей был ESC
		LogManager::getSingleton().logMessage( "*** ESC: shutdown ***" );
		mEscWasPressed = true;
	}
	return true;
}

bool keyListener::keyReleased( const KeyEvent &e ) {
	//клавиша отпущена
	LogManager::getSingleton().logMessage( "key's been released" );
	return true;
}

bool keyListener::frameStarted( const FrameEvent& evt ) {
	mKeyboard->capture();
	return !mEscWasPressed;
}
