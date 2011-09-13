//
//  Particle.cpp
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Particle.h"

#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;

Particle::Particle()
{
}

Particle::Particle( Vec2f loc, Vec2f vel )
{
	mLoc	= loc;
	mVel	= vel;
	mRadius	= 4.0f;
    
    mXPercentage = 0;
    mYPercentage = 0;
    
    mAge        = 0;
    mLifespan   = 100;
    mAgePercentage = 0;
    mIsDead     = false;
    
    mDecay  = Rand::randFloat(0.97f, 0.99f);
    
}	

void Particle::update(const Perlin &perlin)
{
	// get Perlin noise value based on my location and
	// elapsed seconds and turn this noise value into an angle.
	float nX = mLoc.x * 0.005f;
	float nY = mLoc.y * 0.005f;
	float nZ = app::getElapsedSeconds() * 0.1f;
	float noise = perlin.fBm( nX, nY, nZ );
	float angle = noise * 15.0f;
	Vec2f noiseVector( cos( angle ), sin( angle ) );
    
	mVel += noiseVector * 0.2f * ( 1.0f - mAgePercentage );
    
	mLoc += mVel;
    
    mVel *= mDecay;
    
    
    if (mLoc.x > 0 && mLoc.x < getWindowWidth() ) {
        mXPercentage = (float) mLoc.x / (float) getWindowWidth();
    }
    
    if (mLoc.y > 0 && mLoc.y < getWindowWidth() ) {
        mYPercentage = (float) mLoc.y / (float) getWindowHeight();
    }
    
    if (mAge > mLifespan) {
        mIsDead = true;
    } else {
        mAge++;
        mAgePercentage = (float) mAge / (float) mLifespan;
    }
    
}

void Particle::draw()
{
	//gl::color( mColor );
	//gl::drawSolidCircle( mLoc, mRadius );
}
