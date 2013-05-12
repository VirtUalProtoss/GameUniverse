#include "keyListener.h"

using namespace Ogre;
using namespace OIS;

//исполнение KeyListener
keyListener::keyListener() : mEscWasPressed( false ) {
	mKeyboard = 0;
    mCameraTranslateVector = Ogre::Vector3::ZERO;
    mRotScale = 0.0f;
    mCameraYaw = 0.0f;
    mMoveScale = 10;
    mFrontMoving = 0.0f;
    mSideMoving = 0.0f;
    mTopMoving = 0.0f;
}

bool keyListener::keyPressed( const KeyEvent &e ) {
    LogManager::getSingleton().logMessage( "key's been pressed" );

    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectKeyDown(e.key);
    sys.injectChar(e.text);
    
    if ( mKeyboard->isKeyDown(OIS::KC_ESCAPE) ) {
		LogManager::getSingleton().logMessage( "*** ESC: shutdown ***" );
        mShutDown = true;
		return false;
	}
    
    if ( e.key == OIS::KC_LSHIFT )
        mMoveScale *= 10;

    if ( e.key == OIS::KC_A )
        mSideMoving = -mMoveScale;	// Move camera left

    if ( e.key == OIS::KC_D )
        mSideMoving = mMoveScale;	// Move camera RIGHT

    if ( e.key == OIS::KC_UP || e.key == OIS::KC_W )
        mFrontMoving = -mMoveScale;	// Move camera forward

    if ( e.key == OIS::KC_DOWN || e.key == OIS::KC_S )
        mFrontMoving = mMoveScale;	// Move camera backward

    if ( e.key == OIS::KC_PGUP )
        mTopMoving = mMoveScale;	// Move camera up

    if ( e.key == OIS::KC_PGDOWN )
        mTopMoving = -mMoveScale;	// Move camera down

    if ( e.key == OIS::KC_RIGHT )
        mCameraYaw -= mRotScale;

    if ( e.key == OIS::KC_LEFT )
        mCameraYaw += mRotScale;
	
    return true;
}

bool keyListener::keyReleased( const KeyEvent &e ) {
	LogManager::getSingleton().logMessage( "key's been released" );
    CEGUI::System::getSingleton().injectKeyUp(e.key);
    
    if ( e.key == OIS::KC_LSHIFT )
        mMoveScale /= 10;

    if ( e.key == OIS::KC_A || e.key == OIS::KC_D )
        mSideMoving = 0.0f;

    if ( e.key == OIS::KC_UP || e.key == OIS::KC_W || e.key == OIS::KC_DOWN || e.key == OIS::KC_S )
        mFrontMoving = 0.0f;

    if ( e.key == OIS::KC_PGUP || e.key == OIS::KC_PGDOWN )
        mTopMoving = 0.0f;
 
	return true;
}

bool keyListener::frameStarted( const FrameEvent& evt ) {
	mKeyboard->capture();
	return true;
}
