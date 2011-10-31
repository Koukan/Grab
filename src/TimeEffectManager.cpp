#include "TimeEffectManager.hpp"

TimeEffectGroup::TimeEffectGroup()
	: _timeEffect(1)
{
}

double		TimeEffectGroup::getTimeEffect()
{
  return _timeEffect;
}

void		TimeEffectGroup::setTimeEffect(double timeEffect)
{
  _timeEffectList.push_back(timeEffect);
  update(timeEffect);
}

void		TimeEffectGroup::removeTimeEffect()
{
  double	slow = _timeEffectList.front();

  _timeEffectList.pop_front();
  update(slow);
}

void		TimeEffectGroup::update(double timeEffect)
{
  if (_timeEffect == timeEffect)
  {
    double	time = 1000;
    for (std::list<double>::iterator it = _timeEffectList.begin();
	 it != _timeEffectList.end(); it++)
    {
      if (*it < time)
	time = *it;
    }
    _timeEffect = time;
  }
  if (_timeEffectList.empty())
    _timeEffect = 1;
}

TimeEffectManager::TimeEffectManager()
{
}

TimeEffectManager::~TimeEffectManager()
{
  for (std::map<std::string, TimeEffectGroup*>::iterator it = _timeEffectMap.begin();
	it != _timeEffectMap.end(); it++)
    delete it->second;
}

TimeEffectGroup	*TimeEffectManager::getTimeEffect(std::string const &name)
{
  std::map<std::string, TimeEffectGroup*>::iterator	it = _timeEffectMap.find(name);

  if (it != _timeEffectMap.end())
    return it->second;
  TimeEffectGroup	*group = new TimeEffectGroup;
  _timeEffectMap[name] = group;
  return group;
}

void		TimeEffectManager::setTimeEffect(std::string const &name,
						 double timeEffect)
{
  TimeEffectGroup	*group = getTimeEffect(name);

  group->setTimeEffect(timeEffect);
}

void		TimeEffectManager::removeTimeEffect(std::string const &name)
{
  TimeEffectGroup	*group = getTimeEffect(name);

  group->removeTimeEffect();
}
