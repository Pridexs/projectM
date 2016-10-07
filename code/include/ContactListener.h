#ifndef CONTACTLISTNER_HPP
#define CONTACTLISTNER_HPP

#include <Box2D\Box2D.h>

class ContactListener : public b2ContactListener
{
public:
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);

	void		setFoot(bool* isGrounded);

private:
	bool*		isGrounded;
};

#endif