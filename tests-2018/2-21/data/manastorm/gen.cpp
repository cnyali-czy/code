#include <bits/stdc++.h>

#define For(i, j, k) for(int i = j; i <= k; i++)
#define Forr(i, j, k) for(int i = j; i >= k; i--)

using namespace std;

const int CASE = 6, MX = 1e9;
const int limN[CASE] = {6, 2, 6, 300, 5000, 100000};
const int limK[CASE] = {6, MX, MX, 300, MX, MX};
const int limA = MX;

int randint(int l, int r) {
	return rand() % (r - l + 1) + l;
}

int main() {

	srand(time(0));

	For (i, 0, CASE - 1) {
		
		char buf[100];
		sprintf(buf, "manastorm%d.in", i + 1);
		freopen(buf, "w", stdout);

		int n = limN[i] - randint(0, limN[i] / 100),
			k = randint(limK[i] / 2, limK[i]);

		printf("%d %d\n", n, k);

		For (j, 1, n) printf("%d%c", randint(0, limA), j == n ? '\n' : ' ');

		freopen("CON", "w", stdout);
		sprintf(buf, "time ./manastorm < manastorm%d.in > manastorm%d.out", i + 1, i + 1);
		assert(system(buf) != -1);

	}

	return 0;
}
