#include <Human.h>
#include <ResourceHolder.h>

#include <Category.h>
#include <DataTables.h>

#include <iostream>

namespace
{
	const std::vector<HumanData> Table = initializeHumanData();
}

Textures::ID toTextureID(Human::Type type)
{
	switch (type)
	{
	case Human::Player:
		return Textures::Player;
	}
	return Textures::Kib;
}

Human::Human(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].walkFrames.at(0))
	, mGrounded(false)
	, playerSpeed(Table[type].speed)
	, mWalkFrame(0)
	, mWalkClock()
	, mWalkingLeft(false)
	, mDead(false)
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

	mWalkClock.restart();

	jumpTimer.restart();
}

void Human::updateCurrent(sf::Time dt)
{
	const float kPixelsPerMeter = 100.0f;

	b2Vec2 position = mBody->GetPosition();
	setPosition(position.x * kPixelsPerMeter, position.y * kPixelsPerMeter);

	b2Vec2 currentVelocity = mBody->GetLinearVelocity();
	if (fabsf(currentVelocity.x) < 4.0f)
	{
		float x = mImpulse.x * dt.asSeconds();

		this->mBody->ApplyLinearImpulse(b2Vec2(x, 0.f), mBody->GetWorldCenter(), true);
	}
	else if ( (currentVelocity.x > 0 && mImpulse.x < 0) || (currentVelocity.x < 0 && mImpulse.x > 0))
	{
		float x = mImpulse.x * dt.asSeconds();

		this->mBody->ApplyLinearImpulse(b2Vec2(x, 0.f), mBody->GetWorldCenter(), true);
	}
	

	// PLAYER ANIMATION HANDLING
	if (!mGrounded) 
	{
		mSprite.setTextureRect(Table[mType].jumpFrames.at(0));
	}
	else
	{
		mSprite.setTextureRect(Table[mType].walkFrames.at(mWalkFrame));
	}

	if ((currentVelocity.x > 0 || currentVelocity.x < 0) && mWalkClock.getElapsedTime().asSeconds() > Table[mType].frameTime)
	{
		if (++mWalkFrame >= Table[mType].walkFrames.size())
			mWalkFrame = 0;
		mWalkClock.restart();
	}
	else if (currentVelocity.x == 0)
	{
		mWalkFrame = 0;
	}

	if (currentVelocity.x < 0 && !mWalkingLeft)
	{
		mSprite.setScale(-1.0f, 1.0f);
		mWalkingLeft = true;
	}
	else if (currentVelocity.x > 0 && mWalkingLeft)
	{
		mSprite.setScale(1.0f, 1.0f);
		mWalkingLeft = false;
	}
	// PLAYER ANIMATION HANDLING

}

void Human::jump()
{
	if (!mGrounded) return;
	if (jumpTimer.getElapsedTime().asSeconds() < 0.2f) return;

	b2Vec2 nImpulse;
	nImpulse.x = 0.0f;
	nImpulse.y = -5.3f;
	mBody->ApplyLinearImpulse(nImpulse, mBody->GetWorldCenter(), true);
	jumpTimer.restart();

}

void Human::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Human::addEntityToWorld(b2World& world)
{
	const float kPixelsPerMeter = 100.0f;

	// Body Definition
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(
		this->getWorldPosition().x / kPixelsPerMeter,
		this->getWorldPosition().y / kPixelsPerMeter
		);
	bodyDef.fixedRotation = true;

	this->mBody = world.CreateBody(&bodyDef);

	// Shape Definition
	b2PolygonShape Shape;
	Shape.SetAsBox((Table[mType].textureRect.width / 2.f) / kPixelsPerMeter, (Table[mType].textureRect.height / 2.f) / kPixelsPerMeter);

	// Fixture Definition
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 1.f;
	FixtureDef.shape = &Shape;
	
	b2Fixture* bodyFixture = mBody->CreateFixture(&FixtureDef);
	bodyFixture->SetUserData(this);

	//Sensor
	b2PolygonShape Sensor;
	Sensor.SetAsBox((40.0f / 2.f) / kPixelsPerMeter, (10.0f / 2.f) / kPixelsPerMeter, b2Vec2(0.f, ((Table[mType].textureRect.height / 2.0f) + 5.0f) / kPixelsPerMeter), 0);
	
	b2FixtureDef sensorFixture;
	sensorFixture.isSensor = true;
	sensorFixture.shape = &Sensor;
	b2Fixture* footSensorFixture = mBody->CreateFixture(&sensorFixture);
	footSensorFixture->SetUserData( (void*)3 );

	// Add boxes with friciton 0 to the right and left side of the player so it doesnt glue to the wall
	b2PolygonShape leftArm;
	leftArm.SetAsBox((2.0f / 2.f) / kPixelsPerMeter, (Table[mType].textureRect.height / 2.1f) / kPixelsPerMeter, b2Vec2((-70.0f / 2.f) / kPixelsPerMeter, 0.0f), 0);
	
	b2FixtureDef leftFixture;
	leftFixture.friction = 0.0f;
	leftFixture.shape = &leftArm;
	b2Fixture* leftArmFixture = mBody->CreateFixture(&leftFixture);

	b2PolygonShape rightArm;
	rightArm.SetAsBox((2.0f / 2.f) / kPixelsPerMeter, (Table[mType].textureRect.height / 2.1f) / kPixelsPerMeter, b2Vec2((+70.0f / 2.f) / kPixelsPerMeter, 0.0f), 0);

	b2FixtureDef rightFixture;
	rightFixture.friction = 0.0f;
	rightFixture.shape = &rightArm;
	b2Fixture* rightArmFixture = mBody->CreateFixture(&rightFixture);
}

unsigned int Human::getCategory() const 
{
	switch (mType)
	{
	case Player:
		return Category::PlayerHuman;
	}
	return ::Category::None;
}

void Human::inGround(bool grounded)
{
	mGrounded = grounded;
}

bool Human::isDestroyed() const
{
	return mDead;
}

void Human::collectCoin()
{
	std::cout << "COIN COLLECTED";
}

bool Human::isMarkedForRemoval() const
{
	return isDestroyed();
}

bool* Human::getIsGrounded()
{
	return &mGrounded;
}