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

#include <Pickup.h>
#include <DataTables.h>

namespace
{
	std::vector<PickupData> Table = initializePickupData();
}

Pickup::Pickup(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.get(Table[type].texture), Table[type].textureRect)
	, mFrameTimer()
	, mFrame(0)
	, mPicked(false)
{
	mFrameTimer.restart();
}

Pickup::~Pickup()
{

}

void Pickup::apply(Human& player) const
{
	Table[mType].action(player);
}

void Pickup::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

void Pickup::addEntityToWorld(b2World& world)
{
	const float kPixelsPerMeter = 100.0f;

	// Body Definition
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(
		this->getWorldPosition().x / kPixelsPerMeter,
		this->getWorldPosition().y / kPixelsPerMeter
		);	bodyDef.fixedRotation = true;

	this->mBody = world.CreateBody(&bodyDef);

	// Shape Definition
	b2PolygonShape Shape;
	Shape.SetAsBox((Table[mType].textureRect.width / 2.f) / kPixelsPerMeter, (Table[mType].textureRect.height / 2.f) / kPixelsPerMeter);

	// Fixture Definition
	b2FixtureDef FixtureDef;
	FixtureDef.density = 1.f;
	FixtureDef.friction = 1.f;
	FixtureDef.shape = &Shape;
	FixtureDef.isSensor = true;

	b2Fixture* pickupFixture =  mBody->CreateFixture(&FixtureDef);
	pickupFixture->SetUserData(this);
}

void Pickup::setPicked()
{
	mPicked = true;
}

void Pickup::updateCurrent(sf::Time dt)
{
	if (mFrameTimer.getElapsedTime().asSeconds() > Table[mType].frameTime)
	{
		mFrame++;
		if (mFrame >= Table[mType].pickupFrames.size())
		{
			mFrame = 0;
		}
		mSprite.setTextureRect(Table[mType].pickupFrames.at(mFrame));
		mFrameTimer.restart();
	}
}

bool Pickup::isDestroyed() const
{
	return mPicked;
}

bool Pickup::isMarkedForRemoval() const
{
	return isDestroyed();
}

void Pickup::removeWrecks()
{
	mBody->GetWorld()->DestroyBody(mBody);
}