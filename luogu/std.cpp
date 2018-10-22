
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
using namespace std;
int n,Num[15],i[6][8],Ans[6][3];
bool Remove(int i[6][8]) //清除。
{
    bool Flag(0),f[6][8]={0};
    for (int a=1;a<=5;a++)
      for (int b=1;b<=7;b++)
        if (i[a][b])
        {
            if (a<=3&&i[a][b]==i[a+1][b]&&i[a+1][b]==i[a+2][b])
              f[a][b]=f[a+1][b]=f[a+2][b]=true;
            if (b<=5&&i[a][b]==i[a][b+1]&&i[a][b+1]==i[a][b+2])
              f[a][b]=f[a][b+1]=f[a][b+2]=true;
        }
    for (int a=1;a<=5;a++)
      for (int b=1;b<=7;b++)
        if (f[a][b]) //值得学习，本次清除过格子。
        {
            i[a][b]=0;
            Flag=true;
        }
    return Flag;
}
void Falldown(int i[6][8]) //下落。
{
    for (int a=1;a<=5;a++) //直接类似于重建图，进行填补。
    {
        int t(0);
        for (int b=1;b<=7;b++)
        {
            int T=i[a][b];
            i[a][b]=0;
            if (T)
              i[a][++t]=T;
        }
    }
}
bool Check(int i[6][8]) //检验。
{
    for (int a=1;a<=5;a++)
      for (int b=1;b<=7;b++)
        if (i[a][b])
        return false;
    return true;
}
void DFS(int T,int i[6][8]) //深搜。
{
    if (T>n) //步数超过限制。
    {
        if (Check(i))
        {
            for (int a=1;a<=n;a++)
              if (Ans[a][2]) //判断左移右移。
                printf("%d %d -1\n",Ans[a][0],Ans[a][1]-1);
              else
                printf("%d %d 1\n",Ans[a][0]-1,Ans[a][1]-1);
            exit(0);
        }
        return;
    }
    memset(Num,0,sizeof(Num)); //存储某种颜色格子现存数。
    for (int a=1;a<=5;a++)
      for (int b=1;b<=7;b++)
        if (i[a][b])
          Num[i[a][b]]++;
    for (int a=1;a<=10;a++)
      if (Num[a]==1||Num[a]==2) //注意，当等于0时并不需要返回。
        return;
    int f[6][8]={0}; //小白鼠数组。
    for (int a=1;a<5;a++)
      for (int b=1;b<=7;b++)
        if (i[a][b]!=i[a+1][b]) //颜色不一样，交换才有价值，注意是比较的左列，但依然能实现左右移动。
        {
            memcpy(f,i,sizeof(f));
            Ans[T][0]=a;
            Ans[T][1]=b;
            Ans[T][2]=!i[a][b]; //若为空，即是true，若为有，即是false。
            swap(f[a][b],f[a+1][b]); //交换。
            Falldown(f);
            while (Remove(f)) //不断消除。
              Falldown(f);
            DFS(T+1,f);
        }
}
int main() //赤裸裸的深搜，考验编程能力。
{
    scanf("%d",&n);
    for (int a=1;a<=5;a++)
      for (int b=1;;b++)
      {
        scanf("%d",&i[a][b]); //注意i代表第几列，j代表第几行。
        if (!i[a][b]) //存储颜色。
          break;
      }
    DFS(1,i);
    printf("-1");
    return 0;
}

