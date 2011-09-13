//
//  ParticleController.h
//  ParticleSystemExperiment
//
//  Created by Willy Chyr on 11-09-13.
//  Copyright 2011. All rights reserved.
//

#include "Particle.h"
#include <list>


class ParticleController {
public:
	ParticleController();
	void update();
	void draw();
	void addParticles( int amt, const Vec2i &mouseLoc, const Vec2f &mouseVel );
	void removeParticles( int amt ); 
	
	std::list<Particle>	mParticles;

};