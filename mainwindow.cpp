#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "wiringPi.h"


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

    connect(ui->blinkButton, &QPushButton::click, [=](){
        this->onBlinkButton();
    });

    //wiringPiSetup () ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onDutyCycleValueChanged(int newValue)
{
    QString dutyCycleStringVal = QString("%1").arg(newValue, 3);
    ui->dutyCycleValue->setText(dutyCycleStringVal);
}

void MainWindow::onDurationValueChanged(int newValue)
{
    QString durationStringVal = QString("%1").arg(newValue, 3);
    ui->durationValue->setText(durationStringVal);
}

void  MainWindow::runLoopInSeparateThread()
{
    for (;;)
    {
//      digitalWrite (LED, HIGH) ;	// On
//      delayMicroseconds (10000) ;		// mS
//      digitalWrite (LED, LOW) ;	// Off
//      delayMicroseconds (9000) ;
      //TODO: Verify external variable to stop the looping
    }
}

void MainWindow::onBlinkButton()
{


}
