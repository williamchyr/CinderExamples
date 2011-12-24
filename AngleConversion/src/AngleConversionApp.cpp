#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Utilities.h" 
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "Turtle.h"

#include <vector>

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class AngleConversionApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    // PARAMS
	params::InterfaceGl	mParams;
    
    // CAMERA
    CameraPersp mCam;
    Quatf   mSceneRotation;
    float	mCameraDistance;
    Vec3f   mEye, mCenter, mUp;
    
    // ROTATION
    float xAngle, yAngle, zAngle;
    
    float mDirectional;
    float camAngle;
    
    // TURTLE
    Turtle testTurtle;
    Turtle testTurtle2;
    float rotateX0, rotateZ0, rotateY0;
    float rotateX1, rotateZ1, rotateY1;
    
    vector <Turtle> mTurtles;
    
    vector <string> textStartPosition;
    vector <string> textFinalAngle;
    vector <string> textPreviousAngle;
    vector <string> textSetAngle;
    vector <string> textFinalPosition;
    vector <string> textLocalCoordinates;
    vector <string> textWorldCoordinates;
    
    Vec3f startPosition;
    Vec3f zeroDirection;
    Vec3f initialDirection;
    
    Vec3f direction1, direction2;
    
};

void AngleConversionApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void AngleConversionApp::setup()
{
    // SETUP CAMERA
	mCameraDistance = 1200.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCenter			= Vec3f( 0.0f, 0.0f, 0.0f );
	mUp				= Vec3f::yAxis();
	mCam.setPerspective( 75.0f, getWindowAspectRatio(), 5.0f, 3000.0f );
    
    // CAMERA ROTATION
    xAngle = 0.0f;
    yAngle = 0.0f;
    zAngle = 0.0f;
    
    // OBJECT ROTATION
    rotateX0 = 0.0f;
    rotateY0 = 0.0f;
    rotateZ0 = 0.0f;
    
    // OBJECT ROTATION
    rotateX1 = 0.0f;
    rotateY1 = 0.0f;
    rotateZ1 = 0.0f;
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    mParams.addParam( "Rotate X0", &rotateX0, "min=0.0 max=360.0 step=5.0 keyIncr=u keyDecr=j" );
    mParams.addParam( "Rotate Y0", &rotateY0, "min=0.0 max=360.0 step=5.0 keyIncr=i keyDecr=k" );
    mParams.addParam( "Rotate Z0", &rotateZ0, "min=0.0 max=360.0 step=5.0 keyIncr=o keyDecr=l" );
    
    mParams.addParam( "Rotate X1", &rotateX1, "min=0.0 max=360.0 step=5.0 keyIncr=u keyDecr=j" );
    mParams.addParam( "Rotate Y1", &rotateY1, "min=0.0 max=360.0 step=5.0 keyIncr=i keyDecr=k" );
    mParams.addParam( "Rotate Z1", &rotateZ1, "min=0.0 max=360.0 step=5.0 keyIncr=o keyDecr=l" );

    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    mDirectional = 1.0f;
    
    camAngle = 0;
    
    // TURTLE
    startPosition.set( 0.0f, 0.0f, 0.0f);
    zeroDirection.set( 0.0f, 0.0f, 0.0f);
    initialDirection.set( 0.0f, 0.0f, 0.0f);
    
    direction1.set( 0.0f, 0.0f, 0.0f );
    direction2.set( 0.0f, 0.0f, 0.0f );
    
    testTurtle.init( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(0.0f, 30.0f, 30.0f), direction1, 200.0f, 20.0f );
    mTurtles.push_back(testTurtle);
    
    //testTurtle2.init( testTurtle.mFinalPosition, 
    
    
    
    for (int i = 0; i < mTurtles.size(); i++ ) {
        string textString;
        
        textFinalAngle.push_back(textString);
        
        textSetAngle.push_back(textString);
        
        textPreviousAngle.push_back(textString);
        
        textFinalPosition.push_back(textString);
        
        textStartPosition.push_back(textString);
        
        textLocalCoordinates.push_back(textString);
        
        textWorldCoordinates.push_back(textString);
    }

}

void AngleConversionApp::mouseDown( MouseEvent event )
{
}

void AngleConversionApp::keyDown( KeyEvent event )
{
}


void AngleConversionApp::update()
{
    cout << "number of turtles " + toString( mTurtles.size() ) + "\n";\
    
    camAngle += M_PI/50;
    
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
    //UPDATE TURTLE
    mTurtles[0].update( rotateX0, rotateY0, rotateZ0);
    

    /*
    for (int i = 0; i < mTurtles.size(); i++) {
        mTurtles[i].update();
        
        if (mTurtles[i].mLength < 10.0f) {
            break;
        }    
        
        
        
        if (mTurtles[i].branchNow1 ){
            if ( mTurtles[i].mFinalLength > 2.0f)  {
                Turtle newTurtle;
                newTurtle.init( mTurtles[i].mCurrentPosition, mTurtles[i].mFinalAngle, direction1, mTurtles[i].mFinalLength*0.5f, mTurtles[i].mRadius*0.7f);
                mTurtles.push_back( newTurtle );
            }
        }
        
    }
     */
    
    // TEXT DATA
    for (int i = 0; i < textFinalAngle.size(); i++ ) {
        
        textFinalAngle[i] = "mTurtle" + toString(i) + " mFinalAngle: " + toString( mTurtles[i].mFinalAngle.x) + ", "  + toString( mTurtles[i].mFinalAngle.y) + ", "  + toString( mTurtles[i].mFinalAngle.z) + "\n";
        
        textPreviousAngle[i] = "mTurtle" + toString(i) + " mPreviousAngle: " + toString( mTurtles[i].mPreviousAngle.x) + ", "  + toString( mTurtles[i].mPreviousAngle.y) + ", "  + toString( mTurtles[i].mPreviousAngle.z) + "\n";
        
        textSetAngle[i] = "mTurtle" + toString(i) + " mSetAngle: " + toString( mTurtles[i].mSetAngle.x) + ", "  + toString( mTurtles[i].mSetAngle.y) + ", "  + toString( mTurtles[i].mSetAngle.z) + "\n";
        
        textFinalPosition[i] = "mTurtle" + toString(i) + " mFinalPosition: " + toString( int(mTurtles[i].mFinalPosition.x)) + ", "  + toString( int(mTurtles[i].mFinalPosition.y)) + ", "  + toString( int(mTurtles[i].mFinalPosition.z) ) + "\n";
        
        textStartPosition[i] = "mTurtle" + toString(i) + " mStartPosition: " + toString( int(mTurtles[i].mStartPosition.x)) + ", "  + toString( int(mTurtles[i].mStartPosition.y)) + ", "  + toString( int(mTurtles[i].mStartPosition.z) ) + "\n";
        
        textLocalCoordinates[i] = "mTurtle" + toString(i) + " mLocalPosition: " + toString( int(mTurtles[i].mLocalPosition.x)) + ", "  + toString( int(mTurtles[i].mLocalPosition.y)) + ", "  + toString( int(mTurtles[i].mLocalPosition.z) ) + "\n";
        
        textWorldCoordinates[i] = "mTurtle" + toString(i) + " mWorldPosition: " + toString( int(mTurtles[i].mWorldPosition.x)) + ", "  + toString( int(mTurtles[i].mWorldPosition.y)) + ", "  + toString( int(mTurtles[i].mWorldPosition.z) ) + "\n";
    }

}

void AngleConversionApp::draw()
{
    glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
	
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	GLfloat light_position[] = { -200.0f, 400.0f, 275.0f, mDirectional };
	glLightfv( GL_LIGHT0, GL_POSITION, light_position );
    
    GLfloat light_position1[] = { -500.0f, -300.0f, -400.0f, mDirectional };
    glLightfv( GL_LIGHT1, GL_POSITION, light_position1 );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light1_diffuse );
    
    glMaterialfv( GL_FRONT, GL_AMBIENT,	mat_ambient );
    
    // DRAW AXIS
    ci::ColorA colorX( CM_RGB, 1.0f, 0.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorX );
    gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );
    
    ci::ColorA colorY( CM_RGB, 0.0f, 1.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorY );
    gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );
    
    ci::ColorA colorZ( CM_RGB, 0.0f, 0.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorZ );
    gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );
    
    
    // DRAW TURTLE

    for (int i=0; i < mTurtles.size(); i++) {
        mTurtles[i].draw();
    }
    
    //testTurtle.draw();
    
    ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    gl::drawCube( mTurtles[0].mWorldPosition, Vec3f( 20.0f, 20.0f, 20.0f ) );
    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
    
    // DRAW ANGLE DATA TEXT
     glDisable( GL_LIGHTING );
     gl::setMatricesWindow( 1200, 800 );
     for (int i=0; i < mTurtles.size(); i++) {
     gl::drawString( textStartPosition[i], Vec2f(10.0f, 335.0f + 110.0f*i) );
     gl::drawString( textFinalAngle[i], Vec2f(10.0f, 355.0f + 110.0f*i) );
     gl::drawString( textPreviousAngle[i], Vec2f(10.0f, 375.0f + 110.0f*i) );
     gl::drawString( textSetAngle[i], Vec2f(10.0f, 395.0f + 110.0f*i) );
     gl::drawString( textFinalPosition[i], Vec2f(10.0f, 415.0f + 110.0f*i) );
     gl::drawString( textLocalCoordinates[i], Vec2f(10.0f, 435.0f + 110.0f*i) );
     gl::drawString( textWorldCoordinates[i], Vec2f(10.0f, 455.0f + 110.0f*i) );
     }
}

CINDER_APP_BASIC( AngleConversionApp, RendererGl )
