#include "swap-policy.hpp"

FirstInFirstOutPolicy::FirstInFirstOutPolicy(int input_num_pages, int input_cache_size)
{
  page_count = input_num_pages;
  cache_size = input_cache_size;
  name = "FIFO";
};

bool FirstInFirstOutPolicy::AccessPage(int page_number)
{
  access_counts++;
  if (cache.find(page_number) != cache.end())
    return true;

  else
  {
    cache_misses++;
    while (cache.size() >= cache_size)
    {
      int page_to_remove = cacheQueue.front();
      cacheQueue.pop();
      cache.erase(page_to_remove);
    }
    cacheQueue.push(page_number);
    cache.insert(page_number);

    return false;
  }
}