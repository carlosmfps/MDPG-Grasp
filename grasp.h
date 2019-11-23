#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_ITERATIONS 20

typedef std::vector< std::vector<int> > Graph;

// Algoritmo aplicado: K Largest Distances 2
// como descrito no artigo New Heuristics for the Maximum Diversity Problem, disponível em:
// https://www.researchgate.net/publication/220403323_New_heuristics_for_the_maximum_diversity_problem
int grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes );

int calculate_z( int** solution, Graph instance, int num_groups, int num_nodes );

std::vector<int> build_restricted_candidate_list( int k, Graph instance );

void quick_sort_nodes( std::vector<int>& nodes, std::vector<int> s );