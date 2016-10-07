#include <DataTables.h>


#include <Pickup.h>

#include <functional>
#include <vector>

std::vector<HumanData> initializeHumanData()
{
	std::vector<HumanData> data(Human::TypeCount);

	data[Human::Player].speed = 20.f;
	data[Human::Player].texture = Textures::Player;

	data[Human::Player].textureRect = sf::IntRect(0, 0, 72, 92); //Fix this later

	data[Human::Player].walkFrames.push_back(sf::IntRect(0, 0, 72, 92));
	data[Human::Player].walkFrames.push_back(sf::IntRect(73, 0, 72, 92));
	data[Human::Player].walkFrames.push_back(sf::IntRect(146, 0, 72, 92));
	data[Human::Player].walkFrames.push_back(sf::IntRect(0, 98, 72, 92));
	data[Human::Player].walkFrames.push_back(sf::IntRect(73, 98, 72, 92));
	data[Human::Player].walkFrames.push_back(sf::IntRect(146, 98, 72, 92));


	data[Human::Player].jumpFrames.push_back(sf::IntRect(438, 93, 67, 94));

	data[Human::Player].jumpInterval = 0.2f;
	data[Human::Player].frameTime = 0.1f;

	return data;
}

std::vector<PickupData> initializePickupData()
{
	std::vector<PickupData> data(Pickup::TypeCount);

	// BEGIN COIN
	data[Pickup::Coin].texture = Textures::PickupCoin;

	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0,0,50,50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 50, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 100, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 150, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 200, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 250, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 300, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 350, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 400, 50, 50));
	data[Pickup::Coin].pickupFrames.push_back(sf::IntRect(0, 450, 50, 50));

	data[Pickup::Coin].frameTime = 0.1f;

	data[Pickup::Coin].textureRect = sf::IntRect(0, 0, 50, 50);

	data[Pickup::Coin].action = std::bind(&Human::collectCoin, std::placeholders::_1);
	// END COIN

	return data;
}