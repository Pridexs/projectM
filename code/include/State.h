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

#ifndef STATE_HPP
#define STATE_HPP


#include <StateIdentifiers.h>
#include <ResourceIdentifiers.h>
#include <Player.h>

#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

#include <memory>

class StateStack;

class State
{
public:
    typedef std::unique_ptr<State> Ptr;
    struct Context
    {
        Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Player& player);

        sf::RenderWindow*	window;
        TextureHolder*		textures;
        FontHolder*			fonts;
        Player*				player;
    };

public:
                    State(StateStack& stack, Context context);
    virtual			~State();

    virtual void	draw() = 0;
    virtual bool	update(sf::Time dt) = 0;
    virtual bool	handleEvent(const sf::Event& event) = 0;

protected:
    void			requestStackPush(States::ID stateID);
    void			requestStackPop();
    void			requestStateClear();

    Context			getContext() const;

private:
    StateStack*		mStack;
    Context			mContext;
};

#endif