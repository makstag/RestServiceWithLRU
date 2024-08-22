#pragma once
#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>
#include <mutex>

class LRUCache
{
public:
    LRUCache(int capacity = 2);
    void setCapacity(int capacity);

    // This function returns -1 if key is not
    // present in cache. Else it moves the key to
    // front by first removing it and then adding
    // it, and returns value.
    int get(int key);

    // update cache
    void refer(int key, int value);

    // // displays contents of cache in Reverse Order
    // void display() const;

    std::string getCache() const;

private:
    int capacity_;
    std::list<std::pair<int, int>> cache_;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> map_;
    mutable std::mutex m_;

private:
    void put(int key, int value);

    // This function returns -1 if key is not
    // present in cache. Else it moves the key to
    // front by first removing it and then adding
    // it, and returns value.
    int get_impl(int key);
};
