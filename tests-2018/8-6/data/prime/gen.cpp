#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

LL p(LL x) {
	LL ret = 1;
	For(i, 1, x) ret *= 10;
	return ret;
}

const int TASK = 7;
LL limR[TASK] = {p(3), p(7), p(7), p(14), p(14), p(14), p(14)};
int limN[TASK] = {p(3), p(3), p(7), p(7), p(5), p(6), p(7)};
int limK[TASK] = {p(3), p(7), p(7), 1, p(9), p(9), p(9)};
int fixK[TASK] = {0, 0, 0, 1, p(9), 0, 0};

LL randint(LL L, LL R) {
	return ((1ll * rand() << 31) | rand()) % (R - L + 1) + L;
}

int main() {

	char cmd[200];
	srand(time(0));

	For(idt, 0, TASK - 1) {
		
		sprintf(cmd, "mkdir subtask%d", idt + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 0, 3) {
			sprintf(cmd, "subtask%d/prime%d.in", idt + 1, idc + 1);
			freopen(cmd, "w", stdout);

			LL L, R, K;

			if (!idc) {
				R = limR[idt], L = max(2ll, R - limN[idt]);
				K = limK[idt];
			} else {
				R = randint(limR[idt] / 2, limR[idt]), L = R - limN[idt] + randint(1, 10);
				L = min(R, max(2ll, L));

				if (idc == 1) K = 1;
				else if (idc == 2) K = randint(int(sqrt(R)) / 10, int(sqrt(R)) / 4);
				else if (idc == 3) K = randint(int(sqrt(R)) / 500, int(sqrt(R)) / 100);
				K = max(K, 1ll);
			}

			if (fixK[idt]) K = fixK[idt];
			printf("%lld %lld %lld\n", L, R, K);

			freopen("CON", "w", stdout);
			cerr << "Case " << idc + 1 << ":\n";
			sprintf(cmd, "time ./prime < subtask%d/prime%d.in > subtask%d/prime%d.out", idt + 1, idc + 1, idt + 1, idc + 1);
			system(cmd);
		}
		

	}

	return 0;
}
