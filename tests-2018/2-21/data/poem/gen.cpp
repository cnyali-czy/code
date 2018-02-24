#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int TASK = 5;
const int CASE[TASK] = {5, 5, 3, 3, 7};
const int limN[TASK] = {100, 3000, 1, 5, 100000};
const int limL[TASK] = {100, 3000, 300000, 300000, 300000};

int randint(int L, int R) {
	return rand() % (R - L + 1) + L;
}

const int N = 1e5 + 10, L = 1e6 + 10;

int n;
char S[L];
int len[N];

int main() {

	char cmd[200];
	srand(time(0));

	For(idt, 0, TASK - 1) {
		
		sprintf(cmd, "mkdir subtask%d", idt + 1);
		system(cmd);
		cerr << "Subtask " << idt + 1 << ":\n";

		For(idc, 0, CASE[idt] - 1) {
			sprintf(cmd, "subtask%d/poem%d.in", idt + 1, idc + 1);
			freopen(cmd, "w", stdout);

			char a = randint('a', 'y'), b = randint(a + 1, 'z');
			int rate = sqrt(limL[idt]) * 2;

			if (idc == 0) {
				n = 1;
				For(i, 1, limL[idt]) S[i] = a;
				len[1] = limL[idt];
			} else if (idc == 1) {
				n = min(limL[idt] / 10, limN[idt]);
				For(i, 1, limL[idt]) {
					if (n <= 5) S[i] = rand() % rate == 0 ? randint('a', 'z') : i & 1 ? a : b;
					else S[i] = randint('a', 'f');
				}
				For(i, 1, n) len[i] = limL[idt] / n;
			} else if (idc == 2) {
				n = min(5, limN[idt]);
				For(i, 1, limL[idt]) S[i] = randint('a', 'z');
				For(i, 1, n) len[i] = limL[idt] / n;
			} else {
				n = min(limL[idt] / 3, limN[idt]);
				For(i, 1, n) len[i] = 1;

				int re = limL[idt] - n;
				while (re--) {
					if (rand() % 2) len[randint(1, 5)]++;
					else len[randint(1, n)]++;
				}

				if (idc == 3) For(i, 1, limL[idt]) S[i] = i & 1 ? a : b;
				if (idc == 4) For(i, 1, limL[idt]) S[i] = rand() % rate ? randint('a', 'f') : (i & 1 ? a : b);
				if (idc == 5) For(i, 1, limL[idt]) S[i] = rand() % rate == 0 ? randint('a', 'z') : (i % 26 + a - 'a') % 26 + 'a';
				if (idc == 6) For(i, 1, limL[idt]) S[i] = rand() % rate ? a : b;
			}

			printf("%d\n", n);
			random_shuffle(len + 1, len + n + 1);

			int p = 0;
			For(i, 1, n) {
				For(j, 1, len[i]) putchar(S[++p]);
				putchar('\n');
			}

			freopen("CON", "w", stdout);
			cerr << "Case " << idc + 1 << ":\n";
			sprintf(cmd, "time ./poem < subtask%d/poem%d.in > subtask%d/poem%d.out", idt + 1, idc + 1, idt + 1, idc + 1);
			system(cmd);
		}
		

	}

	return 0;
}
