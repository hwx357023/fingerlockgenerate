#include <stdio.h>
#include <time.h>

#define MAX 3

struct properties{
	int chosed;
	int possible;
};

struct properties pros[MAX][MAX];

int abs(int n)
{
	if(n>=0) return n;
	else return -1*n;
}

int get_possible(int x, int y)
{
	int f = 0;
	int i, j, n =0;

	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(x == i && y== j) continue;
			if(pros[i][j].chosed) continue;

			if(abs(x-i) == 2 || abs(y-j)==2)
			{
				if(abs(x-i)==2 && (abs(y-j) == 0 || abs(y-j)==2) || 
				   abs(y-j)==2 && (abs(x-i)==0   || abs(x-i) ==2))
				{
					if(!pros[(x+i)/2][(y+j)/2].chosed)
					{
						continue;
					}
				}
				else
				{
					if(abs(x-i)==2)
					{
						if(!pros[(x+i)/2][y].chosed || !pros[(x+i)/2][j].chosed)
							continue;
					}
					else
					{
						if(!pros[x][(y+j)/2].chosed || !pros[i][(y+j)/2].chosed)
							continue;
					}
				}
			}
			if(!pros[i][j].chosed)
			{
				pros[i][j].possible = 1;
			}
		}
	}

	return 0;
}

void reset_possible()
{
	int i,j;

	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			pros[i][j].possible = 0;
		}
	}
}

void chose(int r, int* px, int *py)
{
	int n = 0,i,j;
	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			if(pros[i][j].possible)
			{
				if(r == n)
				{
					pros[i][j].chosed = 1;
					reset_possible();
					*px = i;
					*py = j;
					return;
				}
				n++;
			}
			
		}
	}
}

int get_possible_num()
{
	int i,j,num=0;

	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			if(!pros[i][j].chosed && pros[i][j].possible) num++;
		}
	}
	return num;
}

int main()
{
	time_t t;
	long int r;
	int i,j,poss_num,x,y,f;

	t = time(NULL);

	srandom(t);

	for(i=0; i<MAX; i++)
	{
		for(j=0; j<MAX; j++)
		{
			pros[i][j].chosed = 0;
			pros[i][j].possible = 1;
		}
	}
	r = random()%(MAX*MAX);
	chose(r,&x,&y);

	printf("%u%u ",x,y);

	for(i=0;i<(MAX*MAX);i++)
	{
		f = get_possible(x,y);

		poss_num = get_possible_num();
		if(poss_num == 0) break;
		r = random()%poss_num;

		chose(r,&x,&y);
		printf("%u%u ",x,y);
		
	}

	printf("\n");
}

