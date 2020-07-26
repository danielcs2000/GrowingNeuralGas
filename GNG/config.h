
#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <opencv2/highgui.hpp>

// WINDOW SETTINGS

int WITH = 500;
int HEIGHT = 500;

// Hyper Params gng

double EPS_B = 0.05;
double EPS_N =0.005;
int MAX_AGE= 25;
int LAMBDA = 100;
double ALPHA = 0.05;
double BETA = 0.005;
int MAX_NODES = 100;



// GRAPH DISPLAY SETTINGS

//-------Circle---------//
int circleRadio = 4;
cv::Scalar circleColor(0,255,255); // Yellow

//------Line----------//
cv::Scalar lineColor(0,255,255); // Yellow
int lineThickness = 2;







//Util
template<typename T>
struct Position{
    T x;
    T y;
};




#endif