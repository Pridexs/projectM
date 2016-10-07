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

#include <Entity.h>

#include <math.h>

void Entity::setVelocity(sf::Vector2f velocity)
{
    this->mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    this->mVelocity.x = vx;
    this->mVelocity.y = vy;
}

void Entity::accelerate(b2Vec2 impulse)
{
    
    mImpulse = impulse;

}

void Entity::accelerate(float vx, float vy)
{
    mImpulse.x = vx;
    mImpulse.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return this->mVelocity;
}

void Entity::updateCurrent(sf::Time dt)
{
    
}

void Entity::addEntityToWorld(b2World& world)
{
    //Default
}

void Entity::setEntityType(Type type)
{
    mEntityType = type;
}

Entity::Type Entity::getEntityType()
{
    return mEntityType;
}

bool Entity::isDestroyed() const
{
    return false;
}