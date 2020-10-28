#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cfloat>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

struct path {
	int start;
	int end;
};

class matrixUDG {
	#define MAX	   10000
		private:
			vector<path> mcst;
			int vexNum;
			int edgNum;
			double points[MAX][2];
			double adjMatrix[MAX][MAX];
	
	public:
		//readData and generate the adjcent matrix of the given graph
		matrixUDG();
		~matrixUDG();
		//Calculate the weight
		double calWeight(double x1, double y1, double x2, double y2);
		//The prim algorithm
		void prim(int start);
		void print();
};


//Sort method
bool less_first(path p1, path p2) {
	if (p1.start > p2.start)
		return false;
	if (p1.start == p2.start)
	{
		if (p1.end > p2.end)
			return false;
	}
	return true;
}


//Calculate the weight
double matrixUDG::calWeight(double x1,double y1,double x2, double y2) {
	return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

//The construction method is to read data and generate the adjcent matrix of the graph
matrixUDG::matrixUDG() {
	//It is to record the total number of x and y matrix
	cin >> vexNum;
	for (int i = 0; i < vexNum; i++)
	{
		for (int j = 0; j < 2; j++)
			cin >> points[i][j];
	}
	
	//Record the number of the edges
	cin >> edgNum;
	
	//Calculate the Euclidean distance and record it in the adjcent matrix
	//The graph is a complete graph
	if (edgNum == 0)
	{
		edgNum = vexNum * vexNum / 2;
		//Initialize the adjMatrix
		for (int i = 0; i < vexNum; i++)
		{
			for (int j = i ; j < vexNum; j++)
			{				
				adjMatrix[i][j] = DBL_MAX;
				adjMatrix[j][i] = DBL_MAX;
			}
		}
		//Calculate the weight
		for (int i = 0; i < vexNum; i++)
		{
			for (int j = i + 1; j < vexNum; j++)
			{
				adjMatrix[i][j] = calWeight(points[i][0], points[i][1], points[j][0], points[j][1]);
				adjMatrix[j][i] = adjMatrix[i][j];
			}
		}
	}
	else {//The graph is not a complete graph
		//Initialize the adjMatrix
		for (int i = 0; i < vexNum; i++)
		{
			for (int j = i; j < vexNum; j++)
			{
				adjMatrix[i][j] = DBL_MAX;
				adjMatrix[j][i] = DBL_MAX;
			}
		}
		int count = 0;
		for (int i = 0; i < edgNum; i++)
		{
			int tempv1, tempv2;
			for (int j = 0; j < 2; j++)
			{
				cin >> tempv1;
				cin >> tempv2;
				adjMatrix[tempv1][tempv2] = calWeight(points[tempv1][0], points[tempv1][1], points[tempv2][0], points[tempv2][1]);
				adjMatrix[tempv2][tempv1] = adjMatrix[tempv1][tempv2];
				count++;
			}
			if (count >= edgNum)
				break;
		}
	}
	
}

matrixUDG::~matrixUDG(){}

void matrixUDG::prim(int start) {
	int j, k,temp;
	double min;
	//If it belongs to set U, equals 1,else is 0
	int isSetU[MAX];
	for (int i = 0; i < vexNum; i++)
	{
		isSetU[i] = 0;
	}
	//The first vertex must be in set U
	isSetU[0] = 1;
	//To find the MSCT
	for (int i = 0; i < vexNum; i++)
	{
		j = 0;
		k = 0;
		temp = 0;
		min = DBL_MAX;
		//To find the next vertex which has the least weight to the U
		while (j < vexNum)
		{
			//If vertex j is not already in set U
			if (isSetU[j] == 0)
			{
				for (int t = 0; t < vexNum; t++) 
				{
					if (isSetU[t] == 1 && adjMatrix[t][j] < min)
					{
						min = adjMatrix[t][j];
						k = j;
						temp = t;
					}
				}
			}
			j++;
		}
		//Add the edge to the result
		mcst.push_back({temp,k});
		//Add the vertex k to the set U
		isSetU[k] = 1;
	}
}

void matrixUDG::print()
{
	cout << "--********************************************************--" << endl;
	cout << "MCST is:" << endl;
	int swap;
	//Standard output
	for (vector<path>::iterator it = mcst.begin(); it != mcst.end(); it++)
	{
		if (it->start > it->end)
		{
			swap = it->start;
			it->start = it->end;
			it->end = swap;
		}
	}
	//Sort according to start points
	sort(mcst.begin(), mcst.end(),less_first);

	//Print
	for (vector<path>::iterator it = mcst.begin(); it != mcst.end(); it++)
	{
		if (it->start == it->end)
			continue;
		cout << it->start << " " << it->end << endl;
	}
	cout << "--********************************************************--" << endl;
}

int main(){
	matrixUDG* mu;
	mu = new matrixUDG();
	mu->prim(0);
	mu->print();
	return 0;
}
































//for (int i = 0; i < vexNum; i++)
//{
//	for (int j = i + 1; j < vexNum; j++)
//	{
//		cout << fixed << setprecision(8) << adjMatrix[i][j] << " ";
//		cout << fixed << setprecision(8) << adjMatrix[j][i] << endl;
//	}
//}