#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#include "ofxKeyMap.h"
#include "ofxCvColorImage.h"
#include "ofxExtras.h"
#include "ofxMouse.h"
#include "ofxTypeConversion.h"
#include "ofxEasySerial.h"
#include "ofxScope.h"
#include "ofxIniSettings.h"

class DisplayObject {
public:
    bool visible;
    int color,bgColor,fillColor,lineColor,lineWidth,lineSize;
    float radius,rotation;
    ofxVec2f position,scale,size;

    void doColor() { ofSetColor(color); }
    void doTranslate() { ofTranslate(position); }
    void doRotate() { ofRotate(rotation); }
    void doScale() { ofScale(scale); }
};

class Markers : public DisplayObject {
public:
    int count;
    float innerRadius,outerRadius;
};

class Clock : public DisplayObject {
public:
    Markers markers;
    DisplayObject h,m,s,ms;
};

class FloatValue {
public:
    float min,max;
    float value;
};

class Scope : public DisplayObject, public ofxScope {
public:
};

//class Tween : public FloatValue {
//public:
//    float toValue,smooth;
//};

class MyMovie : public DisplayObject, public ofVideoPlayer {
public:
    float minSpeed,maxSpeed;
    float speedTween,favSpeed;
    float favPos,pos,oldPos,actualFPS,actualDuration;
    float speedCorrection,beginPos;
    float toSpeed,curSpeed,powMinScale,powMaxScale;
    int blurSteps;
    bool paused;
    string filename;
};

class Serial : public ofxEasySerial {
public:
    bool enabled;
    string port;
    int speed;
};

class Font : public DisplayObject, public ofTrueTypeFont {
public:
    string filename;
    int size;
};

class Image : public DisplayObject, public ofImage {
public:
    string filename;
};

class Meter : public DisplayObject {
public:
    Image arrow,scaler;
    float indicatorScale,indicatorOffset;
};

class testApp : public ofBaseApp{
public:

    void setup();
    void update();
    void draw();
    void keyPressed(int key);

    Scope scope;
    DisplayObject debugText;
    MyMovie movie;
    ofImage img;
    Serial serial;
    Clock clock;
    FloatValue sensor1,sensor2;
    Font font;
    Meter meter;

    int bufPos;
    int fps;
    float mapped;
    int backgroundColor;

    int numSubPositions;
    float* subPositionList;

    ofxMouse mouse;
    ofxKeyMap keys;
	ofxIniSettings ini;
};

#endif
