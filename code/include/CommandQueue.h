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

#ifndef COMMANDQUEUE_HPP
#define COMMANDQUEUE_HPP

#include <Command.h>
#include <queue>

class CommandQueue
{
public:
    void					push(const Command& command);
    Command					pop();
    bool					isEmpty() const;

private:
    std::queue<Command>		mQueue;
};

#endif