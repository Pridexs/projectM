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