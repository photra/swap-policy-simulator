#include "swap-policy.hpp"
#include <iostream>

RandomPolicy::RandomPolicy(int input_num_pages, int input_cache_size)
{
  page_count = input_num_pages;
  cache_size = input_cache_size;
  name = "Random";
};

bool RandomPolicy::AccessPage(int page_number)
{
  access_counts++;
  if (cache.find(page_number) != cache.end())
    return true;

  else
  {
    cache_misses++;
    while (cache.size() >= cache_size)
    {
      int page_to_remove = rand() % page_count;
      cache.erase(page_to_remove);
    }
    cache.insert(page_number);

    return false;
  }
}