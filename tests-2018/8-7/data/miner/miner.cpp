#include <bits/stdc++.h>

#define pb push_back
#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

const int N = 1e5 + 10;

int n, m;
int fa[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int deg[N], cnt[N];

int main() {

	scanf("%d%d", &n, &m);

	For(i, 1, n) fa[i] = i;
	For(i, 1, m) {
		int u, v;
		scanf("%d%d", &u, &v);
		fa[find(u)] = find(v);
		++deg[u], ++deg[v];
	}
	For(i, 1, n) if (deg[i] & 1) cnt[find(i)]++;

	int ans = 0;
	For(i, 1, n) if (deg[i] && fa[i] == i) ans += max(1, cnt[i] / 2);
	printf("%d\n-1\n", ans - 1);

	return 0;
}
