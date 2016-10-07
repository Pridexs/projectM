#ifndef DATATABLES_HPP
#define DATATABLES_HPP

#include <ResourceIdentifiers.h>

#include <SFML\System\Time.hpp>
#include <SFML\Graphics\Rect.hpp>

#include <vector>

#include <Human.h>

struct HumanData
{
	float						speed;
	Textures::ID				texture;
	sf::IntRect					textureRect;
	std::vector<sf::IntRect>	walkFrames;
	std::vector<sf::IntRect>	jumpFrames;
	float						frameTime;
	float						jumpInterval;
};

struct PickupData
{
	Textures::ID					texture;
	sf::IntRect						textureRect;
	std::vector<sf::IntRect>		pickupFrames;
	float							frameTime;
	std::function<void(Human&)>		action;
};	

std::vector<HumanData>			initializeHumanData();
std::vector<PickupData>			initializePickupData();

#endif