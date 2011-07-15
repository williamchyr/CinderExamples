#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "ParticleController.h"

using namespace ci;
using std::list;
using std::vector;

ParticleController::ParticleController()
{
    angle = 25;
}

void ParticleController::update( const Perlin &perlin, const Channel32f &channel, const Vec2i &mouseLoc )
{
	/*
	for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ) {
		if( p->mIsDead ){
			p = mParticles.erase( p );
		} else {
			p->update( perlin, channel, mouseLoc );
			++p;
		}
	}
	*/
	
	for (int i = 0; i < mParticles.size(); i++ ) {
		mParticles[i].update();
		
		coordinates[i] = mParticles[i].mLoc;
		if (mParticles[i].mIsDead){
			//mParticles[i].clear();
		}
	}

}

void ParticleController::draw()
{
	/*
	 for( list<Particle>::iterator p = mParticles.begin(); p != mParticles.end(); ++p ){
		p->draw();
	}
	 */
	
	for (int i = 0; i < mParticles.size(); i++ ) {
		mParticles[i].draw();
	}
    
    if (coordinates.size() > 1) {
        for (int i = 0; i < coordinates.size()-1; i++ ) {
            gl::drawLine(coordinates[i], coordinates[i+1]);
        }
    }
}

void ParticleController::addParticles( int amt, const Vec2i &mouseLoc, const Vec2f &mouseVel )
{
	for( int i=0; i<amt; i++ )
	{
		angle = i * ( (2 * M_PI)/amt);
        
        //Vec2f loc = mouseLoc + Rand::randVec2f() * 5.0f;
		Vec2f loc;
        loc.x = mouseLoc.x + 50*sin(angle);
        loc.y = mouseLoc.y + 50*cos(angle);
        
        coordinates.push_back(loc);
        
        //Vec2f velOffset = Rand::randVec2f() * Rand::randFloat( 1.0f, 5.0f );
		//Vec2f vel = mouseVel * 0.375f + velOffset;
        
        Vec2f vel;
        vel.set( sin(angle), cos(angle) );
        vel *= Rand::randFloat(3, 10);
        
		mParticles.push_back( Particle( loc, vel ) );
	}
}

void ParticleController::removeParticles( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		mParticles.pop_back();
	}
}

