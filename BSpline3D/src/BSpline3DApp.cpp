#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/BSpline.h"
#include "cinder/Quaternion.h"
#include "cinder/matrix.h"

using namespace ci;
using namespace ci::app;
using namespace std;

//LIGHTS
GLfloat mat_diffuse[]		= { 0.5, 0.5, 0.5, 1.0 };
GLfloat light_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 0.7 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class BSpline3DApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
    void drawCurve( vector<Vec3f> & controlPoints );
    void drawCurveTubes( vector<Vec3f> & controlPoints );
    
    // B-SPLINE
    bool mOpen, mLoop;
    vector< vector<Vec3f> > mControlPoints;
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf   mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    // LIGHTS
    float mDirectional;
};

void BSpline3DApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1280, 720 );
	settings->setFrameRate( 60.0f );
}

void BSpline3DApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 4000.0f );
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=2000.0 step=50.0 keyIncr=s keyDecr=w" );
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    // LIGHTS
    mDirectional = 0.0f;   
    
    // B-SPLINE
    mOpen = true;
    mLoop = false;
    
    // CREATE THE FIRST SET OF CONTROL POINTS
    vector<Vec3f> firstSet;
    firstSet.push_back( Vec3f(0.0f, 0.0f, 0.0f) );
    firstSet.push_back( Vec3f(100.0f, 150.0f, 300.0f) );
    firstSet.push_back( Vec3f(200.0f, 250.0f, 150.0f) );
    firstSet.push_back( Vec3f(400.0f, -100.0f, 0.0f) );
    
    mControlPoints.push_back( firstSet );
}

void BSpline3DApp::mouseDown( MouseEvent event )
{
}

void BSpline3DApp::update()
{
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    mControlPoints[0][1].set( Vec3f(100.0f, 150.0f + 500*sin(getElapsedSeconds()*2), 300.0f) );
    mControlPoints[0][2].set( Vec3f(200.0f, 250.0f + 500*cos(getElapsedSeconds()), 150.0f) );
    mControlPoints[0][3].set( Vec3f(400.0f, -100.0f + 200*sin(getElapsedSeconds()), 300.0f*cos(getElapsedSeconds()) ) );
}

void BSpline3DApp::drawCurve( vector<Vec3f> & controlPoints ) 
{
    // Draw spheres representing control points
    ci::ColorA color3( CM_RGB, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color3 ); 
    gl::drawSphere( controlPoints[0], 10.0f, 30 );
    
    ci::ColorA color4( CM_RGB, 1.0f, 0.0f, 0.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color4 ); 
    gl::drawSphere( controlPoints[1], 10.0f, 30 );
    
    ci::ColorA color5( CM_RGB, 0.0f, 1.0f, 0.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color5 ); 
    gl::drawSphere( controlPoints[2], 10.0f, 30 );
    
    ci::ColorA color6( CM_RGB, 0.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color6 ); 
    gl::drawSphere( controlPoints[3], 10.0f, 30 );
    
    // set up spline
    BSpline3f spline( controlPoints, 3, mLoop, mOpen);
    
    // Create high resolution list of points in path
    float resolution = 1000.0f;
    vector<Vec3f> points;
    float delta = 1.0f / resolution;
    for (float theta = 0.0f; theta < 1.0f; theta += delta)
        points.push_back(spline.getPosition(theta));
    
    // Find start and end points
    uint32_t start = (uint32_t)(0.0f);
    uint32_t end = (uint32_t)((float)points.size());
    
    glLineWidth(3);
    
    // Draw portion of arc
    glBegin(GL_LINES);
    for (uint32_t i = start; i < end - 1; i++)
    {
        // Control alpha with position
        float alpha = (float)(end - i) / (float)(end - start);
        
        ci::ColorA color2( CM_RGB, 0.0f, 1.0f, 1.0f, alpha);
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 ); 
        
        // Draw line segment
        gl::vertex(points[i]);
        gl::vertex(points[i + 1]);
    }
    glEnd();
    
}

void BSpline3DApp::drawCurveTubes( vector<Vec3f> & controlPoints ) 
{
    // Draw spheres representing control points
    ci::ColorA color3( CM_RGB, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color3 ); 
    gl::drawSphere( controlPoints[0], 10.0f, 30 );
    
    ci::ColorA color4( CM_RGB, 1.0f, 0.0f, 0.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color4 ); 
    gl::drawSphere( controlPoints[1], 10.0f, 30 );
    
    ci::ColorA color5( CM_RGB, 0.0f, 1.0f, 0.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color5 ); 
    gl::drawSphere( controlPoints[2], 10.0f, 30 );
    
    ci::ColorA color6( CM_RGB, 0.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color6 ); 
    gl::drawSphere( controlPoints[3], 10.0f, 30 );
    
    // set up spline
    BSpline3f spline( controlPoints, 3, mLoop, mOpen);
    
    float startRadius = 30.0f;
    
    // Create high resolution list of points in path
    float resolution = 1000.0f;
    vector<Vec3f> points;
    float delta = 1.0f / resolution;
    for (float theta = 0.0f; theta < 1.0f; theta += delta) {
        points.push_back(spline.getPosition(theta));
    }
    
    float length = 2.0f*(spline.getLength(0.0f, 1.0f) / resolution);
    
    // Find start and end points
    uint32_t start = (uint32_t)(0.0f);
    uint32_t end = (uint32_t)((float)points.size());
    
    // Draw portion of arc
    for (uint32_t i = start; i < end - 1; i++)
    {
        // Control alpha with position
        //float alpha = (float)(end - i) / (float)(end - start);
        
        ci::ColorA color2( CM_RGB, 0.0f, 1.0f, 1.0f, 1.0f);
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 ); 
        
        Vec3f direction;
        direction = points[i+1] - points[i];
        
        Quatf mQuat;
        mQuat.set( Vec3f(0.0f, 1.0f, 0.0f), direction );
        
        Matrix44<float> mat;
        mat = mQuat.toMatrix44();
        
        float radius1, radius2;
        radius1 = startRadius*((float(end)-float(i))/float(end));
        radius2 = startRadius*((float(end)-float(i)-1)/float(end));
        
        gl::pushMatrices();
        gl::translate( points[i] );
        gl::multModelView( mat );
        gl::drawCylinder( radius1, radius2, length, 12,  1 );
        gl::popMatrices();
    }
}

void BSpline3DApp::draw()
{
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
    
    for (int i = 0; i < mControlPoints.size(); i++ ) {
        drawCurve( mControlPoints[i] );
        drawCurveTubes( mControlPoints[i] );
    }
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( BSpline3DApp, RendererGl )
