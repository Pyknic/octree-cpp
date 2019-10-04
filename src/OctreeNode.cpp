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
T OctreeNode<T, SIZE>::get(uint8_t) const {
    return value;
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

template<typename T, uint8_t SIZE>
Octree<T>* OctreeNode<T, SIZE>::fill(const AABB& bounds, const Shape &shape, const T &val) {
    switch (shape.intersects(bounds)) {
        case DISJOINT: return nullptr;
        case INTERSECTS: {
            Octree<T>* newTree{ new OctreeBranch<T, SIZE>{this->value} };
            newTree->fill(bounds, shape, val);
            return newTree;
        }
        case CONTAINS: {
            return new OctreeNode<T, SIZE>{val};
        }
    }
}

template<typename T, uint8_t SIZE>
uint8_t OctreeNode<T, SIZE>::test(const typename Octree<T>::TPredicate &predicate) const {
    return predicate(value) ? (uint8_t) 0xff : (uint8_t) 0x00;
}

template<typename T, uint8_t SIZE>
void OctreeNode<T, SIZE>::forEach(const AABB &bounds,
                                  const typename Octree<T>::BranchAction &action,
                                  uint8_t) const {
    action(this, bounds);
}
