#include "ofMain.h"
#include "ofApp.h"

int main()
{
	ofSetupOpenGL(1024,768, OF_WINDOW);
	ofRunApp( new ofApp() );
	return 0;
}

#ifdef TARGET_ANDROID
void ofAndroidApplicationInit() {}
void ofAndroidActivityInit() { main(); }
#endif

