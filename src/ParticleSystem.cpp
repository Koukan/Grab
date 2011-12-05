#include "ParticleSystem.hpp"
#include "RendererManager.hpp"
#include "RectHitBox.hpp"

ParticleSystem::ParticleSystem(double x, double y)
	: PhysicObject(*new RectHitBox(x, y, 1, 1))
{
}

ParticleSystem::~ParticleSystem()
{
}

void				ParticleSystem::setX(double x)
{
	this->setPosition(x, this->_y);
}

void				ParticleSystem::setY(double y)
{
	this->setPosition(this->_x, y);
}

void				ParticleSystem::setPosition(double x, double y)
{
	std::vector<SPK::Emitter*>::const_iterator	lit;
	double														rx, ry;

	GameObject::setPosition(x, y);
	rx = this->getX() / static_cast<double>(RendererManager::get().getWidth());
	ry = this->getY() / static_cast<double>(RendererManager::get().getHeight());
	for (std::vector<SPK::Group*>::const_iterator it = this->getGroups().begin();
			it != this->getGroups().end(); it++)
	{
		for (lit = (*it)->getEmitters().begin(); lit != (*it)->getEmitters().end(); lit++)
		{
			(*lit)->getZone()->setPosition(SPK::Vector3D(static_cast<float>(rx), static_cast<float>(ry), 0));
		}
	}
}

void				ParticleSystem::draw(double elapseTime)
{
	if (this->update(static_cast<float>(elapseTime * 0.001)))
	  this->render();
	else
		delete this;
}

/*SPK::Group	*ParticleSystem::addGroup(std::string const &name)
{
	std::map<std::string, Group*>::iterator		it = _groups.find(name);
	SPK::Group												*group;

	if (it == _groups.end())
	{
		group = SPK::Group::create();
		_groups[name] = group;
	}
	else
		group = it->second;
	return group;
}

void				ParticleSystem::addRenderer(SPK::Renderer *renderer, std::string const &name)
{
	SPK::Group												*group = addGroup(name);

	if (group->getRenderer())
		delete group->getRenderer();
	group->setRenderer(renderer);
}

SPK::GL::GLPointRenderer		*ParticleSystem::addPointRenderer(std::string const &name)
{
	SPK::GL::GLPointRenderer		*renderer = SPK::GL::GLPointRenderer::create();

	addRenderer(renderer, name);
	return renderer;
}

SPK::GL::GLLineRenderer		*ParticleSystem::addLineRenderer(std::string const &name)
{
	SPK::GL::GLLineRenderer		*renderer = SPK::GL::GLLineRenderer::create();

	addRenderer(renderer, name);
	return renderer;
}

SPK::GL::GLLineTrailRenderer	*ParticleSystem::addLineTrailREnderer(std::string const &name)
{
	SPK::GL::GLLineTrailRenderer	*renderer = SPK::GL::GLLineTrailRenderer::create();

	addRenderer(renderer, name);
	return renderer;
}

SPK::GL::GLQuadRenderer		*ParticleSystem::addQuadRenderer(std::string const &name)
{
	SPK::GL::GLQuadRenderer		*renderer = SPK::GL::GLQuadRenderer::create();

	addRenderer(renderer, name);
	return renderer;
}

bool										ParticleSystem::addEmitter(SPK::Emitter *emitter, const std::string &name, const std::string &group)
{
	std::map<std::string, SPK::Emitter*>		it = _emitters.find(name);
	if (it != _emitters.end())
		return false;
	SPK::Group											*groups = this->addGroup(group);
	_emitters[name] = emitter;
	groups->addEmitter(emitter);
	return true;
}

SPK::Group							*ParticleSystem::getGroup(std::string const &name)
{
	std::map<std::string, Group*>::iterator	it = _groups[name];

	if (it != _groups.end())
		return it->second;
	return 0;
}

SPK::Renderer						*ParticleSystem::getRenderer(std::string const &name)
{
	SPK::Group						*group = this->getGroup(name);

	if (group)
		return group->getRenderer();
	return 0;
}*/
