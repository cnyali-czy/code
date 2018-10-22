#define  REP(i, s, e) for(register int i = s; i <= e ; i++)
#define DREP(i, s, e) for(register int i = s; i >= e ; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

int n, m, k;
int num[15], i[10][10], ans[6][3];

int Remove(int i[10][10])
{
	register int flag = 0, f[10][10] = {0};
	REP(a, 1, 5)
		REP(b, 1, 7)
		if (i[a][b])
		{
			if (a <= 3 && i[a][b] == i[a+1][b] && i[a+1][b] == i[a+2][b]) f[a][b] = f[a+1][b] = f[a+2][b] = 1;
			if (b <= 5 && i[a][b] == i[a][b+1] && i[a][b+1] == i[a][b+2]) f[a][b] = f[a][b+1] = f[a][b+2] = 1;
		}
	REP(a, 1, 5)
		REP(b, 1, 7)
		if (f[a][b])
		{
			i[a][b] = 0;
			flag = 1;
		}
	return flag;
}
void Fall(int i[10][10])
{
	REP(a, 1, 5)
	{
		register int pos = 0;
		REP(b, 1, 7)
		{
			register int temp = i[a][b];
			i[a][b] = 0;
			if (temp) i[a][++pos] = temp;
		}
	}
}

int Check(int i[10][10])
{
	REP(a, 1, 5)
		REP(b, 1, 7) if (i[a][b]) return 0;
	return 1;
}

void dfs(int A, int i[10][10])
{
	if (A == n)
	{
		if (Check(i))
		{
			REP(a, 1, n)
				if (ans[a][2]) printf("%d %d -1\n", ans[a][0], ans[a][1] - 1);
				else printf("%d %d 1\n", ans[a][0] - 1, ans[a][1] - 1);
			exit(0);
		}
		return;
	}
	A++;
	memset(num, 0, sizeof(num));
	REP(a, 1, 5)
		REP(b, 1, 7) num[i[a][b]]++;
	REP(i, 1, 10)
		if (num[i] == 1 || num[i] == 2) return;
	int f[10][10] = {0};
	REP(a, 1, 4)
		REP(b, 1, 7)
		if (i[a][b] != i[a + 1][b])
		{
			memcpy(f, i, sizeof(f));
			ans[A][0] = a;
			ans[A][1] = b;
			ans[A][2] = (i[a][b] ? 0 : 1);
			swap(f[a][b], f[a+1][b]);
			Fall(f);
			while (Remove(f)) Fall(f);
			dfs(A, f);
		}
}

int main()
{
#ifdef CraZYali
	freopen("1312.in", "r", stdin);
	freopen("1312.out", "w", stdout);
#endif
	cin >> n;
	REP(a, 1, 5)
		REP(b, 1, 1e9)
		{
			scanf("%d", &i[a][b]);
			if (!i[a][b]) break;
		}
	dfs(0, i);
	cout << -1;
	return 0;
}

