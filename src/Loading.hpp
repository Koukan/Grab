#pragma once
#include <list>
#include "GameState.hpp"
#include "AudioManager.hpp"
#include "BulletCommand.hpp"

class Loading : public GameState
{
public:
	Loading();
	~Loading();
	virtual void	onStart();
	virtual	void	update(double elapseTime = 0);

private:
	void			escape(const CL_InputEvent &event);
	void			click(const CL_InputEvent &event);
	void			slowTest(const CL_InputEvent &event);
	void			buttonClick();

	BulletCommand		*_bullet;
};
