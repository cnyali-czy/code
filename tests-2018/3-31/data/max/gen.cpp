#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int CASE = 5;
const int N[CASE] = {5, 2, 5, 40, 40}, 
		  M[CASE] = {5, 10, 10, 10, 10},
		  C[CASE] = {3, 3, 3, 1, 3};
const int Mod = 1e9 + 7;

int randint(int l, int r) {
	return rand() % (r - l + 1) + l;
}

int main() {

	srand(time(0));

	For(i, 0, CASE - 1) {
		char file[30];
		sprintf(file, "_max%d.in", i + 1);
		freopen(file, "w", stdout);
		printf("%d %d %d\n", N[i], M[i], C[i]);

		For(m, 1, M[i]) {
			int sum = 0;
			For(n, 1, N[i]) For(c, 0, C[i]) {
				int x = randint(0, Mod - 1);
				if (C[i] == 1 && !c) x = 0;
				if (n == N[i] && c == C[i]) x = (Mod + 1 - sum) % Mod;
				sum = (sum + x) % Mod;
				printf("%d%c", x, c == C[i] ? '\n' : ' ');	
			}
			assert(sum == 1);
		}

		freopen("CON", "w", stdout);
		char cmd[50];
		sprintf(cmd, "time ./max < %s > _max%d.out", file, i + 1);
		system(cmd);

	}

	return 0;
}
