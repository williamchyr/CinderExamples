//
//  ParticleController.h
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011. All rights reserved.
//

#include "cinder/Perlin.h"
#include "Particle.h"
#include <list>


class ParticleController {
public:
	ParticleController();
	void update(const Perlin &perlin);
	void draw();
	void addParticles( int amt, const Vec2i &mouseLoc, const Vec2f &mouseVel );
	void removeParticles( int amt ); 
	
	std::list<Particle>	mParticles;

};