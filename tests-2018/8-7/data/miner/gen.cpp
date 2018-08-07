#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

LL p(LL x) {
	LL ret = 1;
	For(i, 1, x) ret *= 10;
	return ret;
}

const int mx = 1e5 + 10;
const int CTASK = 6;
const int N[CTASK] = {2, 6, 15, 100, 1000, 100000};
const int M[CTASK] = {2, 6, 15, 1000, 10000, 100000};

LL randint(LL L, LL R) {
	return ((1ll * rand() << 31) | rand()) % (R - L + 1) + L;
}

int Eu[mx], Ev[mx], P[mx];

void randedge(int n, int m, bool ty) {
	if (!ty) For(i, 1, m) Eu[i] = rand() % n + 1, Ev[i] = rand() % n + 1;
	else {
		int o = 1;
		For(i, 1, m) Eu[i] = o, o = Ev[i] = rand() % n + 1;
		if (rand() % 3 == 0) Ev[m] = 1;
	}
}

int main() {

	char cmd[200];
	srand(time(0));

	For(TASK, 0, CTASK - 1) {
		
		int idt = TASK;

		sprintf(cmd, "rm -rf subtask%d", TASK + 1);
		system(cmd);

		sprintf(cmd, "mkdir subtask%d", TASK + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 1, 9) {


			if (idt < 3 && idc < 5) continue;
			if (idt < 5 && idc < 2) continue;

			sprintf(cmd, "subtask%d/miner%d.in", TASK + 1, idc);
			freopen(cmd, "w", stdout);

			int n, m;
			if (idc == 1) n = 2, m = M[TASK], randedge(n, m, idt == 4);
			else if (idc == 2) {
				n = min(M[TASK] / 2 + 1, N[TASK]), m = 2 * (n - 1);
				For(i, 1, n - 1) Eu[i * 2 - 1] = 1, Ev[i * 2 - 1] = i + 1, Eu[i * 2] = i + 1, Ev[i * 2] = 1;
			} else if (idc == 3 && idt != 4) {
				n = N[TASK];
				For(i, 1, n / 2) Eu[i] = i * 2 - 1, Ev[i] = i * 2;
				m = n / 2;
				while (m + 2 <= M[TASK]) {
					++m;
					Eu[m + 1] = Eu[m] = rand() % n + 1;
					Ev[m + 1] = Ev[m] = rand() % n + 1;
					++m;
				}
			} else if (idc == 4 && idt != 4) {
				n = m = N[TASK];
				For(i, 1, n) Eu[i] = i, Ev[i] = i;
			} else if (idc <= 6) {
				n = N[TASK], m = M[TASK];
				randedge(n, m, idt == 4);
			} else if (idc == 7) {
				m = M[TASK];
				n = max(2, int(sqrt(m)));
				randedge(n, m, idt == 4);
			} else if (idc == 8) {
				n = m = N[TASK];
				randedge(n, m, idt == 4);
			} else {
				m = M[TASK], n = max(2, m / 10);
				randedge(n, m, idt == 4);
			}

			printf("%d %d\n", n, m);
			For(i, 1, n) P[i] = i;
			random_shuffle(P + 1, P + n + 1);
			For(i, 1, m) Eu[i] = P[Eu[i]], Ev[i] = P[Ev[i]];

			random_shuffle(P + 1, P + m + 1);
			For(i, 1, m) P[i] = i;
			For(i, 1, m) printf("%d %d\n", Eu[P[i]], Ev[P[i]]);

			freopen("CON", "w", stdout);
			cerr << "Case " << idc << ":\n";
			sprintf(cmd, "time ./miner %d < subtask%d/miner%d.in > subtask%d/miner%d.out", idt, idt + 1, idc, idt + 1, idc);

			system(cmd);
		}
		

	}

	return 0;
}
