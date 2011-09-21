//
//  ParticleController.h
//  BoidsWithTails
//
//  Created by Willy Chyr on 11-09-21.
//  Copyright 2011 Willy Chyr. All rights reserved.
//

#pragma once
#include "Particle.h"
#include <list>

class ParticleController {
public:
	ParticleController();
    
	//void applyForce( float zoneRadius, float lowerThresh, float higherThresh, float attractStrength, float repelStrength, float orientStrength );
    void applyForce(float zoneRadius, float lowerThresh, float higherThresh, float attractStrength, float repelStrength, float alignStrength );
	void pullToCenter( const ci::Vec3f &center );
	void update(bool flatten);
	void draw();
	void addParticles( int amt );
	
	std::list<Particle>	mParticles;
	ci::Vec3f mParticleCentroid;
	int mNumParticles;
};