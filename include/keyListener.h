#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>

//интерфейс KeyListener
class keyListener : public OIS::KeyListener {
	public:
		keyListener();
		virtual bool keyPressed( const OIS::KeyEvent &e );
		virtual bool keyReleased( const OIS::KeyEvent &e );
		virtual bool frameStarted( const Ogre::FrameEvent& evt );
	
    protected:
		OIS::Keyboard* mKeyboard;
        Ogre::Vector3 mCameraTranslateVector;
        bool mShutDown;
        Ogre::Real mFrontMoving;
        Ogre::Real mSideMoving;
        Ogre::Real mTopMoving;
 
	private:
		bool mEscWasPressed;
        Ogre::Real mMoveScale;
        Ogre::Real mRotScale;
        Ogre::Real mCameraYaw;
        
};
#endif //KEYLISTENER_H
