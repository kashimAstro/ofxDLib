#include "ofMain.h"
#include "ofxDlib.h"

using namespace dlib;

class app : public ofBaseApp 
{
        public:
		frontal_face_detector detector;
		ofVideoGrabber vid;
		ofImage dlib_img;
		std::vector<rectangle> dets;
		int w = 640; int h = 480;

		void setup() {
			ofSetVerticalSync(false);

			detector = get_frontal_face_detector();

			vid.setDeviceID(0);
			vid.setDesiredFrameRate(60);
			vid.initGrabber(w,h);

		}

		void update() {
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
			vid.update();
			if(vid.isFrameNew()) {
				dlib_img = vid.getPixels();
				dlib_img.resize(vid.getWidth()/3,vid.getHeight()/3);
				dlib::matrix<dlib::rgb_pixel> img = dlib::mat(dlib_img.getPixels());
				dets = detector(img);
			}
		}

		void draw()
		{
			ofBackground(ofColor::white);
			ofSetColor(ofColor::white);
			vid.draw(0,0);
			for(int i = 0; i < dets.size(); i++)
			{
				auto r = ofxDlib::toOf(dets[i]);
				ofNoFill();
				ofSetColor(ofColor::orange);
				ofSetLineWidth(10);
				ofDrawRectangle(r.x*3,r.y*3,r.width*3,r.height*3);
			}
			ofDrawBitmapStringHighlight("fps: "+to_string(ofGetFrameRate()),20,20);
		}

		void keyPressed(int key) {}
};

int main(int argc, char ** argv)
{
	ofSetupOpenGL(800,600, OF_WINDOW);
	ofRunApp( new app());
}
