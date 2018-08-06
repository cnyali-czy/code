#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int N = 1e7 + 10;

bool vis[N], flag[N];

LL L, R;
int k;

int main(){

	scanf("%lld%lld%d", &L, &R, &k);
	k = min(k, int(sqrt(R)) + 5);

	For(i, 2, k) if (!vis[i]) {
		for (int j = i << 1; j <= k; j += i) vis[j] = true;
		for (LL j = max(2ll, ((L - 1) / i + 1)) * i; j <= R; j += i) flag[j - L] = true;
	}

	LL ans = 0;
	for (LL j = L; j <= R; ++j) if (!flag[j - L]) ans ^= j;
	printf("%lld\n", ans);

	return 0;
}
