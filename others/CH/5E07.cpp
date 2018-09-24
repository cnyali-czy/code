#define DREP(i, s, e) for(register int i = s; i >= e ;i--)
#define  REP(i, s, e) for(register int i = s; i <= e ;i++)

#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
#define chkmax(a, b) a = max(a, b)
#define chkmin(a, b) a = min(a, b)

#include <bits/stdc++.h>

using namespace std;

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

int m, n, k;

bool read(int A[], int len)
{
	int allzero = 0;
	REP(i, 1, len) A[i] = read<int>(), allzero |= A[i];
	return allzero;
}

int A[10];
int dp[30000 + 10];

int num[3000], tot;

void split(int x, int id)
{
	register int temp = 0;
	REP(i, 0, 30)
	{
		x -= 1 << i;
		if (x < 0) {x += 1 << i;break;}
		num[++tot] = id * (1 << i);
	}
	if (x) num[++tot] = id * x;
}

int main()
{
#ifdef CraZYali
	freopen("5E07.in", "r", stdin);
	freopen("5E07.out", "w", stdout);
#endif
	n = 6;
	while (read(A, n))
	{
		register int sum = 0;
		REP(i, 1, n) sum += i * A[i];

		if (sum & 1)
		{
			printf("Can't\n");
			continue;
		}

		register int mid = sum >> 1;

		tot = 0;
		REP(i, 1, n) split(A[i], i);
		
		memset(dp, 0, sizeof(dp));

		REP(i, 1, tot)
			DREP(j, mid, num[i])
				chkmax(dp[j], dp[j - num[i]] + num[i]);
		
		if (dp[mid] == mid) printf("Can\n");
		else printf("Can't\n");
	}
	
	return 0;
}
