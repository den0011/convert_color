#ifndef COLOR_H
#define COLOR_H

//HLS: Hue, Luminance, Saturation
//H: position in the spectrum
//L: color lightness
//S: color saturation

struct color_hsl
{
  double h;
  double s;
  double l;


  color_hsl(double _h = 0, double _s = 0, double _l = 0):
      h(_h), s(_s), l(_l) {}
};


//HSV: Hue, Saturation, Value
//H: position in the spectrum
//S: color saturation
//V: color brightness

struct color_hsv
{
    double h;
    double s;
    double v;


    color_hsv(double _h = 0, double _s = 0, double _v = 0):
        h(_h), s(_s), v(_v) {}
};

//CMYK
//C: Cyan
//M: Magenta
//Y: Yellow
//K: Key

struct color_cmyk
{
    double c;
    double m;
    double y;
    double k;


    color_cmyk(double _c = 0, double _m = 0, double _y = 0, double _k = 0):
        c(_c), m(_m), y(_y), k(_k) {}
};


struct max_min
{
    int max;
    int min;

    max_min(int _max = 0, int _min = 0):
        max(_max), min(_min) {}
};




#endif // COLOR_H
