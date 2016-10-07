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