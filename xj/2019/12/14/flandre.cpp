#define  REP(i, s, e) for (register int i(s), end_##i(e); i <= end_##i; i++)
#define DREP(i, s, e) for (register int i(s), end_##i(e); i >= end_##i; i--)
#define DEBUG fprintf(stderr, "Passing [%s] in Line %d\n", __FUNCTION__, __LINE__)
 
#include <ctime>
#include <cstring>
#include <iostream>
#include <bitset>
#include <cstdio>
using namespace std;
const int maxn = 1000 + 10;
 
int n, k, mins, mine, v[2][maxn];
long long ans = -1, maxsum[maxn];
bitset <maxn> bst, cur;
int dfn;
inline void output()
{
    cout << ans << endl;
    REP(i, 1, n) putchar(bst[i] ? 'E' : 'S');
}
inline void output_noans(int x)
{
    REP(i, 1, x) putchar(cur[i] ? 'E' : 'S');
    putchar(10);
}
const int Count = 45, lim = 900;
void dfs(int x, int s, int e, long long res)
{
    //cout << x << ' ' << fst << ' '<< s << ' '<<e<<' '<<res<<endl;
    //output_noans(x);
    ++dfn;
    if (x >= k && (s < mins || e < mine)) return;
    if (maxsum[x + 1] + res <= ans) return;
    if (x == n)
    {
        if (res >= ans)
        {
            ans = res;
            bst = cur;
        }
        if (dfn % Count == 0 && clock() * 1000. / CLOCKS_PER_SEC >= lim)
        {
            output();
            exit(0);
        }
        return;
    }
    if (dfn % Count == 0 && clock() * 1000. / CLOCKS_PER_SEC >= lim)
    {
        output();
        exit(0);
    }
    x++;
    if (v[1][x] > v[0][x])
    {
        cur[x] = 1;
        dfs(x, s - (x > k ? !cur[x-k] : 0), e - (x > k ? cur[x-k] : 0) + 1, res + v[1][x]);
        cur[x] = 0;
        dfs(x, s - (x > k ? !cur[x-k] : 0) + 1, e - (x > k ? cur[x-k] : 0), res + v[0][x]);
    }
    else
    {
        cur[x] = 0;
        dfs(x, s - (x > k ? !cur[x-k] : 0) + 1, e - (x > k ? cur[x-k] : 0), res + v[0][x]);
        cur[x] = 1;
        dfs(x, s - (x > k ? !cur[x-k] : 0), e - (x > k ? cur[x-k] : 0) + 1, res + v[1][x]);
    }
}
 
signed main()
{
#ifdef CraZYali
    freopen("flandre.in", "r", stdin);
    freopen("flandre.out", "w", stdout);
#endif
    cin >> n >> k >> mins >> mine;
    long long sum[2] = {0};
    REP(i, 0, 1)
        REP(j, 1, n)
        {
            scanf("%d", v[i] + j);
            sum[i] += v[i][j];
        }
    DREP(i, n, 1)
        maxsum[i] = maxsum[i+1] + max(v[0][i], v[1][i]);
    if (k == 1)
    {
        if (mins)   cout << sum[0] << endl << string(n, 'S');
        else        cout << sum[1] << endl << string(n, 'E');
        return 0;
    }
    dfs(1, 1, 0, v[0][1]);
    cur[1] = 1;
    dfs(1, 0, 1, v[1][1]);
    output();
    return 0;
}
