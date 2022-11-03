#include "swap-policy.hpp"
#include <iostream>
LeastRecentlyUsedPolicy::LeastRecentlyUsedPolicy(int input_num_pages, int input_cache_size)
{
  name = "Least Recently Used";
  page_count = input_num_pages;
  cache_size = input_cache_size;
}

bool LeastRecentlyUsedPolicy::AccessPage(int page_number)
{ // if we cannot find the page in the cache,
  // add the page to cache,
  // evict the top one
  access_counts += 1;
  if (pageMap.find(page_number) == pageMap.end())
  {
    cache_misses += 1;
    if (pages.size() < cache_size)
    {
      /*while the deque is not full,
        we simply push back the page
        and update the map
      */
      pageMap[page_number] = pages.size();
      pages.push_back(page_number);
      // cout << "Hit Miss. Cache not full, pushed: " << page_number << "\n";
    }
    else if (pages.size() == cache_size)
    {
      /*if the cache is full, and we didn't find the page
        we evict the front page in cache,
        and erase the page from the map as well
        for every other pages inside the map, we need to
        decrease their value by 1
      */
      int front = pages.front();
      pageMap.erase(front);
      pages.pop_front();
      map<int, int>::iterator it;
      for (it = pageMap.begin(); it != pageMap.end(); ++it)
      {
        it->second -= 1;
      }
      pageMap[page_number] = pages.size();
      pages.push_back(page_number);
      // cout << "Hit Miss. Cache full, evicted: " << front << " , pushed: " << page_number << "\n";
    }
    else
    {
      // cout << "Cache space over limit!\n";
      exit(-1);
    }
    return false;
  }
  else
  {
    /* if we find the page
      we take that page out of the deque and put it in the back
      only when the targe page is not at the end of the deque.
    */
    if (pages.at(pages.size() - 1) != page_number)
    {
      int index = pageMap[page_number];
      for (int i = index + 1; i < pages.size(); i++)
      {
        int currPage = pages.at(i);
        pageMap[currPage] -= 1;
      }
      pages.erase(pages.begin() + index);
      pageMap.erase(page_number);
      pageMap[page_number] = pages.size();
      pages.push_back(page_number);
    }
    if (pages.size() > cache_size)
    {
      // cout << "cache over limit\n";
      exit(-1);
    }
    return true;
  }
}