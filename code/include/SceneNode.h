#ifndef SCENENODE_HPP
#define SCENENODE_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <vector>
#include <memory>
#include <algorithm>
#include <cassert>
#include <Command.h>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
public:
	typedef					std::unique_ptr<SceneNode> Ptr;

public:
							SceneNode();

	void					attachChild(Ptr child);
	Ptr						detachChild(const SceneNode& node);

	void					update(sf::Time dt);

	void					removeWrecks();

	sf::Vector2f			getWorldPosition() const;
	sf::Transform			getWorldTransform() const;

	void					onCommand(Command& command, sf::Time dt);
	virtual unsigned int	getCategory() const;

	virtual bool			isMarkedForRemoval() const;
	virtual bool			isDestroyed() const;

private:
	virtual void			draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
	void					drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void			updateCurrent(sf::Time dt);
	void					updateChildren(sf::Time dt);

private:
	std::vector<Ptr>		mChildren;
	SceneNode*				mParent;

};

#endif