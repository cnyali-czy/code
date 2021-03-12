#define REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <vector>
#define i64 long long

using namespace std;
const int maxn = 5000 + 5;

inline int read()
{
	int x;
	scanf("%d", &x);
	return x;
}

int Ln[2000005], Exp[2000005], inited;

i64 power_pow(i64 base, int b, const i64 p)
{
	if (!base) return !b;
	if (inited) return Exp[1ll * b * Ln[base] % (p - 1)];
	i64 ans = 1;
	while (b)
	{
		if (b & 1) (ans *= base) %= p;
		if (b >>= 1) (base *= base) %= p;
	}
	return ans;
}
#define inv(x) power_pow(x, P - 2, P)

int top, stk[666];
void split(int x)
{
	for (int i = 2; i * i <= x; i++) if (x % i == 0)
	{
		stk[++top] = i;
		while (x % i == 0) x /= i;
	}
	if (x > 1) stk[++top] = x;
}
int calcg(const int p)
{
	split(p - 1);
	REP(i, 1, 114514)
	{
		bool flg = 1;
		REP(j, 1, top) if (power_pow(i, (p - 1) / stk[j], p) == 1) {flg = 0;break;}
		if (flg && power_pow(i, p - 1, p) == 1) return i;
	}
	return -1;
}

int T, K, P, g, w[maxn];

int n, q;
vector <int> G[maxn];

#define poly vector <int>
poly operator * (poly A, poly B)
{
	REP(i, 0, K - 1) A[i] = 1ll * A[i] * B[i] % P;
	return A;
}
poly make(int a)
{
	static const int MOD = P;
	poly res(K);
	i64 fk = power_pow(w[1], a, P);
	res[0] = 1;REP(i, 1, K - 1) res[i] = res[i - 1] * fk % MOD;
	return res;
}
poly operator + (poly a, poly b)
{
	REP(i, 0, K - 1) (a[i] += b[i]) %= P;
	return a;
}
poly operator *= (poly &a, poly b) {return a = a * b;}
poly operator += (poly &a, poly b) {return a = a + b;}
poly operator ^ (poly a, int b) {for (auto &i : a) i = power_pow(i, b, P);return a;}
poly f[maxn];

int CUR;
void dfs(int u, int fa)
{
	f[u] *= f[CUR];
	for (int v : G[u]) if (v ^ fa)
		dfs(v, u);
}

poly get(int u, int fa)
{
	poly res = f[u];
	for (int v : G[u]) if (v ^ fa) res *= get(v, u);
	return res;
}
int calc(poly f, int s)
{
	reverse(f.begin() + 1, f.end());
	i64 ans = 0;
	const int MOD = P;
	DEP(i, K - 1, 0) ans = (ans * w[s] + f[i]) % MOD;
	static i64 ivk = power_pow(K, P - 2, P);
	return ans * ivk % MOD;
}

int dfn[maxn], fa[maxn], dfs_clock, siz[maxn];
void dfs0(int x)
{
	dfn[x] = ++dfs_clock;
	siz[x] = 1;
	for (int y : G[x]) if (y ^ fa[x])
	{
		fa[y] = x;
		dfs0(y);
		siz[x] += siz[y];
	}
}
int bfn[maxn], bfs_clock;

void initTree()
{
	REP(i, 1, n) G[i].clear();
	REP(i, 2, n)
	{
		int x = read(), y = read();
		G[x].emplace_back(y);
		G[y].emplace_back(x);
	}
	REP(i, 1, n) f[i] = poly(K, 1);
	
	dfs_clock = 0;
	dfs0(1);

	bfs_clock = 0;
	static int que[maxn], head, tail;
	que[head = tail = 0] = 1;
	while (head <= tail)
	{
		int x = que[head++];
		bfn[x] = ++bfs_clock;
		for (int y : G[x]) if (y ^ fa[x])
			que[++tail] = y;
	}
}

#define ls p << 1
#define rs p << 1 | 1
#define mid (l + r >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r
struct SMT
{
	poly f[maxn << 2], t[maxn << 2];
	bool need[maxn << 2];
	void init()
	{
		REP(i, 0, (maxn<<2) - 1) f[i] = t[i] = poly(K, 1), need[i] = 0;
	}
	void maintain(int p, int l, int r, poly v)
	{
		f[p] *= (v ^ (r - l + 1));
		t[p] *= v;
		need[p] = 1;
	}
	void pushdown(int p, int l, int r)
	{
		need[p] = 0;
		maintain(lson, t[p]);
		maintain(rson, t[p]);
		t[p] = poly(K, 1);
	}
	void update(int p, int l, int r, int L, int R, poly v)//const poly &v)
	{
//		REP(i, L, R) (f[i] *= v);return;
		if (L <= l && r <= R) maintain(p, l, r, v);
		else
		{
			if (need[p]) pushdown(p, l, r);
			if (L <= mid) update(lson, L, R, v);
			if (R >  mid) update(rson, L, R, v);
			f[p] = f[ls] * f[rs];
		}
	}
	poly query(int p, int l, int r, int L, int R)
	{
//		poly res = f[L];
//		REP(i, L + 1, R) res *= f[i];return res;
		if (L <= l && r <= R) return f[p];
		else
		{
			if (need[p]) pushdown(p, l, r);
			if (R <= mid) return query(lson, L, R);
			if (L >  mid) return query(rson, L, R);
			return query(lson, L, R) * query(rson, L, R);
		}
	}
}t1, t2;

void Dfs(int u, int fa, const poly &fk)
{
	t1.update(1, 1, n, dfn[u], dfn[u], fk);
	for (int v : G[u]) if (v ^ fa)
		Dfs(v, u, fk);
}

void output(const poly &f)
{
	REP(i, 0, K - 1) printf("%d%c", f[i], i == end_i ? '\n' : ' ' );
}

int main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> T >> K >> P;

	const int MOD = P;
	g = calcg(P);
	w[0] = 1;w[1] = power_pow(g, (P - 1) / K, P);REP(i, 2, K) w[i] = 1ll * w[i - 1] * w[1] % MOD;
	inited = 1;
	for (int x = 1, k = 0; k < P; k++)
	{
		Exp[Ln[x] = k] = x;
		x = 1ll * x * g % MOD;
	}

	while (T--)
	{
		n = read();q = read();int Type = read();
		initTree();
		t1.init();t2.init();

		while (q--)
		{
			char c = getchar();
			while (c ^ 'L' && c ^ 'C' && c ^ 'F' && c ^ 'S' && c ^ 'Q') c = getchar();
			if (c == 'L')
			{
				int x = read(), a = read();
				t1.update(1, 1, n, dfn[x], dfn[x], (poly(K, 1) + make(a)));
				f[x] *= (poly(K, 1) + make(a));
				if(f[x]!=t1.query(1,1,n,dfn[x],dfn[x]))DEBUG;
			}
			else if (c == 'C')
			{
				int x = read(), a = read(), b = read();
				t1.update(1, 1, n, dfn[x], dfn[x], (poly(K, 1) + make(a) + make(b)));
				f[x] *= (poly(K, 1) + make(a) + make(b));
				if(f[x]!=t1.query(1,1,n,dfn[x],dfn[x]))DEBUG;
			}
			else if (c == 'F')
			{
				int x = read();
				const poly st = t1.query(1, 1, n, dfn[x], dfn[x]);
				if (fa[x]) t1.update(1, 1, n, dfn[fa[x]], dfn[fa[x]], st), f[fa[x]] *= f[x];
				for (int y : G[x]) if (y ^ fa[x])
				{
					t1.update(1, 1, n, dfn[y], dfn[y], st);
					f[y] *= f[x];
					if(f[y]!=t1.query(1,1,n,dfn[y],dfn[y]))DEBUG;
				}
			}
			else if (c == 'S')
			{
				int u = read(), v = read();
				CUR = u;
				poly st = t1.query(1, 1, n, dfn[u], dfn[u]);
				/*
				if (u == fa[v])
					t1.update(1, 1, n, dfn[v], dfn[v] + siz[v] - 1, st);
				else
				{
					t1.update(1, 1, n, 1, n, st);
					t1.update(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, st ^ (P - 2));
				}
				*/
				if(st!=f[u])DEBUG;
				Dfs(v, u, st);
				dfs(v, u);
			}
			else
			{
				int u = read(), v = read(), s = read();

				poly f1, f2;f1 = f2 = poly(K, 1);
				if (u == fa[v])
				{
					f2 = t1.query(1, 1, n, dfn[v], dfn[v] + siz[v] - 1);
					if (1 <= dfn[v] - 1) f1 *= t1.query(1, 1, n, 1, dfn[v] - 1);
					if (dfn[v] + siz[v] <= n) f1 *= t1.query(1, 1, n, dfn[v] + siz[v], n);
//					f1 = get(u, v);
				}
				else
				{
					f1 = t1.query(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);
					if (1 <= dfn[u] - 1) f2 *= t1.query(1, 1, n, 1, dfn[u] - 1);
					if (dfn[u] + siz[u] <= n) f2 *= t1.query(1, 1, n, dfn[u] + siz[u], n);
				}
				printf("%d %d\n", calc(f1, s), calc(f2, s));
			}
//			printf("Case %d\n", q);
//			REP(i, 1, n) output(t1.query(1, 1, n, dfn[i], dfn[i]));
		}
	}
	return 0;
}
