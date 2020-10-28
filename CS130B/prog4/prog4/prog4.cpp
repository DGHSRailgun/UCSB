#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <cmath>
#include <cfloat>
#include <algorithm>

using namespace std;

struct point {
	double x;
	double y;
};

struct line {
	double a;
	double b;
};

double Caldist(double a, double b, point p) {
	return (abs(a * p.x - p.y + b))/sqrt(a*a + 1);
}

vector<point> RandAlg(vector<point> points) {
	int size = points.size();
	default_random_engine random(time(NULL));
	uniform_int_distribution<int> dis(0, size - 1);
	double medium_error = DBL_MAX;
	double good_a;
	double good_b;
	for (int i = 0; i < log(size)*size; i++)
	{
		int m, n;
		while (true)
		{
			m = dis(random);
			n = dis(random);
			if (m != n)
				break;
		}
		//We select two points randomly points[m] & points[n]
		double a, b;
		//Calculate a,b according to points[m] & points[n]
		a = (points[m].y - points[n].y) / (points[m].x - points[n].x);
		b = (points[m].y - a * points[m].x);
		//Calculate the distance and get the medium error
		vector<double> dist;
		for (int j = 0; j < size; j++)
		{
			if (j != m && j != n)
			{
				double dis = Caldist(a, b, points[j]);
				dist.push_back(dis);
			}
		}

		/*for (int t = 0; t < dist.size(); t++)
			cout << dist[t] <<"size: " <<dist.size()<<endl;*/


		//Find medium error of the rest n-2 points
		sort(dist.begin(), dist.end());
		if ((dist.size() % 2) != 0)
		{
			if (dist[(dist.size() / 2)] < medium_error)
			{
				medium_error = dist[(dist.size() / 2)];
				good_a = a;
				good_b = b;
			}
		}
		else {
			if (((dist[(dist.size() / 2)] + dist[(dist.size() / 2) - 1]) / 2) < medium_error)
			{
				medium_error = (dist[(dist.size() / 2)] + dist[(dist.size() / 2) - 1]) / 2;
				good_a = a;
				good_b = b;
			}
		}
	
	}
	
	//cout << medium_error << endl;
	//cout << "a: " << good_a << " b: " << good_b << endl;
	vector<point> good;
	for (int k = 0; k < size; k++)
	{
		if ((Caldist(good_a, good_b, points[k])) <= medium_error)
		{
			good.push_back(points[k]);
		}
	}

	//for (int i = 0; i < good.size(); i++)
	//	cout << good[i].x << good[i].y << endl;

	return good;
}



line fitLine(vector<point> good) {
	double result_a, result_b;
	double sum_xi = 0, sum_yi = 0, sum_xi2 = 0, sum_yi2 = 0, sum_xiyi = 0;
	int N = good.size();
	for (int i = 0; i < N; i++)
	{
		sum_xi += good[i].x;
		sum_yi += good[i].y;
		sum_xi2 += good[i].x * good[i].x;
		sum_yi2 += good[i].y * good[i].y;
		sum_xiyi += good[i].x * good[i].y;
	}
	
	result_a = ((sum_xi2) * (sum_yi)-(sum_xi) * (sum_xiyi)) / ((N * sum_xi2) - (sum_xi * sum_xi));
	result_b = ((N*sum_xiyi) - (sum_xi*sum_yi)) / ((N*sum_xi2) - (sum_xi*sum_xi));
	
	line result;
	result = {result_a, result_b};
	return result;
}




int main() {
	vector<point> p;
	double tempx, tempy;
	for (int i = 0; i < 11; i++)
	{
		cin >> tempx;
		cin >> tempy;
		p.push_back({tempx,tempy});
	}

	
	line result;
	result = fitLine(RandAlg(p));
	cout << result.a << result.b << endl;

	return 0;
}




