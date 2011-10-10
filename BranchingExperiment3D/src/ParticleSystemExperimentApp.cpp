#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h"
#include "cinder/Perlin.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "ParticleController.h"

#define NUM_PARTICLES_TO_SPAWN 25

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };

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
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float mDirectional;
    
    
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
    
    // SETUP CAMERA
	mCameraDistance = 500.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( getWindowWidth()/2, getWindowHeight()/2, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 2000.0f );
    
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
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
    //UPDATE CAMERA
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
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
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { 100.0f, 200.0f, 75.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    
    ci::ColorA color( CM_RGB, 0.5f, 0.8f, 0.2f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color );
    
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) ); 
    
    
   
    mParticleController.draw();
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( ParticleSystemExperimentApp, RendererGl )
