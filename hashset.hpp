#ifndef HASHSET_HPP_INCLUDED
#define HASHSET_HPP_INCLUDED

#include <iostream>
#include <forward_list>

template <typename T>
class HashSet {
 private:
    // sets the default number of buckets to 16
    size_t DEFAULT_BUCKETS = 16;

    // sets the load threshold to 2
    size_t LOAD_THRESHOLD = 2;

 public:
    std::ostream& showStatistics(std::ostream& out) const;

    /**
     * \brief constructs an empty HashSet
     */
    HashSet();

    /**
     * \brief parameterized constructor constructs an empty HashSet with
     * bucketNumber buckets \param bucketNumber: size_t number of buckets in
     * HashSet
     */
    HashSet(size_t bucketNumber);

    /**
     * \brief destructs an empty HashSet
     */
    ~HashSet();

    /**
     * \brief returns the number of items in the hash table
     */
    size_t size() const;

    /**
     * \brief inserts an item into the hash table
     * \param insertItem: the item to be inserted of type const T&
     */
    void insert(const T& insertItem);

    /**
     * \brief checks if testItem is already in the hash table
     * \param testItem: the item to be checked of type const T&
     */
    bool exists(const T& testItem) const;

    /**
     * \brief returns the number of buckets in the hash table
     */
    size_t buckets() const;

    /**
     * \brief returns the load factor of the hash table ie. size divided by the
     * number of buckets
     */
    double loadFactor() const;

    /**
     * \brief returns the number of times the hash table reallocates its
     * underlying array
     */
    size_t reallocations() const;

    /**
     * \brief returns the number of times a key was inserted into a non-empty
     * bucket since the last time the table was reallocated
     */
    size_t collisions() const;

    /**
     * \brief returns the largest number of steps taken to find a key since the
     * last time the table was reallocated
     */
    size_t maximal() const;

    mutable size_t buckets_;
    size_t size_;
    mutable std::forward_list<T>* table_;
    mutable size_t reallocations_;
    mutable size_t collisions_;
    mutable size_t maximal_;
    mutable size_t steps_;

 private:
    /**
     * \brief reallocates the underlying array of the hash table
     */
    void rehash() const;
};

#include "hashset-private.hpp"

#endif
