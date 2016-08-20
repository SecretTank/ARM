#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "renderarea.h"
#include "define.h"
#include "QTimer"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    oscope_data adc_data;

private slots:
    void update_osil();
private:
    RenderArea *renderArea;
    int voltage;
    QLabel* status;
    int x;
    QTimer *update_timer;


    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H
