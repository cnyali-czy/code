#include<bits/stdc++.h>
const int N = 100000 + 10;
using namespace std;
inline int read(){
    int x = 0, f = 1;char ch = getchar();
    while(ch < '0' || ch>'9'){if(ch == '-') f = -1;ch = getchar();}
    while(ch >= '0' && ch <= '9'){ x = x * 10 + ch - '0';ch = getchar();}
    return x * f;
}
struct node{
    int l,r,num,w,size,re;
}a[N];
int asize,root,n,m,ans,tot;
int heal[N];
void update(int v){
    a[v].size = a[a[v].l].size + a[a[v].r].size + a[v].re;
}
void right_rotate(int &u){
    int t = a[u].l;
    a[u].l = a[t].r;
    a[t].r = u;
    a[t].size = a[u].size;
    update(u);
    u = t;
}
 
void left_rotate(int &u){
    int t = a[u].r;
    a[u].r = a[t].l;
    a[t].l = u;
    a[t].size = a[u].size;
    update(u);
    u = t;
}
 
int insert(int &v,int x){
     
    if (v == 0){
        v = ++asize;
        a[v].w = rand();
        a[v].num = x;
        a[v].re = a[v].size = 1;
        return v;
	}
    a[v].size++;
    int save = v;
    if (a[v].num == x) {
        a[v].re++;
        return v;
    }
    if (x < a[v].num){
    	save=insert(a[v].l,x);
        if (a[a[v].l].w < a[v].w) right_rotate(v);
    }
    else{
        save=insert(a[v].r,x);
        if (a[a[v].r].w < a[v].w) left_rotate(v);
    }
    return save;
}
 
void del(int &v, int x){
    if (v == 0) return;
    if (a[v].num == x){
        if (a[v].re > 1){
            a[v].re--;
            a[v].size--;
            return;
        } 
        if (a[v].l*a[v].r == 0)
          v = a[v].l+a[v].r;
        else
        if (a[a[v].l].w < a[a[v].r].w){
            right_rotate(v);
            del(v, x);
        }
        else{
            left_rotate(v);
            del(v, x);
        }
    }
    else
    if (x > a[v].num){
        a[v].size--;
        del(a[v].r, x);
    }
    else{
        a[v].size--;
        del(a[v].l, x);
    }
}

int ask_rank(int v, int x)
{
    if (v == 0) return 0;
    if (a[v].num == x) return a[a[v].l].size + 1;
    else
    if (x > a[v].num)
    return a[a[v].l].size + a[v].re + ask_rank(a[v].r, x);
    else
    return ask_rank(a[v].l, x);
}

int ask_num(int v, int x)
{
	if (a[v].size < x)return -1;
    if(v == 0)return 0;
    if(x <= a[a[v].l].size)return ask_num(a[v].l, x);
    else if(x > a[a[v].l].size + a[v].re)return ask_num(a[v].r, x - a[a[v].l].size - a[v].re);
    else return a[v].num;
}

void succ(int v,int x)
{
    if(v == 0)return;
    if(a[v].num < x){ans = a[v].num; succ(a[v].r, x);}
    else succ(a[v].l, x);
}
void pred(int v,int x)
{
   if(v == 0)return;
   if(a[v].num > x){ans = a[v].num; pred(a[v].l, x);}
   else pred(a[v].r, x);
}
int find(int v, int x){
	if(x == a[v].num) return v;
	if(x < a[v].num) return find(a[v].l, x);
	else return find(a[v].r, x);
}
int main()
{
	freopen("invest.in", "r", stdin);
	freopen("invest.out", "w", stdout);
	srand(2333);
	n = read();tot = n;
	for(int i = 1; i <= n;i++){
	  	int x = read();
	  	heal[i] = insert(root, x);
	}
	char s[110];
	while(cin.getline(s, 100)){
		if(s[0] == 'E') break;
	 	if(s[0] == 'R'){
	 		int last;
		    //printf("%d %d\n", ask_num(root, tot), ask_num(root, tot - 1))
		    int tmp = ask_num(root, tot);
		    int lala = find(root, tmp);
		    for(int i = 1; i <= n; i++) 
				if(heal[i] == lala){
		    		printf("%d ", i);
		    		last = i;
		    		break;
				}
		    tmp = ask_num(root, tot - 1);
		    lala = find(root, tmp);
		    for(int i = 1; i <= n; i++)
		    	if(heal[i] == lala && i != last){
		    		printf("%d\n", i);
		    		break;
				}
		}
	 	if(s[0] >= '0' && s[0] <= '9'){
	 		int x = 0, y = 0;
	 		int pd = 0;
			for(int i = 0; i < strlen(s); i++){
				if(s[i] == ' '){
					pd = 1;
					continue;
				}
				if(!pd) x = x * 10 + s[i] - '0';
				else y = y * 10 + s[i] - '0'; 
			}
	 		int fx = heal[x], d = a[fx].num;
	 		del(root, d);
	 		heal[x] = insert(root,y);
	 	}
	}
	return 0;
}
