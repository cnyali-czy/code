#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int TASK = 5, CASE = 6, N = 300010;
const int maxn[TASK] = {10, 100, 1500, 7000, 200000};

int w, h, n;
int P[N], X[N], Y[N];

int main() {

	srand(time(0));

	For(i, 1, CASE) {
		char file[110];
		sprintf(file, "TEMP/%d.in", i);
		freopen(file, "r", stdin);

		scanf("%d%d%d", &w, &h, &n);
		For(j, 1, n) P[j] = j, scanf("%d %d", &X[j], &Y[j]);

		For(j, 0, TASK - 1) {
			sprintf(file, "subtask%d/%d.in", j + 1, i);
			freopen(file, "w", stdout);
			printf("%d %d %d\n", w, h, maxn[j]);

			random_shuffle(P + 1, P + n + 1);
			For(k, 1, maxn[j]) printf("%d %d\n", X[P[k]], Y[P[k]]);

			freopen("CON", "w", stdout);
			sprintf(file, "time ./paint < subtask%d/%d.in > subtask%d/%d.out", j + 1, i, j + 1, i);
			system(file);
		}

	}

	return 0;
}
