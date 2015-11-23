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
    ui(new Ui::MainWindow),_blinkerThread(NULL)
{
    ui->setupUi(this);
    QObject::connect(ui->dutyCycleSlider, &QSlider::valueChanged, this, &MainWindow::onDutyCycleValueChanged  );
      QObject::connect(ui->durationSlider, &QSlider::valueChanged, this, &MainWindow::onDurationValueChanged );
//    QObject::connect(ui->durationSlider, &QSlider::valueChanged, [=](const int newValue){
//       this->onDurationValueChanged(newValue);
//    } );
    this->setFixedSize(400, 300);
    ui->dutyCyclelcdNumber->display(ui->dutyCycleSlider->value());
    ui->durationlcdNumber->display(ui->durationSlider->value());

    bool result = QObject::connect(ui->blinkButton, &QPushButton::clicked, [=](){
        this->onBlinkButton();
    });
    qDebug()<<result;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDutyCycleValueChanged(int newValue)
{
  //  QString dutyCycleStringVal = QString("%1").arg(newValue, 3);
  //  ui->dutyCycleValue->setText(dutyCycleStringVal);
    ui->dutyCyclelcdNumber->display(newValue);
}

void MainWindow::onDurationValueChanged(int newValue)
{
   // QString durationStringVal = QString("%1").arg(newValue, 3);
   // ui->durationValue->setText(durationStringVal);
    ui->durationlcdNumber->display(newValue);
}

void  MainWindow::runLoopInSeparateThread()
{
    if(_blinkerThread == NULL){
        _blinkerThread = new LedBlinkerThread(this);
        QObject::connect(ui->dutyCycleSlider, &QSlider::valueChanged, _blinkerThread, &LedBlinkerThread::setDutyCycle);
        QObject::connect(ui->durationSlider, &QSlider::valueChanged, _blinkerThread, &LedBlinkerThread::setDuration);

/* this does not work there is a problem with changing value of datamember inside labda */
//        QObject::connect(ui->dutyCycleSlider, &QSlider::valueChanged, [=](int newValue) mutable {
//            _blinkerThread->setDutyCycle(newValue);
//        });
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
        }
    }
}
