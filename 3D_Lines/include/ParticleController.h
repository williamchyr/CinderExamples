#pragma once
#include "cinder/Channel.h"
#include "Particle.h"
#include "cinder/Perlin.h"
#include <list>

class ParticleController {
 public:
	ParticleController();
	
	
	
	void update( const ci::Vec2i &mouseLoc );
	void draw();
	void addParticles( int amt, int width, int height  );
	void removeParticles( int amt );
	
	std::list<Particle>	mParticles;
	
};