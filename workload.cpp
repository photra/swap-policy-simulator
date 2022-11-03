#include "swap-policy.hpp"
#include <iostream>
#include <iomanip>

void Workload::testEvenWorkload(AbstractPolicy *policy, int iterations)
{
  for (int i = 0; i < iterations; i++)
  {
    int page_number = rand() % policy->get_page_count();
    policy->AccessPage(page_number);
  }

  PrintSimulationResult(policy);
}

void Workload::testCacheableWorkload(AbstractPolicy *policy, int iterations)
{
  int priority_addresses_end = policy->get_page_count() * 0.2;
  int page_count = policy->get_page_count();

  for (int i = 0; i < iterations; i++)
  {
    bool priority = rand() % 10 > 1;

    if (priority)
    {
      policy->AccessPage(rand() % priority_addresses_end);
    }
    else
    {
      int page = rand() % page_count;
      page += priority_addresses_end;
      page = min(page_count - 1, page);
      policy->AccessPage(page);
    }
  }

  PrintSimulationResult(policy);
}

void Workload::PrintSimulationResult(AbstractPolicy *policy)
{
  cout << "*** " + policy->get_policy_name() + " Policy ***" << endl;
  cout << policy->get_access_counts() << " iterations" << endl;

  double miss_rate = (double)policy->get_cache_misses() / policy->get_access_counts() * 100;
  cout << "Cache hit rate: " << setprecision(4) << (100 - miss_rate) << "%" << endl;
  cout << endl;

  policy->reset();
};