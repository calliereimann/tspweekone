#include "cities.hh"
#include <iostream>
#include <fstream>



int main(int argc, char* argv[])
{
  if (argc !=2)
  { std::cout << "Either too many files or no files at all have been added. \n"; //covering all possible reasons for error
    return 1;
  }
  else
  {
    std::ifstream in;
    in.open(argv[1]);
    if(!in)
    {
      std::cerr<<"The file name is invalid.\n";
      return 1;
    }
    unsigned ITERATIONS = 1000000; //a single variable that can be modified rather than having to hunt down each thing
    Cities firstCity;
    Cities* currCity = &firstCity;
    in >> *currCity;
    in.close();
    double currDist = currCity->total_path_distance({}); //this runs a default which doesn't change its order at all
    std::cout<< "0 " << currDist << "\n"; //before any randomization, give the distance as it was at the start. this means that technically it runs ITERATIONS +1 times.
    for (unsigned i = 0; i < ITERATIONS; i++)
    {
        auto permut = random_permutation(currCity->size()); //come up with a random ordering
        auto testCity = currCity->reorder(permut);
        auto testDist = testCity.total_path_distance({}); //set it up and test it
        if (testDist < currDist)
        {
          std::cout<<i << " " << testDist << "\n";
          currDist = testDist;
          *currCity = testCity; //this is my workaround for not implementing an operator=, just using pointer overwriting.
        }
    }
    std::ofstream out;
    out.open("shortest.tsv");
    out << *currCity;
    out.close();
  }
}
