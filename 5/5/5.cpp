#include <iostream>
#include "Graph.h"
using namespace std;
int main()
{
	Graph<int> graph;
	string path = "D:/ВУЗ/Программирование/Типы и структуры/лаб_5 (графы)/input.dat";

	graph.create_graph_out_of_file(path);
	graph.show_graph_table();

	graph.find_the_way(1, 3, WAY::LONGEST);
	graph.create_file_out_of_graph(WAY::ALL);

	///*x1*/ graph.add_node(1);
	///*x2*/ graph.add_node(2);
	///*x3*/ graph.add_node(3);
	///*x4*/ graph.add_node(4);
	///*x5*/ graph.add_node(5);
	///*x6*/ graph.add_node(6);
	///*x7*/ graph.add_node(7);
	///*x8*/ graph.add_node(8);
	///*x9*/ graph.add_node(9);
	///*x10*/ graph.add_node(10);

	///*a1*/ graph.change_connections(1, 2, CONNECTION::CREATE);
	///*a2*/ graph.change_connections(1, 3, CONNECTION::CREATE);
	///*a3*/ graph.change_connections(2, 2, CONNECTION::CREATE);
	///*a4*/ graph.change_connections(2, 5, CONNECTION::CREATE);
	///*a5*/ graph.change_connections(4, 3, CONNECTION::CREATE);
	///*a6*/ graph.change_connections(5, 4, CONNECTION::CREATE); //
	///*a7*/ graph.change_connections(6, 5, CONNECTION::CREATE);
	///*a8*/ graph.change_connections(1, 5, CONNECTION::CREATE);
	///*a9*/ graph.change_connections(6, 1, CONNECTION::CREATE);
	///*a10*/ graph.change_connections(6, 6, CONNECTION::CREATE);
	///*a11*/ graph.change_connections(2, 7, CONNECTION::CREATE);
	///*a12*/ graph.change_connections(7, 9, CONNECTION::CREATE);
	///*a13*/ graph.change_connections(2, 8, CONNECTION::CREATE);
	///*a14*/ graph.change_connections(1, 8, CONNECTION::CREATE);
	///*a15*/ graph.change_connections(8, 9, CONNECTION::CREATE);
	///*a16*/ graph.change_connections(8, 10, CONNECTION::CREATE);
	///*a17*/ graph.change_connections(9, 3, CONNECTION::CREATE);
	///*a18*/ graph.change_connections(9, 4, CONNECTION::CREATE);
	///*a19*/ graph.change_connections(10, 4, CONNECTION::CREATE);
	///*a20*/ graph.change_connections(5, 9, CONNECTION::CREATE);
	//graph.show_graph_table();

	//graph.find_the_way(1, 4, WAY::SHORTEST);
}

