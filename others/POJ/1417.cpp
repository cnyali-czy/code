#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int MAXN=1000;
int bag[MAXN][2];//bag[i][0]表示第i(重新编号了)个连通分量的0类人的个数,bag[i][1]表1类人
map<int,int> mp;//用来将老的连通分量编号映射bag中的新编号
int cnt;//一共有cnt个分量
int insert(int x,int b)//连通分量x,与x的关系是b(0表示同类,1表示异类)
{
    if(mp.find(x)==mp.end())mp[x]=++cnt;
    bag[mp[x]][b]++;//该分量的b类人加1
    return mp[x];
}
int F[MAXN];
int v[MAXN];//表示i与根的关系
int findset(int i)
{
    if(F[i]==-1)return i;
    int temp= findset(F[i]);
    v[i] =(v[i]+v[F[i]])%2;
    return F[i]=temp;
}
void bind(int i,int j,int temp)
{
    int fa=findset(i);
    int fb=findset(j);
    if(fa!=fb)
    {
        F[fb]=fa;
        v[fb]=(v[i]+v[j]+temp)%2;
    }
}
int d[MAXN][310];//DP
int main()
{
    int n,p1,p2;
    while(scanf("%d%d%d",&n,&p1,&p2)==3)
    {
        if(n==0&&p1==0&&p2==0)break;
        cnt=0;
        mp.clear();
        memset(bag,0,sizeof(bag));
        memset(F,-1,sizeof(F));
        memset(v,0,sizeof(v));
        memset(d,0,sizeof(d));
        while(n--)
        {
            int a,b,temp;
            char str[10];
            scanf("%d%d%s",&a,&b,str);
            if(str[0]=='y')
                temp=0;
            else if(str[0]=='n')
                temp=1;
            int fa=findset(a);
            int fb=findset(b);
            if(fa!=fb)//不同分量
                bind(a,b,temp);;
        }
        for(int i=1;i<=p1+p2;i++)//将1到p1+p2所有点重新编号
        {
            int fi=findset(i);
            insert(fi,v[i]);
        }
        d[0][0]=1;//初值
        for(int i=1;i<=cnt;i++)//连通分量编号从1到cnt
        {
            for(int j=0;j<=p1;j++)
            {
                if( j>=bag[i][0] )
                    d[i][j] = d[i-1][j-bag[i][0]];
                if( j>=bag[i][1] )
                    d[i][j] += d[i-1][ j-bag[i][1] ];
            }
        }
        //printf("###%d\n",d[cnt][p1]);
 
        if(d[cnt][p1]==1)//能区分出
        {
            int j=p1;
            int choose[MAXN];//choose[i]=1/0表示第i(重新编号)个连通分量选择第0类还是选第1类
            memset(choose,-1,sizeof(choose));
            for(int k=cnt;k>=1;k--)//逆推找出choose
            {
                if( d[k][j] == d[k-1][j-bag[k][0]] )
                {
                    choose[k]=0;
                    j=j-bag[k][0];
                }
                else if( d[k][j] == d[k-1][j-bag[k][1]] )
                {
                    choose[k]=1;
                    j=j-bag[k][1];
                }
            }
            for(int i=1;i<=p1+p2;i++)
            {
                int fa=findset(i);//找出分量的编号fa
                int num=mp[fa];//找出fa重新编号后的编号 num
                if(v[i]==choose[num])
                    printf("%d\n",i);
            }
            printf("end\n");
        }
        else
        {
            printf("no\n");
        }
    }
    return 0;
}
/*
————————————————
版权声明：本文为CSDN博主「focus_best」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/u013480600/article/details/21231965
*/
