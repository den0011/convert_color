#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test();

    setWindowTitle(QString("Сonvert"));
    connect(ui->pBCalculate, SIGNAL(clicked ()), this, SLOT(calculate()));
    connect(ui->pBSelect, SIGNAL(clicked ()), this, SLOT(select()));
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::select()
{
    colorDialog = new QColorDialog(this);

    colorDialog->setCurrentColor(QColor(ui->sBR->value(),ui->sBG->value(),ui->sBB->value()));
    colorDialog->exec();
    QColor color = colorDialog->selectedColor();
    ui->sBR->setValue(color.red());
    ui->sBG->setValue(color.green());
    ui->sBB->setValue(color.blue());

    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, QColor(color.red(),color.green(),color.blue()));
    ui->pBColorSet->setAutoFillBackground(true);
    ui->pBColorSet->setPalette(Pal);
    update();
}



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wconversion"
//#pragma GCC diagnostic ignored "-Wsometimes-uninitialized"

color_cmyk MainWindow::RgbToCmyk(float r, float g, float b)
{

   float cmyk_scale = 100.0;

   if (r == 0.0 && g == 0.0 && b == 0.0)  {
    return color_cmyk(0, 0, 0, 100);
 }

          float dr = r   / 255.0f;
          float dg = g / 255.0f;
          float db = b  / 255.0f;
          float k = 1 - qMax(qMax(dr, dg), db);
          float c = (1 - dr - k) / (1 - k);
          float m = (1 - dg - k) / (1 - k);
          float y = (1 - db - k) / (1 - k);


      qDebug () << c*cmyk_scale<< m*cmyk_scale<< y*cmyk_scale<< k*cmyk_scale;

      return color_cmyk(c*cmyk_scale, m*cmyk_scale, y*cmyk_scale, k*cmyk_scale);
}



color_hsv MainWindow::RgbToHsv(float r, float g, float b) {

    float h=0, s=0, v=0;

    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;


    float cmax = qMax(r,qMax(g,b));
    float cmin = qMin(r,qMin(g,b));

    float diff = cmax-cmin;

    if (cmax == cmin)
        h = 0;

    else if (cmax == r)
        h = fmod((60 * ((g - b) / diff) + 360), 360.0);

    else if (cmax == g)
        h = fmod((60 * ((b - r) / diff) + 120), 360.0);

    else if (cmax == b)
        h = fmod((60 * ((r - g) / diff) + 240), 360.0);


    if (cmax == 0)
        s = 0;
    else
        s = (diff / cmax) * 100;

    v = cmax * 100;
    printf("h s v=(%f, %f, %f)", h, s, v );
    qDebug() << h << s << v;


    return color_hsv (h,s,v);
}




 color_hsl MainWindow::RgbToHsl( float r, float g, float b )
 {
     color_hsl hls;

     r /= 255.0f;
     g /= 255.0f;
     b /= 255.0f;

     float cmax = qMax(r,qMax(g,b));
     float cmin = qMin(r,qMin(g,b));


     double L = 0.0f;
     double S = 0.0f;
     double H = 0.0f;

     L = (cmax + cmin)/2.0f;

     if(cmax == cmin)
     {
         S = 0.0f;
         H = 0.0f;
     }
     else
     {
         if(L < .50)
         {
             S = (cmax - cmin)/(cmax + cmin);
         }
         else
         {
             S = (cmax - cmin)/(2.0f - cmax - cmin);
         }
         if(cmax == r)
         {
             H = (g - b)/(cmax - cmin);
         }
         if(cmax == g)
         {
             H = 2.0f + (b - r)/(cmax - cmin);
         }
         if(cmax == b)
         {
             H = 4.0f + (r - g)/(cmax - cmin);
         }
     }


     hls.s = (S*100.0f);
     hls.l = (L*100.0f);

     H = H*60.0f;

     if(H < 0)
         H += 360.0f;

     hls.h = H;

     return hls;
 }


#pragma GCC diagnostic pop

void MainWindow::calculate()
{
    int r = ui->sBR->value();
    int g = ui->sBG->value();
    int b = ui->sBB->value();

    color_hsv hsv = RgbToHsv(r, g, b);


    color_cmyk cmyk = RgbToCmyk(r, g, b);


    color_hsl hls = RgbToHsl( r, g, b );

    ui->textEdit->append(QString("(RGB) Red(R) = %1 Green(G) = %2 Blue(B) = %3")
                         .arg(r)
                         .arg(g)
                         .arg(b));

    ui->textEdit->append((QString("(HSV) Hue (H) = %1° Saturation (S) = %2% Value (V) = %3%")
                          .arg(hsv.h)
                          .arg(hsv.s)
                          .arg(hsv.v)));


    ui->textEdit->append((QString("(CMYK) Cyan(C) = %1% Magenta (M) = %2% Yellow (Y) = %3% Black (key)= %4%")
                          .arg(cmyk.c)
                          .arg(cmyk.m)
                          .arg(cmyk.y)
                          .arg(cmyk.k)));

    ui->textEdit->append((QString("(HSL) Hue (H) = %1° Saturation (S) = %2% Lightness (L) = %3%")
                          .arg(hls.h)
                          .arg(hls.s)
                          .arg(hls.l)));

    ui->textEdit->append(QString("Hex = %1").arg(RgbToHex(r,g,b)));

    ui->textEdit->append(QString());


    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, QColor(r,g,b));
    ui->pBColorSet->setAutoFillBackground(true);
    ui->pBColorSet->setPalette(Pal);
    update();
}

QString MainWindow::RgbToHex(int r, int g, int b)
{
    int temp =   ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);;
    QString hex  = QString("#%1").arg(temp, 6, 16, QChar('0'));
    return hex;
}



void MainWindow::test()
{


    RgbToHsv(129, 88, 47);
    qDebug() <<  RgbToHex(0, 0, 255);
    RgbToCmyk(234, 45, 55);




}


