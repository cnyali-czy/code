#include <bits/stdc++.h>
#include "testlib.h"

#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

const int N = 1e5 + 10;

int n, m;
int stans, out = -1;

map<int, int> M[N];

int main(int argc, char *argv[]) {

	registerTestlibCmd(argc, argv);

	out = ouf.readInt();
	stans = ans.readInt();

	if (stans != out) quitf(_wa, "Wrong Answer on line 1");

	n = inf.readInt(), m = inf.readInt();
	For(i, 1, m) {
		int u = inf.readInt(), v = inf.readInt();
		if (u > v) swap(u, v);
		M[u][v]++;
	}

	int o;
	o = ouf.readInt();
	if (o > n || o < 1) quitp(0.5, "Invalid Format on line 2");

	int cnt = 0;
	For(i, 1, m + stans) {
		
		int op = ouf.readInt(), v = ouf.readInt();

		if (op < 0 || op > 1 || v > n || v < 1) {
			char S[100];
			sprintf(S, "Invalid Format on line %d", i + 2);
			quitp(0.5, S);
		}

		if (op == 1) {
			++cnt;
			if (cnt > stans) quitp(0.5, "Invalid Answer : Too many use of operation 1");
		} else {
			int a = o, b = v;
			if (a > b) swap(a, b);

			int &x = M[a][b];
			if (!x) quitp(0.5, "Invalid Answer: Edge has been used or does not exist");
			--x;
		}

		o = v;
	}

	quitf(_ok, "Correct Answer");

	return 0;
}
