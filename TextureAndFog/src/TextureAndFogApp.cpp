#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

// Uncomment this line to enable specialized PNG handling
//#include "cinder/ImageSourcePng.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//LIGHTS
GLfloat mat_diffuse[]		= { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 0.7 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

//FOG
GLfloat density = 0.0003;
GLfloat fogColor[4] = {1.0, 1.0, 1.0, 1.0};

class TextureAndFogApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
    void keyDown( KeyEvent event );
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf   mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    float camAngle;
    
    // ROTATION
    float xAngle, yAngle, zAngle;
    
    // LIGHTS
    float mDirectional;
    
    // TEXTURE
    gl::Texture		mTexture;	
    gl::Texture     mTexture2;
    gl::Texture     mTexture3;
    
    bool mShowFog;
    bool mShowTexture;
    
    // SAVING
    bool mSaveFrame;
};

void TextureAndFogApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void TextureAndFogApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1000.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 8000.0f );
    
    // CAMERA ROTATION
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=2000.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 0.0f;
    
    // FOG  
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP2);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST); 
    
    mShowFog = true;
    
    // TEXTURE
    mTexture = gl::Texture( loadImage( loadResource("wood.jpg") ) );
    mTexture2 = gl::Texture( loadImage( loadResource("marble.jpg") ) );
    mTexture3 = gl::Texture( loadImage( loadResource("plastic.jpg") ) );
}

void TextureAndFogApp::mouseDown( MouseEvent event )
{
}

void TextureAndFogApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'f' ){
		mShowFog = ! mShowFog;
	}
    
    if( event.getChar() == 'k' ){
		mSaveFrame = ! mSaveFrame;
	}
    
}

void TextureAndFogApp::update()
{
    //UPDATE CAMERA
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance ); 
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
}

void TextureAndFogApp::draw()
{
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -10.0f, 10.0f, 10.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    
    GLfloat light_position1[] = { 20.0f, -10.0f, -15.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
	
    
    // DRAW OBJECTS WITHOUT TEXTURE
   
    glDisable(GL_TEXTURE_2D);

    ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 0.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 ); 
    
    for (int i = 0; i < 20; i++ ) {
        for (int j = 0; j < 5; j++ ) {
            for (int k = 2; k < 5; k++) {
                gl::pushMatrices();
                gl::translate( Vec3f( 300+300.0f*k, 600.0f - 300.0f*j, 200.0f - 300.0f*i ) );
                gl::drawCube( Vec3f::zero(), Vec3f(200.0f, 200.0f, 200.0f ) );
                gl::popMatrices();
            }
        }
    }
   
    // ENABLE TEXTURE
    glEnable( GL_TEXTURE_2D);
    
    // SET DEFAULT COLOR TO WHITE SO TEXTURE COLOR IS ACCURATE
    ci::ColorA color2( CM_RGB, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE, color2 );
    
    
    // DRAW OBJECTS WITH WOOD TEXTURE
    
    mTexture.bind();
    
    for (int i = 0; i < 20; i++ ) {
        for (int j = 0; j < 5; j++ ) {
            for (int k = 0; k < 2; k++) {
                gl::pushMatrices();
                gl::translate( Vec3f( 300+300.0f*k, 600.0f - 300.0f*j, 200.0f - 300.0f*i ) );
                gl::drawSphere( Vec3f::zero(), 100.0f, 40 );
                //gl::drawCube( Vec3f::zero(), Vec3f(200.0f, 200.0f, 200.0f ) );
                gl::popMatrices();

            }
        }
    }
    
    mTexture.unbind();
    
    // DRAW OBJECTS WITH PLASTIC TEXTURE
   
    mTexture3.bind();
 
    for (int i = 0; i < 20; i++ ) {
        for (int j = 0; j < 5; j++ ) {
            for (int k = 0; k < 2; k++) {
                gl::pushMatrices();
                gl::translate( Vec3f(- 300.0f*k, 600.0f - 300.0f*j, 200.0f - 300.0f*i ) );
                gl::drawCube( Vec3f::zero(), Vec3f(200.0f, 200.0f, 200.0f ) );
                //gl::drawSphere( Vec3f::zero(), 100.0f, 40 );
                gl::popMatrices();
            }
        }
    }
    
    mTexture3.unbind();
   
    
    // DRAW OBJECTS WITH MARBLE TEXTURE
    mTexture2.bind();
    
    for (int i = 0; i < 20; i++ ) {
        for (int j = 0; j < 5; j++ ) {
            for (int k = 2; k < 3; k++) {
                gl::pushMatrices();
                gl::translate( Vec3f(- 400.0f*k, 600.0f - 400.0f*j, 200.0f -500.0f*i ) );
                gl::drawCube( Vec3f::zero(), Vec3f(350.0f, 300.0f, 450.0f ) );
                gl::popMatrices();
            }
        }
    }
    
    for (int i = 0; i < 20; i++ ) {
        for (int j = 0; j < 5; j++ ) {
            for (int k = 3; k < 5; k++) {
                gl::pushMatrices();
                gl::translate( Vec3f(- 400.0f*k, 600.0f - 400.0f*j, 200.0f - 400.0f*i ) );
                gl::drawSphere( Vec3f::zero(), 100.0f, 40 );
                gl::popMatrices();
            }
        }
    }

    
    // SAVING FRAME
    if( mSaveFrame ){
		writeImage( getHomeDirectory() + "TextureFog/Fog_" + toString( getElapsedFrames() ) + ".png", copyWindowSurface() );
        
        mSaveFrame = false;
	}
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( TextureAndFogApp, RendererGl )
