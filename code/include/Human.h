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

#ifndef HUMAN_HPP
#define HUMAN_HPP

#include <Entity.h>
#include <ResourceIdentifiers.h>

class Human : public Entity
{
public:
    enum Type
    {
        Player,
        TypeCount,
    };

public:
    explicit				Human(Type type, const TextureHolder& textures);

    virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void			updateCurrent(sf::Time dt);

    virtual void			addEntityToWorld(b2World& world);

    virtual unsigned int	getCategory() const;

    virtual bool			isDestroyed() const;
    virtual bool			isMarkedForRemoval() const;

    void					jump();
    void					collectCoin();

    bool*					getIsGrounded();
    void					inGround(bool grounded);

private:
    

private:
    Type					mType;
    sf::Sprite				mSprite;
    b2Body*					mBody;

    sf::Clock				jumpTimer;

    bool					mGrounded;
    bool					mDead;

    //Animation
    sf::IntRect				mTextureSize;
    unsigned int			mWalkFrame;
    sf::Clock				mWalkClock;
    bool					mWalkingLeft;

    float					playerSpeed;

};

#endif
