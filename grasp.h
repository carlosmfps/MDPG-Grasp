#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>

#define MAX_ITERATIONS 20

typedef std::vector< std::vector<int> > Graph;

// Algoritmo aplicado: K Largest Distances 2
// como descrito no artigo New Heuristics for the Maximum Diversity Problem, disponível em:
// https://www.researchgate.net/publication/220403323_New_heuristics_for_the_maximum_diversity_problem
int grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes );

int calculate_z( std::vector< std::vector<int> > solution, Graph instance, int num_groups, int num_nodes );

std::vector< std::vector<int> > build_initial_solution( Graph instance, std::vector<bool>& available_nodes, std::vector<int> group_min_sizes );

void print_solution( std::vector< std::vector<int> > solution );

std::vector<int> build_restricted_candidate_list( int k, Graph instance, std::vector<bool>& available_nodes );