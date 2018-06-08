/*
 * Heap.cpp
 *
 *  Created on: Jun 2, 2018
 *      Author: Andrew Maxwell
 */

#include <vector>
#include <iostream>
#include <math.h>
#include <assert.h>
#include "Heap.h"

using namespace std;

    /**Helper Functions*/

    void Heap::heapify(int i) {
        int l = i * 2;
        int r = i * 2 + 1;
        int greatest = i;
        if (l <= heap_size and heap -> at(l) > heap -> at(greatest)) {
        	greatest = l;
        }
        if (r <= heap_size and heap -> at(r) > heap -> at(greatest)) {
        	greatest = r;
        }
        if (greatest != i) {
        	Order * swap = heap -> at(greatest);
        	heap -> at(greatest) = heap -> at(i);
        	heap -> at(i) = swap;
        	heapify(greatest);
        }
    }
    //helper function to build_heap, remove, and sort
    //bubbles an element down to its proper location within the heap

    void Heap::heap_increase_key(int i, Order * key) {
    	if (*heap -> at(floor(i/2)) < *key) {
    		heap -> at(i) = heap -> at(floor(i/2));
    		heap -> at(floor(i/2)) = key;
    		heap_increase_key(floor(i/2), key);
    	}
    }
    //helper funciton to insert
    //bubbles an element up to its proper location

    /**Constructors*/

    Heap::Heap() {
    	heap_size = 0;
    	heap = new vector<Order *>;
    	Order placeHolder;
    	heap -> push_back(&placeHolder);
    }
    //assigns heap to point to v, an unordered array
    //calls build_heap to convert the unordered array into a valid max heap

    /**Manipulation Procedures*/

    void Heap::build_heap() {
        for (int i = heap_size/2; i > 0; i--) {
            heapify(i);
        }
    }
    //Takes an unordered vector and builds it into a heap
    //Called as a helper function of the constructor
    //Calls heapify as a helper function

    void Heap::place(Order * o, int days) {
    	if (o == NULL) {
    		return;
    	}
    	assert (!o -> isShipped());
    	o -> placeOrder(days);
    	heap -> push_back(o);
    	heap_size++;
    	heap_increase_key(heap_size, o);
    }
    //Inserts a new value onto the end of the heap and
    //Bubbles it up to the correct location in the heap
    //Calls heap_increase_key as a helper function

    void Heap::ship(int index) {
    	assert(1 <= index);
    	assert(index <= heap_size);
    	heap -> at(index) -> ship();
    	heap -> at(index) = heap -> at(heap_size);
    	heap -> pop_back();
    	heap_size--;
    	heapify(index);
    }

    void Heap::ship(Order * o) {
    	for (unsigned i = 0; i < heap -> size(); i++) {
    		if (heap -> at(i) == o) {
    			ship(i);
    		}
    	}
    }
    //removes the node at the provided index of the heap
    //pre: 1 <= i <= get_size()

    /**Access Functions*/

    Order * Heap::get_max() const {
        assert(heap_size > 0);
        return heap -> at(1);
    }
    //returns the maximum value in the heap
    //pre: heap_size > 0

    Order * Heap::get_parent(int i) const {
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(floor(i/2));
    }
    //returns the location (index) of the element stored at index i
    //pre: 0 < i <= heap_size

     Order * Heap::get_left(int i)  const {
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(i * 2);
    }
    //returns the location (index) of the left child of the element stored at i
    //pre: 0 < i <= heap_size

    Order * Heap::get_right(int i)  const {
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at((i * 2) + 1);

    }
    //returns the location (index) of the right child of the element stored at i
    //pre: 0 < i <= heap_size

    int Heap::get_size() const {
        return heap_size;
    }

    Order * Heap::get_element(int i) const {
        assert(0 < i);
        assert(i <= heap_size);
        return heap -> at(i);
    }
    //returns the element at the specified index i
    //pre: 0 < i <= heap_size

    /**Additional Operations*/

    void Heap::displayHeap(ostream& out) const {
        for (int i = 1; i <= heap_size; i++) {
            heap -> at(i) -> print(out);
        }
    }

    void Heap::printSorted(ostream& out) {
    	int realLength = heap_size;
    	while (heap_size > 1) {
    		Order * swap = heap -> at(1);
    		heap -> at(1) = heap -> at(heap_size);
    		heap -> at(heap_size) = swap;
    		heap_size--;
    		heapify(1);
    	}
    	heap_size = realLength;
        for (int i = heap_size; i >= 1; i--) {
            heap -> at(i) -> print(out);
        }
    	build_heap();
    }
    //prints each element in the array (heap) on a different line
