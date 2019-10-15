#define  REP(i, s, e) for (register int i(s), End_##i(e); i <= End_##i; i++)
#define DREP(i, s, e) for (register int i(s), End_##i(e); i >= End_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)

#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 500 + 5;

struct Matrix
{
	double M[maxn][maxn];
	inline Matrix() {memset(M, 0, sizeof M);}
};

int cur = 1;
inline Matrix operator * (const Matrix &a, const Matrix &b)
{
	Matrix res;
	REP(i, 1, cur)
		REP(k, 1, cur) 
		if (a.M[i][k])
			REP(j, 1, cur)
				res.M[i][j] += a.M[i][k] * b.M[k][j];
	return res;
}
inline Matrix operator *=(Matrix &a, const Matrix &b) {return a = a * b;}

Matrix ans;

char s[maxn];
int pos[maxn], fail[maxn], ch[maxn][26], id;
bool End[maxn];

int n, len, m;
double p[maxn];

int q[maxn], head, tail;

inline void ins()
{
	scanf("%s", s + 1);
	int now = 1;
	REP(i, 1, len)
	{
		if (!ch[now][s[i] - 'A']) ch[now][s[i] - 'A'] = ++cur;
		now = ch[now][s[i] - 'A'];
	}
	End[pos[++id] = now] = 1;
}

void build()
{
	q[0] = 1;
	while (head <= tail)
	{
		int u = q[head++];
		End[u] |= End[fail[u]];
		REP(i, 0, m - 1)
		{
			int k = fail[u];
			while (k && !ch[k][i]) k = fail[k];
			if (ch[u][i]) fail[q[++tail] = ch[u][i]] = k ? ch[k][i] : 1;
			else ch[u][i] = k ? ch[k][i] : 1;
		}
	}
}

int main()
{
#ifdef CraZYali
	freopen("1444.in", "r", stdin);
	freopen("1444.out", "w", stdout);
#endif
	cin >> n >> len >> m;
	REP(i, 0, m - 1)
	{
		double x, y;
		scanf("%lf%lf", &x, &y);
		p[i] = x / y;
	}
	REP(i, 1, n) ins();
	build();
	REP(i, 1, cur)
		if (End[i]) ans.M[i][i] = 1;
		else
			REP(j, 0, m - 1)
				ans.M[i][ch[i][j]] += p[j];
	REP(i, 1, 100) ans *= ans;
	REP(i, 1, n) printf("%.2lf\n", ans.M[1][pos[i]]);
	return 0;
}
