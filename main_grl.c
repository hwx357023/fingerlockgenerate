#include <stdio.h>
#include <time.h>
#include <math.h>

#define MAX 4

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
	int i, j, n =0,m=0; 
	int xf,yf;

	for(i=0;i<MAX;i++)
	{
		for(j=0;j<MAX;j++)
		{
			if(x == i && y== j) continue;
			if(pros[i][j].chosed) continue;

			if(abs(x-i)==abs(y-j) || x==i || y==j)
			{
				if(i>x) xf = 1;
				else if(i==x) xf = 0;
				else xf = -1;
				if(j>y) yf = 1;
				else if(j==y) yf = 0;
				else yf = -1;

				n=0;
				f=0;
				while(1)
				{
					n++;
					if(i>x && n+x>=i) break;
					else if(i<x && x-n<=i) break;
					if(j>y && n+y>=j) break;
					else if(j<y && y-n <=j) break;

					if(!pros[x+xf*n][y+yf*n].chosed)
					{
						f=1;
						break;
					}
				}
				if(f==1) continue;

			}
			else
			{
				int dx,dy,smallx,smally,bigx,bigy,dx2,dy2;
				int t;
				double d,d2;
				
				dx = i-x;
				dy = j-y;

				if(i>x)
				{
					smallx=x;
					bigx=i;
				}
				else
				{
					smallx=i;
					bigx=x;
				}
				if(j>y)
				{
					smally=y;
					bigy=j;
				}
				else
				{
					smally=j;
					bigy=y;
				}

				f=0;
				for(m=smallx;m<=bigx;m++)
				{
					for(n=smally;n<=bigy;n++)
					{
						if(m==x && n==y || m==i && n==j) continue;
						dx2 = m-x;
						dy2 = n-y;

						t = dx*dx2 + dy*dy2;
						t=t*t;
						d = sqrt((dx*dx+dy*dy)*(dx2*dx2+dy2*dy2)-t);
						d2 = sqrt(dx*dx+dy*dy);
						if(d/d2<0.7071 && !pros[m][n].chosed)
						{
							f=1;
							break;
						}
					}
					if(f==1) break;
				}
				
				
				if(f==1) continue;

			}

			pros[i][j].possible = 1;
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

