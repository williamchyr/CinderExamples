//
//  Particle.cpp
//  BoidsWithTails
//
//  Created by Willy Chyr on 11-09-21.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#include "Particle.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

using namespace ci;
using namespace ci::app;
using std::list;
using std::vector;

Particle::Particle() 
{
}

Particle::Particle( Vec3f loc, Vec3f vel )
{
    mLoc = loc;
    mVel = vel;
    mAcc = Vec3f::zero();
    
    mRadius = 5.0f;
    mAge = 0;
    
    r = Rand::randFloat(0.0f, 1.0f);
    g = Rand::randFloat(0.2f, 0.5f);
    b = Rand::randFloat(0.5f, 1.0f);
}

void Particle::pullToCenter( const Vec3f &center )
{
	Vec3f dirToCenter = mLoc - center;
	float distToCenter = dirToCenter.length();
	float maxDistance = 300.0f;
	
	if( distToCenter > maxDistance ){
		dirToCenter.normalize();
		float pullStrength = 0.0001f;
		mVel -= dirToCenter * ( ( distToCenter - maxDistance ) * pullStrength );
	}
}	

void Particle::update() 
{
    mLoc.x = mLoc.x - 5; //This is to shift the tail so that the sphere is in the middle
    
    Vec3f mLocOffset;
    mLocOffset = mLoc;
   
    mLocOffset.x = mLoc.x + 10;
    mLocOffset.y = mLoc.y;
    mLocOffset.z = mLoc.z;
    
    tailPositions.push_back(mLoc);
    tailPositions.push_back(mLocOffset);
     
    if (tailPositions.size() > 50) {
        tailPositions.erase( tailPositions.begin(), tailPositions.begin()+2);
    }
    
    float alphaValue = 1.0f;
    
    tailAlpha.push_back( alphaValue );
    tailAlpha.push_back( alphaValue ); //we're pushing alphaValue twice on purpose as we're drawing quads
    
    if (tailAlpha.size() > 50) {
        tailAlpha.erase( tailAlpha.begin(), tailAlpha.begin()+2);
    }
    
    for (int i = 0; i < tailAlpha.size(); i++) {
        tailAlpha[i] = tailAlpha[i] - 0.03f;
    }
    
    
    std::string tailPositionSize; 
    
    tailPositionSize = toString( tailPositions.size() );
    console() << "tailPosition Size: " + tailPositionSize << std::endl;
    
    mAge++;
    
    mVel = mVel + mAcc;
    mLoc = mLoc + mVel;
    
}

void Particle::draw() 
{
    gl::color( ColorA( r, g, b, 1.0f ) );
	gl::drawSphere( mLoc, mRadius, 20 );
    
    glLineWidth(20);
    
    
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < tailPositions.size(); i++) {
        gl::color( ColorA( r, g, b, tailAlpha[i] ) );
        glVertex3f ( tailPositions[i] );
    }
    glEnd();
   
}
