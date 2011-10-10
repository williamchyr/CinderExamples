//
//  ParticleController.cpp
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011. All rights reserved.
//

#include "ParticleController.h"
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"


using namespace ci;
using namespace ci::app;
using std::list;

ParticleController::ParticleController()
{
}

void ParticleController::update(const Perlin &perlin) {
    for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ) {
		if( p->mIsDead ){
			p = mParticles.erase( p );
		} else {
			p->update(perlin);
			++p;
		}
	}
}

void ParticleController::draw() {
    
    
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ) {
        p->draw();
    }
    
    glBegin(GL_TRIANGLE_STRIP);
   
    for (list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ) { 
         //glColor4f( sin( getElapsedSeconds() ), 1.0f - p->mYPercentage, 1.0f - p->mXPercentage, 1.0f);
        glVertex3f( p->mLoc.x, p->mLoc.y, 0.0f);
    }
    
    glEnd();
  
}

void ParticleController::addParticles( int amt, const Vec2i &mouseLoc, const Vec2f &mouseVel ){
    
    for (int i =0; i < amt; i++) {
        
        Vec3f loc = Vec3f( mouseLoc.x, mouseLoc.y, mouseLoc.x) + Rand::randVec3f() * 5.0f;
		Vec3f velOffset = Rand::randVec3f() * Rand::randFloat( 1.0f, 5.0f );
		Vec3f vel = Vec3f( mouseVel.x, mouseVel.y, mouseVel.x) * 0.5f + velOffset;
		mParticles.push_back( Particle( loc, vel ) );

    }
    
}