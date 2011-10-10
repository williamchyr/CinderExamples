#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include <list>

using namespace ci;
using namespace ci::app;
using namespace std;

class FractalStudyApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void branch(float length);
};

void FractalStudyApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void FractalStudyApp::setup()
{
    
}

void FractalStudyApp::mouseDown( MouseEvent event )
{
}

void FractalStudyApp::update()
{
}

void FractalStudyApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    gl::pushMatrices();
    gl::translate( getWindowWidth()/2, getWindowHeight()/2);
    branch(500.0f);
    gl::popMatrices();
}

void FractalStudyApp::branch( float length ) 
{
    length *= 0.66f;
    
    if (length > 10.0f) {
        gl::pushMatrices();
        gl::rotate( 90.0f);
        gl::drawLine( Vec2f(0, 0), Vec2f(0, length) );
        gl::translate( Vec2f( 0, length) );
        branch( length );
        gl::popMatrices();
        
        gl::pushMatrices();
        gl::rotate( -90.0f);
        gl::drawLine( Vec2f(0, 0), Vec2f(0, length) );
        gl::translate( Vec2f( 0, length) );
        branch( length );
        gl::popMatrices();
    }
}


CINDER_APP_BASIC( FractalStudyApp, RendererGl )
