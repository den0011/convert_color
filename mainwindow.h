#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QDebug>
#include <math.h>
#include <QColorDialog>

#include "color.h"



namespace Ui {
class MainWindow;
}




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void test();


    color_hsv RgbToHsv(float r, float g, float b);

    QColorDialog *colorDialog;

    QString RgbToHex(int r, int g, int b);
    color_cmyk RgbToCmyk(float red, float green, float blue);
    color_hsl RgbToHsl( float r, float g, float b );


private slots:
    void calculate();
    void select();


};

#endif // MAINWINDOW_H
