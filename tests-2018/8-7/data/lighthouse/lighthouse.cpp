#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

const int N = 1e7 + 10, M = 45;
const int Mod = 1e9 + 7;

int n, m;
int u[M], v[M];
int deg[N], fac[N], Pow2[N];
int fa[N];

int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int main() {

	scanf("%d%d", &n, &m);

	fac[0] = Pow2[0] = 1;
	For(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % Mod, Pow2[i] = Pow2[i - 1] * 2 % Mod, fa[i] = i;
	For(i, 1, m) scanf("%d%d", &u[i], &v[i]);

	int ans = 1ll * fac[n - 1] * (Mod + 1) / 2 % Mod;

	For(st, 1, (1 << m) - 1) {
		bool ok = true;
		int c = 0;
		For(i, 1, m) if (st & (1 << (i - 1))) ++deg[u[i]], ++deg[v[i]], ++c;
		For(i, 1, m) if (deg[u[i]] > 2 || deg[v[i]] > 2) { ok = false; break; }
		
		if (ok) {

			bool cyc = false;
			For(i, 1, m) if (st & (1 << (i - 1))) {
				int x = find(u[i]), y = find(v[i]);
				if (x == y) cyc = true;
				else fa[x] = y;
			}

			int comp = 0;
			For(i, 1, m) if (st & (1 << (i - 1))) {
				if (fa[u[i]] == u[i]) ++comp, fa[u[i]] = 0;
				if (fa[v[i]] == v[i]) ++comp, fa[v[i]] = 0;
			}
			For(i, 1, m) fa[u[i]] = u[i], fa[v[i]] = v[i];

			if (cyc) {
				if (n != c || comp > 1) ok = false;
				else if (n & 1) --ans;
				else ++ans;
			} else {
				ans = (ans + (1ll * (c & 1 ? -1 : 1) * Pow2[comp - 1] * fac[n - 1 - c])) % Mod;
			}

		}

		For(i, 1, m) deg[u[i]] = deg[v[i]] = 0;
	}
	ans = (ans + Mod) % Mod;

	printf("%d\n", ans);

	return 0;
}
