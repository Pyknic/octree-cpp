#include "OctreeLeaf.h"

template<typename T>
OctreeLeaf<T>::OctreeLeaf(const T & value) : Octree<T>{}, value{value} {}

template<typename T>
OctreeLeaf<T>::~OctreeLeaf() = default;

template<typename T>
bool OctreeLeaf<T>::isLeafAndEqualTo(const T & value) const
{
	return this->value == value;
}

template<typename T>
T OctreeLeaf<T>::get(uint8_t x, uint8_t y, uint8_t z) const
{
	return value;
}

template<typename T>
Octree<T>* OctreeLeaf<T>::set(uint8_t x, uint8_t y, uint8_t z, const T& value)
{
	this->value = value;
	return nullptr;
}
