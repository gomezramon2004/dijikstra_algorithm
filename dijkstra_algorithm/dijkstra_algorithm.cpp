#include "dijkstra_algorithm.hpp"

// Constructor
DijkstraAlgorithm::DijkstraAlgorithm(int total_nodes, const std::vector<std::vector<int>>& adjacency_matrix): SIZE(total_nodes), ADJ_MATRIX(adjacency_matrix) {}

// Iterate through the distance vector and get the mininum distance from a position that wasn't checked
int DijkstraAlgorithm::get_min_distance_index(const std::vector<DistanceInfo>& distances) const {
  int min_distance = INT_MAX;
  int min_index = -1;

  for (int i = 0; i < this->SIZE; ++i) {
    if (!distances[i].finalized && distances[i].distance <= min_distance) {
      min_distance = distances[i].distance;
      min_index = i;
    }
  }

  return min_index;
}

//  Print the results. From the initial to the final node, how much distance have been traveled
void DijkstraAlgorithm::print_result(int index_source, const std::vector<DistanceInfo>& distances) const {
  std::cout << "Dijkstra Algorithm - Node #" << (index_source + 1) << ":\n";
  for (int i = 0; i < this->SIZE; ++i) {
      if (i == index_source) continue;
      std::cout << "Node " << (index_source + 1) << " to Node " << (i + 1) << " : " << distances[i].distance << "\n";
  }
}

// Run the Dikkstra Algorithm, based on the next reference
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-greedy-algo-7/
void DijkstraAlgorithm::run_algorithm(int index_source) {

  // Initialize dynamically a distance vector with dummy data, although the initial node has a distance of zero 
  this->distances = new std::vector<DistanceInfo>(SIZE, DistanceInfo(INT_MAX, false));
  (*this->distances)[index_source].distance = 0;
  int min_idx = index_source;

  // Until all of the finalized paths have been listed, get the mininum distance for each round and calculate the adjacency routes
  while (true) {
    min_idx = this->get_min_distance_index((*this->distances));
    if (min_idx == -1 || (*this->distances)[min_idx].distance == INT_MAX) break;
    (*this->distances)[min_idx].finalized = true;

    for (int current_idx = 0; current_idx < this->SIZE; ++current_idx) {

      const bool& current_distance_is_finalized = (*this->distances)[current_idx].finalized;
      const int& current_matrix_pos_distance = this->ADJ_MATRIX[min_idx][current_idx];
      const int& min_distance = (*this->distances)[min_idx].distance;
      const int& new_distance = min_distance + current_matrix_pos_distance;
      int& curr_distance = (*this->distances)[current_idx].distance;

      if (!current_distance_is_finalized && current_matrix_pos_distance > 0) {
        if (new_distance < curr_distance) curr_distance = new_distance;
      }
    }
  }

  // Print and destroy dynamically the distance vector
  this->print_result(index_source, (*this->distances));
  delete this->distances;
  this->distances = nullptr;
}