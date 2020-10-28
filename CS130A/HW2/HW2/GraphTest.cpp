#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <map>
#include <iostream>
using namespace std;

int main() {
    
    vector<Node> nodes  {
       Node(1, vector<float> { 10, 10}),
       Node(2,vector<float> { 20, 20}),
       Node(3, vector<float> { 30, 30}),
       Node(4, vector<float> { 40, 40}),
	   Node(5, vector<float> { 40, 20}),
	   Node(6, vector<float> { 15, 10})
		};
    
    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(1, 3, 5),Edge(3, 4, 1),Edge(6, 3, 2),Edge(5, 6, 4),
	Edge(1, 6, 7),Edge(4, 5, 3) };
  
    int d = 2;


    FeatureGraph graph = FeatureGraph(6, d, nodes, edges);
    GraphAnalyzer analyzer = GraphAnalyzer(graph);


    cout << analyzer.diameter() << " diameter" << "\n";

    cout << analyzer.openClosedTriangleRatio() << " openClosedTriangleRatio" << "\n";

    cout << analyzer.topKOpenTriangles(10) << "\n";

    
    int newNodeID = 7;
    vector<float> newFeatures {3, 3};
    Node newNode = Node(newNodeID, newFeatures);

    analyzer.insert(newNode);
    /*analyzer.insert(Edge(4, 5, 32));*/
	analyzer.insert(Edge(3, 5, 30));
	analyzer.insert(Edge(4, 7, 50));

	cout << analyzer.openClosedTriangleRatio() << " openClosedTriangleRatio" << "\n";
	cout << analyzer.topKOpenTriangles(15) << "\n";
    
    
    vector<float> weights{1.5, .1};
    //vector<int> neighbors = analyzer.topKNeighbors(2, 3, weights);
	vector<int> neighbors = analyzer.topKNeighbors(3, 3, weights);
    
	cout << "topKNeighbor" << endl;

    for(auto i = neighbors.begin(); i != neighbors.end(); ++i)
        cout << *i << ",";
    cout << "\n";

    cout << analyzer.topNonNeighbor(2, weights) << " topNonNeighbor" << "\n";

    cout << analyzer.jacardIndexOfTopKNeighborhoods(1, 2, 2, weights) << " jacardIndexOfTopKNeighborhoods" << endl;
    return 0;
}
















