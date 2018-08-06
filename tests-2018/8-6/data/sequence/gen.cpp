#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

LL pl(int x) {
	LL ret = 1;
	For(i, 1, x) ret *= 10;
	return ret;
}
int p(int x) {
	int ret = 1;
	For(i, 1, x) ret *= 10;
	return ret;
}

const int TASK = 7;
const int N = 1e6 + 10;

int limN[TASK] = {8, 8, 8, 8, p(6), p(6), p(6)};
LL limM[TASK] = {0, 6, 6, 12, 0, p(6), pl(18)};
int limK[TASK] = {3, 3, 6, 12, 100, 100, 100};

int A[N], P[N];

int main() {

	char cmd[200];
	srand(time(0));

	For(idt, 0, TASK - 1) {
		
		sprintf(cmd, "mkdir subtask%d", idt + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 0, 7) {

			if (idt < 2 && idc > 1) continue;
			if (idt != 2 && idt != 3 && idc >= 3) continue;

			sprintf(cmd, "subtask%d/sequence%d.in", idt + 1, idc + 1);
			freopen(cmd, "w", stdout);

			int n = limN[idt];
			LL m = limM[idt];
			int k = limK[idt];
			
			if (idc && idt != 2 && idt != 3) {
				m -= rand() % (m / 5 + 1);
				n -= rand() % (n / 5 + 1);
				k -= rand() % (k / 5 + 1);
			}

			printf("%d %lld %d\n", n, m, k);

			if (idc == 1 || idc >= 4) {
				For(i, 1, k) P[i] = i;
				random_shuffle(P + 1, P + k + 1);
				For(i, 1, n) A[i] = P[i % k + 1];
			} else if (idc == 2) {
				int ban = rand() % k + 1;
				For(i, 1, n) {
					A[i] = rand() % k + 1;
					if (A[i] == ban) { --i; continue; }
				}
			} else {
				For(i, 1, n) A[i] = rand() % k + 1;
			} 

			For(i, 1, n) printf("%d%c", A[i], i == n ? '\n' : ' ');

			freopen("CON", "w", stdout);
			cerr << "Case " << idc + 1 << ":\n";
			sprintf(cmd, "time ./sequence < subtask%d/sequence%d.in > subtask%d/sequence%d.out", idt + 1, idc + 1, idt + 1, idc + 1);
			system(cmd);
		}
		

	}

	return 0;
}
