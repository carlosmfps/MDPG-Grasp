#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <time.h>

#define MAX_ITERATIONS 2500
#define MAX_NEIGHBOR 250

typedef std::vector< std::vector<float> > Graph;

// Algoritmo aplicado: K Largest Distances 2
// como descrito no artigo New Heuristics for the Maximum Diversity Problem, disponível em:
// https://www.researchgate.net/publication/220403323_New_heuristics_for_the_maximum_diversity_problem
float grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes );

float calculate_z( std::vector< std::vector<int> > solution, Graph instance, int num_groups, int num_nodes );

std::vector< std::vector<int> > build_initial_solution( Graph instance, std::vector<bool>& available_nodes, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes );

int find_person_p_group( std::vector< std::vector<int> > solution, int p );

std::vector< std::vector<int> > build_neighbor( int person_a, int person_b, std::vector< std::vector<int> > solution );

void print_solution( std::vector< std::vector<int> > solution );

std::vector<int> build_restricted_candidate_list( int k, Graph instance, std::vector<bool>& available_nodes );