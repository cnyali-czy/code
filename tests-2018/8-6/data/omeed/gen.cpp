#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int TASK = 8;
const int mx = 998244352;

int limN[TASK] = {10, 10, 10, 1000, 500000, 500000, 500000, 500000};
int limQ[TASK] = {0, 10, 10, 10, 10, 100000, 100000, 500000};

int randint(int L, int R) {
	return rand() % (R - L + 1) + L;
}

void randpair(char c = '\n') {
	int a = rand() % mx, b = rand() % mx;
	if (a > b) swap(a, b);
	if (!b) ++a, ++b;
	printf("%d %d%c", a, b, c);
}

int main() {

	char cmd[200];
	srand(time(0));

	For(i, 1, TASK) {
		
		sprintf(cmd, "omeed%d.in", i);
		freopen(cmd, "w", stdout);

		int n = limN[i - 1], q = limQ[i - 1];
		printf("%d\n", i);
		printf("%d %d ", n, q);

		if (i == 4 || i == 7) printf("0 1 ");
		else randpair(' ');

		printf("%d %d\n", randint(1, 1e9), i == 6 ? 0 : randint(1, 1e9));
		For(j, 1, n) 
			if (i == 2) printf("%d 1\n", rand() % 2);
			else randpair();
		For(j, 1, q) {
			int op = rand() % 2;
			if (j == q) op = 1;
			if (!op) {
				printf("0 %d ", randint(1, n));
				if (i == 2) printf("%d 1\n", rand() % 2);
				else randpair();
			} else {
				int l = rand() % n + 1, r = rand() % n + 1;
				if (rand() % 2 == 0) l = randint(1, n / 10);
				if (rand() % 2 == 0) r = randint(9 * n / 10, n);
				if (l > r) swap(l, r);
				printf("1 %d %d\n", l, r);
			}
		}

		freopen("CON", "w", stdout);
		cerr << "Case " << i << ":\n";
		sprintf(cmd, "time ./omeed < omeed%d.in > omeed%d.out", i, i);
		system(cmd);

	}

	return 0;
}
