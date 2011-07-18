#include "cinder/app/AppBasic.h"
#include "cinder/ImageIO.h"
#include "cinder/gl/Texture.h"
#include "cinder/Perlin.h"
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Utilities.h"
#include "cinder/Rand.h"
#include "cinder/Camera.h"
#include "ParticleController.h"

#define RESOLUTION 10
#define NUM_PARTICLES_TO_SPAWN 20

using namespace ci;
using namespace ci::app;

GLfloat no_mat[]			= { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[]		= { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat mat_specular[]		= { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_emission[]		= { 0.0, 0.1, 0.3, 0.0 };

GLfloat mat_shininess[]		= { 128.0 };
GLfloat no_shininess[]		= { 0.0 };


class SpheresMovingAcorss : public AppBasic {
 public:
	void prepareSettings( Settings *settings );	
	void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );
	void mouseMove( MouseEvent event );
	void mouseDrag( MouseEvent event );
	void setup();
	void resize( ResizeEvent event );
	void update();
	void draw();
	
	Vec2i mMouseLoc;
	Vec2f mMouseVel;
	bool mIsPressed;
	
	ParticleController mParticleController;
	
	bool mDrawParticles;
	bool mSaveFrames;
	
	Vec3f randomLoc;
	
	Vec3f	startLoc;
	Vec3f	endLoc;
	
	CameraPersp		mCam;
	
	bool DIFFUSE;
	bool AMBIENT;
	bool SPECULAR;
	bool EMISSIVE;
	float mDirectional;
	
	float angle;
	
};

void SpheresMovingAcorss::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1200, 675 );
	settings->setFrameRate( 30.0f );
}

void SpheresMovingAcorss::setup()
{	


	mMouseLoc = Vec2i( 0, 0 );
	mMouseVel = Vec2f::zero();
	mDrawParticles = true;
	
	mIsPressed = false;
	mSaveFrames = false;
	
	//mParticleController.addParticles( 65, getWindowWidth(), getWindowHeight() );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
	//gl::enableAdditiveBlending();
	
	randomLoc.set(100, 100, -200);
	
	DIFFUSE		= true;
	AMBIENT		= true;
	SPECULAR	= false;
	EMISSIVE	= false;
	
	mDirectional = 1.0f;
	
	angle = 0;
	startLoc.set(200, 0, -100);
	endLoc.set(300, 500, -500);
}

void SpheresMovingAcorss::resize( ResizeEvent event )
{
	mCam.lookAt( Vec3f( 0.0f, 0.0f, 750.0f ), Vec3f::zero() );
	mCam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
	gl::setMatrices( mCam );
}


void SpheresMovingAcorss::mouseDown( MouseEvent event )
{
	mIsPressed = true;
}

void SpheresMovingAcorss::mouseUp( MouseEvent event )
{
	mIsPressed = false;
}

void SpheresMovingAcorss::mouseMove( MouseEvent event )
{
	mMouseVel = ( event.getPos() - mMouseLoc );
	mMouseLoc = event.getPos();
}

void SpheresMovingAcorss::mouseDrag( MouseEvent event )
{
	mouseMove( event );
}

void SpheresMovingAcorss::keyDown( KeyEvent event )
{

	//mDrawParticles = ! mDrawParticles;
	
	
	if( event.getChar() == 's' ){
		mSaveFrames = ! mSaveFrames;
	}
}

void SpheresMovingAcorss::update()
{
	angle += M_PI/100;
	
	endLoc.x = 300 + 100*sin(angle);
	endLoc.y = 500 + 200 * sin(angle);
	endLoc.z = -500 +200 *cos(angle);
	
	/*
	if(mParticleController.mParticles.size() < 60)
		mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, getWindowWidth(), getWindowHeight() );
	
	
	if( mIsPressed )
		mParticleController.addParticles( NUM_PARTICLES_TO_SPAWN, getWindowWidth(), getWindowHeight() );
	
	mParticleController.update( mMouseLoc );
	*/
	
}

void SpheresMovingAcorss::draw()
{	
	//gl::clear( Color( 0, 0, 0 ), true );
	
	GLfloat light_position[] = { 100, 100, 75.0f, mDirectional };

	
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
	
	glPushMatrix();
	glTranslatef( 100, 100, 0.0);

	if( DIFFUSE ){
		ci::ColorA color( CM_RGB, 1.0, 1.0, 1.0f, 1.0f );
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	color );
	} else {
		glMaterialfv( GL_FRONT, GL_DIFFUSE,	no_mat );
	}
	
	if( AMBIENT )
		glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
	else
		glMaterialfv( GL_FRONT, GL_AMBIENT,	no_mat );
	
	if( SPECULAR ){
		glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular );
		glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess );
	} else {
		glMaterialfv( GL_FRONT, GL_SPECULAR, no_mat );
		glMaterialfv( GL_FRONT, GL_SHININESS, no_shininess );
	}
	
	if( EMISSIVE ) {
		glMaterialfv( GL_FRONT, GL_EMISSION, mat_emission );
	} else{
		glMaterialfv( GL_FRONT, GL_EMISSION, no_mat );	
	}
	
	glColor3f(0.5f, 1.0f, 0.0f);
	gl::drawSphere(randomLoc, 100 , 64);
	
	glLineWidth(30);
	gl::drawLine( startLoc, endLoc );
	glPopMatrix();
	
	/*
	if( mDrawParticles ){
		
		if( DIFFUSE ){
			ci::ColorA color( CM_RGB, 0.5f, 0.2f, 1.0f, 1.0f );
			glMaterialfv( GL_FRONT, GL_DIFFUSE,	color );
		} else {
			glMaterialfv( GL_FRONT, GL_DIFFUSE,	no_mat );
		}
		
		glDisable( GL_TEXTURE_2D );
		mParticleController.draw();
		
		
	}
	 */
	
	if( mSaveFrames ){
		writeImage( "../../image_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
	}
}

CINDER_APP_BASIC( SpheresMovingAcorss, RendererGl )
