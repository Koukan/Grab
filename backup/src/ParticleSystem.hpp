#pragma once

#include <map>
#include <SPK.h>
#include "PhysicObject.hpp"

class ParticleSystem: public PhysicObject, public SPK::System
{
public:
	ParticleSystem(double x = 0, double y = 0);
	virtual ~ParticleSystem();

	virtual void							setX(double x);
	virtual void							setY(double y);
	virtual void							setPosition(double x, double y);
	virtual void							draw(double elapseTime);
	/*SPK::Group							*addGroup(std::string const &name);
	void										addRenderer(SPK::Renderer *renderer, std::string const &name);
	SPK::GL::GLPointRenderer		*addPointRenderer(std::string const &name);
	SPK::GL::GLLineRenderer		*addLineRenderer(std::string const &name);
	SPK::GL::GLLineTrailRenderer	*addLineTrailREnderer(std::string const &name);
	SPK::GL::GLQuadRenderer		*addQuadRenderer(std::string const &name);
	bool										addEmitter(SPK::Emitter *emitter, const std::string &name, const std::string &group);
	SPK::NormalEmitter				*addNormalEmitter(std::string const &name, const std::string &group);
	SPK::RandomEmitter				*addRandomEmitter(std::string const &name, const std::string &group);
	SPK::SphericEmitter				*addSphericEmitter(std::string const &name, const std::string &group);
	SPK::StaticEmitter					*addStaticEmitter(std::string const &name, const std::string &group);
	SPK::StraightEmitter				*addStraightEmitter(std::string const &name, const std::string &group);

	// getter
	SPK::Group							*getGroup(std::string const &name);
	SPK::Renderer						*getRenderer(std::string const &name);

private:

	std::map<std::string, SPK::Emitter*>		_emitters;
	std::map<std::string, SPK::Group*>		_groups;*/
};
