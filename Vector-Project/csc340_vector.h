////////////////////////////////////////////////////////////////////////////////
// csc340_vector.h : CSC340 implementation of std::vector using dynamic arrays.
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// ALL YOUR WORK SHOULD BE DONE IN THIS FILE
//
// Student Name: Hamed Rangeen
// Student ID:   916775826
// Student Email:arangeen@mail.sfsu.edu
////////////////////////////////////////////////////////////////////////////////

#ifndef CSC340_VECTOR_H
#define CSC340_VECTOR_H
#include <iostream>

template <class T>
class csc340_vector {
    
  private:
      
    T* data_;                // Storage for the elements
    unsigned int size_;      // Number of elements defined in the vector
    unsigned int capacity_;  // Number of elements that the vector can hold
    
  public:
    // Define the iterator type to just be a pointer to T.
    typedef T* iterator;

    // Constructs an empty vector. Allocate an initial capacity of 1 element,
    // but do not add an element to the vector (i.e. capacity will be 1 while
    // size will be 0). You do not need to worry about bad_alloc exceptions.
    csc340_vector() {
        // Your code goes here 
        capacity_ = 1; 
        data_ = new T[capacity_];
        size_ = 0;
    }
    
    // Destructs/de-allocates dynamic memory (if any was allocated).
    ~csc340_vector(){
        // Your code goes here
        if(data_ != nullptr){
            delete[] data_;
        }
    }

    // Returns reference to the element at specified location pos, with bounds
    // checking. If pos is not within the range of the vector, an exception of
    // type std::out_of_range is thrown.
    T& at(unsigned int pos) {
        // Your code goes here
        if (pos >= size_) { 
            throw std::out_of_range("Position not within range");
        }
        
        return data_ [pos];
    }
    

    // Returns reference to the element at specified location pos. No bounds
    // checking is performed.
    T& operator[](unsigned int pos) {
        // Your code goes here
        return data_[pos];
    }

    // Returns reference to the first element in the vector. Calling front on an
    // empty container is undefined and won't be tested.
    T& front() {
        // Your code goes here
        return data_[0];
    }

    // Returns reference to the last element in the vector. Calling back on an
    // empty container is undefined and won't be tested.
    T& back() {
        // Your code goes here
        return data_[size_ -1];               
        
    }

    // Checks if the vector has no elements.
    bool empty() {
        // Your code goes here
        return size_ == 0;
        
    }

    // Returns the number of elements in the vector.
    unsigned int size() {
        // Your code goes here
        return size_;                              
    }

    // Increases the capacity of the vector to be >= new_capacity. If
    // new_capacity is greater than the current capacity(), new storage is
    // allocated (i.e. a new array is created, existing data copied over, and
    // the old array is deleted). If new_capacity <= the current capacity() this
    // method does nothing. You do not need to worry about bad_alloc exceptions.
    void reserve(unsigned int new_capacity) {
        // Your code goes here
        if (new_capacity <= capacity_){
            return;
        }
        T* new_data = new T[new_capacity];
         
        //copy elements if any existed 
        for(unsigned int i = 0; i < size_; i++) {
            new_data[i] = data_[i];
        }
        
        // Delete old array if it existed
        if(data_ != nullptr){
            delete[] data_;
        }
                    
        data_ = newData_;
        capacity_ = new_capacity;         
            
    }

    // Returns the number of elements that the vector has currently allocated
    // space for.
    unsigned int capacity() {
        // Your code goes here
        return capacity_;
    }

    // Removes all elements from the vector. Leaves capacity() of the vector
    // unchanged.
    void clear() {
        // Your code goes here
        size_ = 0;
         
    }
    // Appends the given element to the end of the vector. If the new size() is
    // greater than capacity(), it will call reserve() with a new_capacity of
    // double the original capacity() before appending the element.
    void push_back(const T& value) {
        // Your code goes here
        if (size_ == capacity_)
            {
                reserve (2 * capacity_);
            }
        data_ [size_] = T(value);
        ++size_;
        
    }

    // Removes the last element of the vector. Calling pop_back on an empty
    // vector should do nothing.
    void pop_back() {
        // Your code goes here
       if (size_ > 0){ 
            --size_; 
       }
    }

    // Resizes the vector to contain count elements. If the current size() is
    // greater than count, the vector is reduced to its first count elements.
    // If the current size() is less than count, additional elements are
    // appended and initialized with copies of value.
    // HINT: You can call pop_back() and push_back() in a loop.
    void resize(unsigned int count, const T& value = T()) {
        // Your code goes here
        while (count < size_) {
            pop_back();
        }
        while (count > size_) {
            push_back(value);
        }
    }

    iterator begin() {
        // Your code goes here
        return data_;
        
    }

    iterator end() {
        // Your code goes here
        return data_ + size_;
    }

};

#endif // CSC340_VECTOR_H
