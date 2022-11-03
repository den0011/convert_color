#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QDebug>
#include <math.h>
#include <QColorDialog>
#include <QRegExpValidator>

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

    QColorDialog *colorDialog;
    QRegExpValidator *hhValidator;


    void test();



    QString RgbToHex(int r, int g, int b);
    color_hsv RgbToHsv(float r, float g, float b);
    color_hsl RgbToHsl( float r, float g, float b );
    color_cmyk RgbToCmyk(float red, float green, float blue);


    color_rgb CmykToRgb (float c, float m, float y, float k);
    color_rgb HexToRgb(int hexValue);
    color_rgb HsvToRgb(float H, float S,float V);
    color_rgb HslToRgb(float h, float s, float l);
    float HueToRgb(float v1, float v2, float vH);

    void setColorPreview();
    void setColorRgb(color_rgb);
    void setColorHex(QString);
    void setColorHSV(color_hsv);
    void setColorHSL(color_hsl);
    void setColorCMYK(color_cmyk);


private slots:
    void slotSelect();
    void slotResetAll();
    void slotCalculateHex();
    void slotCalculateRGB();
    void slotCalculateHSV();
    void slotCalculateHSL();
    void slotCalculateCMYK();




};

#endif // MAINWINDOW_H
