#pragma once
#include <list>
#include "GameState.hpp"
#include "AudioManager.hpp"
#include "Bullet.hpp"
#include "bulletmlparser.h"

class Loading : public GameState
{
public:
	Loading();
	~Loading();
	virtual void	onStart();
	virtual	void	update(int elapseTime = 0);

private:
	void			escape(const CL_InputEvent &event);
	void			click(const CL_InputEvent &event);

	Bullet			*_bullet;
	BulletMLParser		*_parser;
};
