#include "ledblinkerthread.h"
#ifdef _LINUX_RASP_PI_
#include "wiringPi.h"

#define LED 0

#endif



LedBlinkerThread::LedBlinkerThread(QObject *parent) : QThread(parent)
{
    _duration = 10000;
    _dutyCycle = 1;
#ifdef _LINUX_RASP_PI_
    wiringPiSetup () ;
#endif
}


void LedBlinkerThread::run() {

    while (!QThread::currentThread()->isInterruptionRequested())
    {
        //mutex.lock();
#ifdef _LINUX_RASP_PI_

        digitalWrite (LED, HIGH) ;	// On
        delayMicroseconds (_duration*_dutyCycle/100) ;		// *1000/100 uS
        digitalWrite (LED, LOW) ;	// Off
        delayMicroseconds  (_duration*(100-_dutyCycle)*10) ;
#endif
        //mutex.unlock();
    }
}


void LedBlinkerThread::setDutyCycle(int newValue)
{
    // this methos can be run in other thread
    mutex.lock();
    _dutyCycle = newValue;
    qDebug()<<"New duty Cycle value:" << newValue;
    mutex.unlock();
}

void LedBlinkerThread::setDuration(int newValue)
{
    mutex.lock();
    _duration = newValue;
    qDebug()<<"New Duration value:" << newValue;
    mutex.unlock();
}
