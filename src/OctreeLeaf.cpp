#include "OctreeLeaf.h"

template<typename T>
OctreeLeaf<T>::OctreeLeaf(const T & value) : Octree<T>{}, value{value} {}

template<typename T>
OctreeLeaf<T>::~OctreeLeaf() = default;

template<typename T>
bool OctreeLeaf<T>::isLeafAndEqualTo(const T& val) const {
	return this->value == val;
}

template<typename T>
T OctreeLeaf<T>::get(uint8_t, uint8_t, uint8_t) const {
	return value;
}

template<typename T>
Octree<T>* OctreeLeaf<T>::set(uint8_t, uint8_t, uint8_t, const T& val) {
	this->value = val;
	return nullptr;
}
