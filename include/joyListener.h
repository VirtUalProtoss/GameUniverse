/* 
 * File:   joyListener.h
 * Author: virtual
 *
 * Created on 7 Май 2013 г., 13:49
 */

#ifndef JOYLISTENER_H
#define	JOYLISTENER_H

#include <Ogre.h>
#include <OIS.h>

//интерфейс MouseListener
class joyListener : 	public OIS::JoyStickListener {
	public:
		joyListener();
        
        ~joyListener();
        
		/** @remarks Joystick button down event */
		bool buttonPressed( const OIS::JoyStickEvent &arg, int button );
		
		/** @remarks Joystick button up event */
		bool buttonReleased( const OIS::JoyStickEvent &arg, int button );

		/** @remarks Joystick axis moved event */
		bool axisMoved( const OIS::JoyStickEvent &arg, int axis );

		//-- Not so common control events, so are not required --//
		//! Joystick Event, and sliderID
		bool sliderMoved( const OIS::JoyStickEvent &, int index);
		
		//! Joystick Event, and povID
		bool povMoved( const OIS::JoyStickEvent &arg, int index);

		//! Joystick Event, and Vector3ID
		bool vector3Moved( const OIS::JoyStickEvent &arg, int index);

		bool frameStarted( const Ogre::FrameEvent& evt );
	protected:
		OIS::JoyStick* mJoy;
};

#endif	/* JOYLISTENER_H */
