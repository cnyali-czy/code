#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int TASK = 6;
const int N[TASK] = {10, 100000, 100000, 100000, 100000, 100000};
const int Q[TASK] = {10, 10, 100000, 100000, 100000, 100000};
const int ML[TASK] = {4, 4, 4, 2, 4, 4};
const bool CHAIN[TASK] = {false, false, false, true, true, false};
int mx = 1e9, mxql = 1e5;

int randint(int L, int R) {
	assert(L <= R);
	return rand() % (R - L + 1) + L;
}

int main() {

	freopen("decompose.in", "w", stdout);

	srand(time(0));

	For(task, 0, TASK - 1) {

		static char cmd[110];
		sprintf(cmd, "rm -rf subtask%d", task + 1);
		system(cmd);
		sprintf(cmd, "mkdir subtask%d", task + 1);
		system(cmd);

		// Random

		if (task <= 3) {

			int id = 1;

			sprintf(cmd, "subtask%d/%d.in", task + 1, id);
			freopen(cmd, "w", stdout);

			int n = N[task], q = Q[task], L = ML[task];
			q = min(q, mxql / (L - 1));
			printf("%d %d %d\n", n, q, L);

			For(i, 2, n) printf("%d%c", CHAIN[task] ? i - 1 : randint(1, i - 1), i == n ? '\n' : ' ');
			For(i, 1, n) For(j, 1, L) printf("%d%c", randint(-10, 10), j == L ? '\n' : ' ');
			For(i, 1, q) {
				int o = randint(1, n);
				printf("%d ", o);
				For(j, 1, L) printf("%d%c", randint(-mx, mx), j == L ? '\n' : ' ');
			}

			sprintf(cmd, "time ./decompose < subtask%d/%d.in > subtask%d/%d.out", task + 1, id, task + 1, id);
			freopen("CON", "w", stdout);
			fprintf(stderr, "Subtask %d, Case %d: \n", task + 1, id);
			system(cmd);
		}

		if (task >= 3) {

			int id = 2;
			
			sprintf(cmd, "subtask%d/%d.in", task + 1, id);
			freopen(cmd, "w", stdout);

			int n = N[task], q = Q[task], L = 2;
			q = min(q, mxql / (L - 1));
			printf("%d %d %d\n", n, q, L);

			int o = CHAIN[task] ? n - 2 : n / 2;
			For(i, 2, n) printf("%d%c", i > o && (i - o) % 2 ? o : i - 1, i == n ? '\n' : ' ');
			For(i, 1, (o - 1) / 2) printf("%d %d\n", -i + randint(-i, 0), i + randint(0, i));
			For(i, (o - 1) / 2 + 1, o - 1) printf("%d %d\n", -i * 3, 3 * i);

			bool big = true;
			printf("%d %d\n", -mx, mx);
			For(i, o + 1, n) printf("%d %d\n", -mx + randint(1, 1e4), mx - randint(1, 1e4));
			For(i, 1, q) {
				int x = q - i + 1;
				if (i == 1 || rand() % 20 == 0) {
					int p = randint(1, (o - 1) / 2);
					printf("%d %d %d\n", p, -p + randint(-p, 0), p + randint(0, p));
				}
				else if (rand() % 2) {
					if (big) printf("%d %d %d\n", o, -randint(x * 5e3, x * 1e4), randint(x * 5e3, x * 1e4));
					else printf("%d %d %d\n", o, -mx, mx);
					big ^= 1;
				} else {
					int p = randint(1, (n - o) / 2);
					p = o + p * 2 - 1;
					printf("%d %d %d\n", p, -randint(x * 5e3, x * 1e4), randint(x * 5e3, x * 1e4));
				}
			}

			sprintf(cmd, "time ./decompose < subtask%d/%d.in > subtask%d/%d.out", task + 1, id, task + 1, id);
			freopen("CON", "w", stdout);
			fprintf(stderr, "Subtask %d, Case %d: \n", task + 1, id);
			system(cmd);

		}

		if (task >= 3) {

			int id = 3;

			sprintf(cmd, "subtask%d/%d.in", task + 1, id);
			freopen(cmd, "w", stdout);

			int n = N[task], q = Q[task], L = ML[task];
			q = min(q, mxql / (L - 1));
			printf("%d %d %d\n", n, q, L);

			For(i, 2, n) printf("%d%c", CHAIN[task] ? i - 1 : randint(max(1, i - 5), i - 1), i == n ? '\n' : ' ');
			For(i, 1, n) For(j, 1, L) printf("%d%c", (j - 2) * 100000 + randint(0, 1e5), j == L ? '\n' : ' ');
			For(i, 1, q) {
				int o = randint(1, n);
				printf("%d ", o);
				int x = randint(0, i * 2e4);
				For(j, 1, L) printf("%d%c", (j - 2) * x + randint(0, 1e6), j == L ? '\n' : ' ');
			}

			sprintf(cmd, "time ./decompose < subtask%d/%d.in > subtask%d/%d.out", task + 1, id, task + 1, id);
			freopen("CON", "w", stdout);
			fprintf(stderr, "Subtask %d, Case %d: \n", task + 1, id);
			system(cmd);
		}

	}

	return 0;
}
