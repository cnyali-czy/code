#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int TASK = 7;
const int N[TASK] = {8, 18, 50, 10000000, 10000000, 10000000, 10000000};
const int M[TASK] = {20, 20, 8, 0, 1, 2, 20};

LL randint(LL L, LL R) {
	return ((1ll * rand() << 31) | rand()) % (R - L + 1) + L;
}

int Eu[25], Ev[25];

void randedge(int n, int m) {
	set<pair<int, int> > S;
	while (int(S.size()) < m) {
		int u = rand() % n + 1, v = rand() % n + 1;
		if (u == v) continue;
		if (u > v) swap(u, v);
		S.insert(make_pair(u, v));
	}
	int P[25];
	int c = 0;
	For(i, 1, m) P[i] = i, swap(P[i], P[rand() % i + 1]);
	for (auto x : S) Eu[++c] = x.first, Ev[c] = x.second;
}

int P[10000010];

int main() {

	char cmd[200];
	srand(time(0));

	For(idt, 0, TASK - 1) {
		
		sprintf(cmd, "mkdir subtask%d", idt + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 0, 6) {

			if (idt >= 3 && idt <= 5 && idc > 2) continue;
			if (idt == 2 && idc > 4) continue;
			if (idt == 1 && idc > 4) continue;
			if (idt == 6 && idc == 6) continue;

			sprintf(cmd, "subtask%d/lighthouse%d.in", idt + 1, idc + 1);
			freopen(cmd, "w", stdout);

			int n = N[idt], m = M[idt];
			n -= rand() % (n / 10 + 1);

			if (idc == 0) {
				randedge(n, m);
			} else if (idc == 1) {
				m = min(n - 1, m);
				For(i, 1, m) Eu[i] = i, Ev[i] = i + 1;
			} else if (idc == 2) {
				m = min(n - 1, m);
				For(i, 1, m) Eu[i] = rand() % i + 1, Ev[i] = i;
			} else if (idc == 3) {
				randedge(max(5, min(m / 2, n)), m);
			} else if (idc == 4) {
				m = min(n, m);
				randedge(min(m, n), m);
			} else if (idc == 5) {
				n = m = min(n, m);
				For(i, 1, m - 1) Eu[i] = i, Ev[i] = i + 1;
				Eu[m] = 1, Ev[m] = m;
			} else if (idc == 6) {
				n = m = min(n, m);
				m = m / 3 * 3;
				For(i, 1, m / 3) {
					int a = i * 3 - 2, b = a + 1, c = b + 1;
					Eu[a] = a, Ev[a] = b;
					Eu[b] = b, Ev[b] = c;
					Eu[c] = c, Ev[c] = a;
				}
			}

			printf("%d %d\n", n, m);
			For(i, 1, n) P[i] = i, swap(P[i], P[rand() % i + 1]);
			For(i, 1, m) printf("%d %d\n", P[Eu[i]], P[Ev[i]]);

			freopen("CON", "w", stdout);
			cerr << "Case " << idc + 1 << ":\n";
			sprintf(cmd, "time ./lighthouse < subtask%d/lighthouse%d.in > subtask%d/lighthouse%d.out", idt + 1, idc + 1, idt + 1, idc + 1);
			system(cmd);
		}
		

	}

	return 0;
}
