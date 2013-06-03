#ifndef _FRAME_LISTENER_
#define _FRAME_LISTENER_

#include <Ogre.h>
//#include <OgreStringConverter.h>
//#include <OgrePrerequisites.h>
#include <OIS.h>
#include <CEGUI.h>
#include <CEGUIRenderer.h>
#include <CEGUI/RendererModules/Ogre/CEGUIOgreRenderer.h>

#include "keyListener.h"
#include "mouseListener.h"
#include "joyListener.h"
#include "myWindowEventListener.h"

#include <cstdio>


class frameListener : public Ogre::FrameListener, public keyListener, public mouseListener, public joyListener {
    public:
        frameListener( Ogre::RenderWindow* win, Ogre::Camera* cam );
        ~frameListener();
        bool frameRenderingQueued(const Ogre::FrameEvent& evt);
        bool frameStarted( const Ogre::FrameEvent& evt );
        void windowResized( Ogre::RenderWindow* rw );
        void windowClosed( Ogre::RenderWindow* rw );
        void initCEGUI();
        void moveCamera();
        void showDebugOverlay(bool show);
        void updateStats();
        bool frameEnded(const Ogre::FrameEvent& evt);
 
    private:
        Ogre::Real mTime;
        Ogre::RenderWindow* mWindow;
        Ogre::Camera* mCamera;
        OIS::InputManager* mInputManager;
        myWindowEventListener* mEventLst;
        Ogre::Real mMoveSpeed;
        Ogre::Degree mRotateSpeed;
        float mMoveScale;
        float mSpeedLimit;
        Ogre::Degree mRotScale;
        // just to stop toggles flipping too fast
        Ogre::Real mTimeUntilNextToggle ;
        Ogre::Real mCurrentSpeed;
        Ogre::Overlay* mDebugOverlay;
        Ogre::String mDebugText;
};

#endif // _FRAME_LISTENER_
