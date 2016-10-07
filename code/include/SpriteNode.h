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

#ifndef SPRITENODE_HPP
#define SPRITENODE_HPP

#include <SceneNode.h>
#include <SFML/Graphics.hpp>

class SpriteNode : public SceneNode
{
public:
    explicit				SpriteNode(const sf::Texture& texture);
                            SpriteNode(const sf::Texture& texture, const sf::IntRect& rect);

private:
    virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite				mSprite;
};

#endif