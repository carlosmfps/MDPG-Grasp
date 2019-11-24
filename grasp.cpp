#include "grasp.h"

std::vector<int> nodes_si;
std::vector<int> diversities;

int grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes )
{	
	int best_cost_solution = 0;
	int num_groups = group_max_sizes.size();
	int num_nodes = graph.size();
	std::vector<bool> available_nodes( num_nodes, true );

	// constroi solução inicial
	std::vector< std::vector<int> > solution;
	for ( int i = 0; i < num_groups; i++ )
	{
		std::vector<int> row;
		for ( int j = 0; j < num_nodes; j++ )
			row.push_back( 0 );
		solution.push_back( row );
	}
	
	for ( int i = 0; i < num_groups; i++ )						// O(n^2)
	{
		int k = group_min_sizes[i];
		std::vector<int> rcl = build_restricted_candidate_list( k, graph, available_nodes );
		
		for ( int j = 0; j < group_min_sizes[i]; j++ )
			solution[i][rcl[j]] = 1;
	}
	
	std::cout << std::endl << "solucao inicial:" << std::endl;
	for ( int i = 0; i < num_groups; i++) 		// O(n^2)
	{
		for ( int j = 0; j < num_nodes; j++ )
			std::cout << solution[i][j] << "\t";
		std::cout << std::endl;
	}

	return calculate_z( solution, graph, num_groups, num_nodes );
}

int calculate_z( std::vector< std::vector<int> > solution, Graph instance, int num_groups, int num_nodes )
{
	int z = 0;
	for ( int group = 0; group < num_groups; group++ )		// O( m*n^2 ) -> O(n^3)
	{
		int group_diversity = 0;
		for ( int person_a = 0; person_a < num_nodes; person_a++ )					// calcula a diversidade de cada grupo
		{
			if ( solution[group][person_a] == 1 )
			{
				int individual_diversity = 0;
				for ( int person_b = person_a; person_b < num_nodes; person_b++ )
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

std::vector<int> build_restricted_candidate_list( int k, Graph instance, std::vector<bool>& available_nodes )
{
	int num_nodes = instance.size();
	int num_available_nodes = 0;
	for ( int i = 0; i < num_nodes; i++ )
	{
		if ( available_nodes[i] )
			num_available_nodes++;
	}
	
	std::vector<int> rcl;
	std::vector<int> nodes(num_nodes);
	nodes_si.clear();
	
	for ( int i = 0; i < num_nodes; i++ )		// O(n)
		nodes[i] = i;
	
	for ( int i = 0; i < num_nodes; i++ )
	{
		if ( available_nodes[i] )
		{
			diversities.clear();
			diversities.resize( num_nodes );
			for ( int j = 0; j < num_nodes; j++ )
			{
				if ( available_nodes[j] )
					diversities[j] = instance[i][j];
				else
					diversities[j] = INT_MIN;
			}
			
			std::sort( nodes.begin(), nodes.end(), []( int node_a, int node_b ){ return diversities[node_a] >= diversities[node_b]; });
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
	}
	
	// ordena os nodos em ordem decrescente pelos si
	std::sort( nodes.begin(), nodes.end(), []( int node_a, int node_b ){ return nodes_si[node_a] >= nodes_si[node_b]; });
		
	// insere os k primeiros elementos da lista ordenada no rcl
	for ( int i = 0; i < k; i++ )						// O(k)
		rcl.push_back( nodes[i] );
	
	return rcl;
}