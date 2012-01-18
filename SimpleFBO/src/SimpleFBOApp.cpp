#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/gl/Fbo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//LIGHTS
GLfloat mat_diffuse[]		= { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 0.7 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class SimpleFBOApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    
    void renderSceneToFbo();
    gl::Fbo				mFbo;
	Matrix44f			mFboRotation;
	static const int	FBO_WIDTH = 256, FBO_HEIGHT = 256;
    
    float mDirectional;
};

void SimpleFBOApp::setup()
{
    gl::Fbo::Format format;
    //	format.setSamples( 4 ); // uncomment this to enable 4x antialiasing
	mFbo = gl::Fbo( FBO_WIDTH, FBO_HEIGHT, format );
    
	gl::enableDepthRead();
	gl::enableDepthWrite();	
    
	mFboRotation.setToIdentity();
    
    // LIGHTS
    mDirectional = 0.0f;
}

// Render scene into the FBO
void SimpleFBOApp::renderSceneToFbo()
{   
    // this will restore the old framebuffer binding when we leave this function
	gl::SaveFramebufferBinding bindingSaver;
	
	// bind the framebuffer - now everything we draw will go there
	mFbo.bindFramebuffer();
    
	// setup the viewport to match the dimensions of the FBO
	gl::setViewport( mFbo.getBounds() );
    
	// setup our camera to render the torus scene
	CameraPersp cam( mFbo.getWidth(), mFbo.getHeight(), 60.0f );
	cam.setPerspective( 60, mFbo.getAspectRatio(), 1, 1000 );
	cam.lookAt( Vec3f( 2.8f, 1.8f, -2.8f ), Vec3f::zero() );
	gl::setMatrices( cam );
    
    glDisable(  GL_LIGHTING );
    // setup lights within the fbo
    /*
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -10.0f, 10.0f, 10.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    
    GLfloat light_position1[] = { 10.0f, -10.0f, -15.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
    */
    
	// set the modelview matrix to reflect our current rotation
	gl::multModelView( mFboRotation );
	
	// clear out the FBO 
	gl::clear( Color( 0.0f, 1.0f, 1.0f ) );
    
	// render an orange torus, with no textures
	glDisable( GL_TEXTURE_2D );
	gl::color( Color( 1.0f, 0.5f, 0.25f ) );
	gl::drawTorus( 1.4f, 0.3f, 32, 64 );
    //	gl::drawColorCube( Vec3f::zero(), Vec3f( 2.2f, 2.2f, 2.2f ) );
}

void SimpleFBOApp::mouseDown( MouseEvent event )
{
}

void SimpleFBOApp::update()
{
    // Rotate the torus by .06 radians around an arbitrary axis
	mFboRotation.rotate( Vec3f( 0.16666f, 0.333333f, 0.666666f ).normalized(), 0.06f );
	
	// render into our FBO
	renderSceneToFbo();
}

void SimpleFBOApp::draw()
{
	// clear the window to gray
	gl::clear( Color( 0.35f, 0.35f, 0.35f ) );
    
	// setup our camera to render the cube
	CameraPersp cam( getWindowWidth(), getWindowHeight(), 60.0f );
	cam.setPerspective( 60, getWindowAspectRatio(), 1, 1000 );
	cam.lookAt( Vec3f( 2.6f, 1.6f, -2.6f ), Vec3f::zero() );
	gl::setMatrices( cam );
    
	// set the viewport to match our window
	gl::setViewport( getWindowBounds() );
    
    // lighting
    //glDisable(  GL_LIGHTING );
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -10.0f, 10.0f, 10.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse );
    
    GLfloat light_position1[] = { 10.0f, -10.0f, -15.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
    
	// use the scene we rendered into the FBO as a texture
	glEnable( GL_TEXTURE_2D );
	mFbo.bindTexture();
    
	// draw a cube textured with the FBO
	gl::color( Color::white() );
    //gl::drawSphere( Vec3f::zero(), 2.0f, 12 );
    gl::drawCube( Vec3f::zero(), Vec3f( 2.2f, 2.2f, 2.2f ) );
    
	// show the FBO texture in the upper left corner
	gl::setMatricesWindow( getWindowSize() );
	gl::draw( mFbo.getTexture(0), Rectf( 0, 0, 96, 96 ) );
    
    gl::draw( mFbo.getDepthTexture(), Rectf( 96, 0, 96 + 96, 96 ) );
    
}


CINDER_APP_BASIC( SimpleFBOApp, RendererGl )
