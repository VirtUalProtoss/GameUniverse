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
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(e.key);
    sys.injectChar(e.text);
	return true;
}

bool keyListener::keyReleased( const KeyEvent &e ) {
	//клавиша отпущена
	LogManager::getSingleton().logMessage( "key's been released" );
    CEGUI::System::getSingleton().injectKeyUp(e.key);
	return true;
}

bool keyListener::frameStarted( const FrameEvent& evt ) {
	mKeyboard->capture();
	return !mEscWasPressed;
}
