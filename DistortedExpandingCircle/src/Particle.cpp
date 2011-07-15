#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc, Vec2f vel )
{
	mLoc			= loc;
	mVel			= vel;
    startLoc        = loc;
    
    mLoc += mVel*Rand::randInt( 1, 20 );

	mDecay			= Rand::randFloat( 0.96f, 0.99f );
	mRadius			= 0.0f;
	mScale			= 3.0f;
	mAge			= 0;
	mLifespan		= 200;
	mAgePer			= 1.0f;
	mIsDead			= false;
    
    angle1 = 0;
}	

void Particle::update(const Perlin &perlin)
{	
	
  angle1 += M_PI/25;
    
    // get Perlin noise value based on my location and
	// elapsed seconds and turn this noise value into an angle.
	
    float nX = mLoc.x * 0.5f;
	float nY = mLoc.y * 0.5f;
	float nZ = app::getElapsedSeconds() * 0.1f;
	float noise = perlin.fBm( nX, nY, nZ );
	//float angle = noise * 15.0f;
    /*
	Vec2f noiseVector( cos( angle ), sin( angle ) );

	mVel += noiseVector * 0.2f * ( 1.0f - mAgePer );
    */
    
    mLoc += mVel*(noise+1.0);
   // mLoc.x = startLoc.x + 120*sin(angle1);
   // mLoc.y = startLoc.y + 120*cos(angle1);
	//mLoc += mVel;
	//mVel *= mDecay;

	mRadius	= mScale * mAgePer;
	
	mAge++;
	if( mAge > mLifespan ) mIsDead = true;
	mAgePer = 1.0f - ( (float)mAge/(float)mLifespan );
}

void Particle::draw()
{
	//gl::drawSolidCircle( mLoc, mRadius * mAgePer );
    
	/*
    coordinates.push_back(mLoc);
    
    for (int i = 0; i < coordinates.size()-1; i++) {
        gl::drawLine( coordinates[i], coordinates[i+1] );
    }
	 */
	
}



