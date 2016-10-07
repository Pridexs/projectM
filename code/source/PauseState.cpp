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

#include <PauseState.h>

#include <iostream>

PauseState::PauseState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Vector2f windowSize = context.window->getView().getSize();
	sf::Vector2f windowPosition = context.window->getView().getCenter();
	mBox.setSize(sf::Vector2f(windowSize.x * 0.25f, windowSize.y * 0.25));
	mBox.setFillColor(sf::Color::Black);
	mBox.setOrigin(mBox.getSize().x / 2.f, mBox.getSize().y / 2.f);
	mBox.setPosition(windowPosition.x, windowPosition.y);
}


void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBox);
}

bool PauseState::update(sf::Time dt)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
	{
		return false;
	}

	if (event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	return false;
}