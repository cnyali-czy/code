#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>
#define int long long

using namespace std;
const int maxn = 3e5 + 10, inf = 1e17;

template <typename T> inline T read()
{
	T ans(0), p(1);
	char c = getchar();
	while (!isdigit(c))
	{
		if (c == '-') p = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * p;
}

int n, sum[maxn], dp[maxn], h[maxn];

int k[maxn], b[maxn], ls[maxn], rs[maxn], cur;
#define mid (l + r >> 1)
#define lson ls[p], l, mid
#define rson rs[p], mid + 1, r

int f(int k, int b, int x) {return k * x + b;}

void update(int &p, int l, int r, int K, int B)
{
	if (!p)
	{
		p = ++cur;
		k[p] = K, b[p] = B;
	}
	else if (f(K, B, l) <= f(k[p], b[p], l) && f(K, B, r) <= f(k[p], b[p], r))
		k[p] = K, b[p] = B;
	else if (f(K, B, l) >  f(k[p], b[p], l) && f(K, B, r) >  f(k[p], b[p], r) || l == r)
		return;
	else
	{
		int lk = k[p], lb = b[p];
		if (f(K, B, l) <= f(lk, lb, l))
		{
			if (f(K, B, mid) <= f(lk, lb, mid))
			{
				k[p] = K, b[p] = B;
				update(rson, lk, lb);
			}
			update(lson, K, B);
		}
		else
		{
			if (f(K, B, mid+1) <= f(k[p], b[p], mid+1))
			{
				k[p] = K, b[p] = B;
				update(lson, lk, lb);
			}
			update(rson, K, B);
		}
	}
}
int rt, L, R;
int query(int p, int l, int r, int pos){return p ? min(f(k[p], b[p], pos), (pos <= mid ? query(lson, pos) : query(rson, pos))) : inf;}

int query(int pos) {return query(rt, L, R, pos);}
void insert(int k, int b) {update(rt, L, R, k, b);}

signed main()
{
#ifdef CraZYali
	freopen("B.in", "r", stdin);
	freopen("B.out", "w", stdout);
#endif
	cin >> n;
	REP(i, 1, n) h[i] = read<int>();
	REP(i, 1, n) sum[i] = sum[i-1] + read<int>();
	L = -2e6-5;R = 5;
	insert(h[1],dp[1] - sum[1] + h[1] * h[1]);
	REP(i, 2, n)
		insert(h[i], (dp[i] = query(-2 * h[i]) + h[i] * h[i] + sum[i-1]) - sum[i] + h[i] * h[i]);
	cout << dp[n] << endl;
	return 0;
}
