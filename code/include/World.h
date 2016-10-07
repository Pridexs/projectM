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

#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>

#include <ResourceHolder.h>
#include <ResourceIdentifiers.h>
#include <SceneNode.h>
#include <SpriteNode.h>
#include <Human.h>
#include <CommandQueue.h>


#include <tmx/MapLoader.h>
#include <tmx/tmx2box2d.h>

#include <Box2D\Box2D.h>
#include <ContactListener.h>

#include <array>

class World : sf::NonCopyable
{

private:
	enum Layer
	{
		Background,
		Stage,
		LayerCount
	};

public:
	explicit							World(sf::RenderWindow& window);
	void								update(sf::Time dt);
	void								draw();

	CommandQueue&						getCommandQueue();

private:
	void								loadTextures();
	void								buildScene();

private:
	sf::RenderWindow&					mWindow;
	sf::View							mWorldView;
	TextureHolder						mTextures;
	SceneNode							mSceneGraph;
	std::array<SceneNode*, LayerCount>	mSceneLayers;
	Human*								mPlayer;

	sf::IntRect						mWorldBounds;
	sf::Vector2f						mSpawnPosition;

	b2World								mb2World;
	ContactListener						mCL;

	std::vector<std::unique_ptr<sf::Shape>> debugBoxes;
	std::vector<DebugShape>					debugShapes;
	std::map<b2Body*, sf::CircleShape> dynamicShapes;

	CommandQueue						mCommandQueue;
};

#endif