#include "frameListener.h"

using namespace Ogre;
using namespace std;
using namespace CEGUI;

frameListener::frameListener( RenderWindow* win, Ogre::Camera* cam ): mWindow( win ), mInputManager( 0 ) {
    mTime = 0;
    LogManager::getSingletonPtr()->logMessage( "*** Initializing OIS ***" );

    //Настройка InputManager
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;

    mWindow->getCustomAttribute( "WINDOW", &windowHnd );
    windowHndStr << windowHnd;
    pl.insert( std::make_pair( std::string( "WINDOW" ), windowHndStr.str() ) );
    
    mDebugOverlay = 0; //OverlayManager::getSingleton().getByName("Core/DebugOverlay");
    mDebugText = "Test";

    mInputManager = OIS::InputManager::createInputSystem( pl );

    //Создание мыши, клавиатуры
    mKeyboard = static_cast<OIS::Keyboard*>( mInputManager->createInputObject( OIS::OISKeyboard, true ) );
    mMouse = static_cast<OIS::Mouse*>( mInputManager->createInputObject( OIS::OISMouse, true ) );
    mKeyboard->setBuffered(true);
    mMouse->setBuffered(true);
    
    int mWidth = mWindow->getWidth();
    int mHeight = mWindow->getHeight();

    if (mMouse) {
        const OIS::MouseState &ms = mMouse->getMouseState();
        ms.width = (int)mWidth;
        ms.height = (int)mHeight;
    }

    mKeyboard->setEventCallback( this );
    mMouse->setEventCallback( this );

    //Set initial mouse clipping size
    windowResized(mWindow);
 
    //Register as a Window listener
    mEventLst = new myWindowEventListener();
    Ogre::WindowEventUtilities::addWindowEventListener(mWindow, mEventLst);
    mShutDown = false;
    mCamera = cam;
    mTimeUntilNextToggle = 0;
    showDebugOverlay(true);
}

frameListener::~frameListener() {
    //Remove ourself as a Window listener
	WindowEventUtilities::removeWindowEventListener(mWindow, mEventLst);
	windowClosed(mWindow);
}

bool frameListener::frameStarted( const FrameEvent& evt ) {
	return true;
    //( keyListener::frameStarted( evt ) && mouseListener::frameStarted( evt ) );
}

bool frameListener::frameRenderingQueued(const Ogre::FrameEvent& evt) {
    if(mWindow->isClosed())
        return false;
 
    if(mShutDown)
        return false;
 
    //Need to capture/update each device
    mKeyboard->capture();
    mMouse->capture();
 
    //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);
    
    Ogre::Vector3 lastMotion = mCameraTranslateVector;

    // ramp up / ramp down speed
    if ( mCameraTranslateVector == Ogre::Vector3::ZERO ) {
        // decay (one third speed)
        mCurrentSpeed -= evt.timeSinceLastFrame * 0.3;
        mCameraTranslateVector = lastMotion;
    } else {
        // ramp up
        mCurrentSpeed += evt.timeSinceLastFrame;
    }

    // Limit motion speed
    if (mCurrentSpeed > 1.0)
        mCurrentSpeed = 1.0;
    if (mCurrentSpeed < 0.0)
        mCurrentSpeed = 0.0;

    mCameraTranslateVector *= mCurrentSpeed;
        
    moveCamera();
 
    return true;
}

bool frameListener::frameEnded(const FrameEvent& evt) {
    updateStats();
    return true;
}

void frameListener::updateStats() {
    // TODO: debug overlay with CEGUI
    static Ogre::String currFps = "Current FPS: ";
    static Ogre::String avgFps = "Average FPS: ";
    static Ogre::String bestFps = "Best FPS: ";
    static Ogre::String worstFps = "Worst FPS: ";
    static Ogre::String tris = "Triangle Count: ";
    static Ogre::String batches = "Batch Count: ";

    // update stats when necessary
    try {
        OverlayElement* guiAvg = OverlayManager::getSingleton().getOverlayElement("Core/AverageFps");
        OverlayElement* guiCurr = OverlayManager::getSingleton().getOverlayElement("Core/CurrFps");
        OverlayElement* guiBest = OverlayManager::getSingleton().getOverlayElement("Core/BestFps");
        OverlayElement* guiWorst = OverlayManager::getSingleton().getOverlayElement("Core/WorstFps");

        const Ogre::RenderTarget::FrameStats& stats = mWindow->getStatistics();
        guiAvg->setCaption(avgFps + StringConverter::toString(stats.avgFPS));
        guiCurr->setCaption(currFps + StringConverter::toString(stats.lastFPS));
        guiBest->setCaption(bestFps + StringConverter::toString(stats.bestFPS)
            +" "+StringConverter::toString(stats.bestFrameTime)+" ms");
        guiWorst->setCaption(worstFps + StringConverter::toString(stats.worstFPS)
            +" "+StringConverter::toString(stats.worstFrameTime)+" ms");

        OverlayElement* guiTris = OverlayManager::getSingleton().getOverlayElement("Core/NumTris");
        guiTris->setCaption(tris + StringConverter::toString(stats.triangleCount));

        OverlayElement* guiBatches = OverlayManager::getSingleton().getOverlayElement("Core/NumBatches");
        guiBatches->setCaption(batches + StringConverter::toString(stats.batchCount));

        OverlayElement* guiDbg = OverlayManager::getSingleton().getOverlayElement("Core/DebugText");
        guiDbg->setCaption(mDebugText);
    }
    catch(...) { /* ignore */ }
}

void frameListener::showDebugOverlay(bool show) {
    // TODO: debug overlay with CEGUI
    if (mDebugOverlay) {
        if (show) {
            LogManager::getSingletonPtr()->logMessage( "Showing debug overlay." );
            mDebugOverlay->show();
        } else {
            mDebugOverlay->hide();
        }
    }
}

//Adjust mouse clipping area
void frameListener::windowResized( RenderWindow* rw ) {
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = mMouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

//Unattach OIS before window shutdown (very important under Linux)
void frameListener::windowClosed( RenderWindow* rw ) {
    //Only close for window that created OIS (the main window in these demos)
    if( rw == mWindow ) {
        if( mInputManager ) {
            mInputManager->destroyInputObject( mMouse );
            mInputManager->destroyInputObject( mKeyboard );
            mInputManager->destroyInputObject( mJoy );

            OIS::InputManager::destroyInputSystem( mInputManager );
            mInputManager = 0;
        }
    }
}

void frameListener::moveCamera() {
    mCameraTranslateVector = Ogre::Vector3::ZERO;
    mCameraTranslateVector.x = mSideMoving;
    mCameraTranslateVector.y = mTopMoving;
    mCameraTranslateVector.z = mFrontMoving;
    mCamera->yaw(mCameraRotX);
    mCamera->pitch(mCameraRotY);
    mCamera->moveRelative(mCameraTranslateVector);
    mCameraRotX = 0;
    mCameraRotY = 0;
}
