#include <forward_list>
#include <functional>
#include <iostream>
#include <vector>

template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class HashTable
{

  public:
  HashTable(size_t bucket_count = 10)
      : bucket_count_(bucket_count), element_count_(0), buckets_(bucket_count)
  {
  }

  void insert(const Key& key)
  {
    check_load_factor();

    size_t bucket_index = Hash{}(key) % bucket_count_;
    for(const auto& element : buckets_[bucket_index])
    {
      if(KeyEqual{}(element, key))
      {
        return;
      }
    }
    buckets_[bucket_index].push_front(key);
    ++element_count_;
  }

  bool find(const Key& key)    // stl'find returns an iterator, and stl'count returns 1 or 0
  {
    size_t bucket_index = Hash{}(key) % bucket_count_;

    for(const auto& element : buckets_[bucket_index])
    {
      if(KeyEqual{}(element, key))
      {
        return true;
      }
    }
    return false;
  }

  void erase(const Key& key)
  {
    size_t bucket_index = Hash{}(key) % bucket_count_;
    // take advantage of forward_list's remove_if
    buckets_[bucket_index].remove_if([&key](const auto& element) {
      return KeyEqual{}(element, key);
    });
    --element_count_;
  }

  size_t size() const
  {
    return element_count_;
  }

  private:
  void check_load_factor()
  {
    double load_factor = static_cast<double>(element_count_) / static_cast<double>(bucket_count_);
    if(load_factor > 0.7)
    {
      rehash(bucket_count_ * 2);
    }
  }

  void rehash(size_t new_bucket_count)
  {
    std::vector<std::forward_list<Key>> new_buckets(new_bucket_count);
    for(const auto& bucket : buckets_)
    {
      for(const auto& element : bucket)
      {
        size_t new_bucket_index = Hash{}(element) % new_bucket_count;
        new_buckets[new_bucket_index].push_front(element);
      }
    }
    std::swap(new_buckets, buckets_);
    bucket_count_ = new_bucket_count;
  }

  size_t                              bucket_count_;
  size_t                              element_count_;
  std::vector<std::forward_list<Key>> buckets_;
};

template <typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class UnorderedSet
{
  private:
  HashTable<Key, Hash, KeyEqual> table;

  public:
  void insert(const Key& key)
  {
    table.insert(key);
  }

  bool find(const Key& key)
  {
    return table.find(key);
  }

  void erase(const Key& key)
  {
    table.erase(key);
  }

  size_t size() const
  {
    return table.size();
  }
};

template <typename Key, typename Value>
struct Pair
{
  using Key = Key;
  Key   key;
  Value value;

  Pair(const Key& k, const Value& v) : key(k), value(v) {}
};

template <
    typename Pair,
    typename Hash     = std::hash<Pair::Key>,
    typename KeyEqual = std::equal_to<Pair::Key>>
class UnorderedMap
{
  private:
  HashTable<Pair, Hash, KeyEqual> table;
};

int main()
{
  auto set = HashTable<int>();
  set.insert(19);
  set.insert(5);
  set.insert(3);
  set.erase(5);
  std::cout << set.find(5) << " " << set.size() << std::endl;
}