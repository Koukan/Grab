/*
 * Reactor.hpp
 *
 *  Created on: Nov 8, 2011
 *      Author: snap
 */

#ifndef REACTOR_HPP_
#define REACTOR_HPP_

#include <functional>
#include <set>
#include <unordered_map>

#include "NetDef.hpp"
#include "network.h"
#include "Socket.hpp"
#include "Clock.hpp"

NET_BEGIN_NAMESPACE

class EventHandler;

/*!
 \brief Base class of Event demultiplixer
 */
class NET_DLLREQ Reactor
{
public:
	Reactor();
	virtual ~Reactor();


	/*!
	 \brief Event codes
	 */
	enum	EventMask
	{
		READ = 1, //!< the read event
		WRITE = 2, //!< the write event
		ACCEPT = 4 //!< the accept event
	};

	/*!
	 \brief Register a socket and call the handler when a event specified in the mask is detected

	 \param socket Socket to register
	 \param handler Handler to be called
	 \param mask Mask of event desired
	 \details Events can be ORed ex : READ | WRITE
	 \return false on failure, true otherwise
	 */
	virtual bool	registerHandler(Socket &socket, EventHandler &handler, int mask) = 0;
	/*!
	 \brief Remove a Socket already registered

	 \param socket

	 \return false on failure, true otherwise
	 */
	virtual bool	removeHandler(Socket &socket) = 0;
	/*!
	 \brief Wait for events to happen 

	 \param timeout Timeout to return 
	 \details If the timeout is -1, then the wait is infinite, may not be true on specific platform
	 \return -1 on failure or timeout
	 */
	virtual int	waitForEvent(int timeout = -1) = 0;
	/*!
	 \brief Schedule a timer

	 \param handler Handler to be called when the timer trigger
	 \param delay Relative time of the trigger in miliseconds
	 \param repeat Automatically repeat the timer
	 \details If you want to wait infinitly and use timers, on some cases you must call this function before waitForEvent 
	 \return Timer id
	 */
	virtual	uint32_t	scheduleTimer(EventHandler &handler, size_t delay, bool repeat = false);
	uint32_t		scheduleTimer(std::function<void (size_t)>, size_t delay, bool repeat = false);
	/*!
	 \brief	Cancel a timer 

	 \param handler Associated Id to the timer

	 \return false on failure, true otherwise
	 */
	virtual	bool		cancelTimer(uint32_t timerId);
	/*!
	 \brief Break the waitForEvent even infinite
	 \details Not thread-safe, must be called from the same thread as waitForEvent
	 */
	virtual void	stopWaiting();

protected:
	struct	timerdata
	{
		bool operator<(timerdata const &other) const;

		size_t		timeout;
		size_t		timerId;
		EventHandler	*handler;
		size_t		delay;
		bool		repeat;
	};
	typedef std::unordered_map<uint32_t, std::multiset<timerdata>::iterator> mapTimeout;

	uint32_t		getTimerId();
	int				handleTimers(int &timeout);

	bool			_wait;
	uint32_t		_timerIdgenerator;
	Clock			_clock;
	std::multiset<timerdata>	_listTimeout;
	mapTimeout		_mapHandler;
};

NET_END_NAMESPACE

#endif /* REACTOR_HPP_ */
