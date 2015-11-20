#include "ledblinkerthread.h"
#ifdef _LINUX_RASP_PI_
#include "wiringPi.h"
#endif

LedBlinkerThread::LedBlinkerThread(QObject *parent) : QThread(parent)
{
    _duration = 10000;
}


void LedBlinkerThread::run() {

    for (;;)
    {
        if ( QThread::currentThread()->isInterruptionRequested() )
            {
                    return;
            }
#ifndef _MAC_BUILD_
        digitalWrite (LED, HIGH) ;	// On
        delayMicroseconds (_duration*_dutyCycle/100) ;		// mS
        digitalWrite (LED, LOW) ;	// Off
        delayMicroseconds (_duration*(100-_dutyCycle)/100) ;
#endif
    }

}
