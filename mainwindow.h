#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class LedBlinkerThread;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void runLoopInSeparateThread();

private:
    Ui::MainWindow *ui;
    LedBlinkerThread* _blinkerThread;

private slots:
    void onDutyCycleValueChanged(int newValue);
    void onDurationValueChanged(int newValue);
    void onBlinkButton();

};

#endif // MAINWINDOW_H
