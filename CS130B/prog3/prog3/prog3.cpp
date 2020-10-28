//#include <iostream>
//#include <vector>
//#include <getopt.h>
//#include <string>
//#include <cstring>
//
//using namespace std;
//
//double max(double x1, double x2, double x3);
//double match(char a, char b, double m, double c);
//double DP(vector<char> S, vector<char> T, int m, int n, double mat, double cha, double del);
//
//double max(double x1, double x2, double x3) {
//	double max = -999999;
//	if (x1 > x2)
//	{
//		max = x1;
//	}
//	else {
//		max = x2;
//	}
//	if (max < x3)
//	{
//		max = x3;
//	}
//	return max;
//}
//
//double match(char a, char b, double m, double c) {
//	if (a == b)
//		return m;
//	else
//		return c;
//}
//
//double DP(vector<char> S, vector<char> T, int m, int n, double mat, double cha, double del) {
//	vector<vector<double> > dp;
//	dp.resize(m + 1);
//	for (int k = 0; k < m + 1; k++)
//	{
//		dp[k].resize(n + 1);
//	}
//	for (int i = 0; i < m + 1; i++)
//	{
//		dp[i][0] = (-1.0) * i;
//	}
//	for (int j = 0; j < n + 1; j++)
//	{
//		dp[0][j] = (-1.0) * j;
//	}
//	for (int i = 1; i < m + 1; i++)
//	{
//		for (int j = 1; j < n + 1; j++)
//		{
//			dp[i][j] = max( (dp[i - 1][j - 1] + match(S[i - 1], T[j - 1], mat, cha)), (dp[i - 1][j] + del), (dp[i][j - 1] + del));
//		}
//	}
//	return dp[m][n];
//
//}
//
//int main(int argc, char* argv[]) {
//	double def_mat = 2.0;
//	double def_cha = -0.5;
//	double def_del = -1.0;
//	double mat, cha, del;
//	double best_score;
//	char str1[5000];
//	char str2[5000];
//
//	int opt;
//	const char* optstring = "1:2:m:c:d:";
//	while ((opt = getopt(argc, argv, optstring)) != -1) {
//		cout << opt << " " << optarg << " " << optind << " " << argv[optind - 1] <<endl;
//	}
//	/*cin >> str1;
//	cin >> str2;
//	int str1_size = strlen(str1);
//	int str2_size = strlen(str2);
//	vector<char> S(str1, str1 + sizeof(str1) / sizeof(char));
//	vector<char> T(str2, str2 + sizeof(str2) / sizeof(char));
//	best_score = DP(S, T, str1_size, str2_size, def_mat, def_cha, def_del);
//
//	cout << best_score;*/
//	return 0;
//}

