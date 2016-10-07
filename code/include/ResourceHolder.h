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

#ifndef RESOURCEHOLDER_HPP
#define RESOURCEHOLDER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class ResourceHolder
{
public:
	void							load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void							load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource&						get(Identifier id);
	const Resource&					get(Identifier id) const;

private:
	void							insertResource(Identifier id, std::unique_ptr<Resource> resource);

private:
	std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;

};

#include "ResourceHolder.inl"
#endif