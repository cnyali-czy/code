#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 40000 + 10, maxblock = 200 + 5;

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
	else
	{
		if (x / 10) write(x / 10);
		putchar(x % 10 + '0');
	}
}

int m, n, cur, a[maxn];

set <int> vis;
set <int> :: iterator it;
map <int, int> to;
int back[maxn];

int belong[maxn], Left[maxblock], Right[maxblock], block_siz, block_cnt;
int cnt[maxn][maxblock];
void get_belong()
{
	block_siz = sqrt(n);
	register int l = 1, r = block_siz;
	while (l <= n)
	{
		block_cnt++;
		Left[block_cnt] = l;Right[block_cnt] = r;
		REP(i, l, r) cnt[a[i]][belong[i] = block_cnt]++;
		l += block_siz;r += block_siz;
		chkmin(r, n);
	}
}

int times(int x, int S, int T) {return cnt[x][T] - cnt[x][S - 1];}

int ans[maxblock][maxblock];

void calc(int S, int T)
{
	register int &res = ans[S][T];
	res = ans[S][T-1];
	REP(i, Left[T], Right[T])
		if (times(a[i], S, T) > times(res, S, T) || times(a[i], S, T) == times(res, S, T) && a[i] < res) res = a[i];
}

int tempcnt[maxn], lastans;

int solve(int l, int r)
{
	if (l > r) swap(l, r);
	register int bl = belong[l], br = belong[r];
	if (br - bl < 2)
	{
		REP(i, l, r) tempcnt[a[i]] = 0;
		REP(i, l, r) tempcnt[a[i]]++;
		lastans = a[l];
		REP(i, l + 1, r)
			if (tempcnt[a[i]] > tempcnt[lastans] || tempcnt[a[i]] == tempcnt[lastans] && a[i] < lastans) lastans = a[i];
	}
	else
	{
		lastans = ans[bl + 1][br - 1];
		tempcnt[lastans] = 0;
		REP(i, l, Right[bl])	tempcnt[a[i]] = 0;
		REP(i, Left[br], r)		tempcnt[a[i]] = 0;
		REP(i, l, Right[bl])	tempcnt[a[i]]++;
		REP(i, Left[br], r)		tempcnt[a[i]]++;
		REP(i, l, Right[bl])
			if (tempcnt[a[i]] + times(a[i], bl + 1, br - 1) >  tempcnt[lastans] + times(lastans, bl + 1, br - 1) ||
				tempcnt[a[i]] + times(a[i], bl + 1, br - 1) == tempcnt[lastans] + times(lastans, bl + 1, br - 1) && a[i] < lastans) lastans = a[i];
		REP(i, Left[br], r)
			if (tempcnt[a[i]] + times(a[i], bl + 1, br - 1) >  tempcnt[lastans] + times(lastans, bl + 1, br - 1) ||
				tempcnt[a[i]] + times(a[i], bl + 1, br - 1) == tempcnt[lastans] + times(lastans, bl + 1, br - 1) && a[i] < lastans) lastans = a[i];
	}
	return lastans;
}

int main()
{
#ifdef CraZYali
	freopen("2724.in", "r", stdin);
	freopen("2724.out", "w", stdout);
#endif
	cin >> n >> m;
	REP(i, 1, n) vis.insert(a[i] = read<int>());
	for (it = vis.begin(); it != vis.end(); it++) back[to[*it] = ++cur] = *it;
	REP(i, 1, n) a[i] = to[a[i]];
	get_belong();
	REP(i, 1, cur)
		REP(j, 2, block_cnt)
		cnt[i][j] += cnt[i][j-1];

	REP(i, 1, block_cnt)
		REP(j, i, block_cnt) calc(i, j);	

	while (m --> 0) printf("%d\n", lastans = back[solve((read<int>() + lastans - 1) % n + 1, (read<int>() + lastans - 1) % n + 1)]);
	return 0;
}
