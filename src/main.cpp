#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

//========================================================================
int main( ){
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1000,600, OF_FULLSCREEN);			// <-------- setup the GL context

//    #ifdef TARGET_WIN32
//        HWND handleWindow;
//        AllocConsole();
//        handleWindow = FindWindowA("ConsoleWindowClass", NULL);
//        ShowWindow(handleWindow, 0);
//    #endif

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());



}
