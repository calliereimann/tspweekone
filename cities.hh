/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>
#include <cmath>
#include <chrono>
// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of cities. Each value represents a unique index
  // into the current city ordering in some container.
  using permutation_t = std::vector<unsigned int>;
  using size_t = unsigned;
  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  //various overloaded operators
  friend std::istream& operator>> (std::istream& is, Cities& cities);
  friend std::ostream& operator<< (std::ostream& os, Cities& cities);


  //public size access method
  size_t size() {return citylist_.size();}
private:
  std::vector<coord_t> citylist_;
  void add_city(coord_t); //used in operator>>
  void clear(); //I don't remember if this is actually used anywhere, but it's good to have if needed in the future.
  coord_t generate_positions(unsigned point1, unsigned point2, const permutation_t& ordering) const; //submethod for total_path_distance()
  double single_path_distance(coord_t pos) const; //submethod for total_path_distance()
  std::stringstream new_arrangement(const permutation_t& ordering) const; //submethod for reorder()
  bool validate(const permutation_t& ordering) const; //technically not needed but it's cleaner to package on its own
};

Cities::permutation_t random_permutation(unsigned len);
