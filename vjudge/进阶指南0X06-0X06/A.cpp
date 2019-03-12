#pragma GCC optimize(3,"Ofast","inline")
#define  REP(i, s, e) for (int i = s; i <= e; i++)
#define DREP(i, s, e) for (int i = s; i >= e; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %lld\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstdio>

#define int long long

using namespace std;
const int maxn = 5e6 + 10, maxm = 5e5 + 10;
int n, m, k;
template <typename T> T read()
{
	T ans = 0, p = 1;
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

int a[maxn], t1[maxn], t2[maxn], t3[maxn], t4[maxn];

int calc(int l, int r, int R)
{
	REP(i, l, r) t2[i] = t1[i];
	REP(i, r + 1, R) t3[i] = a[i];
	sort(t3 + r + 1, t3 + R + 1);
	int i = l, j = r + 1;
	REP(k, l, R)
		if (j > R || i <= r && t2[i] < t3[j]) t4[k] = t2[i++];
		else t4[k] = t3[j++];
	int res = 0, cnt = 1;
	while (l < R && cnt <= m)
	{
		cnt++;
		res += (t4[l] - t4[R]) * (t4[l] - t4[R]);
		l++;R--;
	}
	return res;
}

int get_right(int l)
{
	int len = 1, r = l;
	t1[l] = a[l];
	while (len && r <= n)
		if (calc(l, r, r + len) <= k)
		{
			r += len;
			len <<= 1;
			REP(i, l, r) t1[i] = t4[i];
		}
		else len >>= 1;
	return r;
}

signed main()
{
#ifdef CraZYali
	freopen("A.in", "r", stdin);
	freopen("A.out", "w", stdout);
#endif
	register int T = read<int>();
	while (T --> 0)
	{
		n = read<int>();m = read<int>();k = read<int>();
		REP(i, 1, n) a[i] = read<int>();
		int l = 1, ans(0);
		/*
		while (l <= n)
		{
			while (!q1.empty()) q1.pop();
			while (!q2.empty()) q2.pop();
			q1.push(a[l]);q2.push(-a[l]);
			int r = l, len = (1 << (int)log2(n - l + 1));
			while (len > 1)
			{
				while (r + len - 1 > n && len > 1) len >>= 1;
				if (len <= 1) break;
				int res = 0, cnt = 1;
				REP(i, r + 1, r + len - 1) q3.push(a[i]), q4.push(-a[i]);
				bool flag = 1;
				while (!q3.empty() && cnt <= m)
				{
					cnt++;
					q5.push(q3.top());
					q6.push(q4.top());
					res += (q3.top() + q4.top()) * (q3.top() + q4.top());
					if (res > k) {flag = 0;break;}
					q3.pop();q4.pop();
				}
				if (flag && res <= k)
				{
					REP(i, r + 1, r + len - 1) q1.push(a[i]), q2.push(-a[i]);
					r = r + len - 1;
				}
				else len >>= 1;
			}
			ans++;
//			cerr << l << ' ' << r << endl;
			l = r + 1;
		}
		*/
		
		while (l <= n)
		{
			l = get_right(l) + 1;
			ans++;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
