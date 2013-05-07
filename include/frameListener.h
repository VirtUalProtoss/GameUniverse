#ifndef _FRAME_LISTENER_
#define _FRAME_LISTENER_

#include <Ogre.h>
#include <OIS.h>
#include <CEGUI.h>
#include <CEGUIRenderer.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "keyListener.h"
#include "mouseListener.h"
#include "joyListener.h"


class frameListener : public Ogre::FrameListener, public keyListener, public mouseListener, public joyListener {
    public:
        frameListener( Ogre::RenderWindow* win );
        bool frameStarted( const Ogre::FrameEvent& evt );
        void windowResized( Ogre::RenderWindow* rw );
        void windowClosed( Ogre::RenderWindow* rw );
        void initCEGUI();
    private:
        Ogre::Real mTime;
        Ogre::RenderWindow* mWindow;

        OIS::InputManager* mInputManager;
};

#endif // _FRAME_LISTENER_
