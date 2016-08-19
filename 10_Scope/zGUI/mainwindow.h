#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include "renderarea.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<int> adc_data;

private slots:
    void update_osil();
private:
    RenderArea *renderArea;
    int voltage;
    QLabel* status;
    int x;


    QWidget *mainWidget;
    QVBoxLayout *mainLayout;
};

#endif // MAINWINDOW_H