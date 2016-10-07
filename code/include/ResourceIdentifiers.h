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

#ifndef RESOURCEIDENTIFIERS_HPP
#define RESOURCEIDENTIFIERS_HPP


namespace sf
{
	class Texture;
	class Font;
}


namespace Textures
{
	enum ID
	{
		Player,
		Kib,
		Sky,
		Ground,
		TileMap1,
		PickupCoin,
	};
}

namespace Fonts
{
	enum ID
	{
		Main,
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>		  FontHolder;
#endif