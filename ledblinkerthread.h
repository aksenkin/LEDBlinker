#ifndef LEDBLINKERTHREAD_H
#define LEDBLINKERTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include <QMutex>

/**
 * @brief The LedBlinkerThread class
 */
class LedBlinkerThread : public QThread
{
    Q_OBJECT
public:

    Q_PROPERTY(int dutyCycle READ dutyCycle WRITE setDutyCycle)
    Q_PROPERTY(int duration READ duration WRITE setDuration )
    explicit LedBlinkerThread(QObject *parent = 0);
    void run() Q_DECL_OVERRIDE;

    // dutyCycle getter
    inline int dutyCycle()
    {
        return _dutyCycle;
    }

    inline int duration()
    {
        return _duration;
    }


signals:

public slots:
    // dutyCycle setter
    void setDutyCycle(int newValue);
    void setDuration(int newValue);

private:
    int _dutyCycle;
    int _duration;

public:
    QMutex mutex;
};

#endif // LEDBLINKERTHREAD_H
