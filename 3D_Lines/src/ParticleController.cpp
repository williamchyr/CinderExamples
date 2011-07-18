#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;

ParticleController::ParticleController()
{	
}

void ParticleController::update(  const Vec2i &mouseLoc )
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ) {
		if( p->mIsDead ){
			p = mParticles.erase( p );
		} else {
			p->update(mouseLoc);
			++p;
		}
	}
	
	
}

void ParticleController::draw()
{
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
}

void ParticleController::addParticles( int amt, int width, int height )
{
	for( int i=0; i<amt; i++ )
	{
		Vec3f loc = Rand::randVec3f();
		
		loc.x *= Rand::randInt(-width, width );
		loc.y *= Rand::randInt(0, height);
		loc.z *= Rand::randInt(-500, 200);
		Vec2f velOffset = Rand::randVec2f() * Rand::randFloat( 1.0f, 10.0f );
				
		mParticles.push_back( Particle( loc) );
	}
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}

