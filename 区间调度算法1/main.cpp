/******************************************************************************
 *\file main.cpp
 *\detail 区间调度算法：最大任务数
 *\date 2017/03/01
******************************************************************************/
#include <stdio.h>

struct pair{
	
	unsigned int	uint_s;	///< 起始时间
	unsigned int	uint_e;	///< 结束时间
};

struct pair  pairs[20];
unsigned int len;

void get_input_args(void)
{
	unsigned int s = 0, e = 0, i = 0;
	
	while (2 == scanf("%u,%u", &s, &e))
	{
		printf("%u - %u\n", s, e);
		pairs[i].uint_e = e;
		pairs[i].uint_s = s;
		++i;
	}
	
	len = i;
}

void sort_by_etime(void)
{
	unsigned int i = 0, j = 0;
	
	for (; i < len; ++i)
	{
		for (j = i; j < len; ++j)
		{
			if (pairs[i].uint_e > pairs[j].uint_e)
			{
				unsigned int tmp = pairs[j].uint_e;
				pairs[j].uint_e = pairs[i].uint_e;
				pairs[i].uint_e = tmp;
				
				
				tmp = pairs[j].uint_s;
				pairs[j].uint_s = pairs[i].uint_s;
				pairs[i].uint_s = tmp;
			}
		}
	}
}

void print_pairs(void)
{
	unsigned int i = 0;
	
	for (i = 0; i < len; ++i)
	{
		printf("(%02u): %u - %u\n", i, pairs[i].uint_s, pairs[i].uint_e);
	}
}

void select_pairs(void)
{
	unsigned int i = 0; 
	
	printf("result:");
	len?printf("(%02u): %u - %u\n", 0, pairs[0].uint_s, pairs[0].uint_e):printf("nil\n");
	for (i = 0; i < len-1; ++i)
	{
		if (pairs[i].uint_e < pairs[i+1].uint_s)
		{
			printf("(%02u): %u - %u\n", i+1, pairs[i+1].uint_s, pairs[i+1].uint_e);
		}
	}
}

int main(void)
{
	get_input_args();
	
	sort_by_etime();
	
	print_pairs();
	
	select_pairs();
	
	return 0;
}