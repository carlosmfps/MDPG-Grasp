#include <iostream>
#include <vector>
#include <iostream>     
#include <fstream>      
#include "grasp.h"

int main(int argc, char *argv[])
{	
	srand(atoi(argv[2]) );
	std::ifstream input;
	input.open(argv[1]);
	std::string tipo_arq;
	float best_solution;
	std::vector< std::vector<int> > graph;
	std::vector<int> group_min_sizes, group_max_sizes;
	int num_vertex, num_arch, num_groups;
	
	//recebe o numero de pessoas
	input >> num_vertex;
	//recebe o numero de grupos
	input >> num_groups;
	input >> tipo_arq;
	num_arch = ( ( num_vertex * num_vertex ) - num_vertex ) / 2;

	
	
	//preenche os vetores de limites de listas
	for ( int i = 0; i < num_groups; i++ )		// O(m)
	{
		int min, max;
		input >> min >> max;
		group_min_sizes.push_back( min );
		group_max_sizes.push_back( max );
	}
	// inicializa grafo preenchido com 0
	std::vector<int> column( num_vertex );
	std::fill( column.begin(), column.end(), 0 );
	for ( int i = 0; i < num_vertex; i++ ){		// O(n)
		graph.push_back( column );
	}
		
	// le arestas
	for ( int i = 0; i < num_arch; i++ )			// O(n^2)
	{
		int a, b, diversity;
		input >> a >> b >> diversity;
		graph[a][b] = diversity;
		graph[b][a] = diversity;
	}
	
	input.close();
	
	best_solution = grasp( graph, group_min_sizes, group_max_sizes );
	
	std::cout << std::endl << "melhor solucao encontrada: " << best_solution << std::endl;
	
	return 0;
}