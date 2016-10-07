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

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <CommandQueue.h>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <Human.h>
#include <map>


class Player
{
public:
										enum Action
										{
											MoveLeft,
											MoveRight,
											Jump,
											ActionCount,
										};

	void								assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key					getAssignedKey(Action action) const;
public:
										Player();
	void								handleEvent(const sf::Event& event, CommandQueue& commands);
	void								handleRealTimeInput(CommandQueue& commands);


private:
	static bool							isRealtimeAction(Action action);
	void								initializeActions();

private:
	std::map<sf::Keyboard::Key, Action>	mKeyBinding;
	std::map<Action, Command>			mActionBinding;
};

#endif