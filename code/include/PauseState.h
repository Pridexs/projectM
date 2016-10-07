#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include <State.h>
#include <SFML\Graphics\RectangleShape.hpp>

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context);

	virtual void		draw();
	virtual bool		update(sf::Time dt);
	virtual bool		handleEvent(const sf::Event& event);

private:
	sf::RectangleShape	mBox;
};

#endif