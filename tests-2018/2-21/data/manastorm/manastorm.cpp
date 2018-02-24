#include <bits/stdc++.h>

#define pb push_back
#define For(i, j, k) for (int i = j; i <= k; i++)
#define Forr(i, j, k) for (int i = j; i >= k; i--)

using namespace std;

typedef vector<int> Poly;

const int Mod = 998244353, r = 3;
const int N = 140000;

int Pow(int x, int e) {
	int ret = 1;
	while (e) {
		if (e & 1) ret = 1ll * ret * x % Mod;
		x = 1ll * x * x % Mod;
		e >>= 1;
	}
	return ret;
}

namespace FFT{

	int a[N], b[N];
	int w[N], rev[N], n;

	void DFT(int *A, int f) {
		For (i, 0, n - 1) if (i < rev[i]) swap(A[i], A[rev[i]]);
		for (int i = 1; i < n; i <<= 1) {
			
			w[0] = 1;
			w[1] = Pow(r, (Mod - 1) / (i << 1));
			if(f == -1) w[1] = Pow(w[1], Mod - 2);
			for (int j = 2; j < i; ++j) w[j] = 1ll * w[j - 1] * w[1] % Mod;

			for (int j = 0; j < n; j += (i << 1))
				for (int k = 0; k < i; ++k) {
					int x = A[j + k], y = 1ll * w[k] * A[i + j + k] % Mod;
					A[j + k] = (x + y) % Mod, A[i + j + k] = (x - y + Mod) % Mod;
				}
			
		}
	}

	void mult(Poly& A, const Poly& B) {
		int la = A.size(), lb = B.size();
		int sz = (la + lb - 1);

		n = 1;
		while (n <= sz) n <<= 1;

		For (i, 0, n - 1) {
			a[i] = i < la ? A[i] : 0, b[i] = i < lb ? B[i] : 0;
			rev[i] = rev[i >> 1] >> 1 | ((i & 1) * (n >> 1));
		}

		DFT(a, 1), DFT(b, 1);
		For (i, 0, n - 1) a[i] = 1ll * a[i] * b[i] % Mod;
		DFT(a, -1);

		A.resize(sz);
		int inv = Pow(n, Mod - 2);
		For (i, 0, sz - 1) A[i] = 1ll * a[i] * inv % Mod;
	}

};

Poly P[N];

int main() {

	int n, k;
	scanf("%d%d", &n, &k);
	For (i, 1, n) {
		int x;
		scanf("%d", &x);
		P[i].pb(1), P[i].pb(x % Mod);
	}

	for (int i = 1; i < n; i <<= 1)
		for (int j = 1; i + j <= n; j += (i << 1))
			FFT::mult(P[j], P[j + i]);

	int coe = 1, ans = 0, inv = Pow(n, Mod - 2);
	Forr (i, n, 0) {
		ans = (ans + 1ll * coe * P[1][i]) % Mod;
		coe = 1ll * coe * (Mod - 1) % Mod * (k - (n - i) + Mod) % Mod * inv % Mod;
	}
	printf("%d\n", (P[1][n] - ans + Mod) % Mod);

	return 0;
}
