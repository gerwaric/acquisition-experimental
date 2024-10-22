#pragma once

#include <QMainWindow>

class Acquisition;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(Acquisition& acquisition);
private:
    Acquisition& m_acquisition;
};