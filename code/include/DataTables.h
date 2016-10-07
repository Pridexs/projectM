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