#include <functional>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>
#include <bitset>
#include <set>
#include <vector>

using namespace std;

const double pi = acos(-1.0);
const int inf = 0x3f3f3f3f;
const double eps = 1e-15;
typedef long long LL;
typedef pair <int, int> PLL;

int V[20], C[20];
int dp[(1 << 15) + 10];
int use[20];

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, E;
        scanf("%d%d", &n, &E);
        memset(dp, -1, sizeof(dp));
        dp[0] = 0;
        memset(use, 0, sizeof(use));
        for (int i = 0; i < n; ++i) {
            scanf("%d", &V[i]);
        }
        for (int i = 0; i < n; ++i) {
            scanf("%d", &C[i]);
        }
        int m, tmp;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &m);
            while (m--) {
                scanf("%d", &tmp);
                --tmp;
                use[i] |= (1 << tmp);
            };
        }
        for (int i = 0; i < (1 << n); ++i) {
            int cost = 0;
            for (int j = 0; j < n; ++j) {
                if (i & (1 << j)) {
                    cost += C[j];
                }
            }
            if (cost > E) {
                continue;
            }
            for (int j = 0; j < n; ++j) {
                if (!(i & (1 << j)) && dp[i] != -1) {
                    if ((use[j] & i) == use[j]) {
                        if (cost + C[j] <= E) {
                            dp[i | (1 << j)] = max(dp[i | (1 << j)], dp[i] + V[j]);;
                        }
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < (1 << n); ++i) {
            ans = max(ans, dp[i]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
