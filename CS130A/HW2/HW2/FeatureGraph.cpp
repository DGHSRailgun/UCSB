#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include "FeatureGraph.h"
#include "GraphHelper.h"


using namespace std;


FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
    //TODO
	this->N = N;
	this->d = d;
	this->nodes = nodes;
	this->edges = edges;
	for (unsigned int i = 0; i < this->nodes.size(); i++)
	{
		map_index[this->nodes[i].id] = i;
	};
	//init adj_matrix
	this->adj_matrix.resize(this->N);
	for (int i = 0; i < this->N; i++)
	{
		for (int j = 0; j < this->N; j++)
		{
			if (i == j)
			{
				this->adj_matrix[i].push_back(0);
			}
			else
			{
				this->adj_matrix[i].push_back(-1);
			}
		}
	}
	//init edges weight of adj_matrix
	for (unsigned int i = 0; i < this->edges.size(); i++)
	{
		int s = this->map_index.find(this->edges[i].IdA)->second;
		int e = this->map_index.find(this->edges[i].IdB)->second;
		this->adj_matrix[s][e] = this->edges[i].weight;
		this->adj_matrix[e][s] = this->edges[i].weight;
	}

	/*for (int i = 0; i < this->N; i++)
	{
		for (int j = 0; j < this->N; j++) {
			cout << adj_matrix[i][j] << "\t";
		}
		cout << endl;
	}*/

	this->open_triangle_heap;
	this->closed_triangle_heap;

	//init the closed and open triangle
	for (int i = 0; i < this->N; i++)
	{
		//to find who is the neibours of i
		vector<int> neibours;
		for (int j = 0; j < this->N; j++)
		{
			if (this->adj_matrix[i][j] != -1 && i != j) {
				neibours.push_back(j);
				//cout << i << " neibours " << j;
			}
			//cout << endl;
		}		

		for (unsigned int j = 0; j < neibours.size(); j++)
		{
			for (unsigned int k = j+1; k < neibours.size(); k++)
			{
				//cout << "traingle" << i << " " << j << " " << k << " " << endl;

				if (this->adj_matrix[neibours[j]][neibours[k]] == -1) {
					//there is no edges between j and k, it is a open triangle, add it into heap
					int weight = this->adj_matrix[i][neibours[j]] + this->adj_matrix[i][neibours[k]];

					//cout << "open" << i << " " << j << " " << k << " " << endl;

					this->open_triangle_heap.push_back(Triangle(this->nodes[i].id, this->nodes[neibours[j]].id, this->nodes[neibours[k]].id, weight));
				}
				else
				{
					if (i == min(min(i, neibours[j]), neibours[k]))
					{
						//if i is smaller than j and k, it means the triange is the first times to be found
						int weight = this->adj_matrix[i][neibours[j]] + this->adj_matrix[i][neibours[k]] + this->adj_matrix[neibours[j]][neibours[k]];
						this->closed_triangle_heap.push_back(Triangle(this->nodes[i].id, this->nodes[neibours[j]].id, this->nodes[neibours[k]].id, weight));
					}
				}
			}
		}
	}
};

void FeatureGraph::insert(Node node){
    //TODO
	this->N++;
	this->nodes.push_back(node);
	//store the id-index pair into map
	this->map_index[node.id] = this->N - 1;
	//update the adj_matrix
	this->adj_matrix.resize(this->N);
	for (int i = 0; i < this->N; i++)
	{
		if (i < this->N-1)
		{
			this->adj_matrix[i].push_back(-1);
		}
		else
		{
			for (int j = 0; j < this->N; j++)
			{
				if (i == j)
				{
					this->adj_matrix[i].push_back(0);
				}
				else
				{
					this->adj_matrix[i].push_back(-1);
				}
			}
		}
	}

};
    
void FeatureGraph::insert(Edge edge){
    //TODO
	this->edges.push_back(edge);
	//map the idA and idB's index
	int s = this->map_index.find(edge.IdA)->second;
	int e = this->map_index.find(edge.IdB)->second;
	//change the weight between idA and idB
	this->adj_matrix[s][e] = edge.weight;
	this->adj_matrix[e][s] = edge.weight;
	//to change the open and cloesd triangle

	//change s and 's traingle
	//to find who is the neibours of s, except the e, record their index
	vector<int> neibour_s;
	vector<int> neibour_e;
	for (int j = 0; j < this->N; j++)
	{
		if (this->adj_matrix[s][j] != -1 && (s != j) && (e != j)) {
			neibour_s.push_back(j);
		}
		if (this->adj_matrix[e][j] != -1 && (e != j) && (s != j)) {
			neibour_e.push_back(j);
		}
	}

	//calcuate s
	for (unsigned int i = 0; i < neibour_s.size(); i++)
	{
		if (this->adj_matrix[neibour_s[i]][e] == -1) {
			//that means neibours[i] and e is not connected, it is a open triangle
			int weight = edge.weight + this->adj_matrix[s][neibour_s[i]];
			this->open_triangle_heap.push_back(Triangle(this->nodes[s].id, this->nodes[neibour_s[i]].id, this->nodes[e].id, weight));
		}
		else
		{
			
			if (s == min(min(s, neibour_s[i]), e))
			{
				//a new closed triangle
				int weight = edge.weight + this->adj_matrix[s][neibour_s[i]] + this->adj_matrix[neibour_s[i]][e];
				Triangle temp(this->nodes[s].id, this->nodes[neibour_s[i]].id, this->nodes[e].id, weight);
				this->closed_triangle_heap.push_back(temp);
				//delete the previous open triangle heap
				for (unsigned int k = 0; k < open_triangle_heap.size(); k++)
				{
					if (open_triangle_heap[k] == temp)
					{
						this->open_triangle_heap.erase(open_triangle_heap.begin()+k);
					}
				}
			}
		}
	}

	//calcuate e
	for (unsigned int i = 0; i < neibour_e.size(); i++)
	{
		if (this->adj_matrix[neibour_e[i]][s] == -1) {
			//that means neibours[i] and s is not connected, it is a open triangle, center is e
			int weight = edge.weight + this->adj_matrix[e][neibour_e[i]];
			this->open_triangle_heap.push_back(Triangle(this->nodes[e].id, this->nodes[neibour_e[i]].id, this->nodes[s].id, weight));
		}
		else
		{

			if (e == min(min(e, neibour_e[i]), s))
			{
				//a new closed triangle
				int weight = edge.weight + this->adj_matrix[e][neibour_e[i]] + this->adj_matrix[neibour_e[i]][s];
				Triangle temp(this->nodes[e].id, this->nodes[neibour_e[i]].id, this->nodes[s].id, weight);
				this->closed_triangle_heap.push_back(temp);
				//delete the previous open triangle heap
				for (unsigned int k = 0; k < open_triangle_heap.size(); k++)
				{
					if (open_triangle_heap[k] == temp)
					{
						this->open_triangle_heap.erase(open_triangle_heap.begin() + k);
					}
				}
			}
		}
	}

};



