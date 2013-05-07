/* 
 * File:   myWindowEventListener.h
 * Author: virtual
 *
 * Created on 7 Май 2013 г., 16:10
 */

#include <Ogre.h>

#ifndef MYWINDOWEVENTLISTENER_H
#define	MYWINDOWEVENTLISTENER_H

class myWindowEventListener: public Ogre::WindowEventListener {
public:
    myWindowEventListener();
    myWindowEventListener(const myWindowEventListener& orig);
    virtual ~myWindowEventListener();
private:

};

#endif	/* MYWINDOWEVENTLISTENER_H */

