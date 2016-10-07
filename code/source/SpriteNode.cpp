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

#include <SpriteNode.h>

#include <SFML/Graphics/RenderTarget.hpp>

SpriteNode::SpriteNode(const sf::Texture& texture)
	: mSprite(texture)
{
}

SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
	: mSprite(texture, textureRect)
{
}

void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}