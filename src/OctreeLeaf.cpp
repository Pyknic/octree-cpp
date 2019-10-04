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
T OctreeLeaf<T>::get(uint8_t) const {
    return value;
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

template<typename T>
Octree<T> *OctreeLeaf<T>::fill(const AABB &bounds, const Shape &shape, const T &val) {
    if (shape.intersects(bounds)) {
        this->value = val;
    }
    return nullptr;
}

template<typename T>
uint8_t OctreeLeaf<T>::test(const typename Octree<T>::TPredicate &predicate) const {
    return predicate(value) ? (uint8_t) 0xff : (uint8_t) 0x00;
}

template<typename T>
void OctreeLeaf<T>::forEach(const AABB &bounds,
                            const typename Octree<T>::BranchAction &action,
                            uint8_t) const {
    action(this, bounds);
}
