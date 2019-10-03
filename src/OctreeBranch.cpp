#include "OctreeBranch.h"
#include "OctreeNode.h"
#include "OctreeLeaf.h"

template<typename T, uint8_t SIZE>
OctreeBranch<T, SIZE>::OctreeBranch(const T & defaultValue) :
	Octree<T>{}, children{} {
	if (SIZE == 0) 
	{
		for (int i = 0; i < 8; i++) {
			children[i] = new OctreeLeaf<T>{ defaultValue };
		}
	}
	else 
	{
		constexpr uint8_t HALF = SIZE >> 1;
		for (int i = 0; i < 8; i++) {
			children[i] = new OctreeNode<T, HALF>{ defaultValue };
		}
	}
}

template<typename T, uint8_t SIZE>
OctreeBranch<T, SIZE>::~OctreeBranch()
{
	for (int i = 0; i < 8; i++) {
		delete children[i];
	}
}

template<typename T, uint8_t SIZE>
bool OctreeBranch<T, SIZE>::isLeafAndEqualTo(const T & value) const
{
	return false; // This is never a leaf
}

template<typename T, uint8_t SIZE>
T OctreeBranch<T, SIZE>::get(uint8_t x, uint8_t y, uint8_t z) const
{
	uint8_t idx{};
	if (x >= SIZE) {
		idx |= 0x1;
		x -= SIZE;
	}

	if (y >= SIZE) {
		idx |= 0x2;
		y -= SIZE;
	}

	if (z >= SIZE) {
		idx |= 0x4;
		z -= SIZE;
	}

	return children[idx]->get(x, y, z);
}

template<typename T, uint8_t SIZE>
Octree<T>* OctreeBranch<T, SIZE>::set(uint8_t x, uint8_t y, uint8_t z, const T& value)
{
	constexpr uint8_t HALF = SIZE >> 1;

	uint8_t idx{};
	if (x >= HALF) {
		idx |= 0x1;
		x -= HALF;
	}

	if (y >= HALF) {
		idx |= 0x2;
		y -= HALF;
	}

	if (z >= HALF) {
		idx |= 0x4;
		z -= HALF;
	}

	Octree<T>* replacement = children[idx]->set(x, y, z, value);
	if (replacement != nullptr) {
		delete children[idx];
		children[idx] = replacement;
	}

	for (int i = 0; i < 8; i++) {
		if (!children[i]->isLeafAndEqualTo(value)) {
			return nullptr;
		}
	}

	return new OctreeNode<T, SIZE>{ value };
}
