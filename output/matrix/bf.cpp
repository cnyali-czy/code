#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 998244353;

int n, A[maxn][maxn];

inline int power(int a, int b)
{
    int r = 1;
    while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; }
    return r;
}

signed main()
{
    freopen("matrix3.in", "r", stdin);
    freopen("bf.out", "w", stdout);
    scanf("%lld", &n);
    // srand(time(0));
    REP(i, 1, n) REP(j, 1, n) { double x; scanf("%lf", &x); if ( x > 0 ) A[i][j]=1ll*rand()*rand()%Mod;}
    REP(i, 1, n) A[i][i] = A[i][n + i] = 1;
    REP(i, 1, n)
    {
        int Max = i;
        REP(j, 1, 2 * n) swap(A[i][j], A[Max][j]);
        if ( !A[i][i] ) { puts("No Solution"); return 0; }
        A[i][i] = power(A[i][i], Mod - 2);
        REP(j, 1, 2 * n) if ( j != i ) A[i][j] = A[i][j] * A[i][i] % Mod;
        REP(j, 1, n) if ( j != i ) REP(k, i + 1, n * 2) A[j][k] = (A[j][k] - A[j][i] * A[i][k]) % Mod;
    }
    int ans = 0;
    REP(i, 1, n) REP(j, n + 1, n + n) if ( A[i][j] != 0 ) ++ ans;
    printf("%lld\n", ans);
    return 0;
}
