#define DREP(i, s, e) for(int i = s; i >= e ;i--)
#define  REP(i, s, e) for(int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
const int maxn = 30000 + 10;

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

int n;
char s[maxn];

template <long long base, long long MOD>
struct Hash_Table
{
	long long bin[maxn], Hash[maxn];
	Hash_Table()
	{
		bin[0] = 1;
		REP(i, 1, maxn-10) bin[i] = bin[i-1] * base % MOD;
	}
	void calc()
	{
		REP(i, 1, n) Hash[i] = (Hash[i-1] * base % MOD + s[i] - 'a') % MOD;
	}
	long long get_val(int l, int r)
	{
		long long res = Hash[r] - Hash[l-1] * bin[r - l + 1] % MOD;
		return (res % MOD + MOD) % MOD;
	}
};
Hash_Table <23, (long long)1e9 + 7> H1;
Hash_Table <31, (long long)1e9 + 9> H2;
bool same(int l1, int r1, int l2, int r2)
{
	return (r1 - l1 + 1 == r2 - l2 + 1) && H1.get_val(l1, r1) == H1.get_val(l2, r2) && H2.get_val(l1, r1) == H2.get_val(l2, r2);
}

long long pre[maxn], nex[maxn], ans;
void add(long long s[], int Start, int End, int val)
{
#ifdef CraZYali
	fprintf(stderr, "%s: %d\t%d\t%d\n", s==pre?"pre":"nex",Start, End, val);
#endif
	s[Start] += val;
	s[End+1] += -val;
}
void calc()
{
	REP(i, 1, n) pre[i] += pre[i-1];
	REP(i, 1, n) nex[i] += nex[i-1];
	ans = 0;
	REP(i, 1, n-1) ans += pre[i] * nex[i+1];
}

int main()
{
#ifdef CraZYali
	freopen("1117.in", "r", stdin);
	freopen("1117.out", "w", stdout);
	freopen("1117.err", "w", stderr);
#endif
	int T = read<int>();
	while (T--)
	{
		scanf("%s", s + 1);
		n = strlen(s + 1);
		H1.calc();H2.calc();
		REP(i, 1, n) pre[i] = nex[i] = 0;
		REP(L, 1, n)
			for (int i = 2; i * L <= n; i++)
				if (s[(i-1) * L] == s[i * L])
				{
					int pos1 = (i-1) * L, pos2 = i * L, l, r, head(pos1), tail(pos2), Start, End;
					l = max(1, pos1 - L + 1), r = pos1;
					while (l <= r)
					{
						int mid = l + r >> 1;
						if (same(mid, pos1, pos2 - (pos1 - mid), pos2))
						{
							head = mid;
							r = mid - 1;
						}
						else l = mid + 1;
					}
					l = pos2, r = min(n, pos2 + L - 1);
					while (l <= r)
					{
						int mid = l + r >> 1;
						if (same(pos2, mid, pos1, pos1 + (mid - pos2)))
						{
							tail = mid;
							l = mid + 1;
						}
						else r = mid - 1;
					}
#ifdef CraZYali
					fprintf(stderr, "%d %d %d %d %d\n", L, pos1, pos2, head, tail);
#endif
					Start = head, End = tail - L * 2 + 1;
					if (Start <= End) add(nex, Start, End, 1);
					Start = head + L * 2 - 1, End = tail;
					if (Start <= End) add(pre, Start, End, 1);
				}
		calc();
#ifdef CraZYali
		REP(i, 1, n) fprintf(stderr, "%lld%c", pre[i], i == n ? '\n' : ' ');
		REP(i, 1, n) fprintf(stderr, "%lld%c", nex[i], i == n ? '\n' : ' ');
		int pos1 = 3, pos2 = 6, mid = 8;
		cerr << "judge: " << same(pos2, mid, pos1 - (mid - pos2), pos1)<<endl;
		fputs("==========\n", stderr);
#endif
		printf("%lld\n", ans);
	}
	return 0;
}
