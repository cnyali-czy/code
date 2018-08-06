#include <bits/stdc++.h>

#define For(i, j, k) for (int i = j; i <= k; i++)

using namespace std;

typedef long long LL;

const int N = 5e5 + 10;
const int Mod = 998244353;

int Pow(int x, int e) {
	int ret = 1;
	while (e) {
		if (e & 1) ret = 1ll * ret * x % Mod;
		x = 1ll * x * x % Mod;
		e >>= 1;
	}
	return ret;
}

int getp() {
	int x, y;
	scanf("%d%d", &x, &y);
	return 1ll * x * Pow(y, Mod - 2) % Mod;
}

struct Info {
	LL k, b, sk, sb;

	Info operator + (const Info& B) const {
		return (Info){k * B.k % Mod, (B.k * b + B.b) % Mod, (sk + k * B.sk) % Mod, (b * B.sk + sb + B.sb) % Mod};
	}
};


int n, q, A, B, t;
int P[N];

struct Segment_Tree {

	Info c[N << 2];

	#define lc (o << 1)
	#define rc (o << 1 | 1)
	#define M ((L + R) >> 1)

	void getinfo(int o, int i) {
		c[o] = (Info){(P[i] + 1ll * (Mod + 1 - P[i]) * t) % Mod, P[i], 1ll * B * P[i] % Mod, 1ll * (A + B) * P[i] % Mod};
	}

	void build(int o, int L, int R) {
		if (L == R) getinfo(o, L);
		else {
			build(lc, L, M), build(rc, M + 1, R);
			c[o] = c[lc] + c[rc];
		}
	}

	void modify(int o, int L, int R, int x) {
		if (L == R) getinfo(o, L);
		else {
			x <= M ? modify(lc, L, M, x) : modify(rc, M + 1, R, x);
			c[o] = c[lc] + c[rc];
		}
	}

	Info query(int o, int L, int R, int l, int r) {
		if (l <= L && R <= r) return c[o];
		else {
			if (r <= M) return query(lc, L, M, l, r);
			else if (l > M) return query(rc, M + 1, R, l, r);
			else return query(lc, L, M, l, r) + query(rc, M + 1, R, l, r);
		}
	}

}T;

int main() {

	scanf("%*d%d%d", &n, &q);
	t = getp();
	scanf("%d%d", &A, &B);
	For(i, 1, n) P[i] = getp();
	T.build(1, 1, n);

	while (q--) {
		int op;
		scanf("%d", &op);
		if (!op) {
			int x;
			scanf("%d", &x);
			P[x] = getp();
			T.modify(1, 1, n, x);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			assert(l <= r);
			printf("%lld\n", T.query(1, 1, n, l, r).sb);
		}
	}

	return 0;
}
