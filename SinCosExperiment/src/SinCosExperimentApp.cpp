#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SinCosExperimentApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
    void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    gl::Texture myImage;
    
    ParticleController mParticleController;
    
    bool mSaveFrame;
    
};

void SinCosExperimentApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 600 );
	settings->setFrameRate( 60.0f );
}


void SinCosExperimentApp::setup()
{
    mParticleController = ParticleController (10);
    mSaveFrame = false;
}

void SinCosExperimentApp::mouseDown( MouseEvent event )
{
}

void SinCosExperimentApp::update()
{
    mParticleController.update();
}

void SinCosExperimentApp::draw()
{
    gl::clear();

    mParticleController.draw();
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        mSaveFrame = false;
	}
}

void SinCosExperimentApp::keyDown( KeyEvent event ) {
    if( event.getChar() == 's' ){
		mSaveFrame = true;
	}
}


CINDER_APP_BASIC( SinCosExperimentApp, RendererGl )
