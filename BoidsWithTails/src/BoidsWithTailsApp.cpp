#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h"
#include "cinder/Vector.h"
#include "cinder/Rand.h"
#include "cinder/ImageIO.h"
#include "ParticleController.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BoidsWithTailsApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
	
	// CAMERA
	CameraPersp			mCam;
	Quatf				mSceneRotation;
	Vec3f				mEye, mCenter, mUp;
	float				mCameraDistance;
    
    // BOIDS Settings
    float mZoneRadius;
    float mLowerThresh, mHigherThresh;
    float mAttractStrength, mRepelStrength;
    
    ParticleController mParticleController;
    
    bool mSaveFrames;
};

void BoidsWithTailsApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void BoidsWithTailsApp::setup()
{
    /*
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    */
    
    gl::enableAlphaBlending();
    // SETUP CAMERA
	mCameraDistance = 500.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f::zero();
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    // SETUP PARAMS
	mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 300 ) );
	mParams.addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
	mParams.addSeparator();
	mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );
    
    // BOIDS Settings
    mZoneRadius = 80.0f;
    mLowerThresh = 0.4f;
    mHigherThresh = 0.75f;
    mAttractStrength = 0.005f;
    mRepelStrength = 0.01f;
    
    mParticleController.addParticles(100);    
    
    mSaveFrames = true;
}

void BoidsWithTailsApp::mouseDown( MouseEvent event )
{
}

void BoidsWithTailsApp::update()
{
    // UPDATE CAMERA
	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCam.lookAt( mEye, mCenter, mUp );
	gl::setMatrices( mCam );
	gl::rotate( mSceneRotation );
    
    mParticleController.applyForce(mZoneRadius, mLowerThresh, mHigherThresh, mAttractStrength, mRepelStrength);
    mParticleController.pullToCenter( mCenter );
    mParticleController.update();
    
}

void BoidsWithTailsApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ), true ); 
    gl::enableDepthRead();
	gl::enableDepthWrite();

    
    mParticleController.draw();
    
    // DRAW PARAMS WINDOW
	//params::InterfaceGl::draw();
    
    if( mSaveFrames ){
		writeImage( getHomeDirectory() + "flocking/image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
	}
}


CINDER_APP_BASIC( BoidsWithTailsApp, RendererGl )
