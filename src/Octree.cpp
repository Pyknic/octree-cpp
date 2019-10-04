#include "Octree.h"
#include "OctreeNode.h"

template <typename T>
Octree<T>::Octree() = default;

template<typename T>
Octree<T>* Octree<T>::create(const T &value) {
    return new OctreeNode<T, OCTREE_MAX_SIZE>{value};
}