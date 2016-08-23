#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "renderarea.h"
#include "define.h"
#include "QTimer"
#include "osil.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    oscope_data adc_data;

private slots:
    void update_osil();
    void try_connect();
private:
    RenderArea *renderArea;
    int voltage;
    QLabel* status;
    int x;
    osil *device;
    QTimer *update_timer;
    QTimer *connect_timer;


    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H
