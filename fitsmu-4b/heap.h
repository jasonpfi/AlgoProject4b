/*
 * Team: fitsmu
 * Jason Fitch
 * Sam Smucny
 *
 * heap.h: Contains the declarations and implementation of methods for the
 *         templated heap class. In this project, the typename T will be a
 *         string
 */

#pragma once
#include <vector>
#include <math.h>

 // Template heap class declaration
template<typename T>
class heap
{

public:

	// Constructor specifying the vector to be used for the heap
	//
	// vector<T> n: vector of type T to be copied into the nodes member
	heap(std::vector<T> &n) :
		nodes(n), heapSize(n.size())
	{}

	// Empty Constructor
	heap() {}

	// Returns a reference to the item at index n. Return type is a reference
	//  in order to mutate the list by simply requesting data on the node
	//
	// int n: index of the member vector to be accessed
	T& getItem(const int& n);

	// Swap the items at index i and index largest
	//
	// int i: first index to be saved to a temporary variable
	// int largest: second index to be swapped with the item at index i
	void swap(const int& i, const int& largest);

	// Initializes the Max-Heap by copying the vector parameter into the nodes
	//  member. Also, sets the size of the heap to be the size of the vector.
	//
	// vector<T> v: vector to be copied
	void initializeMaxHeap(const std::vector<T>& v);

	// Maintains the heap property in the vector member function. Assumes that
	//  the left and right subtrees of nodes.at(i) are max heaps, but the item
	//  at nodes.at(i) may be smaller than its children. If the left or right
	//  children of nodes.at(i) is larger than the value of nodes.at(i), then
	//  the larger child is swapped with nodes.at(i). Then this method is
	//  recursively called by passing in the new position of the node that
	//  was swapped with its child. In this way, the incorrect node "flows down"
	//  the binary tree until the heap property is maintained.
	//
	//  int i : the index of the node being examined
	void maxHeapify(const int& i);

	// Build a full max heap from an unsorted array. Starts at the parent of
	//  the bottom-rightmost child and works up into the tree until the root
	//  is reached. At each iteration, the node being examined is moved down
	//  into its correct position in the tree. All nodes below the current node
	//  being examined are sorted.
	void buildMaxHeap();

	// Sorts the vector. Loops through the entire length of the heap. Swaps
	//  the current root with the last item in the heap, putting it in the
	//  sorted position in the vector; then decrements the heap size by 1.
	//  Finishes when there is only the root left. Returns sorted vector.
	std::vector<T> heapsort();

	T pop();

	void push();

	// Parent of the node at the given index
	static int parent(const int& index);

	// Left child of the node at the given index
	static int left(const int& index);

	// Right child at the node at the given index
	static int right(const int& index);

private:

	// Private data members
	std::vector<T> nodes;
	int heapSize;

}; // End Heap Class

// Parent of the node at the given index
template <typename T>
int heap<T>::parent(const int& index)
{
	return index / 2;
}

// Left child of the node at the given index
template <typename T>
int heap<T>::left(const int& index)
{
	return 2 * index;
}

// Right child at the node at the given index
template <typename T>
int heap<T>::right(const int& index)
{
	return 2 * index + 1;
}

// Returns a reference to the item at index n. Return type is a reference
//  in order to mutate the list by simply requesting data on the node
//
// int n: index of the member vector to be accessed
template <typename T>
T& heap<T>::getItem(const int& n)
{
	return this->nodes.at(n - 1);
}

// Maintains the heap property in the vector member function. Assumes that
//  the left and right subtrees of nodes.at(i) are max heaps, but the item
//  at nodes.at(i) may be smaller than its children. If the left or right
//  children of nodes.at(i) is larger than the value of nodes.at(i), then
//  the larger child is swapped with nodes.at(i). Then this method is
//  recursively called by passing in the new position of the node that
//  was swapped with its child. In this way, the incorrect node "flows down"
//  the binary tree until the heap property is maintained.
//
//  int i : the index of the node being examined
template <typename T>
void heap<T>::maxHeapify(const int& i)
{
	// Current largest, left child, right child
	int largest;
	int l = this->left(i);
	int r = this->right(i);

	// Check that left child is within the heap and larger than node at i
	if (l <= this->heapSize && this->getItem(l) > this->getItem(i))
	{
		largest = l;
	}
	else
		largest = i;

	// Check that right child is within the heap and larger than node at i
	if (r <= this->heapSize && this->getItem(r) > this->getItem(largest))
	{
		largest = r;
	}

	// If the largest is not the node at i, swap the node at i with the
	//  largest, recur on the new position for node at i
	if (largest != i)
	{
		this->swap(i, largest);
		this->maxHeapify(largest);
	}

} // End maxHeapify

// Swap the items at index i and index largest
//
// int i: first index to be saved to a temporary variable
// int largest: second index to be swapped with the item at index i
template <typename T>
void heap<T>::swap(const int& i, const int& largest)
{
	T tmp = this->getItem(i);
	this->getItem(i) = this->getItem(largest);
	this->getItem(largest) = tmp;
}

// Build a full max heap from an unsorted array. Starts at the parent of
//  the bottom-rightmost child and works up into the tree until the root
//  is reached. At each iteration, the node being examined is moved down
//  into its correct position in the tree. All nodes below the current node
//  being examined are sorted.
template <typename T>
void heap<T>::buildMaxHeap()
{
	for (int i = floor((this->nodes.size()+1) / 2); i > 0; i--)
	{
		this->maxHeapify(i);
	}
}

// Initializes the Max-Heap by copying the vector parameter into the nodes
//  member. Also, sets the size of the heap to be the size of the vector.
//
// vector<T> v: vector to be copied
template <typename T>
void heap<T>::initializeMaxHeap(const std::vector<T>& v)
{
	this->nodes = v;
	this->heapSize = v.size();
}

// Sorts the vector. Loops through the entire length of the heap. Swaps
//  the current root with the last item in the heap, putting it in the
//  sorted position in the vector; then decrements the heap size by 1.
//  Finishes when there is only the root left.
template <typename T>
std::vector<T> heap<T>::heapsort()
{
	this->buildMaxHeap();

	for (int i = heapSize; i >= 1; i--)
	{
		this->swap(1, i);
		this->heapSize--;
		this->maxHeapify(1);
	}

	return this->nodes;
}

template<typename T>
T heap<T>::pop()
{
	this->buildMaxHeap();
	this->swap(1, heapSize);
	this->heapSize--;
	this->maxHeapify(1);
	return this->getItem(heapSize + 1);
}

template<typename T>
void heap<T>::push()
{
	this->swap(heapSize + 1, 1);
	this->heapSize++;
}
