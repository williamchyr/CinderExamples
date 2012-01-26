#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
using std::vector;

Particle::Particle()
{
}

Particle::Particle( Vec3f pos, Vec3f vel, bool followed )
{
	mPos			= pos;
	mTailPos		= pos;
	mVel			= vel;
	mVelNormal		= Vec3f::yAxis();
	mAcc			= Vec3f::zero();
	
	mNeighborPos	= Vec3f::zero();
	mNumNeighbors	= 0;
	mMaxSpeed		= Rand::randFloat( 2.5f, 4.0f );
	mMaxSpeedSqrd	= mMaxSpeed * mMaxSpeed;
	mMinSpeed		= Rand::randFloat( 1.0f, 1.5f );
	mMinSpeedSqrd	= mMinSpeed * mMinSpeed;
	
	mColor			= ColorA( 1.0f, 1.0f, 1.0f, 1.0f );
		
	mDecay			= 0.99f;
	mRadius			= 1.0f;
	mLength			= 5.0f;
	mFear			= 1.0f;
	mCrowdFactor	= 1.0f;
	
	mIsDead			= false;
	mFollowed		= followed;
    
    r = Rand::randFloat(0.0f, 1.0f);
    g = Rand::randFloat(0.2f, 0.5f);
    b = Rand::randFloat(0.5f, 1.0f);
}

void Particle::pullToCenter( const Vec3f &center )
{
	Vec3f dirToCenter = mPos - center;
	float distToCenter = dirToCenter.length();
	float distThresh = 400.0f;
	
	if( distToCenter > distThresh ){
		dirToCenter.normalize();
		float pullStrength = 0.00025f;
		mVel -= dirToCenter * ( ( distToCenter - distThresh ) * pullStrength );
	}
}


void Particle::update( bool flatten )
{	
    
    //CREATE RIBBON
    
    Vec3f posOffset1 = mPos;
    Vec3f posOffset2 = mPos;
    
    posOffset1.x = mPos.x - 5;
    posOffset2.x = mPos.x + 5;
    
    
    ribbonPositions.push_back(posOffset1);
    ribbonPositions.push_back(posOffset2);
    
    if (ribbonPositions.size() > 50) {
        ribbonPositions.erase( ribbonPositions.begin(), ribbonPositions.begin()+2);
    }
    
    float alphaValue = 1.0f;
    
    ribbonAlpha.push_back( alphaValue );
    ribbonAlpha.push_back( alphaValue ); //we're pushing alphaValue twice on purpose as we're drawing quads
    
    if (ribbonAlpha.size() > 50) {
        ribbonAlpha.erase( ribbonAlpha.begin(), ribbonAlpha.begin()+2);
    }
    
    for (int i = 0; i < ribbonAlpha.size(); i++) {
        ribbonAlpha[i] = ribbonAlpha[i] - 0.02f;
    }

    //CROWD BEHAVIOR
    
	mCrowdFactor -= ( mCrowdFactor - ( 1.0f - mNumNeighbors * 0.02f ) ) * 0.1f;
	mCrowdFactor = constrain( mCrowdFactor, 0.5f, 1.0f );
	
	mFear -= ( mFear - 0.0f ) * 0.2f;
	
	if( flatten )
		mAcc.z = 0.0f;
	
	mVel += mAcc;
	mVelNormal = mVel.normalized();
	
	limitSpeed();
	
	
	mPos += mVel;
	if( flatten )
		mPos.z = 0.0f;
	
	mTailPos = mPos - ( mVelNormal * mLength );
	mVel *= mDecay;
	
	float c = math<float>::min( mNumNeighbors/50.0f, 1.0f );
	mColor = ColorA( CM_HSV, 1.0f - c, c, c * 0.5f + 0.5f, 1.0f );
	
	mAcc = Vec3f::zero();
	mNeighborPos = Vec3f::zero();
	mNumNeighbors = 0;
}

void Particle::limitSpeed()
{
	float maxSpeed = mMaxSpeed + mCrowdFactor;
	float maxSpeedSqrd = maxSpeed * maxSpeed;
	
	float vLengthSqrd = mVel.lengthSquared();
	if( vLengthSqrd > maxSpeedSqrd ){
		mVel = mVelNormal * maxSpeed;
		
	} else if( vLengthSqrd < mMinSpeedSqrd ){
		mVel = mVelNormal * mMinSpeed;
	}
	mVel *= (1.0 + mFear );
}

void Particle::draw()
{
	glColor4f( mColor );
	gl::drawVector( mPos - mVelNormal * mLength, mPos - mVelNormal * mLength * 0.75f, mLength * 0.7f, mRadius );
	
	
}

void Particle::drawTail()
{
	glColor4f( mColor );
	glVertex3fv( mPos );
	glColor4f( ColorA( mColor.r, mColor.g, mColor.b, 0.01f ) );
	glVertex3fv( mTailPos );
}

void Particle::drawRibbon()
{
    gl::color( ColorA( r, g, b, 1.0f ) );
	gl::drawSphere( mPos, mRadius, 20 );
    
    glBegin(GL_QUAD_STRIP);
    
    for (int i = 0; i < ribbonPositions.size(); i++) {
        //gl::color( ColorA( r, g, b, ribbonAlpha[i] ) );
        ci::ColorA color( CM_RGB, r, g, b, ribbonAlpha[i] );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color );
        
        ci::ColorA color1( CM_RGB, g, b, r, ribbonAlpha[i] );
        glMaterialfv( GL_FRONT, GL_DIFFUSE,	color1 );
        
        glVertex3f ( ribbonPositions[i] );
    }
    glEnd();
    
}

void Particle::addNeighborPos( Vec3f pos )
{
	mNeighborPos += pos;
	mNumNeighbors ++;
}


