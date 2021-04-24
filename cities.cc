#include "cities.hh"


bool Cities::validate(const permutation_t& ordering) const
{
  bool orderFits = citylist_.size() >= ordering.size() ; //if the permutation is too big things might get called out of bounds
  bool twoCities = citylist_.size() > 1 ; // the city needs 2 elements or else distance is meaningless
  return orderFits && twoCities; //this used to have more checks but they all crashed if the permutation was empty and none of them were violated by the output of random_permutation.
}


std::stringstream Cities::new_arrangement(const permutation_t& ordering) const
{
  std::stringstream ss;
  if (validate(ordering)) //checking if the permutation is legal
  {
    for (unsigned i = 0; i<citylist_.size(); i++) //running over each city in the setup
    {
      if ( i < ordering.size()) //this allows for permutations smaller than citylist to work, like a {1, 0} to swap the first two elements and ignore the rest
      {ss << citylist_[ordering[i]].first << " " << citylist_[ordering[i]].second << "\n";}
      else
      {ss << citylist_[i].first << " " << citylist_[ordering[i]].second << "\n";}
    }
  }
  return ss;
}


Cities Cities::reorder(const permutation_t& ordering) const
{
  Cities newcity;
  auto ss = new_arrangement(ordering);
  ss >> newcity; //the way this input operator works means that it functions perfectly fine here
  return newcity;
}

double distance(Cities::coord_t city1, Cities::coord_t city2)
{
  double diffY = city1.second - city2.second; //this is the standard pythagorean distance formula
  double diffX = city1.first - city2.first;
  return std::sqrt((diffY*diffY)+(diffX*diffX));
}



Cities::coord_t Cities::generate_positions(unsigned point1, unsigned point2, const permutation_t& ordering) const
{
  int pos1, pos2; //i never have to check for the case where point2 is above and point1 is below
  if (point1 < ordering.size())//since this is only ever called where point2 = point1 - 1, or point2 = 0.
  {
    pos1 = ordering[point2];
    pos2 = ordering[point1];
  }
  else if (point2 < ordering.size())
  {
    pos1 = ordering[point2];
    pos2 = point1;
  }
  else
  {
    pos1 = point2;
    pos2 = point1;
  }
  return std::pair(pos1, pos2);
}

double Cities::single_path_distance(coord_t pos) const
{
  coord_t city1 = citylist_[pos.first]; //a microfunction which just makes total_path_distance cleaner
  coord_t city2 = citylist_[pos.second]; //gets the two cities which positions finds, and distance calculates them.
  return distance(city1, city2);
}

Cities::permutation_t random_permutation(unsigned len)
{
  Cities::permutation_t sortedBaseCase;
  Cities::permutation_t output;
  for (unsigned i = 0; i < len; i++) //generating a list from zero to len in regular numeric order
  {sortedBaseCase.push_back(i);}
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();//using time as a random seed for generation purposes
  std::default_random_engine generator (seed);
  while (sortedBaseCase.size() > 0) //we shrink the original list
  {
    std::uniform_int_distribution<unsigned> distribution(0, sortedBaseCase.size()-1); //create the randomizer for this list size
    unsigned pos = distribution(generator);//first, decide on which element of the remaining part of the list to remove
    output.push_back(sortedBaseCase[pos]); //add it to the output
    sortedBaseCase.erase(sortedBaseCase.begin() + pos); //then remove it from the input to allow the while loop to run down to an endpoint
  }
  return output;
}

double Cities::total_path_distance(const permutation_t& ordering) const
{
  double distsum = 0;
  if (validate(ordering))
  {
    for (unsigned i = 1; i < citylist_.size(); i++)
    {
      coord_t pos = generate_positions(i, i-1, ordering);
      distsum += single_path_distance(pos);
    }
    coord_t pos = generate_positions(citylist_.size()-1, 0, ordering); //the highest valid value for citylist, and zero. this is the 'return trip'.
    distsum += single_path_distance(pos);

  }
  return distsum;
}



std::istream& operator>> (std::istream& is, Cities& cities) //i made this be a friend rather than a method
{//since it does rely on a private add_city method.
  std::string inputline; //there should be no way to add a city other than to import a new stream.
  Cities::coord_t city; //this function does not check to make sure that the cities object is empty
  while(getline(is, inputline)) //and it should not check that.
  {
    std::stringstream ss;
    ss<<inputline;
    ss>>city.first>>city.second;
    cities.add_city(city);
  }
  return is;
}

void Cities::clear()
{
  citylist_.clear();
}

void Cities::add_city(coord_t city)
{
  citylist_.push_back(city);
}



std::ostream& operator<< (std::ostream& os, Cities& cities)
{
    if(!cities.citylist_.empty())
    {
      for (Cities::coord_t city : cities.citylist_)
      {
        os<<city.first<<" "<<city.second<<"\n";
      }
    }
    return os;
}
