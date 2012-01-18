#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc )
{
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= 0.0f;
	mRadius	= 4.0f;

}	
	
void Particle::update()
{
	mRadius = ( sin( mLoc.y * mLoc.x * mLoc.x) + 1.0f ) * 3.0f;
	
	//mLoc += mDir * mVel;
    
    r = sin(mLoc.y * mLoc.x);
    g = sin(mLoc.x * mLoc.x);
    b = sin(mLoc.y * mLoc.y);
    
    mColor = Color( r, g, b);
}

void Particle::draw()
{
	gl::color( mColor );
	gl::drawSolidCircle( mLoc, mRadius );
}
