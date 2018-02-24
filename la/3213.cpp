#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <bitset>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

using namespace std;
const int maxn = 105;

int n, A[30], B[30];
char a[maxn], b[maxn];

int main() {
#ifdef CraZYali
	freopen("3213.in", "r", stdin);
	freopen("3213.out", "w", stdout);
#endif
	while (scanf("%s\n%s", a + 1, b + 1) != EOF) {
		n = strlen(a + 1);
		memset(A, 0, sizeof(A));
		memset(B, 0, sizeof(B));
		REP(i, 1, n) {
			A[a[i] + 1 - 'A']++;
			B[b[i] + 1 - 'A']++;
		}
		sort(A + 1, A + 27);
		sort(B + 1, B + 27);
		register bool flag = 1;
		REP(i, 1, 26)
			if (A[i] != B[i]) {
				printf("NO\n");
				flag = 0;
				break;
			}
		if (flag) printf("YES\n");
	}

	return 0;
}
