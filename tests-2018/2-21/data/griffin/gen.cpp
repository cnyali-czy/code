#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int TASK = 4, MX = 1e9;
const int limN[TASK] = {180, 180, 40, 180};
const int limW[TASK] = {MX, 1000, MX, MX};
const int limC[TASK] = {1, 50, 50, 50};
const int limM = 3e4;

int randint(int L, int R) {
	return rand() % (R - L + 1) + L;
}

const int N = 210, M = N * N;

int fr[M], to[M], g[M];
int P[N], w[N];
int n, m, c;

void add(int u, int v, int s) {
	g[++m] = s, fr[m] = u, to[m] = v;
}

int main() {

	char cmd[200];
	srand(time(0));

	For(idt, 0, TASK - 1) {

		sprintf(cmd, "rm -rf subtask%d", idt + 1);
		system(cmd);
		
		sprintf(cmd, "mkdir subtask%d", idt + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		int cnt = 0;

		For(idc, 0, 19) {
			
			n = limN[idt] - randint(0, 5);
			c = limC[idt] == 1 ? 1 : limC[idt] - randint(0, 3);
			m = 0;

			int rate = n / 12;
			int rate2 = n / 7;

			if (idc == 0) {
				// unconnected
				int x = randint(2, n - 2);
				For(i, 1, x) For(j, 1, x) if(rand() % 2) add(i, j, randint(1, c));
				For(i, x + 1, n) For(j, x + 1, n) if(rand() % 2) add(i, j, randint(1, c));
			} else if (idc == 1) {
				// no way to go
				if (c == 1) continue;

				For(i, 1, n) For(j, i + 1, n) if(rand() % 2)
					add(i, j, j == n ? c : randint(1, c - 1));
				For(i, 1, c - 1) w[i] = max(0, i - 5);
				w[c] = limW[idt];
			} else if (idc == 2) {
				// graph max
				For(i, 1, n) For(j, 1, n) add(i, j, randint(1, c));
			} else if (idc >= 3 && idc <= 4) {
				// rand max
				if(idc == 3) add(1, 1, 1);
				For(i, 1, n) For(j, 1, n) if(rand() % 2) add(i, j, randint(1, c));
			} else if (idc >= 5 && idc <= 6) {
				// rand
				if(idc == 5) add(1, 1, 1);
				For(i, 1, n) For(j, 1, n) if(rand() % rate == 0) add(i, j, randint(1, c));
			} else if (idc >= 7 && idc <= 8) {
				// ans max
				if (c == 1) continue;

				For(i, 1, n) For(j, 1, n) if(rand() % rate == 0)
					add(i, j, j == n ? c : randint(1, c - 1));
				For(i, 1, c - 1) w[i] = max(0, (limW[idt] / c) * (i - 5));
				w[c] = limW[idt];
			} else if (idc >= 9 && idc <= 12) {
				// cycle
				if (c == 1) continue;

				For(i, 1, n - 1) add(i, i == n - 1 ? 1 : i + 1, 1);
				For(i, 1, n - 1) if(rand() % rate2) add(i, n, idc == 12 ? c : randint(20, c));
				if (idc <= 10) {
					For(i, 1, n - 1) if (rand() % rate2) 
						For(j, 1, n - 1) if (rand() % rate2) add(i, n, randint(20, c));
				}

				if (idc & 1) {
					w[1] = 0;
					For(i, 1, c) w[i] = limW[idt] / (c - 1) * (i - 1);
				}

			} else if (idc >= 13 && idc <= 14) {
				// only one way
				add(1, 1, 1);
				For(i, 1, n - 1) add(i, i + 1, c == 1 ? 1 : randint(2, c));
				if (idc == 12) For(i, 2, c) w[i] = limW[idt];
			} else if (idc == 15) {
				// c[1] != 0
				For(i, 1, n) For(j, 1, n) if(rand() % 2) add(i, j, randint(1, c));
				For(i, 1, c) w[i] = i;
			} else if (idc >= 16 && idc <= 19) {
				// rand
				if(idc <= 17) add(1, 1, 1);
				For(i, 1, n) For(j, 1, n) if(rand() % rate2 == 0) add(i, j, randint(1, c));
			} 

			sprintf(cmd, "subtask%d/griffin%d.in", idt + 1, ++cnt);
			freopen(cmd, "w", stdout);

			P[1] = 1, P[n] = n;
			For(i, 2, n - 1) P[i] = i, swap(P[i], P[randint(2, i)]);
			
			printf("%d %d %d\n", n, m, c);
			For(i, 1, m) printf("%d %d %d\n", P[fr[i]], P[to[i]], g[i]);
			
			if (!w[c]) {
				For(i, 1, min(c, 6)) w[i] = 0;
				For(i, 7, c) w[i] = randint(1, limW[idt]);
				sort(w + 1, w + c + 1);
			}
			For(i, 1, c) printf("%d%c", w[i], i == c ? '\n' : ' '), w[i] = 0;

			freopen("CON", "w", stdout);
			cerr << "Case " << idc + 1 << ":\n";
			sprintf(cmd, "time ./griffin < subtask%d/griffin%d.in > subtask%d/griffin%d.out", idt + 1, cnt, idt + 1, cnt);
			system(cmd);
		}
		

	}

	return 0;
}
