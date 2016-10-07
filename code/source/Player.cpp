#include <Player.h>
#include <Human.h>
#include <Category.h>
#include <CommandQueue.h>
#include <Command.h>


#include <iostream>
struct HumanMovement
{
	HumanMovement(float vx, float vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Human& human, sf::Time) const
	{
		human.accelerate(velocity);
	}

	b2Vec2 velocity;
};


struct HumanJump
{
	HumanJump()
	{
	}

	void operator() (Human& human, sf::Time) const
	{
		human.jump();
	}
};

Player::Player()
{
	mKeyBinding[sf::Keyboard::A] = MoveLeft;
	mKeyBinding[sf::Keyboard::D] = MoveRight;
	mKeyBinding[sf::Keyboard::W] = Jump;

	initializeActions();
	
	for (auto &pair : mActionBinding)
	{
		pair.second.category = Category::PlayerHuman;
	}
	
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
	for (std::pair<sf::Keyboard::Key, Action> pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			commands.push(mActionBinding[pair.second]);
		}
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (std::map<sf::Keyboard::Key, Action>::iterator itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
	{
		if (itr->second == action)
		{
			mKeyBinding.erase(itr++);
		}
		else
		{
			itr++;
		}
	}
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (std::pair<sf::Keyboard::Key, Action> pair : mKeyBinding)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Unknown;
}

bool Player::isRealtimeAction(Action action)
{
	switch (action)
	{
	case MoveLeft:
	case MoveRight:
	case Jump:
		return true;

	default:
		return false;
	}
}

void Player::initializeActions()
{
	const float playerSpeed = 20.f;
	mActionBinding[MoveLeft].action = derivedAction<Human>(HumanMovement(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Human>(HumanMovement(+playerSpeed, 0.f));
	mActionBinding[Jump].action = derivedAction<Human>(HumanJump());
}