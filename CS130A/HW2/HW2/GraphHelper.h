#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    // NOTE: Do not edit node struct
    int id;
    vector<float> features;
    
    Node(int id, vector<float> features): id(id), features(features) {}
    Node(const Node &n2) { id = n2.id; features=n2.features;}
};


struct Edge {
    // NOTE: Do not edit Edge struct
    int IdA, IdB, weight;
    
    Edge(int IdA, int IdB, int weight): IdA(IdA), IdB(IdB), weight(weight) {}
};

class Triangle {

// TODO make a Triangle class with appropriate fields and methods
private:
	int idA;
	int idB;
	int idC;
	int weight;//the open triangle weight

public:

    // TODO make appropriate constuctor
    Triangle(int id1, int id2, int id3, int w) { 
		this->idA = id1;
		this->idB = id2;
		this->idC = id3;
		this->weight = w;
	}


	string display() const {
		return to_string(idA) + " " + to_string(idB) + " " + to_string(idC) + " weight:" + to_string(weight);
	}
    
    // Operator overloading for storage in priority queue
    // returns true iff t2 is greater than t1. 
    //
    // Note: Must be transitive
    //      This means if t1<t2 and t2<t3 than t1< t3
	bool operator < (Triangle const& other) {
		//TODO
		return this->weight < other.weight;
	};

	friend bool operator<(const Triangle& n1, const Triangle& n2) {
		return n1.weight < n2.weight;
	};
	//To compare the triangles
	bool operator==(Triangle const& other){
		vector<int> t1;
		vector<int> t2;
		t1.push_back(this->idA);
		t1.push_back(this->idB);
		t1.push_back(this->idC);
		t2.push_back(other.idA);
		t2.push_back(other.idB);
		t2.push_back(other.idC);

		if (t2[0] == t1[0])
		{
			if ((t2[1] == t1[1] && t2[2] == t1[2]) || (t2[2] == t1[1] && t2[1] == t1[2])) {
				return true;
			}
		}
		if (t2[1] == t1[0]) {
			if ((t2[0] == t1[1] && t2[2] == t1[2]) || (t2[2] == t1[1] && t2[0] == t1[2])) {
				return true;
			}
		}
		if (t2[2] == t1[0]) {
			if ((t2[0] == t1[1] && t2[1] == t1[2]) || (t2[1] == t1[1] && t2[0] == t1[2])) {
				return true;
			}
		}
		return false;
	}

};


#endif

    




    
