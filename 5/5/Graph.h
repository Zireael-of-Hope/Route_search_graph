#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <fstream>
#include "Queue.h"
using namespace std;

enum class CONNECTION
{
	INVERT,
	DELETE,
	CREATE
};

enum class WAY
{
	LONGEST,
	SHORTEST,
	ALL
};

template<class T>
class Graph
{

	class Node
	{
	public:
		T data;
		map<int, Node*> connection_out;
		map<int, Node*> connection_in;
		bool is_passed;

		bool is_node_connected_out_to(int node_this_node_connected_to)
		{
			for (auto iter = connection_out.begin(); iter != connection_out.end(); iter++)
			{
				if (iter->first == node_this_node_connected_to)
					return true;
			}
			return false;
		}

		bool is_node_connected_in_from(int node_this_node_connected_from)
		{
			for (auto iter = connection_in.begin(); iter != connection_in.end(); iter++)
			{
				if (iter->first == node_this_node_connected_from)
					return true;
			}
			return false;
		}

		Node(T new_data)
		{
			this->data = new_data;
			this->is_passed = false;
		}
	};

	map<int, Node*> all_nodes;
	int size;
	set< vector<int> > all_ways; // здесь находятся все пути из ноды в ноду после выполнения void find_the_shortest_way(int node_from, int node_to, WAY action)

	void connect_node_to_node(int node_from, int node_to)
	{
		auto iter_1 = all_nodes.find(node_to);
		auto iter_2 = all_nodes.find(node_from);

		if (iter_1 != all_nodes.end() && iter_2 != all_nodes.end())
		{
			all_nodes[node_from]->connection_out.insert(make_pair(iter_1->first, iter_1->second));
			all_nodes[node_to]->connection_in.insert(make_pair(iter_2->first, iter_2->second));
		}
	}

	void disconnect_node_from_node(int node_from, int node_to)
	{
		auto iter_1 = all_nodes.find(node_to);
		auto iter_2 = all_nodes.find(node_from);

		if (iter_1 != all_nodes.end() && iter_2 != all_nodes.end())
		{
			all_nodes[node_from]->connection_out.erase(iter_1);
			all_nodes[node_to]->connection_in.erase(iter_2);
		}
	}

public:

	Graph()
	{
		size = 0;
	}

	void add_node(T value)
	{
		Node* new_node = new Node(value);
		all_nodes.insert(make_pair(++size, new_node));
	}

	void change_connections(int number_node_from, int number_node_to, CONNECTION action)
	{
		if (all_nodes[number_node_from] != nullptr && all_nodes[number_node_to] != nullptr)
			switch (action)
			{
			case CONNECTION::CREATE:
				connect_node_to_node(number_node_from, number_node_to);
				break;
			case CONNECTION::DELETE:
				disconnect_node_from_node(number_node_from, number_node_to);
				break;
			case CONNECTION::INVERT:
				disconnect_node_from_node(number_node_from, number_node_to);
				connect_node_to_node(number_node_to, number_node_from);
				break;
			}
	}

	void show_graph_table()
	{
		cout << "   ";
		for (auto iter = all_nodes.begin(); iter != all_nodes.end(); iter++)
		{
			cout << "N" << iter->first << " ";
		}

		cout << endl;

		for (auto iter_1 = all_nodes.begin(); iter_1 != all_nodes.end(); iter_1++)
		{
			if (iter_1->first < 10)
				cout << "N" << iter_1->first << " ";
			else
				cout << "N" << iter_1->first;
			for (auto iter_2 = all_nodes.begin(); iter_2 != all_nodes.end(); iter_2++)
			{
				if ((iter_1->second)->is_node_connected_out_to(iter_2->first) == true)
				{
					cout << " 1 ";
				}
				else
				{
					cout << " 0 ";
				}
			}
			cout << endl;
		}
	}

	void clear_node_passes()
	{
		for (auto iter = all_nodes.begin(); iter != all_nodes.end(); iter++)
		{
			(iter->second)->is_passed = false;
		}
	}

	void bypass_in_death(int first_el)
	{
		all_nodes[first_el]->is_passed = true;
		for (auto iter = all_nodes[first_el]->connection_out.begin(); iter != all_nodes[first_el]->connection_out.end(); iter++)
		{
			if ((iter->second)->is_passed == false)
			{
				bypass_in_death(iter->first);
			}
		}
	}

	void find_the_way(int node_from, int node_to, WAY action)
	{
		static int very_node_from = node_from;
		int min, max;
		vector<int> temp_arr;
		stack<int> connections_to_pass;
		static Queue<int> bypassed_nodes;

		bypassed_nodes.push(node_from);

		for (auto iter = all_nodes[node_from]->connection_out.begin(); iter != all_nodes[node_from]->connection_out.end(); iter++)
		{
			if (iter->first == node_to)
			{
				for (int i = 0; i < bypassed_nodes.size(); i++)
				{
					temp_arr.push_back(bypassed_nodes.front());
					bypassed_nodes.push(bypassed_nodes.pop());
				}
				temp_arr.push_back(node_to);
				all_ways.insert(temp_arr);
			}
			else if (iter->first != node_from && iter->first != very_node_from)
				connections_to_pass.push(iter->first);
		}

		for (int i = 0; i < connections_to_pass.size(); i++)
		{
			find_the_way(connections_to_pass.top(), node_to, action);
			connections_to_pass.pop(); i--;
		}

		bypassed_nodes.pop_back();

		if (bypassed_nodes.empty())
		{
			switch (action) 
			{
			case WAY::ALL:
				cout << endl;
				cout << "All ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					for (int i = 0; i < (*iter).size(); i++)
						if (i == 0)
							cout << (*iter)[i];
						else
							cout << " -> " << (*iter)[i];
					cout << endl;
				}
				break;
			case WAY::SHORTEST:
				cout << endl;
				cout << "Shortest ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter == all_ways.begin())
						min = iter->size();
					else if (iter->size() < min)
						min = iter->size();
				}
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter->size() == min)
					{
						for (int i = 0; i < (*iter).size(); i++)
							if (i == 0)
								cout << (*iter)[i];
							else
								cout << " -> " << (*iter)[i];
						cout << endl;
					}
				}
				break;
			case WAY::LONGEST:
				cout << endl;
				cout << "Longest ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter == all_ways.begin())
						max = iter->size();
					else if (iter->size() > max)
						max = iter->size();
				}
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter->size() == max)
					{
						for (int i = 0; i < (*iter).size(); i++)
							if (i == 0)
								cout << (*iter)[i];
							else
								cout << " -> " << (*iter)[i];
						cout << endl;
					}
				}
				break;
			}		
		}
	}

	bool create_graph_out_of_file(const string path)
	{
		int temp_fin, size;
		int** matrix;
		ifstream fin;
		fin.exceptions(ifstream::badbit | ifstream::failbit);

		try
		{
			fin.open(path);
		}
		catch (const ifstream::failure& ex)
		{
			cout << ex.what() << endl;
			return false;
		}

		if (fin.is_open())
		{
			fin >> size;

			matrix = new int* [size];
			for (int i = 0; i < size; i++)
				matrix[i] = new int[size];

			while (!fin.eof())
			{
				for (int i = 0; i < size; i++)
					for (int j = 0; j < size; j++)
					{
						fin >> temp_fin;
						matrix[i][j] = temp_fin;
					}
			}

			for (int i = 0; i < size; i++)
				add_node(i + 1);

			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
				{
					if (matrix[i][j] == 1)
						change_connections(i+1, j+1, CONNECTION::CREATE);
				}

			for (int i = 0; i < size; i++)
				delete[]matrix[i];
				delete[]matrix;

			fin.close();
			return true;
		}
	}

	bool create_file_out_of_graph(WAY action) 
	{
		int min, max;
		string path = "D:/ВУЗ/Программирование/Типы и структуры/лаб_5 (графы)/output.dat";
		fstream fout;
		fout.exceptions(ofstream::badbit | ofstream::failbit);

		try
		{
			fout.open(path, ios_base::out);
		}
		catch (const ofstream::failure& ex)
		{
			cout << ex.what() << endl;
			return false;
		}

		if (fout.is_open())
		{
			fout << "   ";
			for (auto iter = all_nodes.begin(); iter != all_nodes.end(); iter++)
			{
				fout << "N" << iter->first << " ";
			}

			fout << endl;

			for (auto iter_1 = all_nodes.begin(); iter_1 != all_nodes.end(); iter_1++)
			{
				if (iter_1->first < 10)
					fout << "N" << iter_1->first << " ";
				else
					fout << "N" << iter_1->first;
				for (auto iter_2 = all_nodes.begin(); iter_2 != all_nodes.end(); iter_2++)
				{
					if ((iter_1->second)->is_node_connected_out_to(iter_2->first) == true)
					{
						fout << " 1 ";
					}
					else
					{
						fout << " 0 ";
					}
				}
				fout << endl;
			}

			switch (action)
			{
			case WAY::ALL:
				fout << endl;
				fout << "All ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					for (int i = 0; i < (*iter).size(); i++)
						if (i == 0)
							fout << (*iter)[i];
						else
							fout << " -> " << (*iter)[i];
					fout << endl;
				}
				break;
			case WAY::SHORTEST:
				fout << endl;
				fout << "Shortest ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter == all_ways.begin())
						min = iter->size();
					else if (iter->size() < min)
						min = iter->size();
				}
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter->size() == min)
					{
						for (int i = 0; i < (*iter).size(); i++)
							if (i == 0)
								fout << (*iter)[i];
							else
								fout << " -> " << (*iter)[i];
						fout << endl;
					}
				}
				break;
			case WAY::LONGEST:
				fout << endl;
				fout << "Longest ways:" << endl;
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter == all_ways.begin())
						max = iter->size();
					else if (iter->size() > max)
						max = iter->size();
				}
				for (auto iter = all_ways.begin(); iter != all_ways.end(); iter++)
				{
					if (iter->size() == max)
					{
						for (int i = 0; i < (*iter).size(); i++)
							if (i == 0)
								fout << (*iter)[i];
							else
								fout << " -> " << (*iter)[i];
						fout << endl;
					}
				}
				break;
			}

			fout.close();
			return true;
		}
	}
};






