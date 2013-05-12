#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>

//интерфейс MouseListener
class mouseListener : 	public OIS::MouseListener {
	public:
		mouseListener();
		virtual bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		virtual bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id );
		virtual bool mouseMoved( const OIS::MouseEvent &e );
		virtual bool frameStarted( const Ogre::FrameEvent& evt );
 
	protected:
		OIS::Mouse* mMouse;
        Ogre::Radian mCameraRotX;
        Ogre::Radian mCameraRotY;
};

#endif // MOUSELISTENER_H
