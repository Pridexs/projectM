#include <ContactListener.h>

#include <Entity.h>
#include <Human.h>
#include <Pickup.h>


#include <iostream>

void ContactListener::BeginContact(b2Contact* contact)
{
	void* userData1 = contact->GetFixtureA()->GetUserData();
	void* userData2 = contact->GetFixtureB()->GetUserData();

	if (userData1 == NULL && userData2 == NULL)
		return;

	if ((int)userData1 == 3 && userData2 == NULL)
	{
		*isGrounded = true;
	}
	else if (userData1 == NULL && (int)userData2 == 3)
	{
		*isGrounded = true;
		return;
	}

	if (userData1 == NULL || userData2 == NULL || (int)userData1 == 3 || (int)userData2 == 3)
	{
		return;
	}

	Entity *ent1 = (Entity*)userData1;
	Entity *ent2 = (Entity*)userData2;

	if (ent1->getEntityType() == Entity::Type::PickupT && ent2->getEntityType() == Entity::Type::HumanT)
	{
		static_cast<Human*>(ent2)->collectCoin();
		static_cast<Pickup*>(ent1)->setPicked();
	}
	
	if (ent1->getEntityType() == Entity::Type::HumanT && ent2->getEntityType() == Entity::Type::PickupT)
	{
		static_cast<Human*>(ent1)->collectCoin();
		static_cast<Pickup*>(ent2)->setPicked();
	}

}

void ContactListener::EndContact(b2Contact* contact)
{
	void* userData1 = contact->GetFixtureA()->GetUserData();
	void* userData2 = contact->GetFixtureB()->GetUserData();

	if (userData1 == NULL && userData2 == NULL)
		return;
	if ((int)userData1 == 3 && userData2 == NULL)
	{
		*isGrounded = false;
		return;
	}
	else if (userData1 == NULL && (int)userData2 == 3)
	{
		*isGrounded = false;
		return;
	}
}

void ContactListener::setFoot(bool* isGrounded)
{
	this->isGrounded = isGrounded;
}