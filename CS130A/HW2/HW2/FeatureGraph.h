#ifndef FEATURE_H
#define FEATURE_H


#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "GraphHelper.h"


using namespace std;



class FeatureGraph {

private:
	friend class GraphAnalyer;
	vector<Node> nodes;
	vector<Edge> edges;
	int N;//nodes number
	int d;//skills number
	unordered_map<int,int> map_index;
	vector<vector<int> > adj_matrix;//graph_matrix
	//priority_queue<Triangle,vector<Triangle>, CmpTriangle> open_triangle_heap;
	vector<Triangle> open_triangle_heap;//a MaxHeap to store triangle
	vector<Triangle> closed_triangle_heap;

public:
    // TODO add necessary private fields


    // Constructor
    // 
    // N: The number of nodes
    // d: the sizee of the skill vectors of all nodes
    // nodes: vector of nodes to insert
    // edges: vector of edges to insert
    FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges);


    //Insert node with given ID and feature vectors
    void insert(Node node);

    // insert given edge
    // May assume nodes in edge are already present
    void insert(Edge edge);

	friend class GraphAnalyzer;
};  

#endif
