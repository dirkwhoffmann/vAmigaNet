// -----------------------------------------------------------------------------
// This file is part of vAmiga
//
// Copyright (C) Dirk W. Hoffmann. www.dirkwhoffmann.de
// Licensed under the GNU General Public License v3
//
// See https://www.gnu.org for license information
// -----------------------------------------------------------------------------

#pragma once

#include "Types.h"
#include <utility>

namespace util {

/* The emulator uses buffers at various places. Most of them are derived from
 * one of the following two classes:
 *
 *                Array : A fixed size array
 *          SortedArray : A fixed size array with sorted insert
 *           RingBuffer : A standard ringbuffer
 *     SortedRingBuffer : A standard ringbuffer with sorted insert
 */

//
// Array
//

template <class T, isize capacity> struct Array
{
    // Element storage
    T elements[capacity];

    // Write pointer
    isize w;

    
    //
    // Initializing
    //

    Array() { clear(); }
    
    void clear() { w = 0; }
    void clear(T t) { for (isize i = 0; i < capacity; i++) elements[i] = t; clear(); }
    void align(isize offset) { w = offset; }

    
    //
    // Serializing
    //
    
    template <class W>
    void operator<<(W& worker)
    {
        worker << this->elements << this->w;
    }
    
    
    //
    // Querying the fill status
    //

    isize cap() const { return capacity; }
    isize count() const { return w; }
    isize free() const { return capacity - w; }
    double fillLevel() const { return (double)count() / capacity; }
    bool isEmpty() const { return w == 0; }
    bool isFull() const { return count() == capacity; }


    //
    // Reading and writing elements
    //
    
    T operator [] (isize i) const
    {
        assert(i >= 0 && i < capacity);
        return elements[i];
    }

    T& operator [] (isize i)
    {
        assert(i >= 0 && i < capacity);
        return elements[i];
    }

    void write(T element)
    {
        assert(!isFull());
        elements[w++] = element;
    }
};

template <class T, isize capacity>
struct SortedArray : public Array<T, capacity>
{
    // Key storage
    i64 keys[capacity];
    
    // Inserts an element at the end
    void write(i64 key, T element)
    {
        assert(!this->isFull());

        this->elements[this->w] = element;
        this->keys[this->w] = key;
        this->w++;
    }
    
    // Inserts an element at the proper position
    void insert(i64 key, T element)
    {
        assert(!this->isFull());

        // Search the proper position
        auto pos = this->w;
        while (pos && keys[pos - 1] > key) pos--;
        
        // Create a free spot
        for (isize i = this->w; i > pos; i--) {
            this->elements[i] = this->elements[i - 1];
            keys[i] = keys[i - 1];
        }
        
        // Add the new element
        this->elements[pos] = element;
        this->keys[pos] = key;
        this->w++;
    }
};

//
// Ringbuffer
//

template <class T, isize capacity> struct RingBuffer
{
    // Element storage
    T elements[capacity];

    // Read and write pointers
    isize r, w;

    
    //
    // Initializing
    //

    RingBuffer() { clear(); }
    
    void clear() { r = w = 0; }
    void clear(T t) { for (isize i = 0; i < capacity; i++) elements[i] = t; clear(); }
    void align(isize offset) { w = (r + offset) % capacity; }

    
    //
    // Serializing
    //
    
    template <class W>
    void operator<<(W& worker)
    {
        worker << this->elements << this->r << this->w;
    }
    
    
    //
    // Querying the fill status
    //

    isize cap() const { return capacity; }
    isize count() const { return (capacity + w - r) % capacity; }
    isize free() const { return capacity - count() - 1; }
    double fillLevel() const { return (double)count() / capacity; }
    bool isEmpty() const { return r == w; }
    bool isFull() const { return count() == capacity - 1; }

    
    //
    // Working with indices
    //

    isize begin() const { return r; }
    isize end() const { return w; }
    static isize next(isize i) { return i < capacity - 1 ? i + 1 : 0; }
    static isize prev(isize i) { return i > 0 ? i - 1 : capacity - 1; }


    //
    // Reading and writing elements
    //
    
    T& read()
    {
        assert(!isEmpty());

        auto oldr = r;
        r = next(r);
        return elements[oldr];
    }
    
    const T& read(T fallback)
    {
        if (isEmpty()) write(fallback);
        return read();
    }

    void write(T element)
    {
        assert(!isFull());

        elements[w] = element;
        w = next(w);
    }
    
    void skip()
    {
        r = next(r);
    }
    
    void skip(isize n)
    {
        r = (r + n) % capacity;
    }
    
    
    //
    // Examining the element storage
    //

    const T& current() const
    {
        return elements[r];
    }

    T *currentAddr()
    {
        return &elements[r];
    }

    const T& current(isize offset) const
    {
        return elements[(r + offset) % capacity];
    }
};

template <class T, isize capacity>
struct SortedRingBuffer : public RingBuffer<T, capacity>
{
    // Key storage
    i64 keys[capacity];
    
    // Inserts an element at the proper position
    void insert(i64 key, T element)
    {
        assert(!this->isFull());

        // Add the new element
        auto oldw = this->w;
        this->write(element);
        keys[oldw] = key;

        // Keep the elements sorted
        while (oldw != this->r) {

            // Get the index of the preceeding element
            auto p = this->prev(oldw);

            // Exit the loop once we've found the correct position
            if (key > keys[p]) break;
            
            // Otherwise, swap elements
            std::swap(this->elements[oldw], this->elements[p]);
            std::swap(keys[oldw], keys[p]);
            oldw = p;
        }
    }
    
    // Inserts an element for which we know that sorting is not necessary
    void append(i64 key, T element)
    {
        assert(!this->isFull());
        assert(this->isEmpty() || this->keys[this->prev(this->w)] <= key);
        
        this->elements[this->w] = element;
        this->keys[this->w] = key;
        this->w = this->next(this->w);
    }
};

}
