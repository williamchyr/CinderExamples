#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"
#include "cinder/Color.h"
#include "cinder/Perlin.h"
#include <vector>

class Particle {
 public:
	Particle();
	Particle( ci::Vec3f );
	void update(const ci::Vec2i &mouseLoc );
	void draw();
	
	ci::Vec3f	mLoc;
	ci::Vec3f	mVel;
	
	
	
	float		mDecay;
	float		mRadius;
	float		mScale;
	
	float		mMass;
	
	int			mAge;
	int			mLifespan;
	float		mAgePer;
	bool		mIsDead;
	
	float		angle;
	
	int			angleDivision;
	
	float		radiusValue;
	
	float		color1;
	float		color2;
	float		color3;
	
	float		rotationAngle;
	int			rotationAngleDivision;
	float		rotationRadius;
	float		rotationValue;
	
};