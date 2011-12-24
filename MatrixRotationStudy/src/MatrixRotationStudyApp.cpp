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
    
    // GET END POSITION IN WORLD COORDINATES (TO BE PASSED TO NEXT OBJECT)
    Vec3f getWorldEndPosition( Vec3f localStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition );
    
    // GET TOTAL ROTATION MATRIX (TO BE PASSED TO NEXT OBJECT)
    Matrix44<float> getTotalLocalRotation( Vec3f localStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition );
    
    Vec3f mLocalStartPosition; //where the local basis translate to
    Vec3f mLocalBasisRotation; //How the local basis is rotated
    Vec3f mLocalObjectRotation; //how the object is rotated in relation to the local basis
    
    Vec3f mLocalEndPosition;
    Vec3f mWorldEndPosition;
    
    Matrix44 <float> mTotalRotationMatrix;

    
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
    
    mLocalStartPosition.set(100.0f, 100.0f, 0.0f);
    mLocalBasisRotation.set(20.0f, 30.0f, 45.0f);
    mLocalObjectRotation.set(40.0f, 130.0f, 60.0f);
    mLocalEndPosition.set( 0.0f, 300.0f, 0.0f); //I know what the local end position is because I'm drawing a cylinder of length 300. 
    
    mWorldEndPosition = getWorldEndPosition( mLocalStartPosition, mLocalBasisRotation, mLocalObjectRotation, mLocalEndPosition );
    
    mTotalRotationMatrix = getTotalLocalRotation( mLocalStartPosition, mLocalBasisRotation, mLocalObjectRotation, mLocalEndPosition );
    
    mShowCube = true;
    
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

Vec3f MatrixRotationStudyApp::getWorldEndPosition( Vec3f localStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition )
{
    Matrix44 <float> m4;
    Vec3f worldEndPosition;
    
    m4 = m4.createTranslation( localStartPosition );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(( localBasisRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, ( localBasisRotation.y/180.0f)*M_PI, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localBasisRotation.z/180.0f)*M_PI) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    printMatrix( m4 );
    
    worldEndPosition = m4.transformPoint( localEndPosition );
    cout << "translate and rotate: " + toString( worldEndPosition .x) + ", " + toString( worldEndPosition .y) + ", " + toString( worldEndPosition .z) + "\n";
    
    return worldEndPosition;
}

Matrix44<float> MatrixRotationStudyApp::getTotalLocalRotation( Vec3f localStartPosition, Vec3f localBasisRotation, Vec3f localObjectRotation, Vec3f localEndPosition )
{
    Matrix44 <float> m4;
    Vec3f totalLocalRotation;
    
    m4.setToIdentity();
    
    m4.rotate( Vec3f(( localBasisRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, ( localBasisRotation.y/180.0f)*M_PI, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localBasisRotation.z/180.0f)*M_PI) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(( localObjectRotation.x/180.0f)*M_PI, 0.0f, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, ( localObjectRotation.y/180.0f)*M_PI, 0.0f) );
    printMatrix( m4 );
    
    m4.rotate( Vec3f(0.0f, 0.0f, ( localObjectRotation.z/180.0f)*M_PI) );
    printMatrix( m4 );
    
    return m4;
    
}

void MatrixRotationStudyApp::draw()
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
    
    // DRAW CUBES
    
    gl::pushMatrices();
    gl::translate( mLocalStartPosition );
    gl::rotate( mLocalBasisRotation );
    
        // DRAW AXIS
        ci::ColorA colorX1( CM_RGB, 1.0f, 0.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorX1 );
        gl::drawLine( Vec3f(-500.0f, 0.0f, 0.0f), Vec3f(500.0f, 0.0f, 0.0f) );
        
        ci::ColorA colorY1( CM_RGB, 1.0f, 1.0f, 0.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorY1 );
        gl::drawLine( Vec3f(0.0f, -500.0f, 0.0f), Vec3f(0.0f, 500.0f, 0.0f) );
        
        ci::ColorA colorZ1( CM_RGB, 0.0f, 1.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	colorZ1 );
        gl::drawLine( Vec3f(0.0f, 0.0f, -500.0f), Vec3f(0.0f, 0.0f, 500.0f) );
        
        ci::ColorA color1( CM_RGB, 1.0f, 1.0f, 1.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
        
        gl::pushMatrices();
        gl::rotate( mLocalObjectRotation ); 
            gl::drawCylinder( 20.0f, 20.0f, 300.0f );
        gl::popMatrices();
    
    gl::popMatrices();

    /*
    gl::pushMatrices();
    gl::translate( mWorldEndPosition );
    gl::rotate( mLocalBasisRotation );
    gl::rotate( mLocalObjectRotation );
    if (!mShowCube) {
        ci::ColorA color2( CM_RGB, 1.0f, 1.0f, 0.0f, 1.0f );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color2 );
        gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(30.0f, 30.0f, 30.0f) );
        
        gl::drawCylinder( 10.0f, 10.0f, 200.0f );
    } 
    gl::popMatrices();
    */
    if (!mShowCube) {
        gl::pushMatrices();
        gl::translate( mWorldEndPosition );
        gl::multModelView(  mTotalRotationMatrix );
        
            ci::ColorA color3( CM_RGB, 1.0f, 0.0f, 1.0f, 1.0f );
            glMaterialfv( GL_FRONT, GL_DIFFUSE,	color3 );
            gl::drawCube( Vec3f(0.0f, 0.0f, 0.0f), Vec3f(30.0f, 30.0f, 30.0f) );
            
            gl::drawCylinder( 10.0f, 10.0f, 300.0f );
            
                        
        gl::pushMatrices();
        gl::rotate( Vec3f(0.0f, 0.0f, 30.0f) );
            ci::ColorA color4( CM_RGB, 0.0f, 1.0f, 1.0f, 1.0f );
            glMaterialfv( GL_FRONT, GL_DIFFUSE,	color4 );
            gl::drawCylinder( 10.0f, 10.0f, 200.0f );
        gl::popMatrices();
        gl::popMatrices();
    } 
    // DRAW PARAMS WINDOW
	params::InterfaceGl::draw();
}


CINDER_APP_BASIC( MatrixRotationStudyApp, RendererGl )

