#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"


using namespace ci;

Particle::Particle()
{
}

Particle::Particle( Vec3f loc)
{
	mLoc			= loc;
	//mVel			= vel;
	
	mVel.set(1.0f, 1.0f, 0.0f);
	
	mVel = mVel*Rand::randInt(1, 5);

	mDecay			= Rand::randFloat( 0.96f, 0.99f );
	radiusValue		= Rand::randFloat( 10.0f, 40.0f );
	mScale			= 3.0f;
	mAge			= 0;
	mLifespan		= Rand::randInt( 250, 400 );
	mAgePer			= 1.0f;
	mIsDead			= false;
	
	angle = 0.0f;
	angleDivision = Rand::randInt(100, 500);
	
	rotationAngle = 0.0f;
	rotationAngleDivision = Rand::randInt(100, 600);
	rotationRadius = Rand::randFloat(100, 700);
	
	
	color1			= Rand::randFloat(0.0f, 0.5f);
	color2			= Rand::randFloat(0.7f, 1.0f);
	color3			= Rand::randFloat(0.5f, 1.0f);
	
}	

void Particle::update( const Vec2i &mouseLoc )
{	
	
	angle += M_PI/angleDivision; 	
	mLoc += mVel;	
	mRadius = radiusValue*sin(angle);
	
	rotationAngle += M_PI/rotationAngleDivision;
	
	mLoc.x = rotationRadius*sin(rotationAngle);
	mLoc.z = rotationRadius*cos(rotationAngle);
	
	
		
	mAge++;
	if( mAge > mLifespan ) mIsDead = true;
	mAgePer = 1.0f - ( (float)mAge/(float)mLifespan );
}

void Particle::draw()
{	
	glColor3f( color1, color2, color3 );
	//gl::drawSolidCircle( mLoc, mRadius * mAgePer );
	
	gl::drawSphere( mLoc, mRadius * mAgePer, 64);
}



