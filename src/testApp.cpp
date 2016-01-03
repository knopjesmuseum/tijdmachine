#include "testApp.h"
#include "conio.h" //for _getch
#include "ofxOpenCvExtra.h"

//--------------------------------------------------------------
void testApp::setup(){
    cout << "loading settings.ini..." << endl;
    ini.load("settings.ini");
    ini.outputFilename = "settings.ini";
    string profile = ini.get("profile",(string)"");
    if (profile!="") ini.load(profile+".ini",false);

    movie.filename = ini.get("movie.filename",(string)"");
    if (movie.filename=="") die("undefined movie filename");
    cout << "loading movie: " << movie.filename << endl;
    if (!ofFileExists(movie.filename)) die("movie file not found: " + movie.filename);
    movie.loadMovie(movie.filename);
    movie.setPaused(true);
	cout << "movie loaded..." << endl;

    movie.actualFPS=movie.getTotalNumFrames()/movie.getDuration();
    movie.actualDuration = movie.getTotalNumFrames()/movie.actualFPS;
    cout << "fps from movie: " << movie.actualFPS << endl;
    cout << "duration from movie: " << movie.getDuration() << endl;

    if (ini.has("movie.fps")) {
        movie.actualFPS=ini.get("movie.fps",movie.actualFPS);
        movie.actualDuration = movie.getTotalNumFrames()/movie.actualFPS;
        movie.speedCorrection = movie.actualFPS/(movie.getTotalNumFrames()/movie.getDuration());
        cout << "correction from ini file: fps changed to: " << movie.actualFPS << endl;
        cout << "duration changed to " << movie.actualDuration << endl;
    }

    img.allocate(movie.width,movie.height,OF_IMAGE_COLOR);
    img.setAnchorPercent(.5,.5);

    backgroundColor = ini.get("backgroundColor",0);
    fps = ini.get("frameRate",100);
	ofSetFrameRate(fps);

	movie.toSpeed = ini.get("movie.speed",1.0f);;
	movie.minSpeed = ini.get("movie.minSpeed",.001f);;
	movie.maxSpeed = ini.get("movie.maxSpeed",100.0f);;
	movie.favPos = ini.get("movie.favPos",0.0f);;
    movie.beginPos = ini.get("movie.beginPos",0.0f);
	movie.pos = movie.beginPos;
	movie.color = ini.get("movie.color",0xffffff);
	movie.position = ini.get("movie.position",ofxVec2f(0,0));

    movie.scale = ini.get("movie.scale",1.0f);
    movie.speedTween = ini.get("movie.speedTween",.05f);
    movie.favSpeed = ini.get("movie.favSpeed",1);
    movie.rotation = ini.get("movie.rotation",180);
    movie.position = ini.get("movie.position",ofxVec2f(0,0));
    movie.powMinScale = log10f(movie.minSpeed);
    movie.powMaxScale = log10f(movie.maxSpeed);

    scope.position = ini.get("scope.position",ofxVec2f(0,0));
    scope.setSize(400,150);
    scope.addWatch(sensor2.value,0x0000ff,sensor2.min,sensor2.max); //blauwe!

	serial.enabled = ini.get("serial.enabled",true);
    sensor1.min = ini.get("sensor1.min",0);
    sensor1.max = ini.get("sensor1.max",1024);
    sensor2.min = ini.get("sensor2.min",0);
    sensor2.max = ini.get("sensor2.max",1024);

    meter.bgColor = ini.get("meter.bgColor",0x000000);
    meter.fillColor = ini.get("meter.fillColor",0xff0000);
    meter.position = ini.get("meter.position",ofxVec2f(0,0));
    meter.size = ini.get("meter.size",ofxVec2f(100,100));
    meter.scale = ini.get("meter.scale",ofxVec2f(1,1));
    meter.visible = ini.get("meter.visible",true);

    meter.position = ini.get("meter.position",ofxVec2f(0,0));
    meter.rotation = ini.get("meter.rotation",0);
    meter.scale = ini.get("meter.scale",ofxVec2f(1,1));

    meter.indicatorScale = ini.get("meter.indicatorScale",60);
    meter.indicatorOffset = ini.get("meter.indicatorOffset",-38);

    meter.arrow.filename = ini.get("meter.arrow.filename",(string)"arrow.png");
    meter.arrow.loadImage(meter.arrow.filename);
    meter.arrow.position = ini.get("meter.arrow.position",ofxVec2f(0,0));
    meter.arrow.rotation = ini.get("meter.arrow.rotation",0);
    meter.arrow.color = ini.get("meter.arrow.color",0xffffff);
    meter.arrow.scale = ini.get("meter.arrow.scale",ofxVec2f(1,1));
    meter.arrow.visible = ini.get("meter.arrow.visible",true);
    meter.arrow.setAnchorPercent(.5,.5);

    meter.scaler.filename = ini.get("meter.scaler.filename",(string)"scale1.png");
    meter.scaler.loadImage(meter.scaler.filename);
    meter.scaler.position = ini.get("meter.scaler.position",ofxVec2f(0,0));
    meter.scaler.rotation = ini.get("meter.scaler.rotation",0);
    meter.scaler.color = ini.get("meter.scaler.color",0xffffff);
    meter.scaler.scale = ini.get("meter.scaler.scale",ofxVec2f(1,1));
    meter.scaler.visible = ini.get("meter.scaler.visible",true);
    meter.scaler.setAnchorPercent(.5,.5);

    clock.lineWidth = ini.get("clock.lineWidth",1);
    clock.visible = ini.get("clock.visible",true);
    clock.position = ini.get("clock.position",ofxVec2f(0,0));
    clock.scale = ini.get("clock.scale",ofxVec2f(1,1));
    clock.radius = ini.get("clock.radius",100);
    clock.color = ini.get("clock.color",0xffffff);

    clock.markers.color = ini.get("clock.markers.color",0xffffff);
    clock.markers.innerRadius = ini.get("clock.markers.innerRadius",40);
    clock.markers.outerRadius = ini.get("clock.markers.outerRadius",50);
    clock.markers.lineWidth = ini.get("clock.markers.lineWidth",1);
    clock.markers.count = ini.get("clock.markers.count",12);

    clock.h.color = ini.get("clock.h.color",0xffffff);
    clock.m.color = ini.get("clock.m.color",0xffffff);
    clock.s.color = ini.get("clock.s.color",0xffffff);
    clock.ms.color = ini.get("clock.ms.color",0xffffff);

    clock.h.lineWidth = ini.get("clock.h.lineWidth",1);
    clock.m.lineWidth = ini.get("clock.m.lineWidth",1);
    clock.s.lineWidth = ini.get("clock.s.lineWidth",1);
    clock.ms.lineWidth = ini.get("clock.ms.lineWidth",1);

    clock.h.lineSize = ini.get("clock.h.lineSize",40);
    clock.m.lineSize = ini.get("clock.m.lineSize",40);
    clock.s.lineSize = ini.get("clock.s.lineSize",40);
    clock.ms.lineSize = ini.get("clock.ms.lineSize",40);
    clock.ms.position = ini.get("clock.ms.position",ofxVec2f(0,0));

    clock.h.rotation = ofRandomuf();
    clock.m.rotation = ofRandomuf();
    clock.s.rotation = ofRandomuf();
    clock.ms.rotation = ofRandomuf();

    debugText.visible = ini.get("debugText.visible",false);
    debugText.position = ini.get("debugText.position",ofxVec2f(0,0));
    debugText.rotation = ini.get("debugText.rotation",0);
    debugText.scale = ini.get("debugText.scale",ofxVec2f(1,1));
    debugText.color = ini.get("debugText.color",0xffffff);

    font.filename = ini.get("font.filename",(string)"palab.ttf");
    font.size = ini.get("font.size",20);
    font.color = ini.get("font.color",0xffffff);
    font.loadFont(font.filename,font.size);

    if (!ini.get("mouse.visible",false)) ofHideCursor();

    if (serial.enabled) {
        serial.port = ini.get("serial.port",(string)"COM6");
        serial.speed = ini.get("serial.speed",9600);
        cout << "connecting to Arduino on port " << serial.port << " with speed=" << serial.speed << endl;
        serial.setup(serial.port,serial.speed);
    }

    movie.blurSteps = ini.get("movie.blurSteps",5);
    movie.oldPos = 0;

    ofSetCircleResolution(32);

    mapped = 0;

    // setup subPosition series for blending intermediate frames
    int primes[] = {2,3,5,7,11,13,17,19,23,29};
    int numPrimes=4;
    numSubPositions=0;
    for (int i=0; i<numPrimes; i++) numSubPositions+=primes[i]-1;
    subPositionList = (float*)malloc(numSubPositions*sizeof(float));
    int p=0;
    for (int i=0; i<numPrimes; i++) for (int j=1; j<primes[i]; j++) subPositionList[p++]=(float)primes[i]/j;
    bool checkSorted = false;
    float mem;
    while(checkSorted==false) {
        checkSorted = true;
        for (int i=0; i<numSubPositions-1; i++) if (subPositionList[i]>subPositionList[i+1]) {
            checkSorted = false;
            mem = subPositionList[i];
            subPositionList[i] = subPositionList[i+1];
            subPositionList[i+1] = mem;
        }
    }
}

//--------------------------------------------------------------
void testApp::update(){

    if (serial.enabled) {
        serial.request();
        vector<string> items = ofSplitString(serial.readLine(),",");
        if (items.size()==2) {
            float mapped,inverse;
            sensor1.value = 0; //tmp
            sensor2.value = ofToFloat(items[1]);

            //avg 50-500
            //moet zijn 0.1 - 5000
            //a=(avg-50)/450 > 0-1
            //b=a*4.2-1 > -1 - 3.2
            //c=10^b > 0.1 - 1000
            mapped = ofMap(sensor2.value,sensor2.min,sensor2.max,0,1);
            float a = mapped;
            float b = a*(movie.powMaxScale-movie.powMinScale)+movie.powMinScale;
            float c = pow(10,b);
            movie.toSpeed = c;

            scope.update();
        }
    }

    movie.toSpeed = ofClamp(movie.toSpeed,-10000,10000);
    movie.curSpeed += (movie.toSpeed-movie.curSpeed) * movie.speedTween;

    if (!movie.paused) movie.pos += (movie.curSpeed/fps) / movie.actualDuration;
    movie.pos = fmodf(movie.pos,1);
    if (movie.pos<0) movie.pos++;
    movie.setPosition(movie.pos);

    int avg[192*432*3];
    int depth = 3;
    unsigned char *movPix = movie.getPixels();
    unsigned char *imgPix = img.getPixels();

    //clear
    for (int i=0; i<movie.width*movie.height*depth; i++) {
        avg[i] = 0;
    }

    //avg
    for (int p=0; p<numSubPositions; p++) {
        movie.setPosition(ofLerp(movie.oldPos,movie.pos,subPositionList[p]));
        for (int i=0; i<movie.width*movie.height*depth; i++ ) avg[i] += movPix[i];
    }

    //div & set
    for (int i=0; i<movie.width*movie.height*depth; i++ ) {
        imgPix[i] = avg[i] / numSubPositions;
    }

    img.update();
    movie.oldPos = movie.pos;

    float curFPS = (float)ofGetFrameRate()+.0001; //tmp
    clock.ms.rotation += movie.curSpeed/curFPS/60.0*100;
    clock.ms.visible = (movie.curSpeed/curFPS/60.0*100)<.25;
    clock.s.rotation += movie.curSpeed/curFPS/60.0;
    clock.s.visible = (movie.curSpeed/curFPS/60.0)<.25;
    clock.m.rotation += movie.curSpeed/curFPS/60.0/60.0;
    clock.m.visible = (movie.curSpeed/curFPS/60.0/60.0)<.25;
    clock.h.rotation += movie.curSpeed/curFPS/60.0/60.0/60.0;
    clock.h.visible = (movie.curSpeed/curFPS/60.0/60.0/60.0)<.25;
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(backgroundColor);
    ofSetColor(movie.color);
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2,ofGetHeight()/2,0);
    ofTranslate(movie.position);
    ofRotate(movie.rotation);
    ofScale(movie.scale);
    img.draw(0,0);
    ofPopMatrix();

    ofEnableAlphaBlending();

    if (meter.visible) {
        ofPushMatrix();
        meter.doTranslate();
        meter.doScale();
        meter.doRotate();

        if (meter.scaler.visible) {
            ofPushMatrix();
            meter.scaler.doTranslate();
            ofTranslate(ofxVec2f(0,log10f(movie.curSpeed)*meter.indicatorScale+meter.indicatorOffset));
            meter.scaler.doScale();
            meter.scaler.doRotate();
            meter.scaler.doColor();
            meter.scaler.draw(0,0);
            ofPopMatrix();
        }

        if (meter.arrow.visible) {
            ofPushMatrix();
            meter.arrow.doTranslate();
            meter.arrow.doScale();
            meter.arrow.doRotate();
            meter.arrow.doColor();
            meter.arrow.draw(0,0);
            ofPopMatrix();
        }
        ofPopMatrix();
    }

    if (clock.visible) {
        ofEnableSmoothing();
        ofPushMatrix();
            ofTranslate(clock.position);
            ofScale(clock.scale);
            ofNoFill();
            ofSetColor(clock.color);
            ofSetLineWidth(clock.lineWidth);
            ofCircle(0,0,clock.radius);
            ofPushMatrix();
                ofSetLineWidth(clock.markers.lineWidth);
                ofSetColor(clock.markers.color);
                for (int i=0; i<clock.markers.count; i++) {
                     ofRotate(360/clock.markers.count);
                     ofLine(clock.markers.innerRadius,0,clock.markers.outerRadius,0);
                }
            ofPopMatrix();
            if (clock.ms.visible) {
                ofPushMatrix();
                ofTranslate(clock.ms.position);
                ofSetLineWidth(clock.ms.lineWidth);
                ofSetColor(clock.ms.color);
                ofRotate(clock.ms.rotation*360);
                ofLine(0,0,clock.ms.lineSize,0);
                ofPopMatrix();
            }
            if (clock.s.visible) {
                ofPushMatrix();
                ofSetLineWidth(clock.s.lineWidth);
                ofSetColor(clock.s.color);
                ofRotate(clock.s.rotation*360);
                ofLine(0,0,clock.s.lineSize,0);
                ofPopMatrix();
            }
            if (clock.m.visible) {
                ofPushMatrix();
                ofSetColor(clock.m.color);
                ofRotate(clock.m.rotation*360);
                ofSetLineWidth(clock.m.lineWidth);
                ofLine(0,0,clock.m.lineSize,0);
                ofPopMatrix();
            }
            if (clock.h.visible) {
                ofPushMatrix();
                ofSetColor(clock.h.color);
                ofRotate(clock.h.rotation*360);
                ofSetLineWidth(clock.h.lineWidth);
                ofLine(0,0,clock.h.lineSize,0);
                ofPopMatrix();
            }
        ofPopMatrix();
        ofSetLineWidth(1);
    }

    if (debugText.visible) {
        ofSetColor(debugText.color);
        ofTranslate(debugText.position);
        ofRotate(debugText.rotation);
        int y=50;
        ofDrawBitmapString("duration:     " + ofToString(movie.getDuration(),0),50,y+=12);
        ofDrawBitmapString("num frames:   " + ofToString(movie.getTotalNumFrames()),50,y+=12);
        ofDrawBitmapString("movie fps:    " + ofToString(movie.getTotalNumFrames()/movie.getDuration(),2),50,y+=12);
        ofDrawBitmapString("movie act.fps:" + ofToString(movie.actualFPS,2),50,y+=12);
        ofDrawBitmapString("correction:   " + ofToString(movie.speedCorrection,2),50,y+=12);
        ofDrawBitmapString("act.duration: " + ofToString(movie.actualDuration,2),50,y+=12);
        ofDrawBitmapString("cur fps:      " + ofToString(ofGetFrameRate(),0),50,y+=12);
        ofDrawBitmapString("cur speed:    " + ofToString(movie.curSpeed,2),50,y+=12);
        ofDrawBitmapString("min speed:    " + ofToString(movie.minSpeed,2),50,y+=12);
        ofDrawBitmapString("max speed:    " + ofToString(movie.maxSpeed,2),50,y+=12);
        ofDrawBitmapString("to speed:     " + ofToString(movie.toSpeed,2),50,y+=12);
        ofDrawBitmapString("cur frame:    " + ofToString(movie.getCurrentFrame()),50,y+=12);
        ofDrawBitmapString("cur pos:      " + ofToString(movie.getPosition()),50,y+=12);
        ofDrawBitmapString("serialEnabled:" + ofToString(serial.enabled),50,y+=12);
        //ofDrawBitmapString("sensor 1:     " + ofToString(sensor1),50,y+=12);
        ofDrawBitmapString("sensor 2:     " + ofToString(sensor2.value),50,y+=12);
        ofDrawBitmapString("mapped:       " + ofToString(mapped),50,y+=12);
        ofDrawBitmapString("blur steps:   " + ofToString(movie.blurSteps),50,y+=12);
    }

    if (scope.visible) {
        scope.draw((int)scope.position.x,(int)scope.position.y);
    }
}

//----------------------of----------------------------------------
void testApp::keyPressed  (int key){
    float step = keys.isShiftDown() ? 2 : 1.01;

    if (movie.toSpeed<.000001 && movie.toSpeed>=.000001) movie.toSpeed+=.000001;

    switch (key) {
        case OF_KEY_UP: movie.toSpeed*=step; break;
        case OF_KEY_DOWN: movie.toSpeed/=step; break;
        case ' ': movie.paused=!movie.paused; break;
//        case OF_KEY_RIGHT: pos += fabs(toSpeed * step) * ((1.0/fps) / movie.getDuration()); break;
//        case OF_KEY_LEFT: pos -= fabs(toSpeed * step) * ((1.0/fps) / movie.getDuration()); break;
        case OF_KEY_HOME: movie.pos = movie.beginPos; break;
        case OF_KEY_END: movie.pos = .9999; break;
//        case 'r': movie.toSpeed = -movie.toSpeed; break;
//        case 'h': movie.toSpeed = 0; serial.enabled = false; break;
        case 'a': movie.toSpeed = movie.maxSpeed; serial.enabled = false; break;
        case 'i': movie.toSpeed = movie.minSpeed; serial.enabled = false; break;
        case 'n': movie.toSpeed = 1; break;
        case 's': serial.enabled = !serial.enabled; break;
        case 'b': movie.blurSteps++; break;
        case 'B': movie.blurSteps--; break;
        case 'd': debugText.visible=!debugText.visible; break;
        case 'm': meter.visible=!meter.visible; break;
        case 'X': movie.position.y--; break;
        case 'x': movie.position.y++; break;
        case 'Y': movie.position.x--; break;
        case 'y': movie.position.x++; break;
        case 'z': movie.scale+=.01; break;
        case 'Z': movie.scale-=.01; break;
        case 'f': movie.toSpeed=movie.favSpeed; break;
        case 'p': movie.pos=movie.favPos; break;
        case 'P': movie.favPos = movie.pos; ini.set("movie.favPos",movie.favPos); cout << "favpos saved" << endl; break;
        case OF_KEY_CTRL_S:
            ini.set("movie.position",movie.position);
            ini.set("movie.scale",movie.scale);
            ini.set("debugText.visible",debugText.visible);
            cout << "settings saved" << endl;
            break;
    }

    movie.toSpeed = ofClamp(movie.toSpeed,movie.minSpeed,movie.maxSpeed);
}
