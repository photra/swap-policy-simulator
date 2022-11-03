#pragma once
#include <deque>
#include <queue>
#include <map>
#include <unordered_set>

using namespace std;

class AbstractPolicy
{
protected:
  int access_counts = 0;
  int cache_misses = 0;
  int page_count;
  int cache_size;
  string name;

public:
  virtual bool AccessPage(int page_number) = 0;
  string get_policy_name()
  {
    return name;
  };
  int get_access_counts()
  {
    return access_counts;
  };
  int get_page_count()
  {
    return page_count;
  };
  int get_cache_misses()
  {
    return cache_misses;
  };
  void reset()
  {
    access_counts = 0;
    cache_misses = 0;
  };
};

class Workload
{
  AbstractPolicy *policy;

  void PrintSimulationResult(AbstractPolicy *input_policy);

public:
  void testEvenWorkload(AbstractPolicy *input_policy, int iterations);
  void testCacheableWorkload(AbstractPolicy *input_policy, int iterations);
};

class LeastRecentlyUsedPolicy : public AbstractPolicy
{
  map<int, int> pageMap;
  deque<int> pages;

public:
  LeastRecentlyUsedPolicy(int input_num_pages, int input_cache_size);
  bool AccessPage(int page_number);
};

class FirstInFirstOutPolicy : public AbstractPolicy
{
  unordered_set<int> cache;
  queue<int> cacheQueue;

public:
  FirstInFirstOutPolicy(int input_num_pages, int input_cache_size);
  bool AccessPage(int page_number);
};

class RandomPolicy : public AbstractPolicy
{
  unordered_set<int> cache;

public:
  RandomPolicy(int input_num_pages, int input_cache_size);
  bool AccessPage(int page_number);
};