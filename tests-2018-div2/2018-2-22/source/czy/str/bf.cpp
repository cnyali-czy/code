#define  REP(i, s, e) for(register int i = s; i <= e ;i++)
#define DREP(i, s, e) for(register int i = s; i >= e ;i--)

#define DEBUG fprintf(stderr, "Passing [%s] in LINE %d\n", __FUNCTION__, __LINE__)
#define chkmin(a, b) a = min(a, b)
#define chkmax(a, b) a = max(a, b)

#include <bits/stdc++.h>

using namespace std;
const int maxn = 1000 + 10;

char a[maxn], b[maxn];
int lena, lenb, f[maxn][maxn];

int main()
{
	freopen("str.in", "r", stdin);
	freopen("str.out", "w", stdout);
	scanf("%s\n%s", a, b);
	lena = strlen(a) - 1;
	lenb = strlen(b) - 1;
	
	memset(f, 127/3, sizeof(f));
	f[lena + 1][lenb + 1] = 0;
	int ans = 1e9;
	DREP(i, lena + 1, 0)
	{
		DREP(j, lenb + 1, 0)
		{
			if (i <= lena && j <= lenb) chkmin(f[i][j], f[i + 1][j + 1] + (a[i] != b[j]));
			if (i <= lena) chkmin(f[i][j], f[i + 1][j] + 1);
			if (j <= lenb) chkmin(f[i][j], f[i][j + 1] + 1);
		}
		chkmin(ans, f[i][0]);
	}
	cout << ans;
	return 0;
}
