#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 5000 + 10, maxm = 5000 + 10 ;

template <typename T> T read()
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

int m, n, k;

namespace bf
{
	short a[maxn], b[maxn];
	pair <int, int> c[maxn];

	inline bool cmp(short x, short y) {return x > y;}

	inline void doit(short x, short y)
	{
		sort(a + x, a + 1 + y, cmp);
		register short l = x, r = y, pos = x;
		register bool flag = 1;
		while (pos <= y)
		{
			if (flag) b[l++] = a[pos++];
			else b[r--] = a[pos++];
			flag ^= 1;
		}
		REP(i, x, y) a[i] = b[i];
	}

	struct opt
	{
		bool opt;
		int x, y;
	}o[maxm];

	vector <short> v;

	short s[maxm][maxm];

	map <int, short> M;
	int to[maxn];

	bool cmp1(pair<int, int> A, pair<int, int> B) {return A.first > B.first;}

	bool flag[maxn];

	inline void work()
	{
		REP(i, 1, n) c[i] = make_pair(read<int>(), i);
		sort(c + 1, c + 1 + n, cmp1);
	
		register int cnt(n);
		REP(i, 1, n)
		{
			if (!M[c[i].first]) to[M[c[i].first] = cnt--] = c[i].first;
			a[c[i].second] = M[c[i].first];
		}
	
		REP(i, 1, m)
		{
			o[i].opt = read<short>() - 1;
			if (!o[i].opt) o[i].x = read<int>(), o[i].y = read<int>();
			else o[i].x = read<int>();
		}
		REP(i, 1, n) s[0][i] = a[i];
		register int nowx = 0;
		REP(i, 1, m)
			if (o[i].opt == 0) nowx++;
			else flag[max(0, nowx - o[i].x)] = 1;
		nowx = 0;
		REP(i, 1, m)
			if (o[i].opt == 0)
			{
				nowx++;
				doit(o[i].x, o[i].y);
				if (flag[nowx])
					REP(j, 1, n) s[nowx][j] = a[j];
			}
			else REP(j, 1, n) a[j] = s[max(0, nowx - o[i].x)][j];
		printf("%d\n", to[a[k]]);
	}
};

int main()
{
	freopen("coach.in", "r", stdin);
	freopen("coach.out", "w", stdout);
	cin >> n >> m >> k;
	if (n <= 5000 && m <= 5000) bf::work();
	
	return 0;
}
