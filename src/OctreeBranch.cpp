#include "OctreeBranch.h"
#include "OctreeNode.h"
#include "OctreeLeaf.h"

template<typename T, uint8_t SIZE>
OctreeBranch<T, SIZE>::OctreeBranch(const T & defaultValue) :
	Octree<T>{}, children{} {
	if (SIZE == 0) {
		for (auto &child : children) {
            child = new OctreeLeaf<T>{ defaultValue };
		}
	} else {
		constexpr uint8_t HALF = SIZE >> (uint8_t) 1;
		for (auto &child : children) {
            child = new OctreeNode<T, HALF>{ defaultValue };
		}
	}
}

template<typename T, uint8_t SIZE>
OctreeBranch<T, SIZE>::~OctreeBranch() {
	for (auto &child : children) {
		delete child;
	}
}

template<typename T, uint8_t SIZE>
bool OctreeBranch<T, SIZE>::isLeafAndEqualTo(const T & value) const {
	return false; // This is never a leaf
}

template<typename T, uint8_t SIZE>
T OctreeBranch<T, SIZE>::get(uint8_t index) const {
    return children[index]->get(index);
}

template<typename T, uint8_t SIZE>
T OctreeBranch<T, SIZE>::get(uint8_t x, uint8_t y, uint8_t z) const {
	uint8_t idx{};
	if (x >= SIZE) {
		idx |= (uint8_t) 0x1;
		x -= SIZE;
	}

	if (y >= SIZE) {
		idx |= (uint8_t) 0x2;
		y -= SIZE;
	}

	if (z >= SIZE) {
		idx |= (uint8_t) 0x4;
		z -= SIZE;
	}

	return children[idx]->get(x, y, z);
}

template<typename T, uint8_t SIZE>
Octree<T>* OctreeBranch<T, SIZE>::set(uint8_t x, uint8_t y, uint8_t z, const T& value) {
	constexpr uint8_t HALF = SIZE >> (uint8_t) 1;

	uint8_t idx{};
	if (x >= HALF) {
		idx |= (uint8_t) 0x1;
		x -= HALF;
	}

	if (y >= HALF) {
		idx |= (uint8_t) 0x2;
		y -= HALF;
	}

	if (z >= HALF) {
		idx |= (uint8_t) 0x4;
		z -= HALF;
	}

	Octree<T>* replacement = children[idx]->set(x, y, z, value);
	if (replacement != nullptr) {
		delete children[idx];
		children[idx] = replacement;
	}

	for (const auto &child : children) {
        if (!child->isLeafAndEqualTo(value)) {
            return nullptr;
        }
    }

	return new OctreeNode<T, SIZE>{ value };
}

template<typename T, uint8_t SIZE>
Octree<T> *OctreeBranch<T, SIZE>::fill(const AABB &bounds, const Shape &shape, const T &value) {
    switch (shape.intersects(bounds)) {
        case DISJOINT: {
            return nullptr;
        }
        case INTERSECTS: {
            for (uint8_t i = 0; i < 8; i++) {
                const AABB childBounds {bounds.subdivide(i)};
                Octree<T>* newChild {children[i]->fill(childBounds, shape, value)};
                if (newChild != nullptr) {
                    delete children[i];
                    children[i] = newChild;
                }
            }

            for (const auto &child : children) {
                if (!child->isLeafAndEqualTo(value)) {
                    return nullptr;
                }
            }

            return new OctreeNode<T, SIZE>{ value };
        }
        case CONTAINS: {
            return new OctreeNode<T, SIZE>{ value };
        }
    }
}

template<typename T, uint8_t SIZE>
uint8_t OctreeBranch<T, SIZE>::test(const typename Octree<T>::TPredicate &predicate) const {
    uint8_t bitmap {0x0};
    for (uint8_t i = 0; i < 8; i++) {
        const T& childValue {get(i)};
        if (predicate(childValue)) {
            bitmap |= (uint8_t) ((uint8_t) 0x1 << i);
        }
    }
    return bitmap;
}

template<typename T, uint8_t SIZE>
void OctreeBranch<T, SIZE>::forEach(const AABB &bounds,
                                    const typename Octree<T>::BranchAction &action,
                                    uint8_t childSize) const {
    if (childSize == SIZE) {
        action(this, bounds);
    } else {
        for (uint8_t i = 0; i < 8; i++) {
            const AABB childBounds {bounds.subdivide(i)};
            children[i]->forEach(childBounds, action, childSize);
        }
    }
}
