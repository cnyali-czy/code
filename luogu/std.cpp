
#include<bits/stdc++.h>
#define maxn 100
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int T,n,ans,tot,flag;
int p[maxn],sg[maxn];
bool vis[maxn];
void SG()
{
    for(int i=n-1;i;--i)
    {
        memset(vis,false,sizeof(vis));
        for(int j=i+1;j<=n;++j)
            for(int k=j;k<=n;++k)
                vis[sg[j]^sg[k]]=true;
        int t=0;
        while(1)
        {
            if(!vis[t])
            {
                sg[i]=t;
                break;
            }
            t++;
        }
    }
}
int main()
{
    read(T);
    while(T--)
    {
        read(n),sg[n]=ans=tot=flag=0;
        for(int i=1;i<=n;++i) read(p[i]);
        SG();
		for(int i=1;i<=n;i++)printf("%d%c",sg[i],i==n?'\n':' ');
        for(int i=1;i<=n;++i)
            if(p[i]%2)
                ans^=sg[i];
        for(int i=1;i<=n;++i)
        {
            if(!p[i]) continue;
            for(int j=i+1;j<=n;++j)
            {
                for(int k=j;k<=n;++k)
                {
                    if((ans^sg[i]^sg[j]^sg[k])==0)
                    {
						cout<<i<<' '<<j<<' '<<k<<endl;
                        tot++;
                        if(!flag)
                        {
                            flag=true;
                            printf("%d %d %d\n",i-1,j-1,k-1);
                        }
                    }
                }
            }
        }
        if(!flag) puts("-1 -1 -1");
        printf("%d\n",tot);
    }
    return 0;
}
