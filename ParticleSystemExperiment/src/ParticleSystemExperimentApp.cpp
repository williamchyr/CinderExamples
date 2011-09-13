#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/Perlin.h"
#include "ParticleController.h"

#define NUM_PARTICLES_TO_SPAWN 25

using namespace ci;
using namespace ci::app;
using namespace std;

class ParticleSystemExperimentApp : public AppBasic {
  public:
    void prepareSettings(Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void mouseUp( MouseEvent event );
    void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    Vec2i mMouseLoc;
	Vec2f mMouseVel;
    bool mIsPressed;
    
    Perlin mPerlin;
    
    ParticleController mParticleController;
    
    bool mSaveFrame;

};


void ParticleSystemExperimentApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 1000, 800 );
    settings->setFrameRate( 40.0f );
}

void ParticleSystemExperimentApp::setup()
{
    gl::enableAlphaBlending();
    
    mIsPressed = false;
    
    mPerlin = Perlin();
}

void ParticleSystemExperimentApp::mouseDown( MouseEvent event )
{
	mIsPressed = true;
}

void ParticleSystemExperimentApp::mouseUp( MouseEvent event )
{
	mIsPressed = false;
}

void ParticleSystemExperimentApp::mouseMove( MouseEvent event )
{
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void ParticleSystemExperimentApp::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void ParticleSystemExperimentApp::keyDown( KeyEvent event )
{
	if( event.getChar() == 's' ){
		mSaveFrame = ! mSaveFrame;
	}
}

void ParticleSystemExperimentApp::update()
{

    
    if( mIsPressed )
		mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, mMouseLoc, mMouseVel );
	
	mParticleController.update(mPerlin);
    
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}

}

void ParticleSystemExperimentApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
    
   
    mParticleController.draw();
}


CINDER_APP_BASIC( ParticleSystemExperimentApp, RendererGl )
