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

#ifndef CATEGORY_HPP
#define CATEGORY_HPP

namespace Category
{
	enum Type
	{
		None = 0,
		Scene = 1 << 0,
		PlayerHuman = 1 << 1,
	};
}

#endif