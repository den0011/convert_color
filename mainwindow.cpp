#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    test();

    setWindowTitle(QString("СonvertColor"));
    connect(ui->ResetALL, SIGNAL(clicked ()), this, SLOT(slotResetAll()));
    connect(ui->SelectRGB, SIGNAL(clicked ()), this, SLOT(slotSelect()));

    connect(ui->CalculateHex, SIGNAL(clicked ()), this, SLOT(slotCalculateHex()));
    connect(ui->CalculateRGB, SIGNAL(clicked ()), this, SLOT(slotCalculateRGB()));
    connect(ui->CalculateHSV, SIGNAL(clicked ()), this, SLOT(slotCalculateHSV()));
    connect(ui->CalculateHSL, SIGNAL(clicked ()), this, SLOT(slotCalculateHSL()));
    connect(ui->CalculateCMYK, SIGNAL(clicked ()), this, SLOT(slotCalculateCMYK()));


    QRegExp rx("(?:[0-9a-fA-F]{6},)*[0-9a-fA-F]{0,6}");
    hhValidator = new QRegExpValidator(rx, this);
    ui->lineEditHex->setValidator(hhValidator);
}



void MainWindow::slotCalculateHex()
{
    QString ColorHex = ui->lineEditHex->text();

    bool ok;
    int ColorInt = ColorHex.toInt(&ok,16);

    color_rgb rgb =  HexToRgb(ColorInt);
    setColorRgb(rgb);

    color_hsv hsv = RgbToHsv(rgb.r, rgb.g, rgb.b);
    setColorHSV(hsv);

    color_hsl hsl = RgbToHsl( rgb.r, rgb.g, rgb.b );
    setColorHSL(hsl);

    color_cmyk cmyk = RgbToCmyk(rgb.r, rgb.g, rgb.b);
    setColorCMYK(cmyk);


    setColorPreview();
}

void MainWindow::slotCalculateRGB()
{
    int r = ui->rgbR->value();
    int g = ui->rgbG->value();
    int b = ui->rgbB->value();

    QString hex = RgbToHex(r, g, b);
    setColorHex(hex);

    color_hsv hsv = RgbToHsv(r, g, b);
    setColorHSV(hsv);

    color_hsl hsl = RgbToHsl( r, g, b );
    setColorHSL(hsl);

    color_cmyk cmyk = RgbToCmyk(r, g, b);
    setColorCMYK(cmyk);


    setColorPreview();
}

void MainWindow::slotCalculateHSV()
{
    double h = ui->hsvH->value();
    double s = ui->hsvS->value();
    double v = ui->hsvV->value();

    color_rgb rgb = HsvToRgb(h, s, v);
    setColorRgb(rgb);

    QString hex = RgbToHex(rgb.r, rgb.g, rgb.b);
    setColorHex(hex);

    color_hsl hsl = RgbToHsl( rgb.r, rgb.g, rgb.b );
    setColorHSL(hsl);

    color_cmyk cmyk = RgbToCmyk(rgb.r, rgb.g, rgb.b);
    setColorCMYK(cmyk);



    setColorPreview();
}


void MainWindow::slotCalculateHSL()
{
    double h = ui->hslH->value();
    double s = ui->hslS->value();
    double l = ui->hslL->value();

    color_rgb rgb = HslToRgb(h,  s,  l);
    setColorRgb(rgb);

    color_hsv hsv = RgbToHsv(rgb.r, rgb.g, rgb.b);
    setColorHSV(hsv);

    QString hex = RgbToHex(rgb.r, rgb.g, rgb.b);
    setColorHex(hex);

    color_cmyk cmyk = RgbToCmyk(rgb.r, rgb.g, rgb.b);
    setColorCMYK(cmyk);



    setColorPreview();
}

void MainWindow::slotCalculateCMYK()
{
   double c = ui->cmykC->value();
   double m = ui->cmykM->value();
   double y = ui->cmykY->value();
   double k = ui->cmykK->value();

   color_rgb rgb = CmykToRgb (c, m, y, k);
   setColorRgb(rgb);


   QString hex = RgbToHex(rgb.r, rgb.g, rgb.b);
   setColorHex(hex);

   color_hsv hsv = RgbToHsv(rgb.r, rgb.g, rgb.b);
   setColorHSV(hsv);

   color_hsl hsl = RgbToHsl( rgb.r, rgb.g, rgb.b );
   setColorHSL(hsl);

   color_cmyk cmyk = RgbToCmyk(rgb.r, rgb.g, rgb.b);
   setColorCMYK(cmyk);


   setColorPreview();

}


void MainWindow::setColorCMYK(color_cmyk cmyk)
{
    ui->cmykC->setValue(cmyk.c);
    ui->cmykM->setValue(cmyk.m);
    ui->cmykY->setValue(cmyk.y);
    ui->cmykK->setValue(cmyk.k);
}

void MainWindow::setColorRgb(color_rgb rgb)
{
    ui->rgbR->setValue(rgb.r);
    ui->rgbG->setValue(rgb.g);
    ui->rgbB->setValue(rgb.b);
}



void MainWindow::setColorHSV(color_hsv hsv)
{
    ui->hsvH->setValue(hsv.h);
    ui->hsvS->setValue(hsv.s);
    ui->hsvV->setValue(hsv.v);
}


void MainWindow::setColorHex(QString hex)
{
    ui->lineEditHex->setText(hex);
}


void MainWindow::setColorHSL(color_hsl hsl)
{
    ui->hslH->setValue(hsl.h);
    ui->hslS->setValue(hsl.s);
    ui->hslL->setValue(hsl.l);
}


void MainWindow::slotResetAll()
{
    ui->lineEditHex->setText("000000");
    ui->rgbR->setValue(0);
    ui->rgbG->setValue(0);
    ui->rgbB->setValue(0);
    ui->hsvH->setValue(0);
    ui->hsvS->setValue(0);
    ui->hsvV->setValue(0);
    ui->hslH->setValue(0);
    ui->hslS->setValue(0);
    ui->hslL->setValue(0);
    ui->cmykC->setValue(0);
    ui->cmykM->setValue(0);
    ui->cmykY->setValue(0);
    ui->cmykK->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::setColorPreview()
{
    int r = ui->rgbR->value();
    int g = ui->rgbG->value();
    int b = ui->rgbB->value();

    QPalette Pal(palette());
    Pal.setColor(QPalette::Button, QColor(r,g,b));
    ui->pBColorSet->setAutoFillBackground(true);
    ui->pBColorSet->setPalette(Pal);
    update();
}

void MainWindow::slotSelect()
{
    colorDialog = new QColorDialog(this);

    colorDialog->setCurrentColor(QColor(ui->rgbR->value(),ui->rgbG->value(),ui->rgbB->value()));
    colorDialog->exec();
    QColor color = colorDialog->selectedColor();
    ui->rgbR->setValue(color.red());
    ui->rgbG->setValue(color.green());
    ui->rgbB->setValue(color.blue());

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



QString MainWindow::RgbToHex(int r, int g, int b)
{
    int temp =   ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);;
    QString hex  = QString("%1").arg(temp, 6, 16, QChar('0'));
    return hex;

}


color_rgb MainWindow::CmykToRgb(float c, float m, float y, float k) {
    unsigned char r = (unsigned char)(255 * (1 - c/100.0f) * (1 - k/100.0f));
    unsigned char g = (unsigned char)(255 * (1 - m/100.0f) * (1 - k/100.0f));
    unsigned char b = (unsigned char)(255 * (1 - y/100.0f) * (1 - k/100.0f));

    qDebug() << r << g << b;

    return color_rgb(r,g,b);
}





color_rgb MainWindow::HsvToRgb(float H, float S,float V){

    float s = S/100.0f;
    float v = V/100.0f;
    float C = s*v;
    float X = C*(1.0f-abs(fmod(H/60.0f, 2.0f)-1.0f));
    float m = v-C;
    float r,g,b;

    if(H >= 0 && H < 60){
        r = C; g = X; b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X; g = C; b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0; g = C; b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0; g = X; b = C;
    }
    else if(H >= 240 && H < 300){
        r = X; g = 0; b = C;
    }
    else{
        r = C; g = 0; b = X;
    }
    unsigned char R = (r+m) * 255.0f;
    unsigned char G = (g+m) * 255.0f;
    unsigned char B = (b+m) * 255.0f;

    qDebug() << R << G << B;

    return color_rgb(R,G,B);
}

float MainWindow::HueToRgb(float v1, float v2, float vH) {
    if (vH < 0)
        vH += 1;

    if (vH > 1)
        vH -= 1;

    if ((6.0f * vH) < 1)
        return (v1 + (v2 - v1) * 6.0f * vH);

    if ((2.0f * vH) < 1)
        return v2;

    if ((3.0f * vH) < 2)
        return (v1 + (v2 - v1) * ((2.0f / 3.0f) - vH) * 6.0f);

    return v1;
}

color_rgb MainWindow::HslToRgb(float h, float s, float l) {
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;

    float H = (float) h/360.0f;
    float S = (float) s/100.0f;
    float L = (float) l/100.0f;


    if (S == 0)
    {
        r = g = b = (unsigned char)(L * 255.0f);
    }
    else
    {
        float v1, v2;
        float hue = (float)H / 360.0f;


        v2 = (L < 0.5) ? (L * (1.0f + S)) : ((L + S) - (L * S));
        v1 = 2 * L - v2;

        r = (unsigned char)(255.0f * HueToRgb(v1, v2, hue + (1.0f / 3.0f)));
        g = (unsigned char)(255.0f * HueToRgb(v1, v2, hue));
        b = (unsigned char)(255.0f * HueToRgb(v1, v2, hue - (1.0f / 3.0f)));
    }

    qDebug() << r << g << b;

    return color_rgb (r,g,b);

}



color_rgb MainWindow::HexToRgb(int hexValue)
{

    unsigned char r = ((hexValue >> 16) & 0xFF);
    unsigned char g = ((hexValue >> 8) & 0xFF);
    unsigned char b = ((hexValue) & 0xFF) ;


    qDebug() << r << g << b;


    return color_rgb(r,g,b);
}

void MainWindow::test()
{
    /*
    RgbToHsv(129, 88, 47);
    qDebug() <<  RgbToHex(0, 0, 255);
    RgbToCmyk(234, 45, 55);

    CmykToRgb(12, 3, 0, 39);

    int hexValue = 0;
    QString h = "#89979C";

    bool ok;
    QString ColorHex=h.remove('#');

    int num = std::stoi(ColorHex.toStdString(), 0, 16);
  //  int ColorInt = ColorHex.toInt(&ok,16);
    int ColorInt = ColorHex.toInt(&ok,16);


    int r2 = num / 0x10000;
    int g4 = (num / 0x100) % 0x100;
    int b5 = num % 0x100;
      qDebug() << r2 << g4 << b5;


    HexToRgb(ColorInt);


    QColor color1;
    color1.setNamedColor(h);

    int r,g,b;
    color1.getRgb(&r,&g,&b);

    qDebug() << r << g << b;


    HSVtoRGB(45,34,3);


    HSLToRGB(30,17,2  );

    */
}


