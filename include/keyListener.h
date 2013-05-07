#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <Ogre.h>
#include <OIS.h>

//интерфейс KeyListener
class keyListener : public OIS::KeyListener {
	public:
		keyListener();
		virtual bool keyPressed( const OIS::KeyEvent &e );
		virtual bool keyReleased( const OIS::KeyEvent &e );
		virtual bool frameStarted( const Ogre::FrameEvent& evt );
	protected:
		OIS::Keyboard* mKeyboard;
	private:
		bool mEscWasPressed;
};
#endif //KEYLISTENER_H
