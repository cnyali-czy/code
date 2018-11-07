#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 50000 + 10, maxm = 50000 + 10;

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

template <typename T> void write(T x)
{
	if (x < 0) putchar('-'), write(-x);
	else if (x / 10) write(x / 10);
	putchar(x % 10 + '0');
}

int m, n, k, a[maxn];
struct que
{
	int l, r, pos;
	bool operator < (que B) const {return l < B.l || l == B.l && r < B.r;}
}q[maxm];

int belong[maxn], Left[maxn], Right[maxn], delta, block_cnt;
void divide()
{
	delta = sqrt(n);
	register int l = 1, r = 2;
	while (r <= m)
	{
		if (q[r].l - q[l].l > delta)
		{
			block_cnt++;
			REP(i, l, r) belong[i] = block_cnt;
			Left[block_cnt] = l;Right[block_cnt] = r;
			l = r + 1;
		}
		r++;
	}
	block_cnt++;
	Left[block_cnt] = l;Right[block_cnt] = m;
	REP(i, l, m) belong[i] = block_cnt;
}
pair <int, int> ans[maxm];
int cnt[maxn];

int main()
{
#ifdef CraZYali
	freopen("2038-new.in", "r", stdin);
	freopen("2038-new.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) a[i] = read<int>();
	REP(i, 1, m) q[i].l = read<int>(), q[i].r = read<int>(), q[i].pos = i;
	sort(q + 1, q + 1 + m);
	divide();
	REP(id, 1, block_cnt)
	{
		register int l = q[Left[id]].l, r = q[Left[id]].r;
		int res = 0;
		REP(i, 1, n) cnt[i] = 0;
		REP(i, l, r) res += cnt[a[i]]++;
		if (r > l)
		{
			ans[q[Left[id]].pos].first = res / __gcd(res, (r - l + 1) * (r - l) / 2); 
			ans[q[Left[id]].pos].second = (r - l + 1) * (r - l) / 2 / __gcd(res, (r - l + 1) * (r - l) / 2); 
		}
		else ans[q[Left[id]].pos] = make_pair(0, 1);
		REP(j, Left[id] + 1, Right[id])
		{
			int L = q[j].l, R = q[j].r;
			while (l < L) res -= --cnt[a[l++]];
			while (r < R) res += cnt[a[++r]]++;
			while (r > R) res -= --cnt[a[r--]];
			if (r > l)
			{
				ans[q[j].pos].first = res / __gcd(res, (r - l + 1) * (r - l) / 2); 
				ans[q[j].pos].second = (r - l + 1) * (r - l) / 2 / __gcd(res, (r - l + 1) * (r - l) / 2); 
			}
			else ans[q[j].pos] = make_pair(0, 1);
		}
	}

	REP(i, 1, m) printf("%d/%d\n", ans[i].first, ans[i].second);
	return 0;
}
