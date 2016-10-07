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

#include <World.h>

#include <Pickup.h>

/* PUT THIS IN A BETTER PLACE LATER*/
const float kPixelsPerMeter = 100.0f;
const float kGravity = 15.0f;

World::World(sf::RenderWindow& window)
    : mWindow(window)
    , mWorldView(window.getDefaultView())
    , mSpawnPosition( (mWorldView.getSize().x / 2.f) - 500.0f, 0 /*mWorldView.getSize().y / 2.f*/)
    , mWorldBounds(0.f, 0.f, 2800.f, 910.f)
    , mPlayer(nullptr)
    , mb2World(b2Vec2(0.0f, kGravity))
    , debugBoxes()
    , debugShapes()
    , dynamicShapes()
    , mCL()
{

    // CHECK THIS LATER
    mb2World.SetAllowSleeping(true);
    mb2World.SetContinuousPhysics(true);
    mb2World.SetContactListener(&mCL);

    loadTextures();
    buildScene();
}

void World::loadTextures()
{
    mTextures.load(Textures::Player, "resources/Textures/p1_spritesheet.png");
    mTextures.load(Textures::Kib, "resources/Textures/kib.png");
    mTextures.load(Textures::Sky, "resources/Textures/BGSkyBlue.png");
    mTextures.load(Textures::Ground, "resources/Textures/ground.png");
    mTextures.load(Textures::PickupCoin, "resources/Textures/coin_spritesheet.png");
}

void World::buildScene()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.attachChild(std::move(layer));
    }


    // Prepare the tiled background
    sf::Texture& texture = mTextures.get(Textures::Sky);
    sf::IntRect textureRect(mWorldBounds);
    texture.setRepeated(true);

    /*
        BEGIN LOAD TMX MAP
    */
    std::unique_ptr<tmx::MapLoader> ml(new tmx::MapLoader("resources/Levels"));
    ml->Load("level2.tmx");

    const std::vector<tmx::MapLayer>& layers = ml->GetLayers();
    for (const auto& l : layers)
    {
        if (l.name == "Static")
        {
            for (const auto& o : l.objects)
            {
                b2Body* b = tmx::BodyCreator::Add(o, this->mb2World);
            }
        }
        if (l.name == "Coins")
        {
            for (const auto& o : l.objects)
            {
                std::unique_ptr<Pickup> coin(new Pickup(Pickup::Coin, mTextures));
                coin->setPosition(o.GetPosition());
                coin->setEntityType(Entity::Type::PickupT);
                coin->addEntityToWorld(mb2World);
                
                mSceneLayers[Stage]->attachChild(std::move(coin));
            }
        }
        if (l.name == "SpawnPoint")
        {
            for (const auto& o : l.objects)
            {
                mSpawnPosition = o.GetPosition();
                std::string a = o.GetName();
                std::cout << "SIGH: " << a << std::endl;
            }
        }
    }
    mWorldBounds = sf::IntRect(0.0f, 0.0f, ml->GetMapSize().x, ml->GetMapSize().y);
    

    /*
        END LOAD TMX MAP
    */

    // Add the background sprite to the scene
    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, mWorldBounds));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    mSceneLayers[Stage]->attachChild(std::move(ml));

    // Add player
    std::unique_ptr<Human> leader(new Human(Human::Player, mTextures));
    mPlayer = leader.get();
    mPlayer->setPosition(mSpawnPosition);
    mPlayer->addEntityToWorld(mb2World);
    mPlayer->setEntityType(Entity::Type::HumanT);

    mCL.setFoot(mPlayer->getIsGrounded());

    mSceneLayers[Stage]->attachChild(std::move(leader));

}

void World::update(sf::Time dt)
{

    mPlayer->accelerate(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
    {
        mSceneGraph.onCommand(mCommandQueue.pop(), dt);
    }

    mb2World.Step(dt.asSeconds(), 8, 3);
    mSceneGraph.update(dt);
    mSceneGraph.removeWrecks();

    /*
        BEGIN VIEW POSITION CAMERA
    */
    
    sf::View view;
    view.setSize(sf::Vector2f(1280.f, 720));
    sf::Vector2f playerPosition = mPlayer->getWorldPosition();
    sf::Vector2f center;
    if (playerPosition.x - (1280.f / 2.f) < 0)
    {
        center.x = 1280.f / 2.f;
    }
    else if (playerPosition.x + (1280.f / 2.f) > mWorldBounds.width)
    {
        center.x = mWorldBounds.width - (1280.f / 2.f);
    }
    else
    {
        center.x = playerPosition.x;
    }

    if (playerPosition.y - (720 / 2.f) < 0)
    {
        center.y = 720.f / 2.f;
    }
    else if (playerPosition.y + (720 / 2.f) > mWorldBounds.height)
    {
        center.y = mWorldBounds.height - (720.f / 2.f) ;
    }
    else
    {
        center.y = playerPosition.y;
    }
    
    view.setCenter(center);
    mWindow.setView(view);
    
    //2800 910
    /*
        END VIEW POSITION CAMERA
    */

}

void World::draw()
{
    mWindow.draw(mSceneGraph);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}