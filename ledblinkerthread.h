#ifndef LEDBLINKERTHREAD_H
#define LEDBLINKERTHREAD_H

#include <QObject>
#include <QThread>

class LedBlinkerThread : public QThread
{
    Q_OBJECT
public:
    Q_PROPERTY(int dutyCycle READ dutyCycle WRITE setDutyCycle);
    explicit LedBlinkerThread(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;

    // dutyCycle getter
    int dutyCycle()
    {
        return _dutyCycle;
    }
    // dutyCycle setter
    void setDutyCycle(int newValue)
    {
        this->_dutyCycle = newValue;
    }
signals:

public slots:

private:
    int _dutyCycle;
    int _duration;
};

#endif // LEDBLINKERTHREAD_H
