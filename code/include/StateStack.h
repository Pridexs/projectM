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

#ifndef STATESTACK_HPP
#define STATESTACK_HPP


#include <State.h>
#include <StateIdentifiers.h>
#include <ResourceIdentifiers.h>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit		StateStack(State::Context context);

    template <typename T>
    void			registerState(States::ID stateID);

    void			update(sf::Time dt);
    void			draw();
    void			handleEvent(const sf::Event& event);

    void			pushState(States::ID stateID);
    void			popState();
    void			clearState();

    bool			isEmpty() const;

private:
    State::Ptr		createState(States::ID stateID);
    void			applyPendingChanges();
    
private:
    struct PendingChange
    {
        explicit	PendingChange(Action action, States::ID stateID = States::None);

        Action		action;
        States::ID	stateID;
    };

private:
    std::vector<State::Ptr>								mStack;
    std::vector<PendingChange>							mPendingList;
    State::Context										mContext;
    std::map<States::ID, std::function<State::Ptr()>>	mFactories;

};

template <typename T>
void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = [this] ()
    {
        return State::Ptr(new T(*this, mContext));
    };
}

#endif
