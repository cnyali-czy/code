#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

const int N = 1e5 + 10;

ofstream fscore, finfo;

void report(const char *S, int w) { 
	finfo << S; 
	fscore << w; 
	exit(0); 
}

int n, m;
int ans, out = -1;

map<int, int> M[N];

int main(int argc, char *argv[]) {

	std::ios::sync_with_stdio(false);

	ifstream fin(argv[1]), fout(argv[2]), fans(argv[3]);
	fscore = ofstream(argv[5]), finfo = ofstream(argv[6]);

	fans >> ans;
	fout >> out;

	if (!fout) report("Invalid Format on line 1", 0);
	if (ans != out) report("Wrong Answer on line 1", 0);

	int score, partial;
	sscanf(argv[4], "%d", &score);
	partial = (int) floor(score * 0.4);
	
	fin >> n >> m;
	For(i, 1, m) {
		int u, v;
		fin >> u >> v;
		if (u > v) swap(u, v);
		M[u][v]++;
	}

	int o;
	fout >> o;
	if (!fout || o > n || o < 1) report("Invalid Format on line 2", partial);

	int cnt = 0;
	For(i, 1, m + ans) {
		
		int op, v;
		fout >> op >> v;

		if (!fout || op < 0 || op > 1 || v > n || v < 1) {
			char S[100];
			sprintf(S, "Invalid Format on line %d", i + 2);
			report(S, partial);
		}

		if (op == 1) {
			++cnt;
			if (cnt > ans) report("Invalid Answer : Too many use of operation 1", partial);
		} else {
			int a = o, b = v;
			if (a > b) swap(a, b);

			int &x = M[a][b];
			if (!x) report("Invalid Answer: Edge has been used or does not exist", partial);
			--x;
		}

		o = v;
	}

	report("Correct Answer", score);

	return 0;
}
