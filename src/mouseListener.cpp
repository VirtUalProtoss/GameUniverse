#include "mouseListener.h"

using namespace Ogre;
using namespace OIS;

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID) {
    switch (buttonID) {
        case OIS::MB_Left:
            return CEGUI::LeftButton;

        case OIS::MB_Right:
            return CEGUI::RightButton;

        case OIS::MB_Middle:
            return CEGUI::MiddleButton;

        default:
            return CEGUI::LeftButton;
    }
}

mouseListener::mouseListener(){
	mMouse = 0;
    mCameraRotX = 0.0f;
    mCameraRotY = 0.0f;
}

bool mouseListener::mousePressed( const MouseEvent &e, MouseButtonID id ) {
    LogManager::getSingleton().logMessage( "mousePressed" );
    CEGUI::System::getSingleton().injectMouseButtonDown(convertButton(id));
    return true;
}

bool mouseListener::mouseReleased( const MouseEvent &e, MouseButtonID id ) {
    LogManager::getSingleton().logMessage( "mouseReleased" );
    CEGUI::System::getSingleton().injectMouseButtonUp(convertButton(id));
    return true;
}

bool mouseListener::mouseMoved( const MouseEvent &e ) {
    //LogManager::getSingleton().logMessage( "mouseMoved" );
    CEGUI::System &sys = CEGUI::System::getSingleton();
    sys.injectMouseMove(e.state.X.rel, e.state.Y.rel);
    // Scroll wheel.
    if (e.state.Z.rel)
        sys.injectMouseWheelChange(e.state.Z.rel / 120.0f);
    
    const OIS::MouseState &ms = mMouse->getMouseState();
    if( ms.buttonDown( OIS::MB_Right ) ) {
        //mTranslateVector.x += ms.X.rel * 0.13;
        //mTranslateVector.y -= ms.Y.rel * 0.13;
    //} else {
        mCameraRotX = Degree(-ms.X.rel * 0.13);
        mCameraRotY = Degree(-ms.Y.rel * 0.13);
    }
    return true;
}

bool mouseListener::frameStarted( const FrameEvent& evt ) {
    mMouse->capture();
    return true;
}
