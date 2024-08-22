#include "lru_cache.h"
#include <sstream>

using namespace std;

LRUCache::LRUCache(int capacity) : capacity_(capacity) {}

void LRUCache::setCapacity(int capacity) { capacity_ = capacity; }

int LRUCache::get(int key)
{
    std::lock_guard g(m_);
    return this->get_impl(key);
}

void LRUCache::refer(int key, int value)
{
    lock_guard g(m_);
    if (this->get_impl(key) >= 0)
    {
        return;
    }
    this->put(key, value);
}

std::string LRUCache::getCache() const
{
    std::lock_guard g(m_);
    stringstream ss;
    ss << "{ ";
    for (auto it = cache_.begin(); it != cache_.end(); ++it)
    {
        ss << it->first << "=" << it->second << ", ";
    }
    ss << "}";
    return ss.str();
}

void LRUCache::put(int key, int value)
{
    if (cache_.size() == capacity_)
    {
        int first_key = cache_.front().first;
        cache_.pop_front();
        map_.erase(first_key);
    }
    cache_.emplace_back(key, value);
    map_[key] = --cache_.end();
}

int LRUCache::get_impl(int key)
{
    auto it = map_.find(key);
    if (it == map_.end())
    {
        return -1;
    }
    cache_.splice(cache_.end(), cache_, it->second);
    return it->second->second;
}
