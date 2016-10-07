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

#ifndef PICKUP_HPP
#define PICKUP_HPP

#include <Entity.h>
#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>

class Human;

class Pickup : public Entity
{
public:
    enum Type
    {
        Coin,
        TypeCount
    };

public:
                            Pickup(Type type, const TextureHolder& textures);
                            ~Pickup();

    void					apply(Human& player) const;

    virtual bool			isDestroyed() const;
    virtual bool			isMarkedForRemoval() const;

    virtual void					removeWrecks();

    void					addEntityToWorld(b2World& world);
    void					setPicked();

protected:
    virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void			updateCurrent(sf::Time dt);

private:

    b2Body*					mBody;
    Type					mType;
    sf::Sprite				mSprite;

    sf::Clock				mFrameTimer;
    unsigned int			mFrame;

    bool					mPicked;
};

#endif