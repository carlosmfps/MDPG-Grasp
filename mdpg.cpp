#include <iostream>
#include <vector>
#include "grasp.h"

std::vector< std::vector<int> > read_graph()
{
	std::vector< std::vector<int> > graph;
	int num_vertex, num_arch;
	
	std::cout << std::endl << "informe o numero de pessoas:" << std::endl << "> ";
	std::cin >> num_vertex;
	num_arch = ( ( num_vertex * num_vertex ) - num_vertex ) / 2;
	
	// inicializa grafo preenchido com 0
	std::vector<int> column( num_vertex );
	std::fill( column.begin(), column.end(), 0 );
	for ( int i = 0; i < num_vertex; i++ )		// O(n)
		graph.push_back( column );

	// le arestas
	std::cout << std::endl << "informe 3 valores para cada par de pessoas - pessoa a, pessoa b e a diversidade entre elas:" << std::endl;
	for ( int i = 0; i < num_arch; i++ )			// O(n^2)
	{
		int a, b, diversity;
		std::cout << "> ";
		std::cin >> a >> b >> diversity;
		graph[a][b] = graph[b][a] = diversity;
	}
	
	return graph;
}

void read_group_sizes( std::vector<int>& group_min_sizes, std::vector<int>& group_max_sizes )
{
	int num_groups;
	
	srand( time( NULL ) );
	
	std::cout << std::endl << "informe o numero de grupos:" << std::endl << "> ";
	std::cin >> num_groups;
	
	std::cout << std::endl << "informe 2 valores para cada grupo - o tamanho minimo e o tamanho maximo de cada um:" << std::endl;
	for ( int i = 0; i < num_groups; i++ )		// O(m)
	{
		int min, max;
		std::cout << "> ";
		std::cin >> min >> max;
		
		group_min_sizes.push_back( min );
		group_max_sizes.push_back( max );
	}
}


int main()
{
	int best_solution;
	std::vector< std::vector<int> > graph;
	std::vector<int> group_min_sizes, group_max_sizes;
	
	graph = read_graph();
	read_group_sizes( group_min_sizes, group_max_sizes );

	best_solution = grasp( graph, group_min_sizes, group_max_sizes );

	std::cout << std::endl << "melhor solucao encontrada: " << best_solution << std::endl;
	
	return 0;
}