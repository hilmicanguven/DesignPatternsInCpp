#include "composite.hpp"
#include <iostream>


int company_total_production(const std::vector<TotalProduction*> items)
{
  int result{0};

  for (auto item : items)
  {
    result += item->get_production();   // it is same interface for single office or multiple offices.
  }

  return result;
}

int main()
{

    SingleOffice s(10);

    ProductionPlant p;
    p.add_production(20);
    p.add_production(30);

    std::vector<TotalProduction*> offices;
    offices.push_back(&s);
    offices.push_back(&p);

    // int total = company_total_production({ &s, &p }); /* this also works, alternative way to pass arguments*/
    int total = company_total_production(offices);

    std::cout << "Total Production: " << total << std::endl;

    return 0;
}