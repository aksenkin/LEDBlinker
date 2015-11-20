#include "mainwindow.h"
#include "ui_mainwindow.h"
#ifdef _LINUX_RASP_PI_
#include "wiringPi.h"
#endif
#include "ledblinkerthread.h"
#include <QDebug>

#define	LED	0

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->dutyCycleSlider, &QSlider::valueChanged, this, &MainWindow::onDutyCycleValueChanged  );
//    QObject::connect(ui->durationSlider, &QSlider::valueChanged, this, &MainWindow::onDurationValueChanged );
    QObject::connect(ui->durationSlider, &QSlider::valueChanged, [=](const int newValue){
        this->onDurationValueChanged(newValue);
    } );

    bool result = QObject::connect(ui->blinkButton, &QPushButton::clicked, [=](){
        this->onBlinkButton();
    });
    qDebug()<<result;
#ifdef _LINUX_RASP_PI_
    wiringPiSetup () ;
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDutyCycleValueChanged(int newValue)
{
    QString dutyCycleStringVal = QString("%1").arg(newValue, 3);
    ui->dutyCycleValue->setText(dutyCycleStringVal);
    _blinkerThread = NULL;
}

void MainWindow::onDurationValueChanged(int newValue)
{
    QString durationStringVal = QString("%1").arg(newValue, 3);
    ui->durationValue->setText(durationStringVal);
}

void  MainWindow::runLoopInSeparateThread()
{
    if(_blinkerThread == NULL){
        _blinkerThread = new LedBlinkerThread(this);
        QObject::connect(ui->dutyCycleSlider, &QSlider::valueChanged, this, [=](int newValue){
              _blinkerThread->setDutyCycle(newValue);
        });
    }
    _blinkerThread->start();
}

void MainWindow::onBlinkButton()
{
    if(_blinkerThread == NULL)
    {
        ui->blinkButton->setText("STOP");
        runLoopInSeparateThread();
    }
    else
    {
        if(_blinkerThread->isRunning())
        {
            _blinkerThread->requestInterruption();
            _blinkerThread->wait();
            ui->blinkButton->setText("BLINK");
        }
        else
        {
            ui->blinkButton->setText("STOP");
            _blinkerThread->start();
            //runLoopInSeparateThread();
        }
    }
}
