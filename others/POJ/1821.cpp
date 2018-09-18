#include<stdio.h>
#include<algorithm>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<vector>
#include<iostream>
#include<string.h>
#include<string>
#include<math.h>
#include<stdlib.h>
#define inff 0x3fffffff
#define eps 1e-8
#define nn 21000
#define mod 1000000007
typedef long long LL;
const LL inf64=LL(inff)*inff;
using namespace std;
int n,k;
int l[nn],p[nn],s[nn];
int dp[110][nn];
int que[nn];
int l1,r1;
void add(int id,int i)
{
    while(r1>l1)
    {
        if(dp[i-1][que[r1-1]]-p[i]*que[r1-1]<=dp[i-1][id]-p[i]*id)
        {
            r1--;
        }
        else
        {
            break;
        }
    }
    que[r1++]=id;
}
void dele(int id)
{
    while(l1<r1)
    {
        if(que[l1]<id)
        {
            l1++;
        }
        else
            break;
    }
}
int main()
{
    int i,j;
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(i=1;i<=k;i++)
        {
            scanf("%d%d%d",&l[i],&p[i],&s[i]);
        }
        for(i=1;i<=k;i++)
        {
            for(j=i+1;j<=k;j++)
            {
                if(s[j]<s[i])
                {
                    swap(l[i],l[j]);
                    swap(s[i],s[j]);
                    swap(p[i],p[j]);
                }
            }
        }
        for(i=0;i<=n;i++)
            dp[0][i]=0;
        int ix;
        for(i=1;i<=k;i++)
        {
            l1=r1=0;
            add(0,i);
            for(j=1;j<=n;j++)
            {
                dp[i][j]=max(dp[i][j-1],dp[i-1][j]);
                if(j>=s[i])
                {
                    ix=max(0,j-l[i]);
                    if(ix<s[i])
                    {
                        dele(ix);
                        dp[i][j]=max(dp[i][j],dp[i-1][que[l1]]-p[i]*que[l1]+p[i]*j);
                    }
                }
                if(j<s[i])
                    add(j,i);
            }
        }
        printf("%d\n",dp[k][n]);
    }
    return 0;
}

