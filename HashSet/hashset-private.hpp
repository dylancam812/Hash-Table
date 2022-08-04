#include <iostream>
#include <algorithm>
#include <forward_list>
#include <string>
#include "hashset.hpp"

template <typename T>
std::ostream& HashSet<T>::showStatistics(std::ostream& out) const {
    return out << reallocations() << " expansions"
               << ", "
               << "load factor " << loadFactor() << ", " << collisions()
               << " collisions"
               << ", "
               << "longest run " << maximal() << std::endl;
}

template <typename T>
HashSet<T>::HashSet()
    : buckets_{DEFAULT_BUCKETS},
      size_{0},
      table_{new std::forward_list<T>[buckets_]},
      reallocations_{0},
      collisions_{0},
      maximal_{0},
      steps_{0} {
}

template <typename T>
HashSet<T>::HashSet(size_t bucketNumber)
    : buckets_{bucketNumber},
      size_{0},
      table_{new std::forward_list<T>[buckets_]},
      reallocations_{0},
      collisions_{0},
      maximal_{0},
      steps_{0} {
}

template <typename T>
HashSet<T>::~HashSet() {
    delete[] table_;
}

template <typename T>
size_t HashSet<T>::size() const {
    return size_;
}

template <typename T>
void HashSet<T>::insert(const T& insertItem) {
    if (!exists(insertItem)) {
        ++size_;
        if (loadFactor() > LOAD_THRESHOLD) {
            rehash();
        }
        if (maximal_ == steps_) {
            ++maximal_;
        }
        size_t hashValue = myhash(insertItem);
        size_t indexBucket = hashValue % buckets_;
        if (table_[indexBucket].begin() != table_[indexBucket].end()) {
            ++collisions_;
        }
        table_[indexBucket].push_front(insertItem);
    }
}

template <typename T>
bool HashSet<T>::exists(const T& testItem) const {
    size_t hashValue = myhash(testItem);
    size_t indexBucket = hashValue % buckets_;
    steps_ = 0;

    for (typename std::forward_list<T>::iterator iter =
             table_[indexBucket].begin();
         iter != table_[indexBucket].end(); ++iter) {
        ++steps_;
        if (steps_ > maximal_) {
            maximal_ = steps_;
        }
        if (*iter == testItem) {
            return true;
        }
    }
    return false;
}

template <typename T>
void HashSet<T>::rehash() const {
    ++reallocations_;
    collisions_ = 0;
    maximal_ = 0;
    size_t newBuckets = buckets_ * 2;

    std::forward_list<T>* newTable = new std::forward_list<T>[newBuckets];

    for (size_t i = 0; i < buckets_; ++i) {
        for (typename std::forward_list<T>::iterator iter = table_[i].begin();
             iter != table_[i].end(); ++iter) {
            size_t hashValue = myhash(*iter);
            size_t indexBucket = hashValue % newBuckets;
            if (newTable[indexBucket].begin() != newTable[indexBucket].end()) {
                ++collisions_;
            }
            newTable[indexBucket].push_front(*iter);
        }
    }
    delete[] table_;
    table_ = newTable;
    buckets_ = newBuckets;
}

template <typename T>
size_t HashSet<T>::buckets() const {
    return buckets_;
}

template <typename T>
double HashSet<T>::loadFactor() const {
    if (buckets_ == 0) {
        return 0;
    } else {
        double sizeDouble = static_cast<double>(size_);
        double bucketsDouble = static_cast<double>(buckets_);
        double loadFactor = sizeDouble / bucketsDouble;
        return loadFactor;
    }
}

template <typename T>
size_t HashSet<T>::reallocations() const {
    return reallocations_;
}

template <typename T>
size_t HashSet<T>::collisions() const {
    return collisions_;
}

template <typename T>
size_t HashSet<T>::maximal() const {
    return maximal_;
}
