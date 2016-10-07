#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <SceneNode.h>
#include <Box2D\Box2D.h>

class Entity : public SceneNode
{
public:
	enum Type
	{
		HumanT,
		PickupT,
		Other
	};

public:
	void			setVelocity(sf::Vector2f velocity);
	void			setVelocity(float vx, float vy);

	void			addEntityToWorld(b2World& world);

	void			accelerate(b2Vec2 mImpulse);
	void			accelerate(float vx, float vy);
	
	void			setEntityType(Type type);
	Entity::Type	getEntityType();

	sf::Vector2f	getVelocity() const;

	virtual bool	isDestroyed() const;

private:
	virtual void	updateCurrent(sf::Time dt);

private:
	sf::Vector2f	mVelocity;
	
protected:
	b2Vec2			mImpulse;
	Type			mEntityType;
	
};

#endif