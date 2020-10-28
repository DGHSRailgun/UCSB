#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <climits>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;


void GraphAnalyzer::insert(Node n) {
    G.insert(n);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
    G.insert(e);
    // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

int GraphAnalyzer::diameter() {
    //TODO
	int* dp = new int[(G.N * G.N)];//a table to store the i to j's path

	//init the table
	//1.init every diff pair node to MAX, same pair node to 0
	for (int i = 0; i < G.N; i++)
	{
		for (int j = 0; j < G.N; j++) {
			if (i == j)
			{
				dp[(i * G.N) + i] = 0;
			}
			else
			{
				dp[(i * G.N) + j] = INT_MAX;
			}
		}
	}
	//2.init the edge position
	for (unsigned int i = 0; i < G.edges.size(); i++)
	{
		int s = (G.map_index.find(G.edges[i].IdA))->second;
		int e = (G.map_index.find(G.edges[i].IdB))->second;
		dp[(s * G.N) + e] = G.edges[i].weight;
		dp[(e * G.N) + s] = G.edges[i].weight;
	}

	/*for (int i = 0; i < this->N; i++)
	{
		for (int j = 0; j < this->N; j++) {
			cout << dp[(i * this->N) + j] << "\t";
		}
		cout << endl;
	}*/

	//loop to fill the table
	for (int k = 0; k < G.N; k++)
	{
		for (int i = 0; i < G.N; i++)
		{
			for (int j = 0; j < G.N; j++)
			{
				if (dp[(i * G.N) + k] != INT_MAX && dp[(k * G.N) + j] != INT_MAX)
				{
					dp[(i * G.N) + j] = min(dp[(i * G.N) + j], dp[(i * G.N) + k] + dp[(k * G.N) + j]);
					dp[(j * G.N) + i] = dp[(i * G.N) + j];
				}
			}
		}
	}

	//after the loop, every position is the min distance from i to j, to find the max one is the diameter
	int diameter = 0;

	for (int i = 0; i < G.N; i++)
	{
		for (int j = 0; j < i; j++) {
			if (dp[(i * G.N) + j] > diameter) {
				diameter = dp[(i * G.N) + j];
			}
			//cout << dp[(i * this->N) + j] << "\t";
		}
		//cout<<endl;
	}

	delete[] dp;

	return diameter;
};


float GraphAnalyzer::openClosedTriangleRatio() {
    //TODO

	/*cout << G.open_triangel_heap.size() << endl;
	cout << G.closed_triangel_size << endl;*/

    return static_cast<float>(( G.open_triangle_heap.size() + 0.0 )/G.closed_triangle_heap.size());
};

string GraphAnalyzer::topKOpenTriangles(int k) {
	//TODO
	priority_queue<Triangle, vector<Triangle>, less<Triangle>> my_heap;
	for (int i = 0; i < G.open_triangle_heap.size(); i++)
	{
		if (i < k)
		{
			my_heap.push(G.open_triangle_heap[i]);
		}
		else
		{
			if (my_heap.top() < G.open_triangle_heap[i])
			{
				my_heap.pop();
				my_heap.push(G.open_triangle_heap[i]);
			}
		}
	}
	string result = "";
	for (int i = 0; i < my_heap.size(); i++)
	{
		result += my_heap.top().display() + '\n';
		my_heap.pop();
	}
    return result;
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
    //TODO
	struct dot_node {
		int index;
		float value;
	};
	//Compare method
	struct lessCmp {
		bool operator ()(const dot_node& a, const dot_node& b) {
			return a.value > b.value;
		}

	};

	if (k == 0) {
		return vector<int> {};
	}

	//vector<dot_node> my_heap;
	priority_queue<dot_node, vector<dot_node>, lessCmp> my_heap;

	int seed_index = ((this->G).map_index).find(nodeID)->second;

	for (int i = 0; i < G.N; i++)
	{
		int weight = G.adj_matrix[seed_index][i];
		//if it is seed's neibours
		if (weight != -1 && i != seed_index) {
			
			//calucate node's dot
			float value = 0;
			for (int j = 0; j < G.d; j++)
			{
				value += G.nodes[i].features[j] * w[j];
			}
			//to decide if the dot_node should go into the heap
			if (static_cast<unsigned int>(my_heap.size()) < k)
			{
				my_heap.push({ i,value });
			}
			else
			{
				if (my_heap.top().value < value) {
					my_heap.pop();
					my_heap.push({ i,value });
				}
			}
		}
	}

	vector<int> indexs;
	while (!my_heap.empty())
	{
		indexs.push_back(G.nodes[my_heap.top().index].id);
		my_heap.pop();
	}

	vector<int> result;
	for (int i = indexs.size()-1; i >= 0; i--)
	{
		result.push_back(indexs[i]);
	}

    return result;
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
    //TODO
	float max_score = 0;

	int seed_index = ((this->G).map_index).find(nodeID)->second;

	int index = -1;

	for (int i = 0; i < G.N; i++)
	{
		int weight = G.adj_matrix[seed_index][i];
		//if it is not the seed's neibours
		if (weight == -1) {

			//calucate node's dot
			float value = 0;
			for (int j = 0; j < G.d; j++)
			{
				value += G.nodes[i].features[j] * w[j];
			}
			//put it into the heap
			if (value > max_score)
			{
				max_score = value;
				index = i;
			}
		}
	}

	return G.nodes[index].id;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w) {
    //TODO

	vector<int> ATopK = this->topKNeighbors(nodeAID, k, w);
	sort(ATopK.begin(), ATopK.end());

	/*cout << "A" << endl;
	for (int i = 0; i < ATopK.size(); i++)
	{
		cout << ATopK[i] << "\t";
	}
	cout << endl;*/

	vector<int> BTopK = this->topKNeighbors(nodeBID, k, w);
	sort(BTopK.begin(), BTopK.end());

	/*cout << "B" << endl;
	for (int i = 0; i < BTopK.size(); i++)
	{
		cout << BTopK[i] << "\t";
	}
	cout << endl;*/

	vector<int> intersect;
	set_intersection(ATopK.begin(), ATopK.end(), BTopK.begin(), BTopK.end(), back_inserter(intersect));

	//cout << intersect.size() << " intersect" << endl;

	float result = static_cast<float>((intersect.size() + 0.0 ) / (0.0 + (float)ATopK.size() + (float)BTopK.size() - intersect.size()));

    return result;
};



