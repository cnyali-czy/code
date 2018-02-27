#include <stdio.h>
#include <limits.h>
#include <assert.h>
#define VTXSIZE 900
#define EDGESIZE 40000
int vtx_num;
int map[VTXSIZE+1][VTXSIZE+1];
int sign[VTXSIZE+1][2]; /* 0 red, 1 green */
int road_num;
int dis[VTXSIZE+1];
int used[VTXSIZE+1];
int from[VTXSIZE+1];

void 
clean_var (void)
{
	int i, j;
	for (i=0;i<VTXSIZE;i++)
	{
		dis[i] = INT_MAX;
		used[i] = 0;
		for (j=0;j<VTXSIZE;j++)
			map[i][j] = INT_MAX;
	}
	dis[0] = 0;
}

int 
read_data (void)
{
	int i, x, y, t;

	scanf ("%d", &vtx_num);
	if (vtx_num==0) return 0;
	assert(vtx_num<VTXSIZE);

	clean_var ();

	for (i=0;i<vtx_num;i++)
		scanf ("%d%d", &sign[i][0], &sign[i][1]);
	sign[vtx_num][0] = 0; sign[vtx_num][1] = INT_MAX;
	scanf ("%d", &road_num);
	for (i=0;i<road_num;i++)
	{
		scanf ("%d%d%d", &x, &y, &t);
		map[x][y] = map[y][x] = t;
	}

	return 1;
}

void
debug (void)
{
	int i;
	for (i=0;i<=vtx_num;i++)
		printf ("%10d ", dis[i]);
	printf ("\n");
}

int
main (void)
{
     freopen("d.in", "r", stdin);
     freopen("d.out", "w", stdout);
	//while (read_data())
	read_data();
	{
		int i, j, idx, min;
		for (i=0;i<=vtx_num;i++)
		{
			min = INT_MAX;
			for (j=0;j<=vtx_num;j++)
				if (min>dis[j]&&used[j]==0)
				{
					min = dis[j];
					idx = j;
				}
			used[idx] = 1;
			for (j=0;j<=vtx_num;j++)
				if (map[idx][j]!=INT_MAX )
				{ 
					int remain = (dis[idx]+map[idx][j])%(sign[j][0]+sign[j][1]);
					if ( remain >= sign[j][1] )
						remain = sign[j][0]+sign[j][1]-remain;
					else
						remain = 0;	
					if ( dis[j]>dis[idx]+map[idx][j]+remain )
					{
						dis[j] = dis[idx]+map[idx][j]+remain;
						from[j] = idx;
					}
				}
		}
		printf ("%d\n", dis[vtx_num]);
	}
	return 0;
}

