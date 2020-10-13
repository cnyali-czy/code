#include "mythological.h"
#define rep(i,a,b) for(i=(a);i<=(b);i++)
#include <stdio.h>
#include <stdlib.h>

const int maxn=100005;

int v[100005],i;

void init(int n, int m, int a[], int t){
	rep(i,1,n)v[i]=a[i];
}

int query(int l, int r){
	return r-l+1;
}
