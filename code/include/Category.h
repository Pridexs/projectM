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