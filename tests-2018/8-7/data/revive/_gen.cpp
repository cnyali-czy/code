#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int TASK = 7;
const int N[TASK] = {100, 4000, 4000, 100000, 100000, 100000, 100000};
const int M[TASK] = {0, 0, 4000, 0, 100000, 0, 500000};
const int mx = 1e9 + 1;

int main() {

	char cmd[200];
	srand(time(0));
	int ccnt = 0;

	For(idt, 0, TASK - 1) {
		
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 0, 4) {

			if (idt < 3 && idc > 3) continue;
			if (idt >= 3 && idt <= 4 && idc) continue;

			sprintf(cmd, "revive%d.in", ++ccnt);
			freopen(cmd, "w", stdout);

			int n = N[idt], m = M[idt];
			n = n - rand() % 10;
			printf("%d\n%d %d\n", idt + 1, n, m);

			if (idc == 0) For(i, 2, n) printf("%d %d\n", i - 1, rand() % mx);
			else if (idc == 1) For(i, 2, n) printf("%d %d\n", rand() % (i - 1) + 1, rand() % mx);
			else if (idc == 2) For(i, 2, n) printf("%d %d\n", max(1, i - rand() % 5 - 1), rand() % mx);
			else if (idc == 3) For(i, 2, n) printf("%d %d\n", rand() % 2 ? 1 : rand() % (i - 1) + 1, rand() % mx);
			else if (idc == 4) {
				For(i, 2, n / 2) printf("%d %d\n", max(1, i - rand() % 4 - 1), rand() % mx);
				For(i, n / 2 + 1, n) printf("%d %d\n", rand() % 2 ? n / 2 : rand() % (i - 1) + 1, rand() % mx);
			}

			while (m--)
				printf("%d %d\n", rand() % (n - 1) + 2, rand() % mx);

			cerr << "Case " << ccnt << ":\n";
			sprintf(cmd, "time ./revive < revive%d.in > revive%d.out", ccnt, ccnt);
			system(cmd);
		}

		cout << "ccnt = " << ccnt << endl; 

	}

	return 0;
}
