#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
    int r=0,t=1,c=getchar();
    while(c<'0'||c>'9')
    {
        t=c=='-'?-1:1;
        c=getchar();
    }
    while(c>='0'&&c<='9')
    {
        r=r*10+c-48;
        c=getchar();
    }
    return r*t;
}
#define u32 unsigned int
const int N=410,M=1<<16|10;
//             12345678
const int inf=1e8;
// max cost:  4000000
inline void Min(u32 &a,u32 b){ if(a>b) a=b; }
inline int Inf(int a){ return a==inf?-1:a; }
int n,e,m,q;
u32 a[N][N],d0[N][N],d1[N][N],d2[N][N],d3[N][N],ans[N][N];
u32 d[M][N];
int vis[N];
u32 V[N],Z[N];
int v[N],z[N],p[N],c;
int main()
{
	freopen("treasure.in","r",stdin);freopen("std.out","w",stdout);
    n=read(); e=read(); m=read();
    fr(i,1,n) fr(j,1,n) if(i!=j) d0[i][j]=a[i][j]=inf;
    fr(i,0,m+m-1) fr(j,1,n) d1[i][j]=inf;
    fr(i,0,m-1) fr(j,0,m-1) d3[i][j]=inf;
    fr(i,0,m+m-1) fr(j,0,m+m-1) d2[i][j]=inf;
    fr(i,1,e)
    {
        int u=read(),v=read();
        u32 w=read();
        a[u][v]=a[v][u]=std::min(a[u][v],w);
    }
    fr(i,0,m-1)
    {
        p[c++]=v[i]=read(); p[c++]=z[i]=read();
        V[v[i]]|=1<<i; Z[z[i]]|=1<<i;
    }
    fr(i,1,n) fr(j,1,n) if(!V[i]&&!V[j]) d0[i][j]=a[i][j];
    fr(k,1,n) fr(i,1,n) fr(j,1,n) Min(d0[i][j],d0[i][k]+d0[k][j]);
    fr(i,0,c-1) fr(j,1,n) if(!V[j]) fr(k,1,n) Min(d1[i][j],a[p[i]][k]+d0[k][j]);
    fr(i,0,c-1) fr(j,0,c-1)
    {
        d2[i][j]=a[p[i]][p[j]];
        fr(k,1,n) fr(l,1,n) if(!V[k]&&!V[l]) Min(d2[i][j],a[p[i]][k]+d0[k][l]+a[l][p[j]]);
    }
    fr(i,0,c-1) d1[i][p[i]]=0;
    fr(i,0,m-1)
    {
        fr(j,0,c-1) fr(k,0,(1<<m)-1) d[k][j]=inf;
        d[Z[z[i]]][i<<1|1]=0;
        fr(j,0,(1<<m)-1)
        {
            int J=((1<<m)-1)^j;
            fr(k,0,c-1) vis[k]=0;
            fr(t,1,c)
            {
                int x=0;
                while(vis[x]) x++;
                fr(k,x+1,c-1) if(!vis[k]&&d[j][k]<d[j][x]) x=k;
                vis[x]=1; if(d[j][x]>=inf) break;
                fr(k,0,c-1) if(!(V[p[k]]&J)) Min(d[j|Z[p[k]]][k],d[j][x]+d2[x][k]);
            }
            fr(k,0,m-1) Min(d3[i][k],d[j][k<<1]);
        }
    }
    fr(s,1,n) fr(t,1,n)
    {
        if(V[s]){ ans[s][t]=inf; continue; }
        if(s==t) continue;
        ans[s][t]=d0[s][t];
        fr(j,0,m-1) fr(k,0,m-1) if(!V[z[j]]) Min(ans[s][t],d1[j<<1|1][s]+d3[j][k]+d1[k<<1][t]);
    }
    q=read();
    while(q--)
    {
        int s=read(),t=read();
        printf("%d\n",Inf(ans[s][t]));
    }
    return 0;
}
