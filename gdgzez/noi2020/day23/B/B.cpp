#define REP(i, s, e) for (register int i = (s), end_##i = (e); i <= end_##i; i++)
#define DEP(i, s, e) for (register int i = (s), end_##i = (e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) (a < (b) ? a = (b) : a)
#define chkmin(a, b) (a > (b) ? a = (b) : a)

#include <queue>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
#define i64 long long
#define ui64 unsigned i64
template <typename T> T read()
{
	T ans(0), flag(1);
	char c(getchar());
	while (!isdigit(c))
	{
		if (c == '-') flag = -1;
		c = getchar();
	}
	while (isdigit(c))
	{
		ans = ans * 10 + c - 48;
		c = getchar();
	}
	return ans * flag;
}

void file(string s)
{
	freopen((s + ".in").c_str(), "r", stdin);
	freopen((s + ".out").c_str(), "w", stdout);
}

int m, n, k;

const ui64 base = 1e9 + 7;
ui64 H[maxn], bin[maxn];
char s[maxn];
inline ui64 get(int l, int r) {return H[r] - bin[r - l + 1] * H[l - 1];}
inline bool cmp(int x, int y) //[x...n] < [y...n]
{
	int lim = min(n - x + 1, n - y + 1);
	if (s[x] != s[y]) return s[x] < s[y];
	int l = 1, r = lim, lst = 1;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (get(x, x + mid - 1) == get(y, y + mid - 1))
		{
			lst = mid;
			l = mid + 1;
		}
		else r = mid - 1;
	}
	if (lst == lim) return x > y;
	return s[x + lst] < s[y + lst];
}
int blg[maxn], st[maxn], top, l[maxn];

priority_queue <int, vector <int>, greater <int> > q;
int main()
{
#ifdef CraZYali
	file("B");
#endif
	k = read<int>();
	scanf("%s", s + 1);
	n = strlen(s + 1);
	bin[0] = 1;
	REP(i, 1, n)
	{
		H[i] = H[i - 1] * base + s[i];
		bin[i] = bin[i - 1] * base;
	}
	int fir = 1;
	DEP(c, 'z', 'a')
	{
		if (!k) break;
		int tmp = 0, need = 0, last = 0;
		top = 0;
		REP(j, fir, n) if (s[j] == c)
		{
			last = j;
			if (j == fir || s[j] != s[j - 1])
			{
				st[++top] = j;
				l[top] = 1;
				++need;
			}
			else l[top]++;
		}
		if (!top) continue;
		if (s[fir] == c) need--;
		if (need <= k)
		{
			k -= need;
			REP(i, 1, top)
			{
				int x = st[i];
				while (x <= n && s[x] == c) putchar(c), x++;
			}
			fir = last + 1;
			continue;
		}
		if (s[fir] == c)
		{
			for (int x = st[1]; s[x] == c; x++) putchar(c);
			REP(i, 1, top - 1) st[i] = st[i + 1], l[i] = l[i + 1];top--;
		}
		while (!q.empty()) q.pop();
		int L = 0, ql = 0;
		int pick = 0;
		REP(i, 1, top)
		{
			int x = st[i] + l[i], len = l[i];
			int Old = 0;
			if (q.size() > k - 1)
			{
				ql -= (Old = q.top());
				q.pop();
			}
			ql += len;
			if (ql > L || ql == L && cmp(pick, x))
			{
				pick = x;
				q.emplace(len);
				L = ql;
				last = x - 1;
			}
			else
			{
				ql -= len;
				ql += Old;
				q.emplace(Old);
			}
		}
		REP(i, 1, L) putchar(c);
		fir = last + 1;
		break;
	}
	puts(s + fir);
	return 0;
}
