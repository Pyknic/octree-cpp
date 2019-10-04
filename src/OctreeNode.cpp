#include "OctreeNode.h"
#include "OctreeBranch.h"

template <typename T, uint8_t SIZE>
OctreeNode<T, SIZE>::OctreeNode(const T& value) : 
	Octree<T>{}, value{value} {}

template <typename T, uint8_t SIZE>
OctreeNode<T, SIZE>::~OctreeNode() = default;

template<typename T, uint8_t SIZE>
bool OctreeNode<T, SIZE>::isLeafAndEqualTo(const T & val) const {
	return this->value == val;
}

template<typename T, uint8_t SIZE>
T OctreeNode<T, SIZE>::get(uint8_t, uint8_t, uint8_t) const {
	return value;
}

template<typename T, uint8_t SIZE>
Octree<T>* OctreeNode<T, SIZE>::set(uint8_t x, uint8_t y, uint8_t z, const T& val) {
	Octree<T>* newTree{ new OctreeBranch<T, SIZE>{this->value} };
	newTree->set(x, y, z, val);
	return newTree;
}

