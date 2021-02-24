
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<iostream>
#define llong long long
using namespace std;
 
inline int read()
{
    int x=0; bool f=1; char c=getchar();
    for(;!isdigit(c);c=getchar()) if(c=='-') f=0;
    for(; isdigit(c);c=getchar()) x=(x<<3)+(x<<1)+(c^'0');
    if(f) return x;
    return -x;
}
 
const int N = 500;
const int P = 998244353;
llong a[N+3][N+3];
llong c[N+3][N+3];
int n;
 
llong quickpow(llong x,llong y)
{
    llong cur = x,ret = 1ll;
    for(int i=0; y; i++)
    {
        if(y&(1ll<<i)) {y-=(1ll<<i); ret = ret*cur%P;}
        cur = cur*cur%P;
    }
    return ret;
}
llong mulinv(llong x) {return quickpow(x,P-2);}
 
void gauss()
{
    for(int i=1; i<=n; i++)
    {
        if(a[i+1][i]==0)
        {
            bool found = false;
            for(int j=i+2; j<=n; j++)
            {
                if(a[j][i]!=0)
                {
                    for(int k=i; k<=n; k++) swap(a[i+1][k],a[j][k]);
                    for(int k=1; k<=n; k++) swap(a[k][i+1],a[k][j]);
                    found = false; break;
                }
            }
            if(found) {continue;}
        }
        for(int j=i+2; j<=n; j++)
        {
            llong coe = P-a[j][i]*mulinv(a[i+1][i])%P;
            for(int k=i; k<=n; k++) a[j][k] = (a[j][k]+coe*a[i+1][k])%P;
            for(int k=1; k<=n; k++) a[k][i+1] = (a[k][i+1]-coe*a[k][j]%P+P)%P;
        }
    }
}
 
void charpoly()
{
    c[0][0] = 1ll;
    for(int i=1; i<=n; i++)
    {
        for(int j=0; j<=i; j++)
        {
            c[i][j] = (c[i-1][j-1]-a[i][i]*c[i-1][j]%P+P)%P;
        }
        llong coe = P-1,cur = P-a[i][i-1];
        for(int j=i-2; j>=0; j--)
        {
            llong tmp = cur*(P-a[j+1][i])%P;
            tmp = coe*tmp%P;
            for(int k=0; k<=j; k++)
            {
                c[i][k] = (c[i][k]+c[j][k]*tmp)%P;
            }
            cur = cur*(P-a[j+1][j])%P;
            coe = P-coe;
        }
        for(int k=0; k<=i; k++) c[i][k] %= P;
//      printf("%d: ",i); for(int j=0; j<=i; j++) printf("%lld ",c[i][j]); puts("");
    }
}
 
int main()
{
    scanf("%lld",&n);
    for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) scanf("%lld",&a[i][j]);
    gauss();
//  for(int i=1; i<=n; i++) {for(int j=1; j<=n; j++) printf("%lld ",a[i][j]); puts("");}
    charpoly();
    for(int i=0; i<=n; i++) printf("%lld ",c[n][i]); puts("");
    return 0;
}
