#include "grasp.h"

int grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes )
{	
	int best_cost_solution = 0;
	int k;
	int num_groups = group_max_sizes.size();
	int num_nodes = graph.size();

	// como gerar o conjunto inicial de soluções?
	// como gerar os vizinhos?

	return -1;
}

int calculate_z( int** solution, Graph instance, int num_groups, int num_nodes )
{
	int z = 0;
	for ( int group = 0; group < num_groups; group++ )		// O( m*n^2 )
	{
		int group_diversity = 0;
		for ( int person_a = 0; person_a < num_nodes; person_a++ )					// calcula a diversidade de cada grupo
		{
			if ( solution[group][person_a] == 1 )
			{
				int individual_diversity = 0;
				for ( int person_b = 0; person_b < num_nodes; person_b++ )
				{
					if ( solution[group][person_b] == 1 )
						individual_diversity += instance[person_a][person_b];
				}
				
				group_diversity += individual_diversity;
			}
		}
		z += group_diversity;
	}
	
	return z;
}

std::vector<int> build_restricted_candidate_list( int k, Graph instance )
{
	int num_nodes = instance.size();
	
	std::vector<int> rcl;
	std::vector<int> nodes(num_nodes), nodes_si;
	
	for ( int i = 0; i < num_nodes; i++ )				// O(n)
		nodes[i] = i;
	
	for ( int i = 0; i < num_nodes; i++ )				// O(n^2)
	{
		std::vector<int> diversities( num_nodes );
		for ( int j = 0; j < num_nodes; j++ )
			diversities[j] = instance[i][j];
		
		quick_sort_nodes( nodes, diversities );
		
		std::vector<int> top_k_diversities;
		// seleciona os k nodos com maior diversidade de i
		for ( int j = 0; j < k; j++ )
			top_k_diversities.push_back( nodes[j] );
		
		// si: soma das diversidades para os k nodos
		int si = 0;
		for ( int j = 0; j < k; j++ )
			si += top_k_diversities[j];
		
		nodes_si.push_back( si );
	}
	
	// ordena os nodos em ordem decrescente pelos si
	quick_sort_nodes( nodes, nodes_si );
		
	// insere os k primeiros elementos da lista ordenada no rcl
	for ( int i = 0; i < k; i++ )						// O(k)
		rcl.push_back( nodes[i] );
	
	return rcl;
}

void quick_sort_nodes( std::vector<int>& nodes, std::vector<int> s )
{
	
}