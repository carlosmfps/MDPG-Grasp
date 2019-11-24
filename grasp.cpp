#include "grasp.h"

std::vector<float> nodes_si;
std::vector<float> diversities;

float grasp( Graph graph, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes )
{	
	int best_cost_solution = 0;
	int num_groups = group_max_sizes.size();
	int num_nodes = graph.size();
	int person_a, person_b, a_group, b_group;
	std::vector<bool> available_nodes( num_nodes, true );
	
	// fase de construcao - nao garante que a solucao factivel seja localmente otima
	std::vector< std::vector<int> > solution = build_initial_solution( graph, available_nodes, group_min_sizes, group_max_sizes );
	std::cout << std::endl << "solucao inicial:" << std::endl;
	print_solution( solution );
	std::cout << "valor: " << calculate_z( solution, graph, num_groups, num_nodes ) << std::endl;
		
	// busca local
	for ( int i = 0; i < MAX_ITERATIONS; i++ )
	{	
		std::vector< std::vector<int> > best_local_solution = solution;

		for( int j = 0; j< MAX_NEIGHBOR; j++ )
		{
			std::vector< std::vector<int> > neighbor;			
			do
			{
				person_a = rand() % num_nodes;
				person_b = rand() % num_nodes;
				
				a_group = find_person_p_group( best_local_solution, person_a );
				b_group = find_person_p_group( best_local_solution, person_b );
			} while ( a_group == -1 || b_group == -1 || person_a == person_b );			
			
			neighbor = build_neighbor(  person_a, person_b, solution  );
			
			int this_z = calculate_z( best_local_solution, graph, num_groups, num_nodes );
			int neighbor_z = calculate_z( neighbor, graph, num_groups, num_nodes );
			
			if( this_z < neighbor_z )
			{
				best_local_solution = neighbor;
			}
		}
		solution = best_local_solution;
	}
	
	std::cout << std::endl << "solucao final encontrada:" << std::endl;
	for ( int i = 0; i < num_groups; i++ )
	{
		for ( int j = 0; j < num_nodes; j++ )
			std::cout << solution[i][j] << "\t";
		std::cout << std::endl;
	}

	return calculate_z( solution, graph, num_groups, num_nodes );
}

float calculate_z( std::vector< std::vector<int> > solution, Graph instance, int num_groups, int num_nodes )
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

std::vector< std::vector<int> > build_initial_solution( Graph instance, std::vector<bool>& available_nodes, std::vector<int> group_min_sizes, std::vector<int> group_max_sizes )
{
	std::vector< std::vector<int> > solution;
	int num_groups = group_min_sizes.size();
	int num_nodes = instance.size();
	
	for ( int i = 0; i < num_groups; i++ )
	{
		std::vector<int> row;
		for ( int j = 0; j < num_nodes; j++ )
			row.push_back( 0 );
		solution.push_back( row );
	}
	std::cout << "TESTE 1\n";
	for ( int i = 0; i < num_groups; i++ )
	{
		int k = group_max_sizes[i];

		std::vector<int> rcl = build_restricted_candidate_list( k, instance, available_nodes );
		std::cout << "TESTE 1.1\n";
		for ( int j = 0; j < group_min_sizes[i]; j++ )
		{
			if ( rcl.size() > 0 )
			{
				int person = rand() % rcl.size();
			
				solution[i][rcl[person]] = 1;
				available_nodes[rcl[person]] = false;
				rcl.erase( rcl.begin() + person );
			}
		}
	}
	std::cout << "TESTE 2\n";
	for ( int i = 0; i < num_groups; i++ )
	{
		// conta o numero de pessoas no grupo
		int n_people = 0;
		for ( int j = 0; j < num_nodes; j++ )
		{
			if ( solution[i][j] == 1 )
				n_people++;
		}
		
		if ( n_people < group_max_sizes[i] )
		{
			// coloca os nodos que sobraram em grupos que ainda tem espaço
			int k = group_max_sizes[i] - n_people;
			std::vector<int> rcl = build_restricted_candidate_list( k, instance, available_nodes );

			for ( int j = 0; j < rcl.size(); j++ )
			{
				solution[i][rcl[j]] = 1;
				available_nodes[rcl[j]] = false;
			}
		}
	}
	
	return solution;
}

int find_person_p_group( std::vector< std::vector<int> > solution, int p )
{
	for ( int i = 0; i < solution.size(); i++ )
	{
		if ( solution[i][p] == 1 )
			return i;
	}
	
	return -1;
}

std::vector< std::vector<int> > build_neighbor( int person_a, int person_b, std::vector< std::vector<int> > solution )
{
	std::vector< std::vector<int> > neighbor = solution;
	int num_groups = solution.size();
	int person_a_group, person_b_group;
	
	// encontra os grupos de cada pessoa
	for ( int i = 0; i < num_groups; i++ )
	{
		if ( solution[i][person_a] == 1 )
			person_a_group = i;
		if ( solution[i][person_b] == 1 )
			person_b_group = i;
	}

	// troca os grupos
	neighbor[person_a_group][person_a] = 0;
	neighbor[person_b_group][person_a] = 1;
	
	neighbor[person_b_group][person_b] = 0;
	neighbor[person_a_group][person_b] = 1;
	
	return neighbor;
}

void print_solution( std::vector< std::vector<int> > solution )
{
	for ( int i = 0; i < solution.size(); i++ )
	{
		for ( int j = 0; j < solution[i].size(); j++ )
			std::cout << solution[i][j] << "\t";
		std::cout << std::endl;
	}
}

std::vector<int> build_restricted_candidate_list( int k, Graph instance, std::vector<bool>& available_nodes )
{
	// utiliza um algoritmo guloso para estimar o ganho de incluir uma pessoa em um grupo na solucao
	int num_nodes = instance.size();
	int num_available_nodes = 0;
	
	for ( int i = 0; i < num_nodes; i++ )
		num_available_nodes++;
	
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
				if ( available_nodes[j] && i != j )
					diversities[j] = instance[i][j];
				else
					diversities[j] = 0;
			}
			
			std::sort( nodes.begin(), nodes.end(), []( int node_a, int node_b ){ return diversities[node_a] >= diversities[node_b]; });
			std::vector<int> top_k_diversities;
				
			// seleciona os k nodos com maior diversidade de i
			for ( int j = 0; j < k; j++ )
				top_k_diversities.push_back( diversities[nodes[j]] );
			
			// si: soma das diversidades para os k nodos
			int si = 0;
			for ( int j = 0; j < k; j++ )
				si += top_k_diversities[j];
			
			nodes_si.push_back( si );
		}
		else
			nodes_si.push_back( 0 );
	}
	
	// ordena os nodos em ordem decrescente pelos si
	std::sort( nodes.begin(), nodes.end(), []( int node_a, int node_b ){ return nodes_si[node_a] >= nodes_si[node_b]; });
		
	// insere os k primeiros elementos da lista ordenada no rcl
	for ( int i = 0; i < k; i++ )						// O(n)
	{
		if ( available_nodes[nodes[i]] )
			rcl.push_back( nodes[i] );
		else k--;
	}
	
	return rcl;
}