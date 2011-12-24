#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "cinder/Utilities.h" 
#include "cinder/matrix.h"

using namespace ci;
using namespace ci::app;
using namespace std;

GLfloat mat_diffuse[]		= { 0.3, 0.5, 0.8, 1.0 };
GLfloat light1_diffuse[]    = { 1.0, 1.0, 1.0, 1.0 };
GLfloat mat_ambient[]		= { 0.6, 0.3, 0.4, 1.0 };

class MatrixRotationStudyApp : public AppBasic {
public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );	
    void keyDown( KeyEvent event );
	void update();
	void draw();
    
    void printMatrix( Matrix44 <float> m);
    
    // LOCAL TO WORLD COORDINATES (TO BE PASSED TO NEXT OBJECT)
    // using two angles
    //Vec3f getWorldPosition( Vec3f worldStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition );

    // using one matrix and one angle
    Vec3f getWorldPosition( Vec3f worldStartPosition, Matrix44<float> totalLocalRotation, Vec3f localEndPosition );
    
    
    // GET TOTAL ROTATION MATRIX (TO BE PASSED TO NEXT OBJECT)
    //using two angles
    Matrix44<float> getTotalLocalRotation( Vec3f localBasisRotation, Vec3f localObjectRotation );
    
    //using one matrix and one angle
    Matrix44<float> getTotalLocalRotation( Matrix44<float> previousRotation, Vec3f localObjectRotation );
    
    //
    Vec3f mWorldStartPosition0; //where the local basis translate to
    Vec3f mLocalBasisRotation0; //How the local basis is rotated
    Vec3f mLocalObjectRotation0; //how the object is rotated in relation to the local basis
    
    Vec3f mLocalEndPosition0;
    Vec3f mWorldEndPosition0;
    
    Matrix44 <float> mTotalRotationMatrix0;
    
    // 
    Matrix44 <float> mPreviousRotationMatrix1;
    Matrix44 <float> mTotalRotationMatrix1;
    
    Vec3f mWorldStartPosition1;
    Vec3f mLocalObjectRotation1;
    Vec3f mLocalEndPosition1;
    Vec3f mWorldEndPosition1;
    
    //
    Matrix44 <float> mPreviousRotationMatrix2;
    Matrix44 <float> mTotalRotationMatrix2;
    
    Vec3f mWorldStartPosition2;
    Vec3f mLocalObjectRotation2;
    Vec3f mLocalEndPosition2;
    Vec3f mWorldEndPosition2;
    
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
    
    // SHOW CUBE
    bool mShowCube;
};

void MatrixRotationStudyApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1200, 800 );
	settings->setFrameRate( 60.0f );
}

void MatrixRotationStudyApp::setup()
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
    
    //PARAMS
    mParams = params::InterfaceGl( "Control Panel", Vec2i( 200, 160 ) );
    mParams.addParam( "Scene Rotation", &mSceneRotation );
    mParams.addParam( "Eye Distance", &mCameraDistance, "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w" );
    mParams.addParam( "X Angle", &xAngle, "min=0.0 max=360.0 step=5.0 keyIncr=r keyDecr=f" );
    mParams.addParam( "Y Angle", &yAngle, "min=0.0 max=360.0 step=5.0 keyIncr=t keyDecr=g" );
    mParams.addParam( "Z Angle", &zAngle, "min=0.0 max=360.0 step=5.0 keyIncr=y keyDecr=h" );
    
    mDirectional = 1.0f;
    
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	
	gl::enableDepthWrite();
	gl::enableDepthRead();
	gl::enableAlphaBlending();
    
    glDisable( GL_TEXTURE_2D );
    
    
    // Set up coordinates
    
    mWorldStartPosition0.set(100.0f, 100.0f, 0.0f);
    mLocalBasisRotation0.set(20.0f, 30.0f, 45.0f);
    mLocalObjectRotation0.set(0.0f, 30.0f, 30.0f);
    mLocalEndPosition0.set( 0.0f, 300.0f, 0.0f); //I know what the local end position is because I'm drawing a cylinder of length 300. 
    
    mTotalRotationMatrix0 = getTotalLocalRotation( mLocalBasisRotation0, mLocalObjectRotation0 );
    mWorldEndPosition0 = getWorldPosition( mWorldStartPosition0, mTotalRotationMatrix0, mLocalEndPosition0 );
    
    // first transfer
    mWorldStartPosition1 = mWorldEndPosition0;
    mLocalObjectRotation1 = mLocalObjectRotation0;
    mPreviousRotationMatrix1 = mTotalRotationMatrix0;
    mLocalEndPosition1.set( 0.0f, 300.0f, 0.0f);
    
    mTotalRotationMatrix1 = getTotalLocalRotation( mPreviousRotationMatrix1, mLocalObjectRotation1 ); 
    mWorldEndPosition1 = getWorldPosition( mWorldStartPosition1, mTotalRotationMatrix1, mLocalEndPosition1);
 
    // Second transfer
    mWorldStartPosition2 = mWorldEndPosition1;
    mLocalObjectRotation2 = mLocalObjectRotation0;
    mPreviousRotationMatrix2 = mTotalRotationMatrix1;
    mLocalEndPosition2.set( 0.0f, 300.0f, 0.0f);
    
    mTotalRotationMatrix2 = getTotalLocalRotation( mPreviousRotationMatrix2, mLocalObjectRotation2 ); 
    mWorldEndPosition2 = getWorldPosition( mWorldStartPosition2, mTotalRotationMatrix2, mLocalEndPosition2);

}

void MatrixRotationStudyApp::mouseDown( MouseEvent event )
{
}

void MatrixRotationStudyApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'z' ){
		mShowCube = ! mShowCube;
	}
}

void MatrixRotationStudyApp::update()
{
    //UPDATE CAMERA
    
    mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
    
    // mEye = Vec3f( 800.0f * sin(camAngle), 0.0f, 800.0f * cos( camAngle ) );
    mCam.lookAt( mEye, mCenter, mUp );
    gl::setMatrices( mCam );
    gl::rotate( mSceneRotation );
    
}

void MatrixRotationStudyApp::printMatrix( Matrix44 <float> m)
{
    cout << "\n";
    cout << toString(m.m00) + " " + toString(m.m01) + " " + toString(m.m02) + " " + toString(m.m03) +  "\n";
    cout << toString(m.m10) + " " + toString(m.m11) + " " + toString(m.m12) + " " + toString(m.m13) +  "\n";
    cout << toString(m.m20) + " " + toString(m.m21) + " " + toString(m.m22) + " " + toString(m.m23) +  "\n";
    cout << toString(m.m30) + " " + toString(m.m31) + " " + toString(m.m32) + " " + toString(m.m33) +  "\n";
    cout << "\n";
}   
/*
Vec3f MatrixRotationStudyApp::getWorldPosition( Vec3f worldStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition )
{
    Matrix44 <float> m4;
    Vec3f worldEndPosition;
    
    m4 = m4.createTranslation( worldStartPosition );
    
    m4.rotate( Vec3f(( localBasisRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    m4.rotate( Vec3f(0.0f, ( localBasisRotation.y/180.0f)*M_PI, 0.0f) );
    m4.rotate( Vec3f(0.0f, 0.0f, ( localBasisRotation.z/180.0f)*M_PI) );
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    
    worldEndPosition = m4.transformPoint( localEndPosition );
    cout << "translate and rotate: " + toString( worldEndPosition .x) + ", " + toString( worldEndPosition .y) + ", " + toString( worldEndPosition .z) + "\n";
    
    return worldEndPosition;
}
*/

Vec3f MatrixRotationStudyApp::getWorldPosition( Vec3f worldStartPosition, Matrix44<float> totalLocalRotation, Vec3f localEndPosition )
{
    Matrix44 <float> m4;
    Vec3f worldEndPosition;
    
    m4 = m4.createTranslation( worldStartPosition );
    m4 = m4*totalLocalRotation;
    
    worldEndPosition = m4.transformPoint( localEndPosition );
    cout << "translate and rotate: " + toString( worldEndPosition .x) + ", " + toString( worldEndPosition .y) + ", " + toString( worldEndPosition .z) + "\n";
    
    return worldEndPosition;
}

Matrix44<float> MatrixRotationStudyApp::getTotalLocalRotation( Vec3f localBasisRotation, Vec3f localObjectRotation)
{
    Matrix44 <float> m4;
    
    m4.setToIdentity();
    
    m4.rotate( Vec3f(( localBasisRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    m4.rotate( Vec3f(0.0f, ( localBasisRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localBasisRotation.z/180.0f)*M_PI) );
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    
    return m4;
    
}

Matrix44<float> MatrixRotationStudyApp::getTotalLocalRotation( Matrix44<float> previousRotation, Vec3f localObjectRotation )
{
    Matrix44 <float> m4;
    
    m4.setToIdentity();
    m4 = m4*previousRotation;
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    
    return m4;
}

void MatrixRotationStudyApp::draw()
{   
    // LIGHTING
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
    
    
    // DRAW OBJECT 0
    ci::ColorA color0( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color0 );
    
    gl::pushMatrices();
    gl::translate( mWorldStartPosition0 );
    gl::rotate( mLocalBasisRotation0 );
        
        gl::pushMatrices();
        gl::rotate( mLocalObjectRotation0 ); 
            gl::drawCylinder( 20.0f, 20.0f, 300.0f );
        gl::popMatrices();
    
    gl::popMatrices();

    // DRAW OBJECT 1
    ci::ColorA color1( CM_RGB, 1.0f, 0.0f, 1.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
    
    gl::pushMatrices();
    gl::translate( mWorldStartPosition1 );
    gl::multModelView(  mTotalRotationMatrix1 );
        gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(25.0f, 25.0f, 25.0f) );
        gl::drawCylinder( 10.0f, 10.0f, 300.0f );                  
    gl::popMatrices();
    
    // DRAW OBJECT 2
    ci::ColorA color2( CM_RGB, 1.0f, 1.0f, 0.0f, 1.0f );
    glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
    
    gl::pushMatrices();
    gl::translate( mWorldStartPosition2 );
    gl::multModelView(  mTotalRotationMatrix2 );
        gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(25.0f, 25.0f, 25.0f) );
        gl::drawCylinder( 10.0f, 10.0f, 300.0f );                  
    gl::popMatrices();

    
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( MatrixRotationStudyApp, RendererGl )

