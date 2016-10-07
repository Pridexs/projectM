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

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <State.h>
#include <World.h>
#include <Player.h>

class GameState : public State
{
public:
    GameState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);

private:
    World				mWorld;
    Player&				mPlayer;
};

#endif