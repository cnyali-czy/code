#define  REP(i, s, e) for(register int i = s; i <= e ; i++)
#define DREP(i, s, e) for(register int i = s; i >= e ; i--)
#include <bits/stdc++.h>

using namespace std;

void reverse(char s[], int len)
{
    register int l = 1, r = len;
    while (l < r) swap(s[l++], s[r--]);
}

const int maxn = 500 + 5;

int n, m, k;
char a[maxn], b[maxn], c[maxn];

int main()
{
#ifdef CraZYali
	freopen("a.in", "r", stdin);
	freopen("a.out", "w", stdout);
#endif
    scanf("%s\n%s", a + 1, b + 1);
    n = strlen(a + 1);m = strlen(b + 1);
    REP(i, 1, n) a[i] -= '0';REP(i, 1, m)b[i] -= '0';
    reverse(a, n);reverse(b, m);
    k = max(n, m);
    REP(i, 1, k)
    {
        c[i] += a[i] + b[i];
        if (c[i] > 9)
        {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }
    k++;
    while (k > 1 && c[k] == 0) k--;
    DREP(i, k, 1) putchar(c[i] + '0');
    
    return 0;
}
