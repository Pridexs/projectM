/*
 * This code is from projectM a 2D side scroller using SFML.
 * It was made using the help of the SFML Game Development Book
 * 
 * If you have any questions, please contact me at
 * 		pridexs.com
 *
 * For more information visit the repo for this project at:
 * 		github.com/pridexs
 *
 * Alexandre Maros - 2016
 */

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